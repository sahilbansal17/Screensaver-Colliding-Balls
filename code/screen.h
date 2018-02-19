#include  "ball.h"
#include  "terrain.h"
#include  "pthread_barrier.h"
#include <vector>
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define SCREEN_X 500
#define SCREEN_Y 100
#define eps 10e-3

void keyboard(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
ball **b; // double pointer to ball
// Triangle **t; // to draw triangles
// Triangle **t_copy; // to check collisions and keep updating with translating screen

int num_balls; // number of balls
// int num_tri = 4; // number of triangles
// pthread_barrier_t barrier; // create pthread barrier

// initialize balls
void initBalls(int n){
  num_balls = n; // assign proper value to global variable
  b = new ball*[n]; // b points to array of pointers
  for(int i = 0 ; i < n ; i++){
    b[i] = new ball(); // allocate memory to each ball
  }
}

// void initTriangles(){
//   t = new Triangle*[num_tri];
//   t_copy = new Triangle*[num_tri];

//   // terrain objects
//   t[0] = new Triangle(-1.0, -1.0, -0.5 , -0.5 ,  0.0, -1.0);
//   t[1] = new Triangle(-4.0, -1.0, -4.0 , -0.35, -3.5, -1.0);
//   t[2] = new Triangle(-2.5, -1.0, -2.25,  0.0 , -2.0, -1.0);
//   t[3] = new Triangle( 0.0, -1.0,  0.5 ,  0.0 ,  1.0, -1.0);
//   t_copy[0] = new Triangle(-1.0, -1.0, -0.5 , -0.5 ,  0.0, -1.0);
//   t_copy[1] = new Triangle(-4.0, -1.0, -4.0 , -0.35, -3.5, -1.0);
//   t_copy[2] = new Triangle(-2.5, -1.0, -2.25,  0.0 , -2.0, -1.0);
//   t_copy[3] = new Triangle( 0.0, -1.0,  0.5 ,  0.0 ,  1.0, -1.0);


//   t_copy[0]->translatePts(4);
//   t_copy[1]->translatePts(4);
//   t_copy[2]->translatePts(4);
//   t_copy[3]->translatePts(4);
// }

// function to render ball on screen
void drawBall(ball *b){

  vector <float> center = b->getCenter();
  vector <float> color = b->getColor();
  float rad = b->getRadius();

  glLoadIdentity();
  glTranslatef(center[0], center[1], center[2]);

  glBegin(GL_POLYGON);
  glColor3f(color[0], color[1], color[2]); // give color to the sphere
  glutSolidSphere(rad, 50, 50);
  glEnd();
}

// function to control ball coordinates
void* controlBallWall(void* ballPtr){

  ball * b = (ball*) ballPtr;

  // get center of the ball
  vector <float> center = b->getCenter();
  // get velocities of the ball
  vector <float> vel = b->getVel();
  // get color values of the ball
  vector <float> color = b->getColor();
  // get radius of the ball
  float rad = b->getRadius();

  // to make sure that ball does not go beyond the boundaries initially (2d boundary)
  for(int i = 0 ; i < 2 ; i++){
    if(center[i] > 1-rad){
      center[i] = 1 - rad;
    }
    else if(center[i] < -1+rad){
      center[i] = -1 + rad;
    }
  }
  // update the center of the ball using velocities, detecting collision with the walls
  for(int i = 0 ; i < 2 ; i++){
    if(center[i] + vel[i] <= 1-rad && center[i] + vel[i] >= -1+rad){
        center[i] += vel[i];
    }
    else{
      center[i] -= vel[i];
      vel[i] = -1*vel[i];
    }
  }
  // for z-axis
  if(center[2] > -2-rad){
    center[2] = -2 - rad;
  }
  else if(center[2] < -12+rad){
    center[2] = -12 + rad;
  } 
  if(center[2] + vel[2] <= -2-rad && center[2] + vel[2] >= -12+rad){
    center[2] += vel[2];
  }
  else{
    center[2] -= vel[2];
    vel[2] = -1*vel[2];
  }
  
  // pthread_barrier_wait(&barrier);

  //update the center of the balls
  b->setCenter(center[0], center[1], center[2]);
  // update the velocities of the balls if req
  b->setVel(vel[0], vel[1], vel[2]);
  // b->printCenter();
}


void controlBallBall(ball* b1, ball* b2){

  // check whether collision has occurred
  bool res = b1->checkBallBall(b2);

  if(res == 1){
    b1->updateVel(b2);
  }
  return ;
}

// void drawTriangle(Triangle *t){


//   glBegin(GL_TRIANGLES);

//   glColor3f(0.1f, 1.0f, 0.1f);
//   vector <float> pt1(3), pt2(3), pt3(3);
//   pt1 = t->getPt1();
//   pt2 = t->getPt2();
//   pt3 = t->getPt3();
//   glVertex3f(pt1[0], pt1[1], 0.0);
//   glVertex3f(pt2[0], pt2[1], 0.0);
//   glVertex3f(pt3[0], pt3[1], 0.0);

//   glEnd();
// }

void drawCube(){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the buffer

  glLoadIdentity();
  
  glTranslatef(0.0, 0.0, -7.0);

  glBegin(GL_QUADS);
   
  glColor3f(0.3f,0.4f,0.3f);   
  glVertex3f( 01.0f, 01.0f,-05.0f);    // Top Right Of The Quad (Top)
  glVertex3f(-01.0f, 01.0f,-05.0f);    // Top Left Of The Quad (Top)
  glVertex3f(-01.0f, 01.0f, 05.0f);    // Bottom Left Of The Quad (Top)
  glVertex3f( 01.0f, 01.0f, 05.0f);    // Bottom Right Of The Quad (Top)
 
  glColor3f(0.1f,0.1f,0.8f);    
  glVertex3f( 01.0f,-01.0f, 05.0f);    // Top Right Of The Quad (Bottom)
  glVertex3f(-01.0f,-01.0f, 05.0f);    // Top Left Of The Quad (Bottom)
  glVertex3f(-01.0f,-01.0f,-05.0f);    // Bottom Left Of The Quad (Bottom)
  glVertex3f( 01.0f,-01.0f,-05.0f);    // Bottom Right Of The Quad (Bottom)  
  
  glColor3f(0.5f,0.5f,0.5f);    
  glVertex3f( 01.0f, 01.0f, 05.0f);    // Top Right Of The Quad (Front)
  glVertex3f(-01.0f, 01.0f, 05.0f);    // Top Left Of The Quad (Front)
  glVertex3f(-01.0f,-01.0f, 05.0f);    // Bottom Left Of The Quad (Front)
  glVertex3f( 01.0f,-01.0f, 05.0f);    // Bottom Right Of The Quad (Front)
  
  glColor3f(1.0f,0.2f,0.3f);    
  glVertex3f( 01.0f,-01.0f,-05.0f);    // Top Right Of The Quad (Back)
  glVertex3f(-01.0f,-01.0f,-05.0f);    // Top Left Of The Quad (Back)
  glVertex3f(-01.0f, 01.0f,-05.0f);    // Bottom Left Of The Quad (Back)
  glVertex3f( 01.0f, 01.0f,-05.0f);    // Bottom Right Of The Quad (Back)
  
  glColor3f(0.0f,1.0f,0.0f);    
  glVertex3f(-01.0f, 01.0f, 05.0f);    // Top Right Of The Quad (Left)
  glVertex3f(-01.0f, 01.0f,-05.0f);    // Top Left Of The Quad (Left)
  glVertex3f(-01.0f,-01.0f,-05.0f);    // Bottom Left Of The Quad (Left)
  glVertex3f(-01.0f,-01.0f, 05.0f);    // Bottom Right Of The Quad (Left)

  glColor3f(0.7f,0.1f,0.3f);
  glVertex3f( 01.0f, 01.0f,-05.0f);    // Top Right Of The Quad (Right)
  glVertex3f( 01.0f, 01.0f, 05.0f);    // Top Left Of The Quad (Right)
  glVertex3f( 01.0f,-01.0f, 05.0f);    // Bottom Left Of The Quad (Right)
  glVertex3f( 01.0f,-01.0f,-05.0f);    // Bottom Right Of The Quad (Right)

  glEnd();

  // drawTerrain(t_copy, num_tri);

  // for(int i = 0 ; i < num_tri ; i ++){
  //   drawTriangle(t[i]);
  // }

  vector <pthread_t> balls(num_balls); // create n threads, one for each ball

  vector <int> bRet(num_balls); // to store values returned by each thread

  // pthread_barrier_init(&barrier, 0, num_balls);

  // check for ball to ball collsions and update velocities
  // also makes sure that initially no two balls are generated at same place
  for(int i = 0 ; i < num_balls ; i ++){
    for (int j = i+1; j < num_balls; j++){
      controlBallBall(b[i], b[j]);
    }
  }

  // need to check for collisions between ball and the terrain before calling controlBallWall so that ball parameters get updated when collide with terrain object

  // for(int i = 0 ; i < num_balls ; i ++){
  //   for(int j = 0 ; j < num_tri; j ++){
  //     controlBallTerrain(b[i], t_copy[j]);
  //   }
  // }

  for(int i = 0 ; i < num_balls ; i ++){
    bRet[i] = pthread_create(&balls[i], NULL, &controlBallWall, (void*)b[i]); // create a thread
    // controlBallWall checks for ball to wall collisions and updates the coordinates

    pthread_join(balls[i], NULL);

  }
  // pthread_barrier_destroy(&barrier);

  for(int i = 0 ; i < num_balls ; i++){
    drawBall(b[i]);
  }
  
  glutSwapBuffers();
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKey);
}

int ballSelected = -1;
bool full = 0;
void keyboard(unsigned char key, int x, int y){
  if(key == 27){ // escape key
    exit(0);
  }
  else if(key == 'f'){
    if(!full){
      full = 1;
      glutFullScreen();
    }
    else{
      full = 0;
      glutPositionWindow(SCREEN_X, SCREEN_Y);
      glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
    }
  }
  // for keys 0 to 9 give the option of selecting the ball
  int ball_id = key - 48;
  if(key >= '0' && key <= '9' && ball_id < num_balls){
    b[ball_id]->changeColor();
    if(ballSelected = -1){
      ballSelected = ball_id;
    }
    else{
      ballSelected = -1;
    }
  }
  if(key == '=' && ballSelected >= 0){
    b[ballSelected]->increaseVal();
  }
  if(key == '-' && ballSelected >= 0){
    b[ballSelected]->decreaseVal();
  }
}

void specialKey(int key, int x, int y){
  if(key == GLUT_KEY_DOWN && ballSelected >= 0){
    b[ballSelected]->decreaseRad();
  }
  if(key == GLUT_KEY_UP && ballSelected >= 0){
    b[ballSelected]->increaseRad();
  }
}
