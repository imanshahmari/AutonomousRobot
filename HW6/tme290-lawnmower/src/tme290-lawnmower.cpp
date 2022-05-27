/*
 * Copyright (C) 2019 Ola Benderius
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

#include "robot.hpp"
#include "cluon-complete.hpp"
#include "tme290-sim-grass-msg.hpp"




int32_t main(int32_t argc, char **argv) {
  int32_t retCode{0};
  auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);
  if (0 == commandlineArguments.count("cid")) {
    std::cerr << argv[0] 
      << " is a lawn mower control algorithm." << std::endl;
    std::cerr << "Usage:   " << argv[0] << " --cid=<OpenDLV session>" 
      << "[--verbose]" << std::endl;
    std::cerr << "Example: " << argv[0] << " --cid=111 --verbose" << std::endl;
    retCode = 1;
  } else {
    bool const verbose{commandlineArguments.count("verbose") != 0};
    uint16_t const cid = std::stoi(commandlineArguments["cid"]);
    
    cluon::OD4Session od4{cid};
    
    //Robot object 
    Robot grassCutter;
    
    //SensorData object
    SensorData sensorData;

    auto onSensors{[&od4,&sensorData,&grassCutter](cluon::data::Envelope &&envelope)
      {
        auto msg = cluon::extractMessage<tme290::grass::Sensors>(
            std::move(envelope));
        
        
      	sensorData.i = msg.i();
      	sensorData.j = msg.j();
        sensorData.time = msg.time();	
        sensorData.grassTopLeft = msg.grassTopLeft();
        sensorData.grassTopCentre = msg.grassTopCentre(); 
        sensorData.grassTopRight = msg.grassTopRight();
        sensorData.grassLeft = msg.grassLeft();
        sensorData.grassCentre = msg.grassCentre(); 
        sensorData.grassRight = msg.grassRight(); 
        sensorData.grassBottomLeft = msg.grassBottomLeft(); 
        sensorData.grassBottomCentre = msg.grassBottomCentre(); 
        sensorData.grassBottomRight = msg.grassBottomRight();
        sensorData.rain = msg.rain();
        sensorData.battery = msg.battery(); 
        sensorData.rainCloudDirX = msg.rainCloudDirX(); 
        sensorData.rainCloudDirY = msg.rainCloudDirY();

        //std::cout<<"coordinate is:"<<msg.i()<<","<<msg.j()<<std::endl;
        tme290::grass::Control control;
        
        grassCutter.set_sensorData(sensorData);
        // After 20 steps, start pausing on every other step.

        control.command(grassCutter.decideAction());



        /*
        std::cout << "Rain reading " << msg.rain() << ", direction (" <<
        msg.rainCloudDirX() << ", " << msg.rainCloudDirY()<< ")"  <<"time:"<< msg.time()  <<"Grass:" << msg.grassTopLeft()  <<msg.grassTopCentre()  <<msg.grassTopRight()  <<msg.grassLeft()  <<msg.grassCentre() <<msg.grassRight()  <<msg.grassBottomLeft()  <<msg.grassBottomCentre()  <<msg.grassBottomRight()  <<"rain:"<< msg.rain()  <<"battery:"<<msg.battery()  <<"rainCloud:"<< msg.rainCloudDirX()  <<msg.rainCloudDirY() << std::endl; 
        */

        od4.send(control);
      }};

    auto onStatus{[&verbose](cluon::data::Envelope &&envelope)
      {
        auto msg = cluon::extractMessage<tme290::grass::Status>(
            std::move(envelope));
        if (verbose) {
          std::cout << "Status at time " << msg.time() << ": " 
            << msg.grassMean() << "/" << msg.grassMax() << std::endl;
        }
      }};

    od4.dataTrigger(tme290::grass::Sensors::ID(), onSensors);
    od4.dataTrigger(tme290::grass::Status::ID(), onStatus);

    if (verbose) {
      std::cout << "All systems ready, let's cut some grass!" << std::endl;
    }

    tme290::grass::Control control;
    control.command(0);
    od4.send(control);

    while (od4.isRunning()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    retCode = 0;
  }
  return retCode;
}
