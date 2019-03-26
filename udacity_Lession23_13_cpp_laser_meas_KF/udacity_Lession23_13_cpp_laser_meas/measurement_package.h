#ifndef MEASUREMENT_PACKAGE_H_
#define MEASUREMENT_PACKAGE_H_
#include "../eigen/Dense"
using Eigen::MatrixXd;
using Eigen::VectorXd;

class MeasurementPackage
{
public:
	enum SensorType
	{
		LASER,
		RADAR
	} sensor_type_;

	VectorXd raw_measurements_;
	int64_t timestamp_;
};

#endif