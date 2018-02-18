#include  "ball.h"
#include "pthread_barrier.h"
#include "terrain.h"
#include <vector>
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define SCREEN_X 500
#define SCREEN_Y 100

// GLfloat xRotated = 0.0, yRotated = 0.0, zRotated = 0.0;

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
  // b[0] = new ball(0.5, 0, 0, 0.1, 0, 0);
  // b[1] = new ball(0.1, 0, 0, 0.0, 0, 0);
  // b[2] = new ball(-0.5, 0, 0, 0.0, 0, 0);
  // b[3] = new ball(0.9, 0, 0, 0.0, 0, 0);
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
    // balls have collided
    // udpate their velocities

    // cout << "Balls collide.\n";
    // cout << "Intial:\n";
    // vector <float> c1 = b1->getCenter(), c2 = b2->getCenter();
    // vector <float> u1 = b1->getVel(), u2 = b2->getVel();
    // for(int i = 0 ; i < 2 ; i ++){
    //   cout << "x_1_" << i << " " << c1[i] << "\n";
    //   cout << "x_2_" << i << " " << c2[i] << "\n";
    //   cout << "u_1_" << i << " " << u1[i] << "\n";
    //   cout << "u_2_" << i << " " << u2[i] << "\n";
    // }

    b1->updateVel(b2);

    // cout << "Final:\n";
    // vector <float> v1 = b1->getVel(), v2 = b2->getVel();
    // for(int i = 0 ; i < 3 ; i ++){
    //   cout << "v_1_" << i << " " << v1[i] << "\n";
    //   cout << "v_2_" << i << " " << v2[i] << "\n";
    // }
  }
  return ;
}

void drawCube(){
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the buffer

  // glMatrixMode(GL_MODELVIEW);
  
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
}
