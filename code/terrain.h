// #include <pair>
//
// class Triangle{
// private:
//   vector <float> pt1[3];
//   vector <float> pt2[3];
//   vector <float> pt3[3];
//   vector <float> lineL[3];
//   vector <float> lineR[3];
// public:
//   Triangle(float p1x, float p2x, float p1y, float p2y, float p3x, float p3y){
//     pt1[0] = p1x;
//     pt1[1] = p1y;
//     pt2[0] = p2x;
//     pt2[1] = p2y;
//     pt3[0] = p3x;
//     pt3[1] = p3y;
//     pt1[2] = 0.0;
//     pt2[2] = 0.0;
//     pt3[2] = 0.0;
//   }
//   vector <float> getPt1(){
//     return pt1;
//   }
//   vector <float> getPt2(){
//     return pt2;
//   }
//   vector <float> getPt3(){
//     return pt2;
//   }
//   vector <float> getLL(){
//     return lineL;
//   }
//   vector <float> getLR(){
//     return lineR;
//   }
// };


float translateNegX = 4.0;
bool movRight = 1;
void drawTerrain(){

  glTranslatef(0, -0.5, 0.0);
  // assume fixed along x-axis to analyze initially

  if(movRight == 1){
    translateNegX -= 0.01;
    if(translateNegX <= -4){
      movRight = 0;
    }
  }
  else{
      translateNegX += 0.01;
      if(translateNegX >= 4){
        movRight = 1;
      }
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

  glBegin(GL_TRIANGLES);

  // glColor3f(0.1f, 1.0f, 0.1f);
  // glVertex3f(-4.0, -0.5, 0.0);
  // glVertex3f(-3.75, 0.25, 0.0);
  // glVertex3f(-3.5, -0.5, 0.0);
  //
  // glColor3f(0.1f, 1.0f, 0.1f);
  // glVertex3f(-2.5, -0.5, 0.0);
  // glVertex3f(-2.25, 0.5, 0.0);
  // glVertex3f(-2.0, -0.5, 0.0);

  glColor3f(0.1f, 1.0f, 0.1f);
  glVertex3f(-1.0, -0.5, 0.0);
  glVertex3f(-0.5, 0.0, 0.0);
  glVertex3f( 0.0, -0.5, 0.0);

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

  glEnd();
}
