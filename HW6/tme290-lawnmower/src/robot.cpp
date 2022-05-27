#include "robot.hpp"

//Parameters to tune
float sensitivity = 0.1f;


Robot::Robot():m_sensorData{},m_pathHistory{}{}


int Robot::stay(){
	if (isGrassLow(0,sensitivity) == true){
		return -1;
	}
	else{

		return 0;
	}
}



int Robot::cutHorizontallyRight(){
		if (isGrassLow(4,sensitivity) == true){
		return -1;
	}
	else{
		std::pair<uint32_t,uint32_t> coordinate1;
		coordinate1.first = m_sensorData.i + 1;
		coordinate1.second = m_sensorData.j;
		m_pathHistory.push_back(coordinate1);

		return 4;
	}	
}



/*
int Robot::cutVerticallyDown(){
		if ((isGrassLow(6,sensitivity) == true) || isWall() ){
		return -1;
	}
	else{
		std::pair<uint32_t,uint32_t> coordinate2;
		coordinate2.first = m_sensorData.i;
		coordinate2.second = m_sensorData.j +1;
		m_pathHistory.push_back(coordinate2);

		return 6;
	}	
}
*/

bool Robot::isRain(){
	if(m_sensorData.rain <= 0.001f){
		return false;
	} 
	else{
		return true;
	}
}

/*
bool Robot::isWall(){
	std::cout << "error is wall" << std::endl;
	if(m_pathHistory.end()[-1].first == m_pathHistory.end()[-2].first && m_pathHistory.end()[-1].second == m_pathHistory.end()[-2].second){
		return true;
	} 
	else{
		return false;
	}
}
*/

bool Robot::isGrassLow(int action,float sensitivitet){
	bool result = true;
	switch (action) {
	  case 0:
		result = (m_sensorData.grassCentre < sensitivitet) ? (true) : (false);
	  	break;
	  case 1:
		result = (m_sensorData.grassTopLeft < sensitivitet) ? (true) : (false);
	  	break;
	  case 2:
		result = (m_sensorData.grassTopCentre < sensitivitet) ? (true) : (false);
	  	break;
	  case 3:
		result = (m_sensorData.grassTopRight < sensitivitet) ? (true) : (false);
	  	break;
	  case 4:
		result = (m_sensorData.grassRight < sensitivitet) ? (true) : (false);
	  	break;
	  case 5:
		result = (m_sensorData.grassBottomRight < sensitivitet) ? (true) : (false);
	  	break;
	  case 6:
		result = (m_sensorData.grassBottomCentre < sensitivitet) ? (true) : (false);
	  	break;
	  case 7:
		result = (m_sensorData.grassBottomLeft < sensitivitet) ? (true) : (false);
	  	break;
	  case 8:
		result = (m_sensorData.grassLeft < sensitivitet) ? (true) : (false);
	  	break;
	}
	return result;
}



void Robot::set_sensorData(SensorData s){
	m_sensorData = s;	
}

SensorData Robot::get_sensorData(){
	return m_sensorData;
}


int Robot::decideAction(){
	int actionToTake = stay();

	//actionToTake = cutVerticallyDown();
	actionToTake = cutHorizontallyRight();
	std::cout <<"Action number:"<< actionToTake<< std::endl;

	if (actionToTake != -1){
		return actionToTake;
	}
	else{
		return 0;
	}
}
