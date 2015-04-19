#ifndef __OPTION_H
#define __OPTION_H

#include "option.h"
#include <algorithm>

class Option {
	public:
		double S;	//Stock price
		double K;	//Strike price
		double T;	//Expiry time
		double t;	//Current time
		double r;	//Interest rate
		double sigma;	//Volatility
		double delta;	//Dividend rate

		Option(double _S, double _K, double _T,
		       double _t, double _r, double _sigma,
		       double _delta);	//Constructor
		virtual ~Option() {};	//Virtual destructor

		virtual double payOff() const = 0;	//Payoff at expiration

};



class OptionCall : public Option {
	public:
		OptionCall(double _S, double _K, double _T,
			   double _t, double _r, double _sigma,
			   double _delta);
		virtual ~OptionCall() {};

		double payOff() const;
};


class OptionPut : public Option{
	public:
		OptionPut(double _S, double _K, double _T,
			  double _t, double _r, double _sigma,
			  double _delta);
		virtual ~OptionPut() {};

		double payOff() const;
};





#endif











