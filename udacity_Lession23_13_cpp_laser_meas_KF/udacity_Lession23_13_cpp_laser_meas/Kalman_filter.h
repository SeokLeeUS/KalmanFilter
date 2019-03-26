#ifndef KALMAN_FILTER_H_
#define KALMAN_FILTER_H_

#include "../Eigen/Dense"

using Eigen::MatrixXd;
using Eigen::VectorXd;

class KalmanFilter{
public:


	KalmanFilter();

	virtual ~KalmanFilter();

	void Predict();

	void Update(const VectorXd &z);

	VectorXd x_;
	MatrixXd P_;
	MatrixXd F_;
	MatrixXd Q_;
	MatrixXd H_;
	MatrixXd R_;
};

#endif