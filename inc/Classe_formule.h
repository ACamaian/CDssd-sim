#ifndef Classe_formule_h
#define Classe_formule_h 1


#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <math.h>
#include <string>
#include <map>
#include <TMath.h>
//#include <TVector3.h>

class Classe_formule
{
 public:
  static constexpr float  cluce=300.; //mm/ns
  static constexpr float amu=931.49386; //MeV
  static constexpr float me=0.511; //MeV
  static constexpr float ee=1.6E-19; //C
  static constexpr float r0=1.2; //fm
  static constexpr float epsi0=8.854e-12; //C^2 N^-1 m^-2
  
  Classe_formule()
    {

    }

  static float  vcm_classica(float vp,int ap, int at)
    {
      float vcm=ap*vp/(at+ap);
      return vcm;
    }
  static float  vplab_classica(float ebeam)
    {
      float mass=1.;
      float vplab=e2v(ebeam,mass);

      return vplab;
    }
  static float e2v(float e,float mass)
    {

      float v=cluce*TMath::Sqrt(2*e/(amu*mass));
      return v;
    }
  static float v2e(float v,float mass)
    {
      float e=0.5*mass*amu*v*v/(cluce*cluce);

      return e;
    }

  static void polcar(float r, float the, float phi,float *out)
  {
	out[2]=r*cos(the/57.296);
	out[0]=r*sin(the/57.296)*cos(phi/57.296);
	out[1]=r*sin(the/57.296)*sin(phi/57.296);
      }

  static float modulo(float *input)
    {
      float out=TMath::Sqrt(input[0]*input[0]+input[1]*input[1]+input[2]*input[2]);
      return out;
    }

    static float modulo(double *input)
    {
      float out=TMath::Sqrt(input[0]*input[0]+input[1]*input[1]+input[2]*input[2]);
      return out;
    }

  
//   static float modulo(TVector3 input)
//     {
//       float out=TMath::Sqrt(input[0]*input[0]+input[1]*input[1]+input[2]*input[2]);
//       return out;
//     }
  
  
static float modulo(std::vector<float> input)    {
      float out=TMath::Sqrt(input[0]*input[0]+input[1]*input[1]+input[2]*input[2]);
      return out;
    }

  static void carpol(float *r,float *the, float *phi,float *input)
    {
      *r=modulo(input);
    
      float comp=input[2]/(*r);
      if(comp>1){comp=1.;}
      if(comp<-1){comp=-1.;}
      (*the)=57.296*TMath::ACos(comp);

      (*phi)=57.296*TMath::ATan2(input[1],input[0]);
    }
  
  static void cm2lab_classica(float *velocm,float *velolab, float vcm)
    {
      for(int k=0;k<3;k++)
	{
	  velolab[k]=velocm[k];
	  if(k==2){velolab[k]=velolab[k]+vcm;}
	}
    }
  static void lab2cm_classica(float *velocm,float *velolab, float vcm)
    {
      for(int k=0;k<3;k++)
	{
	  velocm[k]=velolab[k];
	  if(k==2){velocm[k]=velocm[k]-vcm;}
	}
    }

  static void vecprod(float *a,float *b,float *vout)
    {
      vout[0]=a[1]*b[2]-a[2]*b[1];
      vout[1]=-a[0]*b[2]+a[2]*b[0];
      vout[2]=a[0]*b[1]-a[1]*b[0];

    }
  static void scaprod(float *v1, float *v2, float *vout)
    {
      *vout=v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2];

    }
	
  static void vparvperp(float *v,float *asse,float *vpar,float *vperp)
    {
      float cosal;
      float scp;
      scaprod(v,asse,&scp);
      cosal=scp/(modulo(v)*modulo(asse));
      if(cosal>1){cosal=1;}
      *vpar=modulo(v)*cosal;      
      float sinal=TMath::Sqrt(1-cosal*cosal);
      *vperp=modulo(v)*sinal;
      return;
      
    }
  static  float doppler(float ein,float velo,float theta)
  {float beta=velo/cluce;
    float eout=ein*(1-beta*TMath::Cos(theta/57.296))/(TMath::Sqrt(1-beta*beta));
    return eout;
  }
  
  static void p2v_cart(float *p,float a,float *v)
  {
    for(int j=0;j<3;j++)
      {
	v[j]=cluce*p[j]/(a*amu);	 
      }
    return;
  }
  static float p2e(float *p,float a)
  {
    float cp=modulo(p);
    float e=cp*cp/(2*a*931.5);
    return e;
  }

   static float p2e(float cp,float a)
  {
    float e=cp*cp/(2*a*931.5);
    return e;
  }

   static float e2p(float e,float a)
   {
     float pp=sqrt(2*a*amu*e);
     return pp;
   }

  
 /* static float v_ela(float theta) */
 /* { */
 /*   float vscat; */
   
 /*    float vscat1=(pow(Classe_analisi::Getanalisi()->reazione.ap,2)*cos(theta/57.296)*Classe_analisi::Getanalisi()->reazione.vplab+sqrt(pow(Classe_analisi::Getanalisi()->reazione.ap,4)*pow(Classe_analisi::Getanalisi()->reazione.vplab,2)*pow(cos(theta/57.296),2)-(pow(Classe_analisi::Getanalisi()->reazione.ap,4)-pow(Classe_analisi::Getanalisi()->reazione.ap*Classe_analisi::Getanalisi()->reazione.at,2))*pow(Classe_analisi::Getanalisi()->reazione.vplab,2)))/(pow(Classe_analisi::Getanalisi()->reazione.ap,2)+Classe_analisi::Getanalisi()->reazione.ap*Classe_analisi::Getanalisi()->reazione.at);  */
 /* float vscat2=(pow(Classe_analisi::Getanalisi()->reazione.ap,2)*cos(theta/57.296)*Classe_analisi::Getanalisi()->reazione.vplab-sqrt(pow(Classe_analisi::Getanalisi()->reazione.ap,4)*pow(Classe_analisi::Getanalisi()->reazione.vplab,2)*pow(cos(theta/57.296),2)-(pow(Classe_analisi::Getanalisi()->reazione.ap,4)-pow(Classe_analisi::Getanalisi()->reazione.ap*Classe_analisi::Getanalisi()->reazione.at,2))*pow(Classe_analisi::Getanalisi()->reazione.vplab,2)))/(pow(Classe_analisi::Getanalisi()->reazione.ap,2)+Classe_analisi::Getanalisi()->reazione.ap*Classe_analisi::Getanalisi()->reazione.at);  */
 /*  vscat=vscat1;  */
 /*  if(vscat<0){vscat=vscat2;}  */
 /*   return vscat; */
 /* } */


 static float thetarel(float *v1,float *v2)
 {
   float thetarel;
   float vvrel[3];
   for(int j=0;j<3;j++)
     {
       vvrel[j]=v1[j]-v2[j];
     }
   thetarel=57.296*TMath::ACos((pow(modulo(v1),2)+pow(modulo(v2),2)-pow(modulo(vvrel),2))/(2*modulo(v1)*modulo(v2)));

   return thetarel;
 }

 static void da_xyz_a1(float vx,float vy,float vz,float *vout)
 {
   vout[0]=vx;
   vout[1]=vy;
   vout[2]=vz;
 }
 static void vrel(float *v1,float *v2, float *vvrel)
 {
   for(int j=0;j<3;j++)
     {
       vvrel[j]=v1[j]-v2[j];
     }
 }

 static std::map<int, double> load_mass_defect(){
   //string AEl - Z, A, mass defect

   std::map<int, double> temp;
   
   std::ifstream in("awm95.txt");
   std::string line;

   if(in.good()){
     while(getline(in, line)){
       if(line[0]=='#') continue;
       std::stringstream ss;
       ss.str(line);

       std::string ll;
       double aa, zz, dd;

       ss >> ll >> zz >> dd;

       aa = std::stod(ll);
       temp.emplace(aa*100+zz,dd);
       
       //std::cout << ll << " " << aa << " " << zz << " " << dd << std::endl;
              
     }
   }
   else std::cout << "File non Esistente" << std::endl;

   return temp;
 }
 
};

#endif
