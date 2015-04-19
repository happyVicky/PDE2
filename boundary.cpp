#ifndef __BOUNDARY_CPP
#define __BOUNDARY_CPP

#include "boundary.h"
#include <iostream>
using namespace std;

BoundaryBase::BoundaryBase(double _x_left, double _x_right, int _x_N,
			   double _sigma, double _T, int _tau_N, double _q_delta) {
	q_delta = _q_delta;
	x_left = _x_left;
	x_right = _x_right;
	tau_max = 0.5*_sigma*_sigma*_T;
	tau_min = 0;
	x_N = _x_N;
	tau_N = _tau_N;
	dx = (x_right-x_left)/(x_N-1);
	dtau = (tau_max-tau_min)/(tau_N-1);

/*I have a question here*/
	dx_square = dx*dx+(x_left+x_right)*dx;

	lambda = dtau/(dx_square);
	calculate_x_vector();
	calculate_tau_vector();

/*Check*/
	cout << "check calculation of parameters, esp lambda: " << endl;
	cout << "tau_max: " << tau_max << endl;
	cout << "dx: " << dx << endl;
	cout << "dtau: " << dtau << endl;
	cout << "dx_square: " << dx_square << endl;
	cout << "lambda: " << lambda << endl;
/*Check end*/

}

void BoundaryBase::calculate_x_vector() {
	x_vector.resize(x_N,0.0);
	for (int i = 0; i < x_N; i++) {
		x_vector[i] = x_left+i*dx;
	}
}

void BoundaryBase::calculate_tau_vector() {
	tau_vector.resize(tau_N, 0.0);
	for (int i = 0; i < tau_N; i++) {
		tau_vector[i] = tau_min+i*dtau;
	}
}

BoundaryCall::BoundaryCall(double _x_left, double _x_right, int _x_N,
			   double _sigma, double _T, int _tau_N, double _q_delta) : 
			   BoundaryBase(_x_left, _x_right, _x_N, _sigma,
			   _T, _tau_N, _q_delta) {
	calculate_bottom();
	calculate_left();
	calculate_right();
}


void BoundaryCall::calculate_bottom() {
	boundary_bottom.resize(x_N,0.0);
	for (int i = 0; i < x_N; i++) {
		boundary_bottom[i] = max((exp(0.5*x_vector[i]*(q_delta+1))
				          -exp(0.5*x_vector[i]*(q_delta-1))),0.0);
	}
}


void BoundaryCall::calculate_left() { 
	boundary_left.resize(tau_N,0.0);
	for (int i = 0; i < tau_N; i++) {
		boundary_left[i] = 0;
	}
}


void BoundaryCall::calculate_right() {
	boundary_right.resize(tau_N,0.0);
	for (int i = 0; i < tau_N; i++) {
		boundary_right[i] = exp(0.5*x_right*(q_delta+1)+0.25*tau_vector[i]*(q_delta+1)*(q_delta+1));
	}
}

BoundaryPut::BoundaryPut(double _x_left, double _x_right, int _x_N,
			 double _sigma, double _T, int _tau_N, double _q_delta) : 
			 BoundaryBase(_x_left, _x_right, _x_N, _sigma,
			 _T, _tau_N, _q_delta) {
	calculate_bottom();
	calculate_left();
	calculate_right();
}

void BoundaryPut::calculate_bottom() {
	boundary_bottom.resize(x_N,0.0);
	for (int i = 0; i < x_N; i++) {
		boundary_bottom[i] = max((exp(0.5*x_vector[i]*(q_delta-1))
					  -exp(0.5*x_vector[i]*(q_delta+1))),0.0);
	}
}

void BoundaryPut::calculate_left() {
	boundary_left.resize(tau_N,0.0);
	for (int i = 0; i < tau_N; i++) {
		boundary_left[i] = exp(0.5*x_left*(q_delta-1)+0.25*tau_vector[i]*(q_delta-1)*(q_delta-1));
	}
}



void BoundaryPut::calculate_right() {
	boundary_right.resize(tau_N,0.0);
	for (int i = 0; i < tau_N; i++) {
		boundary_right[i] = 0;
	}
}


#endif

