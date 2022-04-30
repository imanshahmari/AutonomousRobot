/*
 * Copyright (C) 2020 Ola Benderius
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

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "cluon-complete.hpp"
#include "opendlv-standard-message-set.hpp"

#include "cluon-complete.hpp"
#include "opendlv-standard-message-set.hpp"

#include <iostream>
#include <map>
#include <tuple>

using namespace std;






const int N_MARGIN_CELLS = 2;

const int N_SEARCH_DIRECTIONS = 4;
const int i_CHANGES[N_SEARCH_DIRECTIONS] = {-1,  0, 1, 0};
const int j_CHANGES[N_SEARCH_DIRECTIONS] = { 0, -1, 0, 1};

const cv::Scalar WINDOW_BACKGROUND_COLOR(0, 0, 0);
const cv::Scalar WALLS_COLOR(0, 255, 0);
const cv::Scalar EMPTY_GRID_COLOR(255, 255, 255);
const cv::Scalar WALL_GRID_COLOR(0, 0, 255);
const cv::Scalar PATH_GRID_COLOR(255, 0, 0);
const cv::Scalar AIM_POINT_COLOR(255, 255, 255);
const cv::Scalar KIWI_COLOR(0, 0, 255);

const std::string GRID_WINDOW_NAME = "Grid map";
const std::string KIWI_WINDOW_NAME = "Global map";

const int EMPTY_GRID_CODE = 0;
const int WALL_GRID_CODE = -1;
const int PATH_GRID_CODE = -2;

const double KIWI_LENGTH = 0.36;
const double KIWI_WIDTH = 0.16;

const double PI = 2*std::acos(0.0);

const int WINDOW_WIDTH = 600;

const int ROTATION_HALF_TIME = 10;

const float GROUND_STEERING_WHILE_ROTATION_COEFF = 2*0.290888f/3.1415f;

const float PEDAL_POSITION_WHILE_ROTATION_AND_MOVING_FORWARD = 0.05f;
const float PEDAL_POSITION_WHILE_ROTATION_AND_MOVING_BACKWARD = -PEDAL_POSITION_WHILE_ROTATION_AND_MOVING_FORWARD * 5.22f;

const float PEDAL_POSITION_WHILE_MOVING_FORWARD = 0.1f;

const double MAX_ANGULAR_DEVIATION = 0.08;
const double EPSILLON = 0.1;


// Structs to hold data
struct GridPoint {
  uint32_t i;
  uint32_t j;

  GridPoint(uint32_t a_i, uint32_t a_j): i(a_i), j(a_j) {}
};

struct Point {
  double x;
  double y;

  Point(double a_x, double a_y): x(a_x), y(a_y) {}
};

struct Line {
  double x0;
  double x1;
  double y0;
  double y1;

  Line(double a_x0, double a_y0, double a_x1, double a_y1):
    x0(a_x0), x1(a_x1), y0(a_y0), y1(a_y1) {}

  Point p0() {
    return Point(x0, y0);
  }

  Point p1() {
    return Point(x1, y1);
  }
};

// Functions
bool checkIntersection(Line a, Line b){
  double s0_x{a.x1 - a.x0};
  double s0_y{a.y1 - a.y0};
  double s1_x{b.x1 - b.x0};
  double s1_y{b.y1 - b.y0};

  double s{(-s0_y * (a.x0 - b.x0) + s0_x * (a.y0 - b.y0)) / 
    (-s1_x * s0_y + s0_x * s1_y)};
  double t{(s1_x * (a.y0 - b.y0) - s1_y * (a.x0 - b.x0)) / 
    (-s1_x * s0_y + s0_x * s1_y)};

  if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
    return true;
  }
  return false;
}

// function to define make use of a hashmap(dictionary)
pair<int, int> getValuePrevious(std::map<pair<int, int>, pair<int, int>> map, pair<int, int> key) {

    auto it = map.find(key);

    if ( it == map.end() ) {
        return pair<int, int> (-100, -100);
    }
    else {
        return it->second;
    }
}

int getValueVisited(std::map<pair<int, int>, int > map, pair<int, int> key) {

    auto it = map.find(key);

    if ( it == map.end() ) {
        return -100;
    }
    else {
        return it->second;
    }
}


bool isGridAvailable(std::vector<std::vector<double>> g,GridPoint a){
  if(int(g[a.j][a.i]) == -1){
    return false;
  }
  else{
    return true;
  }
}


double distance(Point p1, Point p2) {
  return std::sqrt(std::pow(p1.x-p2.x,2)+std::pow(p1.y-p2.y,2));
}


double getAngle(Point kiwiCoordinates, double kiwiYaw, Point aimPoint) {
  double pathVectorX = aimPoint.x - kiwiCoordinates.x;
  double pathVectorY = aimPoint.y - kiwiCoordinates.y;
  double pathAngle = atan(pathVectorY/pathVectorX);
  if (pathVectorX<0 && pathVectorY>0) {pathAngle+=PI;}
  else if (pathVectorX<0 && pathVectorY<0) {pathAngle-=PI;}
  double angularDiff = pathAngle-kiwiYaw;
  if (angularDiff<-PI) {angularDiff+=2*PI;}
  else if (angularDiff>PI) {angularDiff-=2*PI;}
  return angularDiff;
}


// Main function
int32_t main(int32_t argc, char **argv) {
  int32_t retCode{0};
  auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);
  if (0 == commandlineArguments.count("cid") 
      || 0 == commandlineArguments.count("map-file")
      || 0 == commandlineArguments.count("start-x")
      || 0 == commandlineArguments.count("start-y")
      || 0 == commandlineArguments.count("end-x")
      || 0 == commandlineArguments.count("end-y")
      || 0 == commandlineArguments.count("frame-id")
      || 0 == commandlineArguments.count("freq")) {
    std::cerr << argv[0] << " finds a path between to points in a walled "
      "arena, and follows it." << std::endl;
    std::cerr << "Example: " << argv[0] << " --cid=111 --freq=10 --frame-id=0 "
      "--map-file=/opt/simulation-map.txt --start-x=0.0 --start-y=0.0 "
      "--end-x=1.0 --end-y=1.0" << std::endl;
    retCode = 1;
  } else {
    bool const verbose = (commandlineArguments.count("verbose") != 0);

    // Part I: Find the path using the map and the start and end points
    std::vector<Point> path;
    std::vector<Line> walls;
    double distanceX;
    double distanceY;

    {
      double gridSize = 0.2;

      Point startPoint(std::stod(commandlineArguments["start-x"]),
            std::stod(commandlineArguments["start-y"]));
      Point endPoint(std::stod(commandlineArguments["end-x"]),
            std::stod(commandlineArguments["end-y"]));

      //std::vector<Line> walls;
      std::ifstream input(commandlineArguments["map-file"]);

      // Parse walls
      uint32_t cellCountX;
      uint32_t cellCountY;
      {
        double minX = std::numeric_limits<double>::max();
        double minY = std::numeric_limits<double>::max();
        double maxX = std::numeric_limits<double>::min();
        double maxY = std::numeric_limits<double>::min();

        for (std::string str; getline(input, str);) {
          std::vector<std::string> coordinates = stringtoolbox::split(
              stringtoolbox::split(stringtoolbox::trim(str), ';')[0], ',');
          if (coordinates.size() == 4) {
            double x0{std::stof(coordinates[0])};
            double y0{std::stof(coordinates[1])};
            double x1{std::stof(coordinates[2])};
            double y1{std::stof(coordinates[3])};
            minX = static_cast<double>(std::min(std::min(x0, x1), minX));
            minY = static_cast<double>(std::min(std::min(y0, y1), minY));
            maxX = static_cast<double>(std::max(std::max(x0, x1), maxX));
            maxY = static_cast<double>(std::max(std::max(y0, y1), maxY));
            Line line{x0, y0, x1, y1};
            walls.push_back(line);
            if (verbose) {
              std::cout << "Added wall from [" << x0 << "," << y0 << "] to [" 
                << x1 << "," << y1 << "]" << std::endl;
            }
          }
        }

        distanceX = maxX - minX;
        distanceY = maxY - minY;
        cellCountX = static_cast<uint32_t>(ceil(distanceX / gridSize));
        cellCountY = static_cast<uint32_t>(ceil(distanceY / gridSize));
      }

      // Allocate grid, set all distances to infinity
      std::vector<std::vector<double>> grid(cellCountY, 
          std::vector<double>(cellCountX, 
            std::numeric_limits<double>::infinity()));

      GridPoint currentNode(0, 0);
      GridPoint endNode(0,0);

      std::pair<int, int> keyVertex (0,0);
      std::pair<int, int> valueVertex (0,0);

      std::pair<int, int> keyVistedNodes(0,0);

      std::map<pair<int, int>, pair<int, int>> previousVertexMap;
      std::map<pair<int, int>, int > visitedNodes;

      

      for (uint32_t n = 0; n < cellCountY; n++) {
        for (uint32_t m = 0; m < cellCountX; m++) {

          keyVistedNodes.first = n;
          keyVistedNodes.second = m;
          visitedNodes[keyVistedNodes] = 0; //zero means is it is unvisited 
        }
      }


      double x0 = 0.0;
      double y0 = 0.0;
      double x1 = 0.0;
      double y1 = 0.0;
      double incrementValue = 0.05;
      // Initialize
      for (uint32_t j = 0; j < cellCountY; j++) {
        for (uint32_t i = 0; i < cellCountX; i++) {
          Point gridP0(i * gridSize, j * gridSize);
          Point gridP2(i * gridSize, j * gridSize + gridSize);
          Point gridP1(i * gridSize + gridSize, j * gridSize);
          Point gridP3(i * gridSize + gridSize, j * gridSize + gridSize);
          for (auto &wall : walls) {
            Point wallP0 = wall.p0();
            Point wallP1 = wall.p1();

            if(int(wallP0.x*2) == int(wallP1.x*2)){
            
              y0 = std::min(wallP0.y,wallP1.y);
              y1 = std::max(wallP0.y,wallP1.y);
              
              while(y0 < y1){
                if(gridP0.x <= wallP1.x && wallP1.x <= gridP3.x){
                  if(gridP0.y<= y0 && y0<= gridP3.y){
                    grid[j][i] = -1.0; 
                  }
                }
                y0 += incrementValue;
              }
            }

            else if(int(wallP0.y*2) == int(wallP1.y*2)){
              
              x0 = std::min({wallP0.x,wallP1.x});
              x1 = std::max({wallP0.x,wallP1.x});
              
              while(x0 < x1){
                if(gridP0.y <= wallP1.y && wallP1.y <= gridP3.y){
                  if(gridP0.x <= x0 && x0 <= gridP3.x){
                    grid[j][i] = -1.0;
                  }
                }
                x0 += incrementValue;
              }
            }

            if (((gridP0.y <= startPoint.y) && (startPoint.y <= gridP3.y)) && ((gridP0.x <= startPoint.x) && (startPoint.x <= gridP3.x))) {    
              grid[j][i] = 0.0;
              currentNode = GridPoint(i, j);
              //startNode = GridPoint(i, j);
            }
            
            if (((gridP0.y <= endPoint.y) && (endPoint.y <= gridP3.y)) && ((gridP0.x <= endPoint.x) && (endPoint.x <= gridP3.x))) {    
              grid[j][i] = 100.0;
              endNode = GridPoint(i, j);
            }
            
          }
        }
      }
      std::cout << "end node is " << endNode.j << "," << endNode.i << std::endl;



      // Printing the grid
      for (uint32_t j = 0; j < cellCountY; j++) {
        for (uint32_t i = 0; i < cellCountX; i++) {
          std::cout << grid[j][i] << " ";
        }
        std::cout << std::endl;
      }


      // Find the path
      {
        std::vector<GridPoint> gridPath;
        GridPoint top(0,0);
        GridPoint below(0,0);
        GridPoint left(0,0);
        GridPoint right(0,0);
        std::vector<GridPoint> neighboursList;
        GridPoint nodeLowestDistan(0,0);


        //int stop = 0;
        bool pathFound = false;

        while (!pathFound) {
          // COMPLETE: Run your path search here!
          for (uint32_t j = 0; j < cellCountY; j++) {
            for (uint32_t i = 0; i < cellCountX; i++) {
              //check if current node
                if (currentNode.j == j && currentNode.i == i){
                  // Put current node in visited node list
                  keyVistedNodes.first = j;
                  keyVistedNodes.second = i;
                  visitedNodes[keyVistedNodes] = 1; // 1 means it has been visited

                  // Get the neighbours
                  top.i = i;
                  top.j = j+1;
                  below.i = i;
                  below.j = j-1;
                  left.i = i-1;
                  left.j = j;
                  right.i = i+1;
                  right.j = j;

                  //For the current vertex examine its unvisited neighbours 
                  if(isGridAvailable(grid,top)){
                    neighboursList.push_back(top);
                  }
                  if(isGridAvailable(grid,below)){
                    neighboursList.push_back(below);
                  }
                  if(isGridAvailable(grid,left)){
                    neighboursList.push_back(left);
                  }
                  if(isGridAvailable(grid,right)){
                    neighboursList.push_back(right);
                  }

                  //Calculate the the distance of each neighbour from the start vertex and 
                  //update the previous vertex of the neighbour if the calculated distance is less than tht known distance
                  for(auto &element:neighboursList){
                    if(grid[currentNode.j][currentNode.i] < grid[element.j][element.i]){
                      grid[element.j][element.i] = grid[currentNode.j][currentNode.i] + 1.0;
                      std::cout << "key value is " <<keyVertex.first << "," << keyVertex.second << " value is "  << valueVertex.first << ","  << valueVertex.second << std::endl;
                      
                      keyVertex.first = element.j;
                      keyVertex.second = element.i;
                      valueVertex.first = currentNode.j;
                      valueVertex.second = currentNode.i;
                      previousVertexMap[keyVertex] = valueVertex;
                      
                    }
                  }
                }

            }
          }
          //Visit the unvisited vertex with the smallest known distance from start vertex  
          double smallestKnownDistance = 10000.0;
          for (uint32_t j = 0; j < cellCountY; j++) {
            for (uint32_t i = 0; i < cellCountX; i++) {
              int isVisited  = getValueVisited(visitedNodes,std::pair<int, int> (j,i));
              if (isVisited == 0 && int(grid[j][i]) != -1){
                double currentDistance = grid[j][i];
                if (currentDistance < smallestKnownDistance) {
                  smallestKnownDistance = currentDistance;
                  currentNode.j=j;
                  currentNode.i=i;
                }
              }
            }
          }
          
          if(currentNode.j == endNode.j && currentNode.i == endNode.i){
            pathFound = true;
            std::cout << "end node is " << currentNode.j << "," << currentNode.i << std::endl;
          }
          neighboursList.clear(); //clear neighbours for each time we find the current node
        }

        // Printing the grid
        std::cout << std::endl;
        for (uint32_t l = 0; l < cellCountY; l++) {
          for (uint32_t k = 0; k < cellCountX; k++) {
            std::cout << grid[l][k] << " ";
          }
          std::cout << std::endl;
        }



        //Trace back the path and put it in the vector result
        pair<int, int> lastNodeInPath;
        lastNodeInPath.first = endNode.j;
        lastNodeInPath.second = endNode.i;

        std::cout<< "debugging input is" <<lastNodeInPath.first<<","<<lastNodeInPath.second<<std::endl;

        pair<int, int> before;
        before.first = 1;
        before.second = 1;

        GridPoint convertGridPoint(0,0);
        std::vector< GridPoint > result;

        pair<int, int> test = getValuePrevious(previousVertexMap,lastNodeInPath);
        std::cout<< "first iteration is " <<test.first<<","<<test.second<<std::endl;


        while(before.first != lastNodeInPath.first && before.second != lastNodeInPath.second){
        pair<int, int> previous = getValuePrevious(previousVertexMap,lastNodeInPath);
        convertGridPoint.j = previous.first;
        convertGridPoint.i = previous.second;
        result.push_back(convertGridPoint);
        lastNodeInPath = previous;
        }
        pair<int, int> previous = getValuePrevious(previousVertexMap,lastNodeInPath);
        convertGridPoint.j = previous.first;
        convertGridPoint.i = previous.second;
        result.push_back(convertGridPoint);


        for(auto &element:result){
          std::cout <<"list element "<< element.j <<","<< element.i << std::endl;
          grid[element.j][element.i] = 8.0;
        }



        // Printing the grid
        std::cout << std::endl;
        for (uint32_t l = 0; l < cellCountY; l++) {
          for (uint32_t k = 0; k < cellCountX; k++) {
            std::cout << grid[l][k] << " ";
          }
          std::cout << std::endl;
        }


        // Transform into metric path
        for (auto &gp : gridPath) {
            double x = (gp.i * gridSize) + gridSize / 2.0;
            double y = (gp.j * gridSize) + gridSize / 2.0;

            Point p(x, y);
            path.push_back(p);
        }
      

      if (verbose) {

          uint32_t windowHeight = (int)((WINDOW_WIDTH*distanceY)/distanceX);
          cv::Mat gridMap(WINDOW_WIDTH, windowHeight, CV_8UC3, cv::Scalar(0, 0, 0));
          cv::Mat map(WINDOW_WIDTH, windowHeight, CV_8UC3, cv::Scalar(0, 0, 0));

          for (uint32_t j = 0; j < cellCountY; j++) {
            for (uint32_t i = 0; i < cellCountX; i++) {
              if ((int)grid[j][i] == -1){
                cv::Scalar color = cv::Scalar(0, 0, 255);
                cv::circle(gridMap, cv::Point((int)(i*gridSize*windowHeight/distanceY), (int)(j*gridSize*WINDOW_WIDTH/distanceX)), 1, color, -1);
              }
              else if((int)grid[j][i] == 0){
                cv::Scalar color = cv::Scalar(0, 0, 255);
                cv::circle(gridMap, cv::Point((int)(i*gridSize*windowHeight/distanceY), (int)(j*gridSize*WINDOW_WIDTH/distanceX)), 4, color, -1);
              }
              else if (int(j) == (int)endNode.j && int(i) == (int)endNode.i ){
                cv::Scalar color = cv::Scalar(0, 0, 255);
                cv::circle(gridMap, cv::Point((int)(i*gridSize*windowHeight/distanceY), (int)(j*gridSize*WINDOW_WIDTH/distanceX)), 4, color, -1);
              }
              else{
                cv::Scalar color = cv::Scalar(255, 255, 255);
                cv::circle(gridMap, cv::Point((int)(i*gridSize*windowHeight/distanceY), (int)(j*gridSize*WINDOW_WIDTH/distanceX)), 1, color, -1);
              }
            }
          }
          for (auto &gp : result) {
            cv::circle(gridMap, cv::Point((int)(gp.i*gridSize*windowHeight/distanceY), (int)(gp.j*gridSize*WINDOW_WIDTH/distanceX)), 2, cv::Scalar(255, 0, 0), -1);
          } 
          cv::imshow("Grid map", gridMap);
          cv::waitKey(1);
      }
      
      }
    }
    // .. by leaving this scope, only the "path" and "verbose" are saved
    // A well-scoped design helps the reader to know how the microservice is
    // structured.
 

    // Part II: Path found, set up the OD4 session and start the path follower
    uint16_t const cid = std::stoi(commandlineArguments["cid"]);
    float const freq = std::stof(commandlineArguments["freq"]);
    uint32_t const frameId = static_cast<uint32_t>(
        std::stoi(commandlineArguments["frame-id"]));

    cluon::OD4Session od4(cid);

    opendlv::sim::Frame latestFrame;
    double distanceFront = 0.0;
    double distanceLeft = 0.0;
    double distanceRear = 0.0;
    double distanceRight = 0.0;

    std::mutex frameMutex;
    std::mutex distanceMutex;

    auto onFrame{[&frameId, &latestFrame, &frameMutex, &verbose](
        cluon::data::Envelope &&envelope)
      {
        uint32_t const senderStamp = envelope.senderStamp();
        if (frameId == senderStamp) {
          std::lock_guard<std::mutex> const lock(frameMutex);
          latestFrame = cluon::extractMessage<opendlv::sim::Frame>(
              std::move(envelope));

          if (verbose) {
            std::cout << "Robot position [" << latestFrame.x() << ", " 
              << latestFrame.y() << ", " << latestFrame.yaw() << "]" <<std::endl;
          }
        }
    }};

    auto onDistanceReading{[&distanceFront, &distanceLeft, &distanceRear,
      &distanceRight, &distanceMutex](
        cluon::data::Envelope &&envelope)
      {
        uint32_t const senderStamp = envelope.senderStamp();
        auto distanceReading = 
          cluon::extractMessage<opendlv::proxy::DistanceReading>(
              std::move(envelope));
          
        std::lock_guard<std::mutex> const lock(distanceMutex);
        if (senderStamp == 0) {
          distanceFront = distanceReading.distance();
        } else if (senderStamp == 1) {
          distanceRear = distanceReading.distance();
        } else if (senderStamp == 2) {
          distanceLeft = distanceReading.distance();
        } else if (senderStamp == 3) {
          distanceRight = distanceReading.distance();
        }
      }};

    bool isRotating = false;
    double angularError = 0;
    int rotationCounter = 0;
    auto atFrequency{[&latestFrame, &frameMutex, &distanceFront, &distanceLeft, 
      &distanceRear, &distanceRight, &distanceMutex, &path, &od4, &verbose, &isRotating, 
      &angularError, &rotationCounter, &distanceY, &distanceX, &walls]() 
        -> bool
      {
        double posX;
        double posY;
        double posYaw;
        double distFront;
        double distLeft;
        double distRear;
        double distRight;
        {
          std::lock_guard<std::mutex> const lock(frameMutex);
          posX = latestFrame.x();
          posY = latestFrame.y();
          posYaw = latestFrame.yaw();
        }
        {
          std::lock_guard<std::mutex> const lock(distanceMutex);
          distFront = distanceFront;
          distLeft = distanceLeft;
          distRear = distanceRear;
          distRight = distanceRight;
        }

        float groundSteering = 0.0f;
        float pedalPosition = 0.0f;

        // COMPLETE: Use the path, the current position, and possibly the
        // distance readings to calculate steering and throttle.

        if (path.size()==0) {return true;}
        
        Point aimPoint = path[0];

        if (distance(aimPoint, Point(posX, posY))<EPSILLON) {path.erase(path.begin());}

        else
        {
          double angle = getAngle(Point(posX,posY), posYaw, aimPoint);
          if (std::abs(std::sin(angle))*distance(aimPoint, Point(posX, posY))>0.9*EPSILLON || std::abs(angle)>PI/2)
          {
            if (isRotating)
            {
              if (rotationCounter<2*ROTATION_HALF_TIME)
              {
                if (rotationCounter<ROTATION_HALF_TIME)
                {
                  groundSteering = GROUND_STEERING_WHILE_ROTATION_COEFF* (float)angularError;
                  pedalPosition = PEDAL_POSITION_WHILE_ROTATION_AND_MOVING_FORWARD;
                }
                else
                {
                  groundSteering = GROUND_STEERING_WHILE_ROTATION_COEFF* (float)angularError;
                  pedalPosition = PEDAL_POSITION_WHILE_ROTATION_AND_MOVING_BACKWARD;
                }
                rotationCounter+=1;
              }
              else
              {
                rotationCounter = 0;
                isRotating = false;
              }
            }
            else
            {
              isRotating = true;
              angularError = angle;
            }
          }
          else
          {
            groundSteering = 0;
            pedalPosition = PEDAL_POSITION_WHILE_MOVING_FORWARD;
          }
        }



        (void) posX; // Remove when used
        (void) posY; // Remove when used
        (void) posYaw; // Remove when used
        (void) distFront; // Remove when used
        (void) distLeft; // Remove when used
        (void) distRear; // Remove when used
        (void) distRight; // Remove when used




        opendlv::proxy::GroundSteeringRequest groundSteeringRequest;
        groundSteeringRequest.groundSteering(groundSteering);

        opendlv::proxy::PedalPositionRequest pedalPositionRequest;
        pedalPositionRequest.position(pedalPosition);
        
        cluon::data::TimeStamp sampleTime;
        od4.send(groundSteeringRequest, sampleTime, 0);
        od4.send(pedalPositionRequest, sampleTime, 0);

        
        if (verbose) {
          uint32_t windowHeight = (int)((WINDOW_WIDTH*distanceY)/distanceX);
          cv::Mat globalMap(WINDOW_WIDTH, windowHeight, CV_8UC3, WINDOW_BACKGROUND_COLOR);

          for (auto &wall : walls) {
          cv::line(globalMap, cv::Point((int)(wall.x0*WINDOW_WIDTH/distanceX), (int)(wall.y0*windowHeight/distanceY)), 
                            cv::Point((int)(wall.x1*WINDOW_WIDTH/distanceX), (int)(wall.y1*windowHeight/distanceY)), 
                            WALLS_COLOR, 2, cv::LINE_8);
          }

          cv::circle(globalMap, cv::Point((int)(aimPoint.x*windowHeight/distanceY), 
                     (int)(aimPoint.y*WINDOW_WIDTH/distanceX)), 4, AIM_POINT_COLOR, -1);
          
          double kiwiX = posX*windowHeight/distanceY;
          double kiwiY = posY*WINDOW_WIDTH/distanceX;
          cv::circle(globalMap, cv::Point((int)kiwiX, (int)kiwiY), 4, KIWI_COLOR, -1);

          double directionVectorEndX = kiwiX + KIWI_LENGTH/2*std::cos(posYaw)*windowHeight/distanceY;
          double directionVectorEndY = kiwiY + KIWI_LENGTH/2*std::sin(posYaw)*windowHeight/distanceY;

          cv::RotatedRect rRect = cv::RotatedRect(cv::Point2f((int)kiwiX,(int)kiwiY), 
                                          cv::Size2f((int)(KIWI_LENGTH*windowHeight/distanceY),
                                                 (int)(KIWI_WIDTH*windowHeight/distanceY)), (float)(posYaw*180.0f/(float)PI));

          
          cv::line(globalMap, cv::Point((int)kiwiX, (int)kiwiY), 
                   cv::Point((int)directionVectorEndX, (int)directionVectorEndY),
                   KIWI_COLOR, 2, cv::LINE_8);

          cv::Point2f vertices[4];
          rRect.points(vertices);
          for (int i = 0; i < 4; i++) {
            line(globalMap, vertices[i], vertices[(i+1)%4], KIWI_COLOR, 2);
          }

          cv::imshow(KIWI_WINDOW_NAME, globalMap);
          cv::waitKey(1);
        }
        
        
        return true;
      }};

    // Register the three data triggers, each spawning a thread
    od4.dataTrigger(opendlv::sim::Frame::ID(), onFrame);
    od4.dataTrigger(opendlv::proxy::DistanceReading::ID(), onDistanceReading);
    
    // Register the time trigger, spawning a thread that blocks execution 
    // until CTRL-C is pressed
    od4.timeTrigger(freq, atFrequency);
  }
  return retCode;
}
