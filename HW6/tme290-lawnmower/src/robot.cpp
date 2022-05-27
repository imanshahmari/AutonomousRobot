#include "robot.hpp"

Robot::Robot():m_sensorData{},m_pathHistory{}{}

void Robot::PrintFunction(){
	std::cout << "Print" << std::endl;
}

void Robot::set_sensorData(SensorData s){
	m_sensorData = s;	
}

SensorData Robot::get_sensorData(){
	return m_sensorData;
}

void Robot::DecideState(){
	
}
