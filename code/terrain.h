float translateNegX = 4.0;
bool movRight = 1;
void drawTerrain(ball** t, int n){

  glTranslatef(translateNegX, 0.0, 0.0);

  if(movRight == 1){
    translateNegX -= 0.005;
    for(int i = 0 ; i < n ; i ++){
        t[i]->updateCenter(-0.005, 0.0, 0.0);
        // terrain balls move along with frame movement
    }
    if(translateNegX <= -4){
      movRight = 0;
    }
  }
  else{
      translateNegX += 0.005;
      for(int i = 0 ; i < n ; i ++){
          t[i]->updateCenter(0.005, 0.0, 0.0);
      }
      if(translateNegX >= 4){
        movRight = 1;
      }
  }


  glBegin(GL_QUADS);

  glColor3f(0.0f,1.0f,0.0f); // green    
  glVertex3f( 05.5f,-01.0f, 05.0f);    // Top Right Of The Quad (Bottom)
  glVertex3f(-05.5f,-01.0f, 05.0f);    // Top Left Of The Quad (Bottom)
  glVertex3f(-05.5f,-01.0f,-05.0f);    // Bottom Left Of The Quad (Bottom)
  glVertex3f( 05.5f,-01.0f,-05.0f);    // Bottom Right Of The Quad (Bottom)  

  glEnd();

}
