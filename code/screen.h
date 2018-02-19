#include  "ball.h"
#include  "terrain.h"
#include  "pthread_barrier.h"
#include <vector>
#include <random>
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define SCREEN_X 500
#define SCREEN_Y 100
#define eps 10e-3

void keyboard(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
ball **b; // double pointer to ball
ball **t; // to draw terrain balls
// Triangle **t_copy; // to check collisions and keep updating with translating screen

int num_balls; // number of balls
int num_t; // number of terrain balls
// pthread_barrier_t barrier; // create pthread barrier

// initialize balls
void initBalls(int n){
  num_balls = n; // assign proper value to global variable
  b = new ball*[n]; // b points to array of pointers
  for(int i = 0 ; i < n ; i++){
    b[i] = new ball(); // allocate memory to each ball
  }
}

void initTerrain(){
  random_device rd; //non-deterministic engine, to seed mt engine
  mt19937 gen(rd()); //mersenne-twister engine
  uniform_real_distribution<float> x(-0.9, 0.9);
  uniform_real_distribution<float> z(-1.0, -10.0);
  uniform_int_distribution<int> num(5, 10);
  num_t = num(gen);
  t = new ball*[num_t];
  for(int i = 0 ; i < num_t ; i ++){
    t[i] = new ball(x(gen), -1.0, z(gen));
  }

  // t_copy[0]->translatePts(4);
  // t_copy[1]->translatePts(4);
  // t_copy[2]->translatePts(4);
  // t_copy[3]->translatePts(4);
}

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
  if(center[2] > -1-rad){
    center[2] = -1-rad;
  }
  else if(center[2] < -10+rad){
    center[2] = -10+rad;
  } 
  if(center[2] + vel[2] <= -1-rad && center[2] + vel[2] >= -10+rad){
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

void controlBallTerrain(ball* b1, ball* b2){

  // check whether collision has occurred
  bool res = b2->checkBallBall(b1);

  if(res == 1){
    b2->updateVelBT(b1);
  }
  return ;
}

bool pause = 0;
void drawCube(){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the buffer

  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
  
  glTranslatef(0.0, 0.0, -5.0);
  // glRotatef(xR, 1.0, 0.0, 0.0);
  // xR += 0.1;
  glBegin(GL_QUADS);
   
  glColor3f(0.0f,1.0f,0.0f); // green   
  glVertex3f( 01.0f, 01.0f,-05.0f);    // Top Right Of The Quad (Top)
  glVertex3f(-01.0f, 01.0f,-05.0f);    // Top Left Of The Quad (Top)
  glVertex3f(-01.0f, 01.0f, 05.0f);    // Bottom Left Of The Quad (Top)
  glVertex3f( 01.0f, 01.0f, 05.0f);    // Bottom Right Of The Quad (Top)
 
  glColor3f(1.0f,0.5f,0.0f); // orange    
  glVertex3f( 01.0f,-01.0f, 05.0f);    // Top Right Of The Quad (Bottom)
  glVertex3f(-01.0f,-01.0f, 05.0f);    // Top Left Of The Quad (Bottom)
  glVertex3f(-01.0f,-01.0f,-05.0f);    // Bottom Left Of The Quad (Bottom)
  glVertex3f( 01.0f,-01.0f,-05.0f);    // Bottom Right Of The Quad (Bottom)  

  glColor3f(1.0f,0.0f,0.0f);  //red
  glVertex3f( 01.0f, 01.0f, 05.0f);    // Top Right Of The Quad (Front)
  glVertex3f(-01.0f, 01.0f, 05.0f);    // Top Left Of The Quad (Front)
  glVertex3f(-01.0f,-01.0f, 05.0f);    // Bottom Left Of The Quad (Front)
  glVertex3f( 01.0f,-01.0f, 05.0f);    // Bottom Right Of The Quad (Front)
  
  glColor3f(1.0f,1.0f,0.0f);  //yellow    
  glVertex3f( 01.0f,-01.0f,-05.0f);    // Top Right Of The Quad (Back)
  glVertex3f(-01.0f,-01.0f,-05.0f);    // Top Left Of The Quad (Back)
  glVertex3f(-01.0f, 01.0f,-05.0f);    // Bottom Left Of The Quad (Back)
  glVertex3f( 01.0f, 01.0f,-05.0f);    // Bottom Right Of The Quad (Back)
  
  glColor3f(0.0f,0.0f,1.0f);  //blue
  glVertex3f(-01.0f, 01.0f, 05.0f);    // Top Right Of The Quad (Left)
  glVertex3f(-01.0f, 01.0f,-05.0f);    // Top Left Of The Quad (Left)
  glVertex3f(-01.0f,-01.0f,-05.0f);    // Bottom Left Of The Quad (Left)
  glVertex3f(-01.0f,-01.0f, 05.0f);    // Bottom Right Of The Quad (Left)

  glColor3f(1.0f,0.0f,1.0f);  //magenta
  glVertex3f( 01.0f, 01.0f,-05.0f);    // Top Right Of The Quad (Right)
  glVertex3f( 01.0f, 01.0f, 05.0f);    // Top Left Of The Quad (Right)
  glVertex3f( 01.0f,-01.0f, 05.0f);    // Bottom Left Of The1Quad (Right)
  glVertex3f( 01.0f,-01.0f,-05.0f);    // Bottom Right Of Th1 Quad (Right)

  glEnd();

  // draw the terrain objects
  for(int i = 0 ; i < num_t ; i ++){
    drawBall(t[i]);
  }

  if(!pause){
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

    for(int i = 0 ; i < num_balls ; i ++){
      for(int j = 0 ; j < num_t; j ++){
        controlBallTerrain(b[i], t[j]);
      }
    }

    for(int i = 0 ; i < num_balls ; i ++){
      bRet[i] = pthread_create(&balls[i], NULL, &controlBallWall, (void*)b[i]); // create a thread
      // controlBallWall checks for ball to wall collisions and updates the coordinates

      pthread_join(balls[i], NULL);

    }
    // pthread_barrier_destroy(&barrier);
  }
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
  else if(key == ' '){
    pause = !pause;
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
