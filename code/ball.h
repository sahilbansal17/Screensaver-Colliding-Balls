#include <iostream>
using namespace std;

class ball{
private:
	float x,y,z; // coordinates for the center
	float r,g,b; // color values
	float vx,vy,vz; // velocities in each direction
	float rad; // radius of the ball
public:
	// constructor
	ball(){
		x = 0.1;
		y = 0.1;
		z = 0.0;
		r = 0.5;
		g = 0.5;
		b = 1.0;
		vx = 0.01;
		vy = -0.005;
		vz = 0.0;
		rad = 0.25;
	}
	// getter functions
	float getRadius(){
		return rad;
	}
	float getCenterX(){
		return x;
	}
	float getCenterY(){
		return y;
	}
	float getCenterZ(){
		return z;
	}
	float getVelX(){
		return vx;
	}
	float getVelY(){
		return vy;
	}
	float getVelZ(){
		return vz;
	}
	float getRed(){
		return r;
	}
	float getBlue(){
		return b;
	}
	float getGreen(){
		return g;
	}
	// setter functions
	void setCenterX(float x_){
		x = x_;
	}
	void setCenterY(float y_){
		y = y_;
	}
	void setCenterZ(float z_){
		z = z_;
	}
	void setVelX(float vx_){
		vx = vx_;
	}
	void setVelY(float vy_){
		vy = vy_;
	}
	void setVelZ(float vz_){
		vz = vz_;
	}
	// printing the center of the ball for testing purpose
	void printCenter(){
		cout << "x-coordinate:" << x << "\n";
		cout << "y-coordinate:" << y << "\n";
		cout << "z-coordinate:" << z << "\n";
	}
};