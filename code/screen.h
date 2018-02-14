#include  "ball.h"
#include <pthread.h>
#include <vector>
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define SCREEN_X 500
#define SCREEN_Y 100

GLfloat xRotated = 0.0, yRotated = 0.0, zRotated = 0.0;

ball **b; // double pointer to ball
int num_balls; // number of balls
// pthread_barrier_t barrier; // create pthread barrier

// initialize balls
void initBalls(int n){
  num_balls = n; // assign proper value to global variable
  b = new ball*[n]; // b points to array of pointers
  for(int i = 0 ; i < n ; i++){
    b[i] = new ball(); // allocate memory to each ball
  }
}

// temporary function to debug threads
void* tempDrawBalls(void* ballPtr){
  ball * b = (ball *) ballPtr;
  cout << "Ball created";
  // cout << b->getCenterX();
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

  // update the center of the ball using velocities, detecting collision with the walls
  for(int i = 0 ; i < 3 ; i++){
    if(center[i] <= 1-rad && center[i] >= -1+rad){
      center[i] += vel[i];
    }
    else{
      center[i] -= vel[i];
      vel[i] = -1*vel[i];
    }
  }

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
    // balls have collided
    // udpate their velocities

    // cout << "Balls collide.\n";
    b1->updateVel(b2);
  }
  return ;
}

void drawCube(){

  glMatrixMode(GL_MODELVIEW);

  glClear(GL_COLOR_BUFFER_BIT); // clear the buffer

  vector <pthread_t> balls(num_balls); // create n threads, one for each ball

  vector <int> bRet(num_balls); // to store values returned by each thread

  for(int i = 0 ; i < num_balls ; i ++){
    bRet[i] = pthread_create(&balls[i], NULL, &controlBallWall, (void*)b[i]); // create a thread
    // controlBallWall checks for ball to wall collisions and updates the coordinates

    pthread_join(balls[i], NULL);

  }

  // check for ball to ball collsions and update velocities
  for(int i = 0 ; i < num_balls ; i ++){
    for (int j = i+1; j < num_balls; j++){
      controlBallBall(b[i], b[j]);
    }
  }

  for(int i = 0 ; i < num_balls ; i++){
    drawBall(b[i]);
  }

  glutSwapBuffers();
}
