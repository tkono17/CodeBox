/*
  acceptance.cxx
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <random>

void generatePoint(double& x, double& y) {
  x = -100.0;
  y = -10.0;
}

void generateAngles(double& theta, double& phi) {
  theta = 10.0;
  phi = 0.0;
}

bool intersectionAtZ0(double x, double y, double theta, double phi, double d,
		      double& x0, double& y0) {
  bool hit=false;
  return hit;
}

int main(int argc, char* argv[]) {
  int npoints=1000;
  int nparticles=1000;
  int ipoint=0;
  int iparticle=0;
  double w=60.0;
  double l=80.0;
  double h=10.0;
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
    generatePoint(x, y);
    for (iparticle=0; iparticle<nparticles; ++iparticle) {
      generateAngles(theta, phi);
      hit = intersectionAtZ0(x, y, theta, phi, d, x0, y0);
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
