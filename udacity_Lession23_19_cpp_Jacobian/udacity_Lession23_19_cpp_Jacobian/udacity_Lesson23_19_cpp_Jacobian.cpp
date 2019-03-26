#include <iostream>
#include <vector>
#include "../eigen/Dense"

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::cout;
using std::endl;

MatrixXd CalculateJacobian(const VectorXd & x_state);

int main()
{
	VectorXd x_predicted(4);
	x_predicted << 1, 2, 0.2, 0.4;
	MatrixXd Hj = CalculateJacobian(x_predicted);
	cout << "Hj:" << endl << Hj << endl;

	return 0;
}

MatrixXd CalculateJacobian(const VectorXd & x_state)
{
	MatrixXd Hj(3, 4);

	float px = x_state(0);
	float py = x_state(1);
	float vx = x_state(2);
	float vy = x_state(3);

	float pxy_sq = px*px + py*py;
	float pxy_sq_rt = sqrt(pxy_sq);
	float pxy_sq_cb = pow(pxy_sq, 3);
	float pxy_sq_cb_rt = pow(pxy_sq, 3 / 2);

	
	/*
	if (px == 0 && py == 0)
	{
		Hj << 0, 0, 0,
			0, 0, 0,
			0, 0, 0;
	}
	*/
	
	if (fabs(pxy_sq) < 0.0001)
		return Hj;

	/*
	https://www.cprogramming.com/fod/fabs.html
	Prototype: double fabs(double number);
	Header File: math.h (C) or cmath (C++)
	Explanation: This function returns the absolute value of 
	a number. It will not truncate the decimal like abs() will, 
	so it is better for certain calculations.
	*/
	else
	{

		Hj << px / pxy_sq_rt, py / pxy_sq_rt, 0, 0,
			-py / pxy_sq, px / pxy_sq, 0, 0,
			py*(vx*py - vy*px) / pxy_sq_cb_rt, px*(vy*px - vx*py) / pxy_sq_cb_rt, px / pxy_sq_rt, py / pxy_sq_rt;
	}

	return Hj;
}

