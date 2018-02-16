float translateNegX = 4.0;
bool movRight = 1;
void drawTerrain(){

  glTranslatef(translateNegX, -0.5, 0.0);

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
  glBegin(GL_QUADS);

  glColor3f(0.1f, 1.0f, 0.1f);
  glVertex3f( 5.0f, -0.5f, 0.0f);
  glVertex3f(-5.0f, -0.5f, 0.0f);
  glVertex3f(-5.0f, -0.2f, 0.0f);
  glVertex3f( 5.0f, -0.2f, 0.0f);

  glEnd();

  glBegin(GL_TRIANGLES);

  glColor3f(0.1f, 1.0f, 0.1f);
  glVertex3f(-4.0, -0.5, 0.0);
  glVertex3f(-3.75, 0.25, 0.0);
  glVertex3f(-3.5, -0.5, 0.0);

  glColor3f(0.1f, 1.0f, 0.1f);
  glVertex3f(-2.5, -0.5, 0.0);
  glVertex3f(-2.25, 0.5, 0.0);
  glVertex3f(-2.0, -0.5, 0.0);

  glColor3f(0.1f, 1.0f, 0.1f);
  glVertex3f(-1.0, -0.5, 0.0);
  glVertex3f(-0.5, 0.37, 0.0);
  glVertex3f( 0.0, -0.5, 0.0);

  glColor3f(0.1f, 1.0f, 0.1f);
  glVertex3f(4.0, -0.5, 0.0);
  glVertex3f(3.75, 0.25, 0.0);
  glVertex3f(3.5, -0.5, 0.0);

  glColor3f(0.1f, 1.0f, 0.1f);
  glVertex3f(2.5, -0.5, 0.0);
  glVertex3f(2.25, 0.5, 0.0);
  glVertex3f(2.0, -0.5, 0.0);

  glColor3f(0.1f, 1.0f, 0.1f);
  glVertex3f(1.0, -0.5, 0.0);
  glVertex3f(0.5, 0.37, 0.0);
  glVertex3f( 0.0, -0.5, 0.0);

  glEnd();
}
