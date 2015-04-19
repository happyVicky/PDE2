#ifndef __CALCULATE_CPP
#define __CALCULATE_CPP

#include "calculate.h"
#include <iostream>

using namespace std;

FDMBase::FDMBase(double _lambda, vector<double> _boundary_bottom,
		 vector<double> _boundary_left, vector<double> _boundary_right,
		 double _x_object, double _tau_object,
		 double _dx,  int _x_N, double _dtau, double _x_left) : 
		 lambda(_lambda), boundary_bottom(_boundary_bottom), boundary_left(_boundary_left),
		 boundary_right(_boundary_right), x_object(_x_object), tau_object(_tau_object),
		 dx(_dx), x_N(_x_N), dtau(_dtau) ,x_left(_x_left){
	steps = (int)(_tau_object/_dtau);
	x_index = (int)((_x_object-_x_left)/_dx-1);

}



explicitMethod::explicitMethod(double _lambda, vector<double> _boundary_bottom,
		 vector<double> _boundary_left, vector<double> _boundary_right,
		 double _x_object, double _tau_object,
		 double _dx,  int _x_N, double _dtau, double _x_left) :
		 FDMBase(_lambda, _boundary_bottom, _boundary_left,
			 _boundary_right, _x_object, _tau_object,
			 _dx, _x_N, _dtau, _x_left) {
	int row = x_N-2;
	int col = x_N-2;
	A.resize(row);
	for(int i = 0; i < col; i++) {
		A[i].resize(col,0.0);
	}
	for(int i = 0; i < row; i++) {
		A[i][i] = 1-2*lambda;
	}
	for(int i = 0; i < row-1; i++) {
		A[i][i+1] = lambda;
		A[i+1][i] = lambda;
	}
	vector<double>::iterator it;
	it = boundary_bottom.begin()+1;
	w_new.assign(it, boundary_bottom.end()-1); 

/*Check*/
        cout << "before cal: Print the whole level (exp): " << endl;
        for (int i = 0; i < row; i++)
                cout << "w_new[" << i << "]: " << w_new[i] << endl;
/*Check end*/

	d.resize(row,0.0);
//	for (int j = 0; j < steps; j++) {
	for (int j = 0; j < 1; j++) {
		d[0] = lambda*boundary_left[j];
		d[row-1] = lambda*boundary_right[j];
		w_old = w_new;
		calculate_vector_ex();
	}
	result = w_new[x_index];
//	result = w_new[2];

/*Check*/
	cout << "Print the whole level (exp): " << endl;
	for (int i = 0; i < row; i++) {
		cout << "w_new[" << i << "]: " << w_new[i] << endl;
/*Check end*/

	}
}

//A, w_old, d -> w_new

void explicitMethod::calculate_vector_ex() {
	int row = x_N-2;
	int col = x_N-2;
	double element = 0;
	double w_element;
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < row; j++) {
			element = element+A[i][j]*w_old[j];
		}
		w_element = element+d[i];
		w_new[i] = w_element;
		element = 0;
	}
}


implicitMethod::implicitMethod(double _lambda, vector<double> _boundary_bottom,
		vector<double> _boundary_left, vector<double> _boundary_right,
		double _x_object, double _tau_object,
		double _dx,  int _x_N, double _dtau, double _x_left) :
		FDMBase(_lambda, _boundary_bottom, _boundary_left,
			_boundary_right, _x_object, _tau_object,
			_dx, _x_N, _dtau, _x_left) {
	int row = x_N-2;	
	int col = x_N-2;
	B.resize(row);
	for(int i = 0; i < col; i++) {
		B[i].resize(col,0.0);
	}
	for(int i = 0; i < row; i++) {
		B[i][i] = 1+2*lambda;
	}
	for(int i = 0; i < row-1; i++) {
		B[i][i+1] = -lambda;
		B[i+1][i] = -lambda;
	}

	vector<double>::iterator it;
	it = boundary_bottom.begin()+1;
	w_new.assign(it, boundary_bottom.end()-1);

/*Check*/
        cout << "before cal: Print the whole level (imp): " << endl;
        for (int i = 0; i < row; i++)
                cout << "w_new[" << i << "]: " << w_new[i] << endl;
/*Check end*/

	d.resize(row,0.0);
//	for (int j = 0; j < steps; j++) {
	for (int j = 0; j < 1; j++) {
		d[0] = lambda*boundary_left[j+1];
		d[row-1] = lambda*boundary_right[j+1];
		w_old = w_new;
		calculate_vector_im();
	}

	result = w_new[x_index];
//	result = w_new[2];

/*Check*/
        cout << "after cal: Print the whole level (imp): " << endl;
        for (int i = 0; i < row; i++) 
                cout << "w_new[" << i << "]: " << w_new[i] << endl;
/*Check end*/

}



//A, w_old, d -> w_new

void implicitMethod::calculate_vector_im() {
	vector<vector<double> > B_copy;
	B_copy = B;

	int row = x_N-2;
	vector<double> wd;
	wd.resize(row);
	double factor;
	for(int i = 0; i < row; i++) {
		wd[i] = w_old[i]+d[i];
	}
	for(int j = 0; j < row-1; j++) {
		factor = B[j+1][j]/B[j][j];
		for(int k = j; k < j+3; k++) {
			B[j+1][k] = B[j+1][k]-B[j][k]*factor;
		}
		wd[j+1] = wd[j+1]-wd[j]*factor;
	}



	for(int j = 0; j < row; j++) {
		factor = B[j][j];
		for(int k = j; k < j+2; k++) {
			B[j][k]=B[j][k]/factor;
		}
		wd[j] = wd[j]/factor;
	}

	for(int i = row-1; i > 0; i--) {
		factor = B[i-1][i];
		B[i-1][i] = 0;
		wd[i-1] = wd[i-1]-wd[i]*factor;
	}
	for(int i = 0; i < row; i++) {
		w_new[i] = wd[i];
	}

	B = B_copy;
}


CNMethod::CNMethod(double _lambda, vector<double> _boundary_bottom,
		   vector<double> _boundary_left, vector<double> _boundary_right,
		   double _x_object, double _tau_object,
		   double _dx,  int _x_N, double _dtau, double _x_left) :
		   FDMBase(_lambda, _boundary_bottom, _boundary_left,
			   _boundary_right, _x_object, _tau_object,
			   _dx, _x_N, _dtau, _x_left) {
	int row = x_N-2;
	int col = x_N-2;
	A.resize(row);
	for(int i = 0; i < row; i++) {
		A[i].resize(col,0.0);
	}
	for(int i = 0; i < row; i++) {
		A[i][i] = 1-lambda;
	}
	for(int i = 0; i < row; i++) {
		A[i][i+1] = 0.5*lambda;
		A[i+1][i] = 0.5*lambda;
	}

	B.resize(row);
	for(int i = 0; i < row; i++) {
		B[i].resize(col,0.0);
	}
	for(int i = 0; i < row; i++) {
		B[i][i] = 1+lambda;
	}
	for(int i = 0; i < row; i++) {
		B[i][i+1] = -0.5*lambda;
		B[i+1][i] = -0.5*lambda;
	}

	vector<double>::iterator it;
	it = boundary_bottom.begin()+1;
	w_new.assign(it, boundary_bottom.end()-1);
	d.resize(row,0.0);
	for (int j = 0; j < steps; j++) {
		d[0] = 0.5*lambda*(boundary_left[j]+boundary_left[j+1]);
		d[row-1] = 0.5*lambda*(boundary_right[j]+boundary_right[j+1]);
		w_old = w_new;
		calculate_vector_CN();
        }

	result = w_new[x_index];

}

//A, B, w_old, d -> w_new

void CNMethod::calculate_vector_CN() {
	int row = x_N-2;
	int col = x_N-2;
	double element = 0;
	double wd_element;
	vector<double> wd;
	double factor;

	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			element = element+A[i][j]*w_old[j];
		}
		wd_element = element+d[i];
		wd.push_back(wd_element);
		element = 0;
	}

	for(int j = 0; j < row-1; j++) {
		factor = B[j+1][j]/B[j][j];
		for(int k = j; k < j+3; k++) {
			B[j+1][k] = B[j+1][k]-B[j][k]*factor;
		}
		wd[j+1] = wd[j+1]-wd[j]*factor;
	}

	for(int j = 0; j < row; j++) {
		for(int k = j; k < j+2; k++) {
			B[j][k]=B[j][k]/B[j][j];
		}
		wd[j] = wd[j]/B[j][j];
	}

	for(int i = row-1; i > 0; i--) {
		factor = B[i-1][i];
		B[i-1][i] = 0;
		wd[i-1] = wd[i-1]-wd[i]*factor;
	}

	for(int i = 0; i < row; i++) {
		w_new[i] = wd[i];
	}

}


#endif
