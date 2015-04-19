#ifndef __CALCULATE_H
#define __CALCULATE_H

#include "calculate.h"
#include <vector>
#include <math.h>
#include <assert.h>

using namespace std;

class FDMBase {
	public:
		double lambda;
		vector<double> boundary_bottom;
		vector<double> boundary_left;
		vector<double> boundary_right;
		double x_object;
		double tau_object;
		double dx;
		int x_N;
		double dtau;
		double x_left;
		int steps;	//i.e. tau_index
		int x_index;	
			
		FDMBase(double _lambda, vector<double> _boundary_bottom,
			vector<double> _boundary_left, vector<double> _boundary_right,
			double _x_object, double _tau_object,
			double _dx,  int _x_N, double _dtau, double _x_left);


};

class explicitMethod : public FDMBase {
	public:
		vector<double> w_new;
		vector<double> w_old;
		vector<double> d;
		vector<vector<double> > A;
		double result;
		explicitMethod(double _lambda, vector<double> _boundary_bottom,
			       vector<double> _boundary_left, vector<double> _boundary_right,
			       double _x_object, double _tau_object,
			       double _dx,  int _x_N, double _dtau, double _x_left);

		void calculate_vector_ex();
};

class implicitMethod : public FDMBase {
	public:
		vector<double> w_new;
		vector<double> w_old;
		vector<double> d;
		vector<vector<double> > B;
		double result;
		implicitMethod(double _lambda, vector<double> _boundary_bottom,
			       vector<double> _boundary_left, vector<double> _boundary_right,
			       double _x_object, double _tau_object,
			       double _dx,  int _x_N, double _dtau, double _x_left);

		void calculate_vector_im();
};

class CNMethod : public FDMBase {
	public:
		vector<double> w_new;
		vector<double> w_old;
		vector<double> d;
		vector<vector<double> > A;
		vector<vector<double> > B;
		double result;
		CNMethod(double _lambda, vector<double> _boundary_bottom,
			 vector<double> _boundary_left, vector<double> _boundary_right,
			 double _x_object, double _tau_object,
			 double _dx,  int _x_N, double _dtau, double _x_left);
		
		void calculate_vector_CN();

};



#endif
