#include <math.h>
#include <vector>

using namespace std;

float centerToCenter(vector <float> c1, vector <float> c2){

  float distSq = 0;
  for(int i = 0 ; i < 3 ; i++){
    distSq += pow(c1[i] - c2[i], 2);
  }

  return sqrt(distSq);
}

// vector <float> commonNormal(vector <float> r1, vector <float> r2){
//
// }
