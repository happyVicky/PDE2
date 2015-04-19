#ifndef __TRANSFORM_CPP
#define __TRANSFORM_CPP

#include "transform.h"

Transform::Transform(double _S, double _K, double _T, double _t,
		     double _r, double _sigma, double _delta) {
	x = log(_S/_K);
	tau = 0.5*_sigma*_sigma*(_T-_t);
	q = 2*_r/(_sigma*_sigma);
	q_delta = 2*(_r-_delta)/(_sigma*_sigma);

}

#endif
