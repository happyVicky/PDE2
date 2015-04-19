#ifndef __OPTION_CPP
#define __OPTION_CPP

#include "option.h"

using namespace std;


Option::Option(double _S, double _K, double _T,
	       double _t, double _r, double _sigma,
	       double _delta) : S(_S), K(_K), T(_T), t(_t), r(_r), sigma(_sigma), delta(_delta) {}

OptionCall::OptionCall(double _S, double _K, double _T,
		       double _t, double _r, double _sigma,
		       double _delta) : Option(_S, _K, _T, _t, _r, _sigma, _delta) {}

double OptionCall::payOff() const {
	return max(0.0,S-K);
}


OptionPut::OptionPut(double _S, double _K, double _T,
		       double _t, double _r, double _sigma,
		       double _delta) : Option(_S, _K, _T, _t, _r, _sigma, _delta) {}


double OptionPut::payOff() const {
	return max(0.0,K-S);
}




#endif
