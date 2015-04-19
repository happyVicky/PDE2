#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include "transform.h"
#include <math.h>


class Transform {
	public:
		double x;
		double tau;
		double q;
		double q_delta;

		Transform(double _S, double _K, double _T,
		  double _t, double _r, double _sigma,
		  double _delta);	//Constructor

		~Transform() {};

};

#endif
