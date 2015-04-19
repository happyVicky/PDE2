#ifndef __BOUNDARY_H
#define __BOUNDARY_H

#include "boundary.h"
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

class BoundaryBase {
	public:
		double q_delta;
		double x_left;
		double x_right;
		double tau_max;
		double tau_min;
		int x_N;
		int tau_N;
		double dx;
		double dtau;
		double dx_square;
		double lambda;
		vector<double> x_vector;
		vector<double> tau_vector;
		
		BoundaryBase(double _x_left, double _x_right, int _x_N,
			     double _sigma, double _T, int _tau_N, double _q_delta);
		
		~BoundaryBase() {};

		void calculate_x_vector();
		void calculate_tau_vector();
		virtual void calculate_bottom() = 0;
		virtual void calculate_left() = 0;
		virtual void calculate_right() = 0;

};


class BoundaryCall : public BoundaryBase {
	public:
		vector<double> boundary_left;
		vector<double> boundary_right;
		vector<double> boundary_bottom;

		BoundaryCall(double _x_left, double _x_right, int _x_N,
			     double _sigma, double _T, int _tau_N, double _q_delta);
		void calculate_bottom();
		void calculate_left();
		void calculate_right();

};


class BoundaryPut : public BoundaryBase {
	public:
		vector<double> boundary_left;
		vector<double> boundary_right;
		vector<double> boundary_bottom;

		BoundaryPut(double _x_left, double _x_right, int _x_N,
			    double _sigma, double _T, int _tau_N, double _q_delta);
		void calculate_bottom();
		void calculate_left();
		void calculate_right();
};




#endif







