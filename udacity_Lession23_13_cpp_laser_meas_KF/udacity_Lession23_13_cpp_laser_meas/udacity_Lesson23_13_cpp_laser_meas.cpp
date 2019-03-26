#include <iostream>
#include <sstream>
#include <vector>
#include "../Eigen/Dense"
#include "measurement_package.h"
#include "tracking.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

int main()
{
	/**
	* Set measurement 	
	*/

	// vector definition with class of MeasurementPackage
	vector<MeasurementPackage> measurement_pack_list;
	string in_file_name_ = "obj_pose-laser-radar-synthetic-input.txt";
	ifstream in_file(in_file_name_.c_str(), ifstream::in);

	if (!in_file.is_open())
	{
		cout << "Cannot open input file:" << in_file_name_ << endl;
	}

	string line;

	int i = 0;
	while (getline(in_file, line) && (i <= 3))
	{
		MeasurementPackage meas_package;
		
		istringstream iss(line);
		string sensor_type;
		iss >> sensor_type; // reads first element from the current line
		int64_t timestamp;

		// std::string::compare() returns an int:
		// equal to zero if s and t are equal,

		if (sensor_type.compare("L") == 0)
		{
			meas_package.sensor_type_ = MeasurementPackage::LASER;
			meas_package.raw_measurements_ = VectorXd(2);
			float x;
			float y;
			iss >> x;
			iss >> y;

			meas_package.raw_measurements_ << x, y;
			iss >> timestamp;
			meas_package.timestamp_ = timestamp;
			measurement_pack_list.push_back(meas_package);
		}

		else if (sensor_type.compare("R") == 0) // skip radar measurement
		{
			continue;
		}
		i++;
	}

	// create a tracking class
	Tracking tracking;

	/*
	std::size_t can store the maximum size of a theoretically possible object 
	of any type (including array). 
	A type whose size cannot be represented by std::size_t 
	is ill-formed (since C++14) On many platforms 
	(an exception is systems with segmented addressing) 
	std::size_t can safely store the value of any non-member pointer, 
	in which case it is synonymous with std::uintptr_t.

	std::size_t is commonly used for array indexing and loop counting.
	Programs that use other types, such as unsigned int, 
	for array indexing may fail on, e.g. 64 - bit systems 
	when the index exceeds UINT_MAX or if it relies 
	on 32 - bit modular arithmetic.
	*/

	// call the processingmesurement() function for each measurement 
	size_t N = measurement_pack_list.size();
	// start filtering from the second frame
	// (the speed is unknown in the first time)

	for (size_t k = 0; k < N; ++k)
	{
		tracking.ProcessMeasurement(measurement_pack_list[k]);
	}

	if (in_file.is_open())
	{
		in_file.close();
	}
	return 0;
}