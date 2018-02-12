#include  "ball.h"
#include <pthread.h>
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define SCREEN_X 500
#define SCREEN_Y 100

GLfloat xRotated = 0.0, yRotated = 0.0, zRotated = 0.0;

ball* b = new ball(); // creating a new ball

void* tempDrawBalls(void* ballPtr){
  ball * b = (ball *) ballPtr;
  cout << "Ball created";
  cout << b->getCenterX();
}

void* drawBalls(void* ballPtr){

  ball * b = (ball*) ballPtr;

  // get center of the ball
  float x = b->getCenterX();
  float y = b->getCenterY();
  float z = b->getCenterZ();

  // get velocities of the ball
  float vx = b->getVelX();
  float vy = b->getVelY();
  float vz = b->getVelZ();

  // get color values of the ball
  float r = b->getRed();
  float g = b->getGreen();
  float blu = b->getBlue();

  // get radius of the ball
  float rad = b->getRadius();

  // update the center of the ball using velocities, detecting collision with the walls
  if(x <= 1-rad && x >= -1+rad){
    x += vx;
  }
  else{
    x -= vx;
    b->setVelX(-vx);
  }
  if(y <= 1-rad && y >= -1+rad){
    y += vy;
  }
  else{
    y -= vy;
    b->setVelY(-vy);
  }
  if(z <= 1-rad && z >= -1+rad){
    z += vz;
  }
  else{
    z -= vz;
    b->setVelZ(-vz);
  }

  //update the center of the balls
  b->setCenterX(x);
  b->setCenterY(y);
  b->setCenterZ(z);

  //b->printCenter();

  glLoadIdentity();
  glTranslatef( x, y, z);
  glBegin(GL_POLYGON);

  glColor3f(r,g,blu); // give color to the sphere

  glutSolidSphere(rad, 50, 50);

  glEnd();
}

void drawCube(){

  glMatrixMode(GL_MODELVIEW);

  glClear(GL_COLOR_BUFFER_BIT); // clear the buffer

  // glLoadIdentity();

  // glTranslatef(0.0,0.0,-10.0);

  // glRotatef(xRotated,-1.0,0.0,0.0); // rotation about X axis
  // glRotatef(yRotated,0.0,-1.0,0.0); // rotation about Y axis
  // glRotatef(zRotated,0.0,0.0,-1.0); // rotation about Z axis

  // glBegin(GL_QUADS); // Draw The Cube Using quads

  // glColor3f(0.0f,1.0f,0.0f);    // Color Blue
  // glVertex3f( 02.0f, 02.0f,-02.0f);    // Top Right Of The Quad (Top)
  // glVertex3f(-02.0f, 02.0f,-02.0f);    // Top Left Of The Quad (Top)
  // glVertex3f(-02.0f, 02.0f, 02.0f);    // Bottom Left Of The Quad (Top)
  // glVertex3f( 02.0f, 02.0f, 02.0f);    // Bottom Right Of The Quad (Top)

  // glColor3f(1.0f,1.0f,0.0f);    // Color Orange
  // glVertex3f( 02.0f,-02.0f, 02.0f);    // Top Right Of The Quad (Bottom)
  // glVertex3f(-02.0f,-02.0f, 02.0f);    // Top Left Of The Quad (Bottom)
  // glVertex3f(-02.0f,-02.0f,-02.0f);    // Bottom Left Of The Quad (Bottom)
  // glVertex3f( 02.0f,-02.0f,-02.0f);    // Bottom Right Of The Quad (Bottom)

  // glColor3f(1.0f,0.0f,0.0f);    // Color Red
  // glVertex3f( 02.0f, 02.0f, 02.0f);    // Top Right Of The Quad (Front)
  // glVertex3f(-02.0f, 02.0f, 02.0f);    // Top Left Of The Quad (Front)
  // glVertex3f(-02.0f,-02.0f, 02.0f);    // Bottom Left Of The Quad (Front)
  // glVertex3f( 02.0f,-02.0f, 02.0f);    // Bottom Right Of The Quad (Front)

  // glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
  // glVertex3f( 02.0f,-02.0f,-02.0f);    // Top Right Of The Quad (Back)
  // glVertex3f(-02.0f,-02.0f,-02.0f);    // Top Left Of The Quad (Back)
  // glVertex3f(-02.0f, 02.0f,-02.0f);    // Bottom Left Of The Quad (Back)
  // glVertex3f( 02.0f, 02.0f,-02.0f);    // Bottom Right Of The Quad (Back)

  // glColor3f(0.0f,0.0f,1.0f);    // Color Blue
  // glVertex3f(-02.0f, 02.0f, 02.0f);    // Top Right Of The Quad (Left)
  // glVertex3f(-02.0f, 02.0f,-02.0f);    // Top Left Of The Quad (Left)
  // glVertex3f(-02.0f,-02.0f,-02.0f);    // Bottom Left Of The Quad (Left)
  // glVertex3f(-02.0f,-02.0f, 02.0f);    // Bottom Right Of The Quad (Left)

  // glColor3f(1.0f,0.0f,1.0f);    // Color Violet
  // glVertex3f( 02.0f, 02.0f,-02.0f);    // Top Right Of The Quad (Right)
  // glVertex3f( 02.0f, 02.0f, 02.0f);    // Top Left Of The Quad (Right)
  // glVertex3f( 02.0f,-02.0f, 02.0f);    // Bottom Left Of The Quad (Right)
  // glVertex3f( 02.0f,-02.0f,-02.0f);    // Bottom Right Of The Quad (Right)

  // yRotated += 0.1;
  // xRotated += 0.1;
  // zRotated += 0.1;
  // glEnd();

  pthread_t ball_1; // create a ball thread

  int bRet1; // ball 1 returning  value

  pthread_create(&ball_1, NULL, &drawBalls, (void*) b);

  pthread_join(ball_1, NULL);

  glutSwapBuffers();
}
