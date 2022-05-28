#include "robot.hpp"

//Parameters to tune
float sensitivity = 0.1f;
float batteryThresh = 0.25f;
float batteryFull = 0.99f;
bool m_findBackState = false;



Robot::Robot():m_sensorData{},m_pathBack{},m_findBackState{}{}


int Robot::stay(){
	if (isGrassLow(0,sensitivity) == true){
		return -1;
	}
	else{
		return 0;
	}
}


int Robot::cutHorizontallyRight(){
		if ((isGrassLow(4,sensitivity) == true) || (isWall(4) == true)){
		return -1;
	}
	else{return 4;}	
}




int Robot::cutVerticallyDown(){
		if ((isGrassLow(6,sensitivity) == true) || (isWall(6) == true) ){
		return -1;
	}
	else{return 6;}	
}


int Robot::backToCharge(){

	if(m_sensorData.j < 17){
		if(isWall(1) == false){return 1;}
		else if(isWall(1) == true && isWall(2) == false){return 2;}
		else if(isWall(1) == true && isWall(2) == true && isWall(8) == false){return 8;}
	}

	else if(m_sensorData.j >=17 && m_sensorData.i > 22){
		return 2;
	}

	else if(m_sensorData.j >=17 && m_sensorData.i < 22){
		if(isWall(3) == false){return 3;}
		else if(isWall(3) == true && isWall(2) == false){return 2;}
		else if(isWall(3) == true && isWall(2) == true && isWall(4) == false){return 4;}
	}
	else if (m_sensorData.j == 0 && m_sensorData.i == 0){
		return -1;
	}
	return 0;
}


int Robot::continueFromLast(){
	int lastElement = m_pathBack.back();
	
	if (lastElement == 1){
		m_pathBack.pop_back();
		return 5;
	}
	else if(lastElement == 2){
		m_pathBack.pop_back();
		return 6;
	}
	else if(lastElement == 8){
		m_pathBack.pop_back();
		return 4;
	}
	else if(lastElement == 3){
		m_pathBack.pop_back();
		return 7;
	}
	else if(lastElement == 4){
		m_pathBack.pop_back();
		return 8;
	}
	return -1;
}




bool Robot::isRain(){
	if(m_sensorData.rain <= 0.001f){
		return false;
	} 
	else{
		return true;
	}
}

bool Robot::isBatteryLow(){
	if(m_sensorData.battery <= batteryThresh){
		return true;
	} 
	else{
		return false;
	}
}

bool Robot::isBatteryFull(){
	if(m_sensorData.battery >= batteryFull){
		return true;
	} 
	else{
		return false;
	}
}


bool Robot::isWall(int action){
	bool result = false;

		switch (action) {
	  case 0:
		result = false;
	  	break;
	  case 1:
		if (m_sensorData.i == 0 || m_sensorData.j == 0 || (m_sensorData.j== 18 && m_sensorData.i <= 23)){
			result = true;
		}
	  	break;
	  case 2:
		if (m_sensorData.j == 0 || (m_sensorData.j == 18 && m_sensorData.i <= 22)){
			result = true;
		}
	  	break;
	  case 3:
		if (m_sensorData.i == 39 || m_sensorData.j == 0 || (m_sensorData.j== 18 && m_sensorData.i <= 21)){
			result = true;
		}
	  	break;
	  case 4:
		if (m_sensorData.i == 39){
			result = true;
		}
	  	break;
	  case 5:
		if (m_sensorData.i == 39 || m_sensorData.j ==39 || (m_sensorData.j== 16 && m_sensorData.i <= 21)){
			result = true;
		}
	  	break;
	  case 6:
		if (m_sensorData.j ==39 || (m_sensorData.j== 16 && m_sensorData.i <= 22)){
			result = true;
		}
	  	break;
	  case 7:
		if (m_sensorData.i == 0 || m_sensorData.j ==39 || (m_sensorData.j== 16 && m_sensorData.i <= 23)){
			result = true;
		}
	  	break;
	  case 8:
		if (m_sensorData.i == 0 || (m_sensorData.j== 16 && m_sensorData.i <= 23)){
			result = true;
		}
	  	break;
	}
	return result;

}


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
	int actionToTake = 0;

	int state1 = stay();
	int state2 = cutHorizontallyRight();
	int state3 = cutVerticallyDown();
	int state4 = backToCharge();
	int state6;

	//Staying
	if (state1 != -1 && !m_findBackState){
		actionToTake = state1;
	}
	//Horisontell Right
	else if (state1 == -1 && state2 != -1 && !m_findBackState){
		actionToTake = state2;
	}
	//Vertical Down
	else if (state1 == -1 && state2 == -1 && state3 != -1 && !m_findBackState){
		actionToTake = state3;
	}
	//Charge
	else if (m_sensorData.j== 0 && m_sensorData.i == 0 && state1 == -1 && state2 == -1 && state3 == -1 && m_sensorData.battery < batteryFull &&!m_findBackState){
		actionToTake = state1;
	}
	//Contnue from where we left 
	else if((m_sensorData.j== 0 && m_sensorData.i == 0 && state1 == -1 && state2 == -1 && state3 == -1 && m_sensorData.battery > batteryFull)||m_findBackState){
		state6 = continueFromLast();
		if (state6 != -1){
			m_findBackState =true;
		}
		else{
			m_findBackState =false;
		}
		actionToTake = state6;
	}

	if (isBatteryLow() && !m_findBackState){
		actionToTake = state4;
		if (actionToTake != -1 && actionToTake != 0){
			m_pathBack.push_back(actionToTake);
			std::cout<<"path back action is: " << actionToTake << std::endl;
		}
	}
	
	std::cout <<"Time is: "<< m_sensorData.time<< std::endl;
	std::cout <<"Action number:"<< actionToTake<< std::endl;
	std::cout <<"Position is:" << m_sensorData.i<<","<<m_sensorData.j<<std::endl;
	std::cout <<"states is:" << state1 << ", " << state2 << ", " << state3 << ", "<<std::endl;


	if (actionToTake != -1){
		return actionToTake;
	}
	else{
		return 0;
	}
}
