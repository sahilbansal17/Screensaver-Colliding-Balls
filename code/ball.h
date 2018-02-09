#include <iostream>
using namespace std;

class ball{
private:
	float x,y,z; // coordinates for the center
	float r,g,b; // color values
	float vx,vy,vz;
	float rad;
public:
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
		rad = 0.9;
	}
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
	void setCenterX(float x_){
		x = x_;
	}
	void setCenterY(float y_){
		y = y_;
	}
	void setCenterZ(float z_){
		z = z_;
	}
	void printCenter(){
		cout << "x-coordinate:" << x << "\n";
		cout << "y-coordinate:" << y << "\n";
		cout << "z-coordinate:" << z << "\n";
	}


};