#include <iostream>
#include <random>
#include <vector>
#include "physics.h"
using namespace std;

class ball{
private:
	vector <float> center; // coordinates for the center
	vector <float> color; // color values
	vector <float> vel; // velocities in each direction
	float rad; // radius of the ball
public:
	// constructor
	ball(){
		center = vector <float> (3);
		color = vector <float> (3);
		vel = vector <float> (3);

		random_device rd; //non-deterministic engine, to seed mt engine
		mt19937 gen(rd()); //mersenne-twister engine

		// coordiantes for center
		uniform_real_distribution<float> coordinates(-1.0, 1.0); //uniform distribution
		for (int i = 0 ; i < 3 ; i ++){
			center[i] = coordinates(gen);
		}

		// speed in each direction
		uniform_real_distribution<float> speed(0.0, 0.05); //uniform distribution
		for (int i = 0 ; i < 3 ; i ++){
			vel[i] = speed(gen);
		}

		// vel[1] = 0 ; // for debugging
		// center[1] = 0.5; // for debugging

		// color values
		uniform_real_distribution<float> colors(0.0, 1.0); //uniform distribution
		for (int i = 0 ; i < 3 ; i ++){
			color[i] = colors(gen);
		}

		// radius
		rad = 0.1;

		// working in 2d
		center[2] = 0.0;
		vel[2] = 0.0;

		// to make sure that ball does not go beyond the boundaries initially (2d boundary)
		for(int i = 0 ; i < 2 ; i++){
			if(center[i] > 1-rad){
				center[i] = 1 - rad;
			}
			else if(center[i] < -1+rad){
				center[i] = -1 + rad;
			}
		}
	}

	ball(float x1, float y1, float z1, float vx, float vy, float vz){
		center = vector <float> (3);
		color = vector <float> (3);
		vel = vector <float> (3);
		center[0] = x1;
		center[1] = y1;
		center[2] = z1;
		vel[0] = vx;
		vel[1] = vy;
		vel[2] = vz;
		random_device rd; //non-deterministic engine, to seed mt engine
		mt19937 gen(rd()); //mersenne-twister engine
		uniform_real_distribution<float> colors(0.0, 1.0); //uniform distribution
		for (int i = 0 ; i < 3 ; i ++){
			color[i] = colors(gen);
		}
		// radius
		rad = 0.1;
	}
	// getter functions
	float getRadius(){
		return rad;
	}
	vector <float> getCenter(){
		return center;
	}
	vector <float> getVel(){
		return vel;
	}
	vector <float> getColor(){
		return color;
	}
	// setter functions
	void setCenter(float x_, float y_, float z_){
		center[0] = x_;
		center[1] = y_;
		center[2] = z_;
	}
	void setVel(float vx_, float vy_, float vz_){
		vel[0] = vx_;
		vel[1] = vy_;
		vel[2] = vz_;
	}
	// printing the center of the ball for testing purpose
	void printCenter(){
		cout << "x-coordinate:" << center[0] << "\n";
		cout << "y-coordinate:" << center[1] << "\n";
		cout << "z-coordinate:" << center[2] << "\n";
	}

	// checking whether ball to ball collision has occurred
	bool checkBallBall(ball* b2){
		// get coordinates of calling ball b1
		vector <float> c1 = center;
		// get coordinates of ball b2
		vector <float> c2 = b2->getCenter();

		float rad_check = rad + b2->getRadius(); // currently same => 0.1 + 0.1 = 0.2
		if(centerToCenter(c1, c2) == rad_check){
			return 1;
		}
		else if(centerToCenter(c1, c2) < rad_check){
			// need to make sure that c1c2 = r1 + r2 so that balls do not stick together after the position gets updated next time

			vector <float> cn = getCommonNormal(c1, c2);
			c2 = diff(c1, mulConst(cn, rad_check));

			// c2[2] += 0.0001;
			b2->setCenter(c2[0], c2[1], c2[2]);

			return 1;
		}
		return 0;
	}

	void updateVel(ball* b2){
		// get the vectors r1 and r2
		vector <float> r1 = center;
		vector <float> r2 = b2->getCenter();
		// get the velocities
		vector <float> u1 = vel;
		vector <float> u2 = b2->getVel();
		// common normal of r1,r2
		vector <float> cn = getCommonNormal(r1, r2);

		// assuming m1 = m2
		// v1 = u1 - ((u1 - u2).cn)cn
		// v2 = u2 - ((u2 - u1).cn)cn
		vector <float> u1u2 = diff(u1, u2);
		vector <float> u2u1 = diff(u2, u1);
		float u1Mul = dotProd(u1u2, cn);
		float u2Mul = dotProd(u2u1, cn);
		vector <float> u1Add = mulConst(cn, u1Mul);
		vector <float> u2Add = mulConst(cn, u2Mul);
		vector <float> v1 = diff(u1, u1Add);
		vector <float> v2 = diff(u2, u2Add);

		// update velocities
		vel = v1;
		b2->setVel(v2[0], v2[1], v2[2]);
	}
};
