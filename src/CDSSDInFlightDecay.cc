#include "CDSSDInFlightDecay.hh"

#include "Classe_formule.h"
#include "globals.hh"

using namespace std;


CDSSDInFlightDecay::CDSSDInFlightDecay(std::string filename):
    decay_scheme_file_name(filename){
    
    qgs=0;
    
    //parent
    estarparent=0; zparent=0; aparent=0; 
    vlab_parent.setX(0); vlab_parent.setY(0); vlab_parent.setZ(0);
    
    //daugther
    estardaughter=0; zdaughter=0; adaughter=0; 
    vdaughter.setX(0); vdaughter.setY(0); vdaughter.setZ(0);
    vlab_daughter.setX(0); vlab_daughter.setY(0); vlab_daughter.setZ(0);
     
    //emitted
    zemitted=0; aemitted=0; 
    vemitted.setX(0);  vemitted.setY(0);  vemitted.setZ(0);
    vlab_emitted.setX(0);  vlab_emitted.setY(0);  vlab_emitted.setZ(0);

    mass_defect = Classe_formule::load_mass_defect();
    decay_scheme = GetDecayScheme();
}

    
CDSSDInFlightDecay::~CDSSDInFlightDecay() {
  
}

void CDSSDInFlightDecay::InitADecay(int idec, G4ThreeVector vlab){
    
    G4IonTable* ionTable = G4IonTable::GetIonTable();
    
    zparent = get<0>(decay_scheme[idec]);
    aparent = get<1>(decay_scheme[idec]);
    estarparent = get<2>(decay_scheme[idec]);
    
    zdaughter = get<3>(decay_scheme[idec]);
    adaughter = get<4>(decay_scheme[idec]);
    estardaughter = get<5>(decay_scheme[idec]);
    
    zemitted = zparent - zdaughter;
    aemitted = aparent - adaughter;
    if(zemitted==2 && aemitted==4) SetEmittedDef((G4Ions*)ionTable->GetIon(zemitted,aemitted,0)); //spin
    
    SetParentLabVelocity(vlab);
}

void CDSSDInFlightDecay::ComputeADecay(){
    
    G4IonTable* ionTable = G4IonTable::GetIonTable();
    
    qgs = (mass_defect[aparent*100+zparent] - mass_defect[adaughter*100+zdaughter] - mass_defect[aemitted*100+zemitted])/1000.; //MeV
    
    double qval = qgs + estarparent - estardaughter + GetCoulombRepulsion();
    double mu = aemitted*adaughter/(aemitted+adaughter);
    double vrel  =  sqrt(2*qval/mu/Classe_formule::amu)*Classe_formule::cluce; //mm/ns
    
    double vvemitted = vrel*adaughter/(adaughter+aemitted); 
    double vvdaughter= vrel*aemitted/(adaughter+aemitted);
    
    double thetaemitted = G4UniformRand() * M_PI;
    double phiemitted = G4UniformRand() * 2*M_PI;
    double thetadaughter = M_PI-thetaemitted;
    double phidaughter=0;
    if(phiemitted<M_PI) phidaughter=M_PI+phiemitted;
    else phidaughter = phiemitted-M_PI;
    
//     G4cout << vvemitted << " " << vvdaughter << G4endl;
//     G4cout << thetaemitted << " " << phiemitted << " " << thetadaughter << " " << phidaughter << G4endl;
    
    vemitted.setX(vvemitted*cos(phiemitted)*sin(thetaemitted));
    vemitted.setY(vvemitted*sin(phiemitted)*sin(thetaemitted));
    vemitted.setZ(vvemitted*cos(thetaemitted));
    
    vdaughter.setX(vvdaughter*cos(phidaughter)*sin(thetadaughter));
    vdaughter.setY(vvdaughter*sin(phidaughter)*sin(thetadaughter));
    vdaughter.setZ(vvdaughter*cos(thetadaughter));
        
    if(zemitted==2 && aemitted==4) SetEmittedDef((G4Ions*)ionTable->GetIon(zemitted,aemitted,0)); //Z, A, spin
    if(zdaughter==2 && adaughter==4) SetDaughterDef((G4Ions*)ionTable->GetIon(zdaughter,adaughter,0)); //Z, A, spin
    
}


void CDSSDInFlightDecay::FromCMToLab(){
    
    vlab_emitted = vemitted + vlab_parent;
    vlab_daughter = vdaughter + vlab_parent;
    
}


void CDSSDInFlightDecay::PrintADecay(){
    
    G4cout << "++++++++++++++++++++++" << G4endl;
    
    G4cout << "Qgs [MeV]: " << qgs << G4endl;
    
    G4cout << "---\n" << G4endl;
    
    G4cout << "Parent [Z, A, E*]: " << zparent << " " << aparent << " " << estarparent << G4endl;
    G4cout << "Vlab [x, y, z] mm/ns: " << vlab_parent.getX() << " " << vlab_parent.getY() << " " << vlab_parent.getZ() << G4endl;
    G4cout << "---\n" << G4endl;
    
       
    G4cout << "Emitted [Z, A, E*]: " << zemitted << " " << aemitted << " " << 0 << G4endl;
    G4cout << "V [x, y, z] mm/ns: " << vemitted.getX() << " " << vemitted.getY() << " " << vemitted.getZ() << G4endl;
    G4cout << "VLab [x, y, z] mm/ns: " << vlab_emitted.getX() << " " << vlab_emitted.getY() << " " << vlab_emitted.getZ() << G4endl;
    G4cout << "EkibLab MeV: " << GetEmittedLabEkin() << G4endl;
    G4cout << "---\n" << G4endl;
    
    G4cout << "Daughter [Z, A, E*]: " << zdaughter << " " << adaughter << " " << estardaughter << G4endl;
    G4cout << "V [x, y, z] mm/ns: " << vdaughter.getX() << " " << vdaughter.getY() << " " << vdaughter.getZ() << G4endl;
    G4cout << "VLab [x, y, z] mm/ns: " << vlab_daughter.getX() << " " << vlab_daughter.getY() << " " << vlab_daughter.getZ() << G4endl;
    G4cout << "EkibLab MeV: " << GetDaughterLabEkin() << G4endl;
    G4cout << "---\n" << G4endl;
    
    G4cout << "EcoulRepulsion: " << GetCoulombRepulsion() << G4endl; 
    
    G4cout << "++++++++++++++++++++++" << G4endl;
    
    
}

double CDSSDInFlightDecay::GetCoulombRepulsion(){

  double r12 = Classe_formule::r0*(pow(adaughter,1/3.)+pow(aemitted,1/3.)); //f
  double k = 1.44; //MeV fm  - e**2/4piepsi0
  double ecoul = k*zemitted*zdaughter/r12;
  
  return ecoul;
  
  
}


std::map<int, std::tuple<double, double, double, double, double, double, std::string> >CDSSDInFlightDecay::GetDecayScheme(){
 
    //zi, ai, ei, - zf, af, ef - particle_type
    
    std::ifstream in (GetDecaySchemeFileName(), std::ifstream::in);
    std::string line;
    int ndecay=0;
      
      if(!in.good()){
       G4cout << "Decay Scheme File not good: " << GetDecaySchemeFileName() << G4endl;   
      }
            
      std::map<int, std::tuple<double, double, double, double, double, double, std::string> > map;
      
      while (getline(in,line)){
        if(line[0]=='#') continue;
        
        std::stringstream ss;
        ss.str(line);
        
        double ai, af, zi, zf;
        double ei, ef;
        std::string particle;
        ss >> zi >> ai >> ei >> zf >> af >> ef >> particle;
        
        
        std::tuple <double, double, double, double, double, double, std::string> temp;
        temp = make_tuple(zi, ai, ei, zf, af, ef, particle);
        map.emplace(ndecay, temp);
        ndecay++;
      }
      
      in.close();
      
      return map;    
}
