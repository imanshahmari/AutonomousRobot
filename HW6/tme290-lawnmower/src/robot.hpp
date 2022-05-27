#ifndef ROBOT_HPP
#define ROBOT_HPP
#include <iostream>
#include <vector>
#include <utility>



struct SensorData{
  uint32_t i;
  uint32_t j;
  uint64_t time; 
  float grassTopLeft;
  float grassTopCentre; 
  float grassTopRight; 
  float grassLeft;
  float grassCentre; 
  float grassRight; 
  float grassBottomLeft;
  float grassBottomCentre;
  float grassBottomRight;
  float rain;
  float battery;
  float rainCloudDirX;
  float rainCloudDirY;
};

class Robot{
    private:
        SensorData m_sensorData;
        std::vector<std::pair<uint32_t ,uint32_t >> m_pathHistory;
        //states
        int stay();
        //int cutHorizontallyLeft();
        int cutHorizontallyRight();
        //int cutVerticallyUp();
        //int cutVerticallyDown();
        //int cutDiagonallyUpLeft();
        //int cutDiagonallyUpRight();
        //int cutDiagonallyDownLeft();
        //int cutDiagonallyDownRight();
        //int backToCharge();
        //int continueFromLast();
        //int avoidRain();
        //int avoidWall();

        //checks
        bool isRain();
        //bool isBatteryLow();
        //bool isWall();
        bool isGrassLow(int,float);

        
	public:
		Robot();
		void set_sensorData(SensorData);
		SensorData get_sensorData();
		int decideAction();


};


#endif
