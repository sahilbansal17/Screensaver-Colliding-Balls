#include <vector>
class Triangle{
private:
  vector <float> pt1; // left
  vector <float> pt2; // top
  vector <float> pt3; // right
  vector <float> lineL; // /type
  vector <float> lineR; // \type
public:
  Triangle(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y){
    pt1 = vector <float> (3);
    pt2 = vector <float> (3);
    pt3 = vector <float> (3);
    lineL = vector <float> (3);
    lineR = vector <float> (3);
    pt1[0] = p1x;
    pt1[1] = p1y;
    pt2[0] = p2x;
    pt2[1] = p2y;
    pt3[0] = p3x;
    pt3[1] = p3y;
    pt1[2] = 0.0;
    pt2[2] = 0.0;
    pt3[2] = 0.0;
    lineL = diff(pt2, pt1);
    lineR = diff(pt2, pt3);
  }
  vector <float> getPt1(){
    return pt1;
  }
  vector <float> getPt2(){
    return pt2;
  }
  vector <float> getPt3(){
    return pt3;
  }
  vector <float> getLL(){
    return lineL;
  }
  vector <float> getLR(){
    return lineR;
  }

  // setter
  float translatePts(float x){
    pt1[0] += x;
    pt2[0] += x;
    pt3[0] += x;
  }
};


float translateNegX = 4.0;
bool movRight = 1;
void drawTerrain(Triangle** t, int n){

  // assume fixed along x-axis to analyze initially
  glTranslatef(translateNegX, 0.0, 0.0);

  if(movRight == 1){
    translateNegX -= 0.01;
    for(int i = 0 ; i < n ; i ++){
        t[i]->translatePts(-0.01);
    }
    if(translateNegX <= -4){
      movRight = 0;
    }
  }
  else{
      translateNegX += 0.01;
      for(int i = 0 ; i < n ; i ++){
          t[i]->translatePts(0.01);
      }
      if(translateNegX >= 4){
        movRight = 1;
      }
  }

  for(int i = 0 ; i < n ; i ++){

  }
  // glBegin(GL_QUADS);
  //
  // glColor3f(0.1f, 1.0f, 0.1f);
  // glVertex3f( 5.0f, -0.5f, 0.0f);
  // glVertex3f(-5.0f, -0.5f, 0.0f);
  // glVertex3f(-5.0f, -0.2f, 0.0f);
  // glVertex3f( 5.0f, -0.2f, 0.0f);
  //
  // glEnd();


  // glBegin(GL_TRIANGLES);

  // glColor3f(0.1f, 1.0f, 0.1f);
  // glVertex3f(-4.0, -0.5, 0.0);
  // glVertex3f(-3.75, 0.25, 0.0);
  // glVertex3f(-3.5, -0.5, 0.0);
  //
  // glColor3f(0.1f, 1.0f, 0.1f);
  // glVertex3f(-2.5, -0.5, 0.0);
  // glVertex3f(-2.25, 0.5, 0.0);
  // glVertex3f(-2.0, -0.5, 0.0);

  // glColor3f(0.1f, 1.0f, 0.1f);
  // glVertex3f(4.0, -0.5, 0.0);
  // glVertex3f(3.75, 0.25, 0.0);
  // glVertex3f(3.5, -0.5, 0.0);
  //
  // glColor3f(0.1f, 1.0f, 0.1f);
  // glVertex3f(2.5, -0.5, 0.0);
  // glVertex3f(2.25, 0.5, 0.0);
  // glVertex3f(2.0, -0.5, 0.0);
  //
  // glColor3f(0.1f, 1.0f, 0.1f);
  // glVertex3f(1.0, -0.5, 0.0);
  // glVertex3f(0.5, 0.5, 0.0);
  // glVertex3f( 0.0, -0.5, 0.0);

  // glEnd();
}
