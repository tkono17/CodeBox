/*
  acceptance.cxx
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <random>

void generatePoint(double& x, double& y, double w, double l) {
  x = (double)rand()/32767.0*w;
  y = (double)rand()/32767.0*l;
  //0<=x<=w , 0<=y<=lの(x,y)がランダムに作られる
}

void generateAngles(double& theta, double& phi, double pi) {
  theta = (double)rand()*pi/2;
  phi = (double)rand()*2*pi;
  //0<=theta<=pi/2 , 0<=phi<=2piのtheta,phiがランダムに作られる
}

bool intersectionAtZ0(double x, double y, double theta, double phi, double d,
                      double& x0, double& y0, double w, double l) {
  bool hit;
  double costheta=std::cos(theta);
  double sintheta=std::sin(theta);
  double cosphi=std::cos(phi);
  double sinphi=std::sin(phi);
  x0=x-d*sintheta*cosphi/costheta;
  y0=y-d*sintheta*sinphi/costheta;
  //z=0での交点(x0,y0)を求めた

  if(x0>=0 && x0<=w && y0>=0 && y0<=l)
    hit=true;
  else
    hit=false;
  //交点が0<=x<=w, 0<=y<=lの範囲に入っていれば、trueを返す
  return hit;
}

int main(int argc, char* argv[]) {
  int npoints=1000;
  int nparticles=1000;
  int ipoint=0;
  int iparticle=0;
  double w=60.0;
  double l=80.0;
  double h=1.0;
  double d=20.0;
  double x, y;
  double theta, phi;
  double x0, y0;
  int nangles=100;
  double dcostheta=1.0/nangles;
  std::vector<int> countsGenerated;
  std::vector<int> countsDetected;
  countsGenerated.assign(nangles, 0);
  countsDetected.assign(nangles, 0);
  int costhetaBin=0;
  double costheta = 0;
  bool hit=false;
  const double pi = 3.1415926535;

  std::random_device seed_gen;
  std::default_random_engine engine(seed_gen());

  std::uniform_real_distribution<> xDist(-w/2.0, w/2.0);
  std::uniform_real_distribution<> yDist(-l/2.0, l/2.0);
  std::uniform_real_distribution<> cosThetaDist(0.0, 1.0);
  std::uniform_real_distribution<> phiDist(0, pi);

  std::cout << "Generate " << npoints << " points on the top surface"
	    << " and " << nparticles << " directions" << std::endl;

  std::ofstream fout("acc.dat");

  for (ipoint=0; ipoint<npoints; ipoint++) {
    generatePoint(x, y, w, l);
    for (iparticle=0; iparticle<nparticles; ++iparticle) {
      generateAngles(theta, phi, pi);
      hit = intersectionAtZ0(x, y, theta, phi, d, x0, y0, w, l);
      costheta = std::cos(theta);      
      costhetaBin = (costheta+1.0)/dcostheta;
      if (costhetaBin >= nangles) {
	costhetaBin = nangles - 1;
      }
      countsGenerated[costhetaBin] += 1;
      if (hit) {
	countsDetected[costhetaBin] += 1;
      }
      // fout << x << " " << y << " " ... << std::endl;
    }
  }
  fout.close();

  return 0;
}
