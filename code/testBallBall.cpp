#include "ball.h"
#include <vector>
#include <iostream>

using namespace std;

int main(){

  ball *b1;
  b1 = new ball(-0.85, 0.5, 0, 1.6, 0, 0);
  ball *b2;
  b2 = new ball(-0.87, 0.5, 0, -1.6, 0, 0);

  b1->updateVel(b2);

  // get final velocities

  vector <float> v1 = b1->getVel();
  vector <float> v2 = b2->getVel();

  cout << "Final:\n";

  for(int i = 0 ; i < 3 ; i ++){
    cout << "v_1_" << i << " " << v1[i] << "\n";
    cout << "v_2_" << i << " " << v2[i] << "\n";
  }
  return 0;
}
