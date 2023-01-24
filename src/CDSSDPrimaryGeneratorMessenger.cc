//////////////////////////////////////////////////////////////////
/// \class CDSSDPrimaryGeneratorMessenger
/// Messenger for the primary event generator.
/////////////////////////////////////////////////////////////////

#include "CDSSDPrimaryGeneratorMessenger.hh"
#include "CDSSDPrimaryGeneratorAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4Ions.hh"
#include "G4ios.hh"
#include "G4Tokenizer.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//////////////////////////////////////////////////////////////////
/// Constructor
/// command included in this CDSSDPrimaryGeneratorMessenger:
/// - /CDSSD/gun/List
/// - /CDSSD/gun/particle
/// - /CDSSD/gun/randomTheta
/// - /CDSSD/gun/randomThetaVal
/// - /CDSSD/gun/randomPhiVal
/// - /CDSSD/gun/Kine/incidentIon
/// - /CDSSD/gun/Kine/targetIon
/// - /CDSSD/gun/Kine/scatteredIon
/// - /CDSSD/gun/Kine/recoilIon
/// - /CDSSD/gun/Kine/userThetaCM
/// - /CDSSD/gun/Kine/userPhiAngle

CDSSDPrimaryGeneratorMessenger::CDSSDPrimaryGeneratorMessenger(CDSSDPrimaryGeneratorAction* CDSSDGun)
  : CDSSDActionGun(CDSSDGun) {

  particleTable = G4ParticleTable::GetParticleTable();
  ionTable = G4IonTable::GetIonTable();

  G4cout << "here " << G4endl;

  G4bool omitable;
  G4UIparameter* parameter;

  gunDir = new G4UIdirectory("/CDSSD/gun/");
  gunDir->SetGuidance("PrimaryGenerator control");

  listCmd = new G4UIcmdWithoutParameter("/CDSSD/gun/List",this);
  listCmd->SetGuidance("List available particles.");
  listCmd->SetGuidance(" Invoke G4ParticleTable.");

  particleCmd = new G4UIcmdWithAString("/CDSSD/gun/particle",this);
  particleCmd->SetGuidance("Select the incident particle.");
  particleCmd->SetGuidance(" (proton is default)");
  particleCmd->SetGuidance(" (ion can be specified for shooting ions)");
  particleCmd->SetParameterName("particle",false);
  particleCmd->SetDefaultValue("proton");
  G4String candidateList;
  G4int nPtcl = particleTable->entries();
  for(G4int i=0;i<nPtcl;i++) {
    if(!(particleTable->GetParticle(i)->IsShortLived())) {
      candidateList += particleTable->GetParticleName(i);
      candidateList += " ";
    }
  }
  candidateList += "ion ";
  particleCmd->SetCandidates(candidateList);


  randomThetaCmd = new G4UIcmdWithAString("/CDSSD/gun/randomTheta",this);
  randomThetaCmd->SetGuidance("Randomize the thetaCM angle of the scattered ion");
  randomThetaCmd->SetGuidance("Choice : on, off(default");
  randomThetaCmd->SetParameterName("choice",true);
  randomThetaCmd->SetDefaultValue("off");
  randomThetaCmd->SetCandidates("on off");
  randomThetaCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  randomThetaValCmd = new G4UIcommand("/CDSSD/gun/randomThetaVal", this);
  randomThetaValCmd->SetGuidance("Sets the limits in the Theta angle for the scattered particle.");
  randomThetaValCmd->SetGuidance("The value is randomly chosen between the limits.");
  parameter = new G4UIparameter("thetaMin", 'd', omitable = true);
  parameter->SetDefaultValue(0.);
  randomThetaValCmd->SetParameter(parameter);
  parameter = new G4UIparameter("thetaMax", 'd', omitable = true);
  parameter->SetDefaultValue(180.);
  randomThetaValCmd->SetParameter(parameter);
  parameter = new G4UIparameter("unit", 's', omitable = true);
  parameter->SetDefaultValue("deg");
  randomThetaValCmd->SetParameter(parameter);

  randomPhiValCmd = new G4UIcommand("/CDSSD/gun/randomPhiVal", this);
  randomPhiValCmd->SetGuidance("Sets the limits in the Phi angle for the scattered particle.");
  randomPhiValCmd->SetGuidance("The value is randomly chosen between the limits.");
  parameter = new G4UIparameter("phiMin", 'd', omitable = true);
  parameter->SetDefaultValue(0.);
  randomPhiValCmd->SetParameter(parameter);
  parameter = new G4UIparameter("phiMax", 'd', omitable = true);
  parameter->SetDefaultValue(180.);
  randomPhiValCmd->SetParameter(parameter);
  parameter = new G4UIparameter("unit", 's', omitable = true);
  parameter->SetDefaultValue("deg");
  randomPhiValCmd->SetParameter(parameter);

  labEnergyCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/gun/labEnergy",this);
  labEnergyCmd->SetGuidance("Sets the laboratory energy.");
  labEnergyCmd->SetParameterName("labEnergy",false);
  labEnergyCmd->SetRange("labEnergy>=0.");
  labEnergyCmd->SetUnitCategory("Energy");
  labEnergyCmd->SetDefaultValue(100.);
  labEnergyCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  thetaLabAngleCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/gun/thetaLabAngle",this);
  thetaLabAngleCmd->SetGuidance("Sets the theta lab angle of the scattered particle");
  thetaLabAngleCmd->SetParameterName("thetaLabAngle",false);
  thetaLabAngleCmd->SetRange("thetaLabAngle>=0.");
  thetaLabAngleCmd->SetUnitCategory("Angle");
  thetaLabAngleCmd->SetDefaultValue(45.);
  thetaLabAngleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  //commands affecting the Kine kinematic reaction generator
  KineDir = new G4UIdirectory("/CDSSD/gun/Kine/");
  KineDir->SetGuidance("Kine generator control");

  KineIncidentIonCmd = new G4UIcommand("/CDSSD/gun/Kine/incidentIon",this);
  KineIncidentIonCmd->SetGuidance("Set properties of incident ion to be generated.");
  KineIncidentIonCmd->SetGuidance("[usage] /CDSSD/gun/Kine/incidentIon Z A Q E Mass");
  KineIncidentIonCmd->SetGuidance("        Z:(int) AtomicNumber");
  KineIncidentIonCmd->SetGuidance("        A:(int) AtomicMass (in Atomic mass unit u)");
  KineIncidentIonCmd->SetGuidance("        Q:(int) Charge of ion (in unit of e)");
  KineIncidentIonCmd->SetGuidance("        E:(double) Excitation energy (in MeV)");
  KineIncidentIonCmd->SetGuidance("     Mass:(double) mass in u");

  G4UIparameter* KineIncidentParam;
  KineIncidentParam = new G4UIparameter("Z",'i',false);
  KineIncidentParam->SetDefaultValue("1");
  KineIncidentIonCmd->SetParameter(KineIncidentParam);
  KineIncidentParam = new G4UIparameter("A",'i',false);
  KineIncidentParam->SetDefaultValue("1");
  KineIncidentIonCmd->SetParameter(KineIncidentParam);
  KineIncidentParam = new G4UIparameter("Q",'i',false);
  KineIncidentParam->SetDefaultValue("0");
  KineIncidentIonCmd->SetParameter(KineIncidentParam);
  KineIncidentParam = new G4UIparameter("E",'d',true);
  KineIncidentParam->SetDefaultValue("0.0");
  KineIncidentIonCmd->SetParameter(KineIncidentParam);
  KineIncidentParam = new G4UIparameter("Mass",'d',true);
  KineIncidentParam->SetDefaultValue("1.0");
  KineIncidentIonCmd->SetParameter(KineIncidentParam);

  KineTargetIonCmd = new G4UIcommand("/CDSSD/gun/Kine/targetIon",this);
  KineTargetIonCmd->SetGuidance("Set properties of target ion to be generated.");
  KineTargetIonCmd->SetGuidance("[usage] /CDSSD/gun/Cine/targetIon Z A Q E Mass");
  KineTargetIonCmd->SetGuidance("        Z:(int) AtomicNumber");
  KineTargetIonCmd->SetGuidance("        A:(int) AtomicMass in (in u)");
  KineTargetIonCmd->SetGuidance("        Q:(int) Charge of ion (in unit of e)");
  KineTargetIonCmd->SetGuidance("        E:(double) Excitation energy (in MeV)");
  KineTargetIonCmd->SetGuidance("     Mass:(double) mass in u");

  G4UIparameter* KineTargetParam;
  KineTargetParam = new G4UIparameter("Z",'i',false);
  KineTargetParam->SetDefaultValue("1");
  KineTargetIonCmd->SetParameter(KineTargetParam);
  KineTargetParam = new G4UIparameter("A",'i',false);
  KineTargetParam->SetDefaultValue("1");
  KineTargetIonCmd->SetParameter(KineTargetParam);
  KineTargetParam = new G4UIparameter("Q",'i',false);
  KineTargetParam->SetDefaultValue("0");
  KineTargetIonCmd->SetParameter(KineTargetParam);
  KineTargetParam = new G4UIparameter("E",'d',true);
  KineTargetParam->SetDefaultValue("0.0");
  KineTargetIonCmd->SetParameter(KineTargetParam);
  KineTargetParam = new G4UIparameter("Mass",'d',true);
  KineTargetParam->SetDefaultValue("1.0");
  KineTargetIonCmd->SetParameter(KineTargetParam);

  KineScatteredIonCmd = new G4UIcommand("/CDSSD/gun/Kine/scatteredIon",this);
  KineScatteredIonCmd->SetGuidance("Set properties of scattered ion to be generated.");
  KineScatteredIonCmd->SetGuidance("[usage] /CDSSD/gun/Cine/scatteredIon Z A Q E Mass");
  KineScatteredIonCmd->SetGuidance("        Z:(int) AtomicNumber");
  KineScatteredIonCmd->SetGuidance("        A:(int) AtomicMass");
  KineScatteredIonCmd->SetGuidance("        Q:(int) Charge of ion (in unit of e)");
  KineScatteredIonCmd->SetGuidance("        E:(double) Excitation energy (in MeV)");
  KineScatteredIonCmd->SetGuidance("     Mass:(double) mass in u");

  G4UIparameter* KineScatteredParam;
  KineScatteredParam = new G4UIparameter("Z",'i',false);
  KineScatteredParam->SetDefaultValue("1");
  KineScatteredIonCmd->SetParameter(KineScatteredParam);
  KineScatteredParam = new G4UIparameter("A",'i',false);
  KineScatteredParam->SetDefaultValue("1");
  KineScatteredIonCmd->SetParameter(KineScatteredParam);
  KineScatteredParam = new G4UIparameter("Q",'i',false);
  KineScatteredParam->SetDefaultValue("0");
  KineScatteredIonCmd->SetParameter(KineScatteredParam);
  KineScatteredParam = new G4UIparameter("E",'d',true);
  KineScatteredParam->SetDefaultValue("0.0");
  KineScatteredIonCmd->SetParameter(KineScatteredParam);
  KineScatteredParam = new G4UIparameter("Mass",'d',true);
  KineScatteredParam->SetDefaultValue("1.0");
  KineScatteredIonCmd->SetParameter(KineScatteredParam);

  KineRecoilIonCmd = new G4UIcommand("/CDSSD/gun/Kine/recoiledIon",this);
  KineRecoilIonCmd->SetGuidance("Set properties of recoil ion to be generated.");
  KineRecoilIonCmd->SetGuidance("[usage] /CDSSD/gun/Cine/recoilIon Z A Q E Mass");
  KineRecoilIonCmd->SetGuidance("        Z:(int) AtomicNumber");
  KineRecoilIonCmd->SetGuidance("        A:(int) AtomicMass");
  KineRecoilIonCmd->SetGuidance("        Q:(int) Charge of ion (in unit of e)");
  KineRecoilIonCmd->SetGuidance("        E:(double) Excitation energy (in MeV)");
  KineRecoilIonCmd->SetGuidance("     Mass:(double) mass in u");

  G4UIparameter* KineRecoilParam;
  KineRecoilParam = new G4UIparameter("Z",'i',false);
  KineRecoilParam->SetDefaultValue("1");
  KineRecoilIonCmd->SetParameter(KineRecoilParam);
  KineRecoilParam = new G4UIparameter("A",'i',false);
  KineRecoilParam->SetDefaultValue("1.");
  KineRecoilIonCmd->SetParameter(KineRecoilParam);
  KineRecoilParam = new G4UIparameter("Q",'i',false);
  KineRecoilParam->SetDefaultValue("0");
  KineRecoilIonCmd->SetParameter(KineRecoilParam);
  KineRecoilParam = new G4UIparameter("E",'d',true);
  KineRecoilParam->SetDefaultValue("0.0");
  KineRecoilIonCmd->SetParameter(KineRecoilParam);
  KineRecoilParam = new G4UIparameter("Mass",'d',true);
  KineRecoilParam->SetDefaultValue("1.0");
  KineRecoilIonCmd->SetParameter(KineRecoilParam);

  KineLabEnergyCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/gun/Kine/labEnergy",this);
  KineLabEnergyCmd->SetGuidance("Sets the laboratory energy.");
  KineLabEnergyCmd->SetParameterName("labEnergy",false);
  KineLabEnergyCmd->SetRange("labEnergy>=0.");
  KineLabEnergyCmd->SetUnitCategory("Energy");
  KineLabEnergyCmd->SetDefaultValue(100.);
  KineLabEnergyCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  
  KineUserThetaCMCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/gun/Kine/userThetaCM",this);
  KineUserThetaCMCmd->SetGuidance("Sets theta CM angle for scattered particle (in degrees)");
  KineUserThetaCMCmd->SetParameterName("userThetaCM",false);
  KineUserThetaCMCmd->SetRange("userThetaCM>=0.");
  KineUserThetaCMCmd->SetUnitCategory("Angle");
  KineUserThetaCMCmd->SetDefaultValue(45.);
  KineUserThetaCMCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  reactionQCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/gun/Kine/reactionQ",this);
  reactionQCmd->SetGuidance("Sets the reaction Q ");
  reactionQCmd->SetParameterName("reactionQ",false);
  reactionQCmd->SetUnitCategory("Energy");
  reactionQCmd->SetDefaultValue(0.);
  reactionQCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//////////////////////////////////////////////////////////////////
/// Destructor
CDSSDPrimaryGeneratorMessenger::~CDSSDPrimaryGeneratorMessenger() {

  delete gunDir;
  delete listCmd;
  delete particleCmd;

  delete randomThetaCmd;
  delete randomThetaValCmd;
  delete randomPhiValCmd;
  
  delete labEnergyCmd;
  delete thetaLabAngleCmd;
  
  delete KineDir;
  delete KineIncidentIonCmd;
  delete KineTargetIonCmd;
  delete KineScatteredIonCmd;
  delete KineRecoilIonCmd;
  delete KineLabEnergyCmd;           // in MeV
  delete reactionQCmd;
  delete KineUserThetaCMCmd;         // in degrees
  delete KineUserPhiAngleCmd;        // in degrees
  
}

//////////////////////////////////////////////////////////////////
/// Setting the values using the interface
void CDSSDPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command,
						    G4String newValues) {
  if( command==listCmd )
    particleTable->DumpTable();

  if( command == particleCmd ) {
    if (newValues =="ion") {
      fShootIon = true;
    } else {
      fShootIon = false;
      G4ParticleDefinition* pd = particleTable->FindParticle(newValues);
      if(pd != 0)
	{ CDSSDActionGun->SetParticleDefinition( pd ); }
    }
  }

  if( command == randomThetaCmd ){
    CDSSDActionGun->SetRandomTheta(newValues);
  }

  if( command == randomThetaValCmd ){
    G4double thetaMax, thetaMin;
    //    ConvertToDoublePair(newValues, thetaMin, thetaMax);

    G4double x, y;
    char unts[30];
    std::istringstream is(newValues);
    is >> x >> y >> unts;
    G4String unt = unts;

    thetaMin = x*G4UIcommand::ValueOf(unt);
    thetaMax = y*G4UIcommand::ValueOf(unt);

    CDSSDActionGun->SetRandomThetaVal(thetaMin,thetaMax);
  }

  if( command == randomPhiValCmd ){
    G4double phiMax, phiMin;
    //    ConvertToDoublePair(newValues, thetaMin, thetaMax);

    G4double x, y;
    char unts[30];
    std::istringstream is(newValues);
    is >> x >> y >> unts;
    G4String unt = unts;

    phiMin = x*G4UIcommand::ValueOf(unt);
    phiMax = y*G4UIcommand::ValueOf(unt);

    CDSSDActionGun->SetRandomPhiVal(phiMin,phiMax);
  }

  if( command == KineIncidentIonCmd )
    KineIncidentIonCommand(newValues);

  if( command == KineTargetIonCmd )
    KineTargetIonCommand(newValues);

  if( command == KineScatteredIonCmd )
    KineScatteredIonCommand(newValues);

  if( command == KineRecoilIonCmd )
    KineRecoilIonCommand(newValues);

  if( command == KineLabEnergyCmd ){
    G4double incidentEnergyTmp;
    incidentEnergyTmp=KineLabEnergyCmd->GetNewDoubleValue(newValues);
    CDSSDActionGun->SetLabEnergy(incidentEnergyTmp);
  }

  if( command == KineUserThetaCMCmd )
    CDSSDActionGun->
      SetThetaCMAngle(KineUserThetaCMCmd->GetNewDoubleValue(newValues));

  if( command == KineUserPhiAngleCmd )
    CDSSDActionGun->      SetPhiCMAngle(KineUserPhiAngleCmd->GetNewDoubleValue(newValues));

  if( command == reactionQCmd )
    CDSSDActionGun->
      SetReactionQ(reactionQCmd->GetNewDoubleValue(newValues));
  
  if( command == labEnergyCmd )
    CDSSDActionGun->SetLabEnergy(labEnergyCmd->GetNewDoubleValue(newValues));

   if( command == thetaLabAngleCmd )
    CDSSDActionGun->SetThetaLabAngle(thetaLabAngleCmd->GetNewDoubleValue(newValues));

}


//////////////////////////////////////////////////////////////////
/// Particular behavior of the (KINE) incident ion command. Ion state should be selected.
void CDSSDPrimaryGeneratorMessenger::KineIncidentIonCommand(G4String newValues){
  G4Tokenizer next( newValues );
  // check argument
  fAtomicNumber = StoI(next());
  fAtomicMass = StoI(next());
  fIonCharge = StoI(next());
  fIonExciteEnergy = StoD(next());
  fIonMass=StoD(next());

  G4Ions* ion;
  ion = (G4Ions*) ionTable->GetIon(fAtomicNumber,
					fAtomicMass,
					fIonExciteEnergy);
  if (ion==0) {
    G4cout << "##################################################################"
	   << G4endl
	   << "####  CDSSDPrimaryGeneratorMessenger::KineIncidentIonCommand() ####"
	   << "Ion with Z=" << fAtomicNumber
	   << " A=" << fAtomicMass << "can not be defined" << G4endl;
    G4cout << "##################################################################"
	   << G4endl;
  } else {
    CDSSDActionGun->SetMassOfProjectile(fIonMass);
    CDSSDActionGun->SetExEnergyOfProjectile(fIonExciteEnergy);
  }
}


//////////////////////////////////////////////////////////////////
/// Particular behavior of the (KINE) target ion command. Ion state should be selected.
void CDSSDPrimaryGeneratorMessenger::KineTargetIonCommand(G4String newValues){
  G4Tokenizer next( newValues );
  // check argument
  fAtomicNumber = StoI(next());
  fAtomicMass = StoI(next());
  fIonCharge = StoI(next());
  fIonExciteEnergy = StoD(next());
  fIonMass=StoD(next());

  G4Ions* ion;
  ion = (G4Ions*) ionTable->GetIon(fAtomicNumber,
					fAtomicMass,
					fIonExciteEnergy);
  if (ion==0) {
    G4cout << "##################################################################"
	   << G4endl
	   << "#####  CDSSDPrimaryGeneratorMessenger::KineTargetIonCommand() ####"
	   << "Ion with Z=" << fAtomicNumber
	   << " A=" << fAtomicMass << "can not be defined" << G4endl;
    G4cout << "##################################################################"
	   << G4endl;
  } else {
    CDSSDActionGun->SetMassOfTarget(fIonMass);
    CDSSDActionGun->SetExEnergyOfTarget(fIonExciteEnergy);
  }
}


//////////////////////////////////////////////////////////////////
/// Particular behavior of the (KINE) scattered ion command. Ion state should be selected.
void CDSSDPrimaryGeneratorMessenger::KineScatteredIonCommand(G4String newValues){
  // Selection of scattered ion command. Ion state should be selected.
  G4Tokenizer next( newValues );
  // check argument
  fAtomicNumber = StoI(next());
  fAtomicMass = StoI(next());
  fIonCharge = StoI(next());
  fIonExciteEnergy = StoD(next());
  fIonMass=StoD(next());

  G4Ions* ion;
  ion = (G4Ions*) ionTable->GetIon(fAtomicNumber,
					fAtomicMass,
					fIonExciteEnergy);
  if (ion==0) {
    G4cout << "##################################################################"
	   << G4endl
	   << "###  CDSSDPrimaryGeneratorMessenger::KineScatteredIonCommand()  ###"
	   << "Ion with Z=" << fAtomicNumber
	   << " A=" << fAtomicMass << "can not be defined" << G4endl;
    G4cout << "##################################################################"
	   << G4endl;
  } else {
    CDSSDActionGun->SetScatteredIon(ion);
    CDSSDActionGun->SetScatteredIonCharge(fIonCharge*eplus);
    CDSSDActionGun->SetMassOfScattered(fIonMass);
    CDSSDActionGun->SetExEnergyOfScattered(fIonExciteEnergy);
    //G4cout << "CDSSDPrimaryGeneratorMessenger::KineScatteredIonCommand(): excitation energy=" << fIonExciteEnergy << G4endl;
  }
}

//////////////////////////////////////////////////////////////////
/// Particular behavior of the (KINE) recoil ion command. Ion state should be selected.
void CDSSDPrimaryGeneratorMessenger::KineRecoilIonCommand(G4String newValues){
  G4Tokenizer next( newValues );
  // check argument
  fAtomicNumber = StoI(next());
  fAtomicMass = StoI(next());
  fIonCharge = StoI(next());
  fIonExciteEnergy = StoD(next());
  fIonMass=StoD(next());

  G4Ions* ion;
  ion =  (G4Ions*) ionTable->GetIon(fAtomicNumber,
					 fAtomicMass,
					 fIonExciteEnergy);
  if (ion==0) {
    G4cout << "##################################################################"
	   << G4endl
	   << "#####  CDSSDPrimaryGeneratorMessenger::KineRecoilIonCommand()  ####"
	   << "Ion with Z=" << fAtomicNumber
	   << " A=" << fAtomicMass << "can not be defined" << G4endl;
    G4cout << "##################################################################"
	   << G4endl;
  } else {
    CDSSDActionGun->SetRecoilIon(ion);
    CDSSDActionGun->SetRecoilIonCharge(fIonCharge*eplus);
    CDSSDActionGun->SetMassOfRecoiled(fIonMass);
    CDSSDActionGun->SetExEnergyOfRecoiled(fIonExciteEnergy);
  }
}
