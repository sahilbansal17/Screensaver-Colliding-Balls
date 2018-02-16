#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "screen.h"

void init(void){
  // initialize projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // initialize modelview matrix
  glLoadIdentity();
  // initialize clear color
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // R, G, B, Alpha
}

void reshape(int x, int y){
    if (y == 0 || x == 0) return;  // empty screen

    // glMatrixMode(GL_PROJECTION);
    // angle of view: 45 degrees
    // near clipping plane distance: 0.0
    // far clipping plane distance: 1000.0
    // gluPerspective(60.0, (GLdouble)x/(GLdouble)y, 0.0, 1000.0);

    // glMatrixMode(GL_MODELVIEW);

    glViewport(0, 0, x, y);  // use the whole window for rendering, 0, 0 specify the lower left side
}

int main(int argc, char** argv){

  int n; // number of balls

  cin >> n;

  initBalls(n); // initialize the properties of all the balls

  glutInit(&argc, argv); // initialize glut

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // create double buffer window

  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(SCREEN_X,SCREEN_Y);
  glutCreateWindow("ScreenSaver Colliding Balls");
  // glutFullScreen(); // make the window full screen

  init(); // post window/context creation initialization

  glutDisplayFunc(drawCube); // set rendering function

  glutReshapeFunc(reshape); // set reshape function

  glutIdleFunc(drawCube); // runs this function continuously

  glutMainLoop(); // start glut main loop

  return 0;
}
