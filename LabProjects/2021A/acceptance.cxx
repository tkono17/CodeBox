/*
  acceptance.cxx
*/

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
  double dtheta=std::M_PI/nangles;
  std::vector<int> countsGenerated;
  std::vector<int> countsDetected;
  countsGenerated.assign(nangles, 0);
  countsDetected.assign(nangles, 0);

  for (ipoint=0; ipoint<npoints; points) {
    generatePoints(x, y);
    generateAngles(theta, phi);
    intersectionAtZ0(x, y, theta, phi, d, x0, y0);
  }

  return 0;
}
