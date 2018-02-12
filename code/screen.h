#include  "ball.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define SCREEN_X 500
#define SCREEN_Y 100

ball b; // creates a ball object

GLfloat xRotated = 0.0, yRotated = 0.0, zRotated = 0.0;
// int p = 0;
// float counter = 0.0;

void drawBalls(void){
  
  // get center of the ball
  float x = b.getCenterX();
  float y = b.getCenterY();
  float z = b.getCenterZ();

  // get velocities of the ball
  float vx = b.getVelX();
  float vy = b.getVelY();
  float vz = b.getVelZ();

  // get color values of the ball
  float r = b.getRed();
  float g = b.getGreen();
  float blu = b.getBlue();

  // get radius of the ball
  float rad = b.getRadius();

  // update the center of the ball using velocities, detecting collision with the walls
  if(x <= 1-rad && x >= -1+rad){
    x += vx;
  }
  else{
    x -= vx;
    b.setVelX(-vx);
  }
  if(y <= 1-rad && y >= -1+rad){
    y += vy;
  }
  else{
    y -= vy;
    b.setVelY(-vy);
  }
  if(z <= 1-rad && z >= -1+rad){
    z += vz;
  }
  else{
    z -= vz;
    b.setVelZ(-vz);
  }


  //update the center of the balls
  b.setCenterX(x);
  b.setCenterY(y);
  b.setCenterZ(z); 
  glLoadIdentity();
  glTranslatef( x, y, z);

  //b.printCenter(); 
  // if(counter<=2.0 && p==0){
  //   counter+=0.01;
  //   if(counter>=1.7){
  //     p=1;
  //   }
  // }
  // else if(p == 1){
  //   counter=counter-0.01;
  //   if(counter<=-1.7){
  //     p=0;
  //   }
  // }
  glBegin(GL_POLYGON);
  
  glColor3f(r,g,blu); // give color to the sphere
  
  glutSolidSphere(rad, 50, 50);
  
  glEnd();         
}
<<<<<<< Updated upstream
void drawCube(void){
  
=======
float counter,p=0;
void drawCube(){

>>>>>>> Stashed changes
  glMatrixMode(GL_MODELVIEW);
  
  glClear(GL_COLOR_BUFFER_BIT); // clear the buffer

  glLoadIdentity();
<<<<<<< Updated upstream
 
  glTranslatef(0.0,0.0,-10.0);

  glRotatef(xRotated,-1.0,0.0,0.0); // rotation about X axis
  glRotatef(yRotated,0.0,-1.0,0.0); // rotation about Y axis
  glRotatef(zRotated,0.0,0.0,-1.0); // rotation about Z axis 

  glBegin(GL_QUADS); // Draw The Cube Using quads
  
  glColor3f(0.0f,1.0f,0.0f);    // Color Blue
  glVertex3f( 01.0f, 01.0f,-01.0f);    // Top Right Of The Quad (Top)
  glVertex3f(-01.0f, 01.0f,-01.0f);    // Top Left Of The Quad (Top)
  glVertex3f(-01.0f, 01.0f, 01.0f);    // Bottom Left Of The Quad (Top)
  glVertex3f( 01.0f, 01.0f, 01.0f);    // Bottom Right Of The Quad (Top)
  
  glColor3f(1.0f,1.0f,0.0f);    // Color Orange
  glVertex3f( 01.0f,-01.0f, 01.0f);    // Top Right Of The Quad (Bottom)
  glVertex3f(-01.0f,-01.0f, 01.0f);    // Top Left Of The Quad (Bottom)
  glVertex3f(-01.0f,-01.0f,-01.0f);    // Bottom Left Of The Quad (Bottom)
  glVertex3f( 01.0f,-01.0f,-01.0f);    // Bottom Right Of The Quad (Bottom)
  
  glColor3f(1.0f,0.0f,0.0f);    // Color Red    
  glVertex3f( 01.0f, 01.0f, 01.0f);    // Top Right Of The Quad (Front)
  glVertex3f(-01.0f, 01.0f, 01.0f);    // Top Left Of The Quad (Front)
  glVertex3f(-01.0f,-01.0f, 01.0f);    // Bottom Left Of The Quad (Front)
  glVertex3f( 01.0f,-01.0f, 01.0f);    // Bottom Right Of The Quad (Front)
  
  glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
  glVertex3f( 01.0f,-01.0f,-01.0f);    // Top Right Of The Quad (Back)
  glVertex3f(-01.0f,-01.0f,-01.0f);    // Top Left Of The Quad (Back)
  glVertex3f(-01.0f, 01.0f,-01.0f);    // Bottom Left Of The Quad (Back)
  glVertex3f( 01.0f, 01.0f,-01.0f);    // Bottom Right Of The Quad (Back)
  
  glColor3f(0.0f,0.0f,1.0f);    // Color Blue
  glVertex3f(-01.0f, 01.0f, 01.0f);    // Top Right Of The Quad (Left)
  glVertex3f(-01.0f, 01.0f,-01.0f);    // Top Left Of The Quad (Left)
  glVertex3f(-01.0f,-01.0f,-01.0f);    // Bottom Left Of The Quad (Left)
  glVertex3f(-01.0f,-01.0f, 01.0f);    // Bottom Right Of The Quad (Left)
  
  glColor3f(1.0f,0.0f,1.0f);    // Color Violet
  glVertex3f( 01.0f, 01.0f,-01.0f);    // Top Right Of The Quad (Right)
  glVertex3f( 01.0f, 01.0f, 01.0f);    // Top Left Of The Quad (Right)
  glVertex3f( 01.0f,-01.0f, 01.0f);    // Bottom Left Of The Quad (Right)
  glVertex3f( 01.0f,-01.0f,-01.0f);    // Bottom Right Of The Quad (Right)
  
=======
   
  glTranslatef(counter,0.0,-8.0);
  

   if(counter<=0.9 && p==0)
     {
         counter+=0.01;
         if(counter>=0.8)
         {
            p=1;
         }
     }else
       if(p == 1)
       {
          counter=counter-0.01;
            if(counter<=-0.8)
            {
              p=0;
            }
        }
  // glRotatef(xRotated,-1.0,0.0,0.0); // rotation about X axis
  // glRotatef(yRotated,0.0,-1.0,0.0); // rotation about Y axis
  // glRotatef(zRotated,0.0,0.0,-1.0); // rotation about Z axis

  glBegin(GL_QUADS); // Draw The Cube Using quads

  glColor3f(1.0f,0.0f,0.0f);    // Color Blue
  glVertex3f( 02.0f, 01.0f,-02.0f);    // Top Right Of The Quad (Top)
  glVertex3f(-02.0f, 01.0f,-02.0f);    // Top Left Of The Quad (Top)
  glVertex3f(-02.0f, 01.0f, 02.0f);    // Bottom Left Of The Quad (Top)
  glVertex3f( 02.0f, 01.0f, 02.0f);    // Bottom Right Of The Quad (Top)

  glColor3f(0.0f,1.0f,0.0f);    // Color Orange
  glVertex3f( 02.0f,-01.0f, 02.0f);    // Top Right Of The Quad (Bottom)
  glVertex3f(-02.0f,-01.0f, 02.0f);    // Top Left Of The Quad (Bottom)
  glVertex3f(-02.0f,-01.0f,-02.0f);    // Bottom Left Of The Quad (Bottom)
  glVertex3f( 02.0f,-01.0f,-02.0f);    // Bottom Right Of The Quad (Bottom)

  glColor3f(0.0f,0.0f,1.0f);    // Color Red
  glVertex3f( 02.0f, 01.0f, 02.0f);    // Top Right Of The Quad (Front)
  glVertex3f(-02.0f, 01.0f, 02.0f);    // Top Left Of The Quad (Front)
  glVertex3f(-02.0f,-01.0f, 02.0f);    // Bottom Left Of The Quad (Front)
  glVertex3f( 02.0f,-01.0f, 02.0f);    // Bottom Right Of The Quad (Front)

  glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
  glVertex3f( 02.0f,-01.0f,-02.0f);    // Top Right Of The Quad (Back)
  glVertex3f(-02.0f,-01.0f,-02.0f);    // Top Left Of The Quad (Back)
  glVertex3f(-02.0f, 01.0f,-02.0f);    // Bottom Left Of The Quad (Back)
  glVertex3f( 02.0f, 01.0f,-02.0f);    // Bottom Right Of The Quad (Back)

  glColor3f(1.0f,0.0f,1.0f);    // Color Blue
  glVertex3f(-02.0f, 01.0f, 02.0f);    // Top Right Of The Quad (Left)
  glVertex3f(-02.0f, 01.0f,-02.0f);    // Top Left Of The Quad (Left)
  glVertex3f(-02.0f,-01.0f,-02.0f);    // Bottom Left Of The Quad (Left)
  glVertex3f(-02.0f,-01.0f, 02.0f);    // Bottom Right Of The Quad (Left)

  glColor3f(0.0f,1.0f,1.0f);    // Color Violet
  glVertex3f( 02.0f, 01.0f,-02.0f);    // Top Right Of The Quad (Right)
  glVertex3f( 02.0f, 01.0f, 02.0f);    // Top Left Of The Quad (Right)
  glVertex3f( 02.0f,-01.0f, 02.0f);    // Bottom Left Of The Quad (Right)
  glVertex3f( 02.0f,-01.0f,-02.0f);    // Bottom Right Of The Quad (Right)

>>>>>>> Stashed changes
  yRotated += 0.1;
  xRotated += 0.1;
  zRotated += 0.1;
  glEnd();
<<<<<<< Updated upstream
=======

  vector <pthread_t> balls(num_balls); // create n threads, one for each ball

  vector <int> bRet(num_balls); // to store values returned by each thread

  for(int i = 0 ; i < num_balls; i ++){
    bRet[i] = pthread_create(&balls[i], NULL, &controlBall, (void*)b[i]); // create a thread

    pthread_join(balls[i], NULL);

    drawBall(b[i]);
  }
>>>>>>> Stashed changes

  drawBalls();
  
  glutSwapBuffers();
}