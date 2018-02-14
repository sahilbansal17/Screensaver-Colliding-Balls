#include <math.h>
#include <vector>

using namespace std;

// compute center to center distance between two points
float centerToCenter(vector <float> c1, vector <float> c2){

  float distSq = 0;
  for(int i = 0 ; i < 3 ; i++){
    distSq += pow(c1[i] - c2[i], 2);
  }
  return sqrt(distSq);
}

// compute vector difference
vector <float> diff(vector <float> a, vector <float> b){
  vector <float> res(3);
  for(int i = 0 ; i < 3 ; i++){
    res[i] = a[i] - b[i];
  }
  return res;
}

// compute vector addition
vector <float> add(vector <float> a, vector <float> b){
  vector <float> res(3);
  for(int i = 0 ; i < 3 ; i++){
    res[i] = a[i] + b[i];
  }
  return res;
}

// compute dot product
float dotProd(vector <float> a, vector <float> b){
  float res = 0;
  for(int i = 0 ; i < 3 ; i++){
    res += a[i]*b[i];
  }
  return res;
}

// multiply constant to a vector
vector <float> mulConst(vector <float> vec, float cons){
  vector <float> res(3);
  for(int i = 0; i < 3 ; i++){
    res[i] = cons * vec[i];
  }
  return res;
}

// get the common normal for two vectors
vector <float> getCommonNormal(vector <float> r1, vector <float> r2){
  vector <float> res = diff(r1, r2);
  // need to multiply with 1/(|r1-r2|)
  float factor = centerToCenter(r1, r2);
  for(int i = 0 ; i < 3 ; i++){
    res[i] = res[i]*1/factor;
  }
  return res;
}
