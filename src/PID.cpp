#include <iostream>
#include "PID.h"

/*
* TODO: Complete the PID class.
*/

PID::PID() {
	Init(0, 0, 0);
}

PID::~PID() {}

void PID::Init(double kp_0, double ki_0, double kd_0) {
	Kp = kp_0;
	Ki = ki_0;
	Kd = kd_0;
	p_error = 0;
	i_error = 0;
	d_error = 0;

#ifdef DEBUG_PID
	std::cout << "PID DEBUG Init k_p: " << Kp << ", k_i: " << Ki << ", k_d: " << Kd << std::endl;
#endif

}

void PID::UpdateError(double cte) {
	d_error = cte - p_error;
	p_error = cte;
	i_error = cte + TotalError();
}

double PID::TotalError() {
	return (i_error);
}

