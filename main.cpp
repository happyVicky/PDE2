#include "option.h"
#include "transform.h"
#include "boundary.h"
#include "calculate.h"

#include <iostream>
using namespace std;


int main(int argc, char** argv) {
	double S = 100;
	double K = 100;
	double T = 1;
	double t = 0;
	double r = 0.2;
	double sigma = 0.3;
	double delta = 0.1;

	cout << "test option" << endl;
	OptionCall call(S,K,T,t,r,sigma,delta);
	cout << call.S << endl;
	cout << call.K << endl;
	cout << call.T << endl;
	cout << call.t << endl;
	cout << call.r << endl;
	cout << call.sigma << endl;
	cout << call.delta << endl;
	cout << call.payOff() << endl;

	cout << "test transform" << endl;
	Transform tran(S,K,T,t,r,sigma,delta);
	cout << tran.x << endl;
	cout << tran.tau << endl;
	cout << tran.q << endl;
	cout << tran.q_delta << endl;

	cout << "test boundary" << endl;
	double q_delta = tran.q_delta;
	double x_left = -0.1;
	double x_right = 0.1;
	int x_N = 55;
	int tau_N = 15;
	BoundaryCall bdcall(x_left, x_right, x_N, sigma, T, tau_N, q_delta);
	cout << "x vector" << endl;
	for (int i = 0; i < x_N; i++)
		cout << bdcall.x_vector[i] << endl;
	cout << "tau vector" << endl;
	for (int i = 0; i < tau_N; i++)
		cout << bdcall.tau_vector[i] << endl;

	cout << "boundary left" << endl;
	for (int i = 0; i < tau_N; i++)
		cout << bdcall.boundary_left[i] << endl;
	cout << "boundary right" << endl;
        for (int i = 0; i < tau_N; i++)
                cout << bdcall.boundary_right[i] << endl;
	cout << "boundary bottom" << endl;
        for (int i = 0; i < x_N; i++)
                cout << bdcall.boundary_bottom[i] << endl;

	cout << "test calcualte" << endl;
	double x_object = 0.05;
	double tau_object = 0.02;

	explicitMethod exp(bdcall.lambda, bdcall.boundary_bottom, bdcall.boundary_left,
			   bdcall.boundary_right, x_object, tau_object, bdcall.dx,
			   bdcall.x_N, bdcall.dtau, bdcall.x_left);

        implicitMethod imp(bdcall.lambda, bdcall.boundary_bottom, bdcall.boundary_left,
                           bdcall.boundary_right, x_object, tau_object, bdcall.dx,
                           bdcall.x_N, bdcall.dtau, bdcall.x_left);
/*
        CNMethod CN(bdcall.lambda, bdcall.boundary_bottom, bdcall.boundary_left,
                           bdcall.boundary_right, x_object, tau_object, bdcall.dx,
                           bdcall.x_N, bdcall.dtau, bdcall.x_left);
*/
	cout << "exp: " << endl;
	cout << exp.result << endl;

	cout << "imp: " << endl;
	cout << imp.result << endl;


//	cout << CN.result << endl;

	return 0;
}





