#include  "ball.h"
#include  "terrain.h"
#include  "pthread_barrier.h"
#include <vector>
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define SCREEN_X 500
#define SCREEN_Y 100
#define eps 10e-3
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

void controlBallTerrain(ball *b){
    // assuming one terrain object

    vector <float> center = b->getCenter();
    vector <float> vel = b->getVel();
    float rad = b->getRadius();
    // check whether distance from center of ball is less than or equal to terrain line

    // find normal vector to the line
    vector <float> p1(3), p2(3);
    p1[0] = -0.5; p1[1] = -0.5;
    p2[0] = -1.0; p2[1] = -1.0;
    p1[2] = 0.0; p2[2] = 0.0;

    vector <float> line = diff(p1, p2);
    vector <float> norm = RnormalToLine(line);
    float norm_mag = mag(norm);
    float dist_check = dotProd(diff(center, p1), norm)/norm_mag;

    // approach 3 - region of collision is fixed
    // cout << check << "\n";

    if(abs(dist_check) <= rad){
      float speed = mag(vel);

      // check whether in the range of the line segment
      float projOnLine = dotProd(diff(p1, center), line);
      if(projOnLine < 0){
        return;
      }

      float init_speed = mag(vel);
      // cout << init_speed << " ";

      // 1st approach - more tedious
      // float cos_angle = dotProd(vel, norm)/(speed*mag(norm));
      // cout << cos_angle << " ";
      // float sin_angle = sqrt(1 - pow(cos_angle, 2));
      // now the new velocity is simply rotating the initial vector by 180 - 2*angle

      // changing the approach
      // find the velocity vector along the normal
      vector <float> v_n = mulConst(norm, dotProd(vel, norm)/norm_mag);

      // final velocity is simply velocity - 2*v_n
      vector <float> f_v = add(vel, mulConst(v_n, -2.0));

      // to maintain same speed of the ball (lost due to less precision of float)
      float final_speed = mag(f_v);
      f_v = mulConst(f_v, init_speed/final_speed);

      // final_speed = mag(f_v);
      // cout << final_speed << "\n";

      // cout << f_v[0] << " " << f_v[1] << " " << f_v[2] << "\n";
      // b->setVel(0, 0, 0);

      // change the velocity
      b->setVel(f_v[0], f_v[1], f_v[2]);

      // set the center so that ball do not stick to triangle
      vector <float> c_new = add(center, mulConst(mulConst(norm, 1/norm_mag), 0.001+rad-dist_check));
      b->setCenter(c_new[0], c_new[1], c_new[2]);
      return;
    }

    // checking with the second side of the triangle
    p1[0] = -0.5; p1[1] = -0.5;
    p2[0] = 0.0; p2[1] = -1.0;
    p1[2] = 0.0; p2[2] = 0.0;

    line = diff(p1, p2);
    norm = LnormalToLine(line);
    norm_mag = mag(norm);
    dist_check = dotProd(diff(center, p1), norm)/norm_mag;

    if(abs(dist_check) <= rad){
      float speed = mag(vel);

      float projOnLine = dotProd(diff(p1, center), line);
      if(projOnLine < 0){
        return;
      }

      float init_speed = mag(vel);

      vector <float> v_n = mulConst(norm, dotProd(vel, norm)/norm_mag);

      vector <float> f_v = add(vel, mulConst(v_n, -2.0));

      float final_speed = mag(f_v);
      f_v = mulConst(f_v, init_speed/final_speed);

      b->setVel(f_v[0], f_v[1], f_v[2]);

      vector <float> c_new = add(center, mulConst(mulConst(norm, 1/norm_mag), rad-dist_check));
      b->setCenter(c_new[0], c_new[1], c_new[2]);
    }
}

void drawCube(){

  glClear(GL_COLOR_BUFFER_BIT); // clear the buffer

  glLoadIdentity();

  drawTerrain();

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
    controlBallTerrain(b[i]);
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
