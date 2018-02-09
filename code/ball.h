#include <iostream>
#include <random>
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
		random_device rd; //non-deterministic engine, to seed mt engine
		mt19937 gen(rd()); //mersenne-twister engine

		// coordiantes for center
		uniform_real_distribution<float> coordinates(-1.0, 1.0); //uniform distribution
		x = coordinates(gen);
		y = coordinates(gen);

		// speed in each direction
		uniform_real_distribution<float> speed(0.0, 0.05); //uniform distribution
		vx = speed(gen);
		vy = speed(gen);

		// color values
		uniform_real_distribution<float> colors(0.0, 1.0); //uniform distribution
		r = colors(gen);
		g = colors(gen);
		b = colors(gen);

		// radius
		rad = 0.1;

		// working in 2d
		z = 0.0;
		vz = 0.0;
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
