


void show_output(int ientry=0){

  TFile *f = new TFile("CDSSD_t0.root");
  TTree *t = (TTree*)f->Get("CDSSDevents");


  TTreeReader r(t);
  TTreeReaderValue<vector<int> > EventID(r,"EventID");
  TTreeReaderValue<vector<int> > TrackID(r,"TrackID");
  TTreeReaderValue<vector<int> > ParentID(r,"ParentID");
  TTreeReaderValue<vector<int> > ParticleID(r,"ParticleID");
  TTreeReaderValue<vector<int> > DetID(r,"DetID");
  TTreeReaderValue<vector<int> > ISec(r,"ISec");
  TTreeReaderValue<vector<int> > IRadius(r,"IRadius");
  TTreeReaderValue<vector<int> > IAzimuth(r,"IAzimuth");
  TTreeReaderValue<vector<double> > Zpart(r,"Zpart");
  TTreeReaderValue<vector<double> > Apart(r,"Apart");
  TTreeReaderValue<vector<double> > Xin(r,"Xin");
  TTreeReaderValue<vector<double> > Yin(r,"Yin");
  TTreeReaderValue<vector<double> > Zin(r,"Zin");
  TTreeReaderValue<vector<double> > Edep(r,"Edep");
  

  r.SetEntry(ientry);

  cout << "EviD: " << EventID->at(0) << endl;
  int nparts=TrackID->size();
  for(int i=0; i<nparts; i++){
    cout << "TrackID: " << TrackID->at(i) << endl;
    cout << "ParentID: " << ParentID->at(i) << endl;
    cout << " \n";
    cout << "DetID: " << DetID->at(i) << endl;
    cout << "ParticleID: " << ParticleID->at(i) << endl;
    cout << " \n";
    cout << "Zpart: " << Zpart->at(i) << endl;
    cout << "Apart: " << Apart->at(i) << endl;
    cout << "InXYZ [cm]: " << Xin->at(i) << " " << Yin->at(i) << " " << Zin->at(i) << endl;
    if(DetID->at(i)>=100000)  cout << "Si2 ISEC: " << ISec->at(i) << endl;
    else cout << "Si 1 ISEC - IRADIUS - IAZIMUTH: " << ISec->at(i) <<  " " << IRadius->at(i) << " " << IAzimuth->at(i) << endl;
    cout << "Edep [MeV]: " <<  Edep->at(i) << endl;
  }
}
