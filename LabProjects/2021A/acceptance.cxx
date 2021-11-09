/*
  acceptance.cxx
*/
#include <iostream>
#include <cmath>
#include <vector>

void generatePoint(double& x, double& y) {
  x = -100.0;
  y = -100.0;
}

void generateAngles(double& theta, double& phi) {
  theta = -100.0;
  phi = -100.0;
}

bool intersectionAtZ0(double x, double y, double theta, double phi, double d,
		      double& x0, double& y0) {
  bool hit=false;
  return hit;
}

int main(int argc, char* argv[]) {
  int npoints=10000;
  int nparticles=10000;
  int ipoint=0;
  int iparticle=0;
  double w=60.0;
  double l=80.0;
  double h=10.0;
  double d=20.0;
  double x, y;
  double theta, phi;
  double x0, y0;
  int nangles=0;
  double dcostheta=2.0/nangles;
  std::vector<int> countsGenerated;
  std::vector<int> countsDetected;
  countsGenerated.assign(nangles, 0);
  countsDetected.assign(nangles, 0);
  int costhetaBin=0;
  double costheta = 0;
  bool hit=false;

  for (ipoint=0; ipoint<npoints; ipoint++) {
    generatePoint(x, y);
    for (iparticle=0; iparticle<nparticles; ++iparticle) {
      generateAngles(theta, phi);
      hit = intersectionAtZ0(x, y, theta, phi, d, x0, y0);
      costheta = std::cos(theta);      
      costhetaBin = (costheta+1.0)/dcostheta;
      countsGenerated[costhetaBin] += 1;
      if (hit) {
	countsDetected[costhetaBin] += 1;
      }
    }
  }

  return 0;
}
