/*
 * Copyright (C) 2018 Ola Benderius
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

#include "behavior.hpp"

Behavior::Behavior() noexcept:
  m_frontUltrasonicReading{},
  m_rearUltrasonicReading{},
  m_leftIrReading{},
  m_rightIrReading{},
  m_wheelSpeedRequestLeft{},
  m_wheelSpeedRequestRight{},
  m_frontUltrasonicReadingMutex{},
  m_rearUltrasonicReadingMutex{},
  m_leftIrReadingMutex{},
  m_rightIrReadingMutex{},
  m_wheelSpeedRequestLeftMutex{},
  m_wheelSpeedRequestRightMutex{}
{
}

opendlv::proxy::WheelSpeedRequest Behavior::getWheelSpeedRequestLeft() noexcept
{
  std::lock_guard<std::mutex> lock(m_wheelSpeedRequestLeftMutex);
  return m_wheelSpeedRequestLeft;
}

opendlv::proxy::WheelSpeedRequest Behavior::getWheelSpeedRequestRight() noexcept
{
  std::lock_guard<std::mutex> lock(m_wheelSpeedRequestRightMutex);
  return m_wheelSpeedRequestRight;
}

void Behavior::setFrontUltrasonic(opendlv::proxy::DistanceReading const &frontUltrasonicReading) noexcept
{
  std::lock_guard<std::mutex> lock(m_frontUltrasonicReadingMutex);
  m_frontUltrasonicReading = frontUltrasonicReading;
}

void Behavior::setRearUltrasonic(opendlv::proxy::DistanceReading const &rearUltrasonicReading) noexcept
{
  std::lock_guard<std::mutex> lock(m_rearUltrasonicReadingMutex);
  m_rearUltrasonicReading = rearUltrasonicReading;
}

void Behavior::setLeftIr(opendlv::proxy::VoltageReading const &leftIrReading) noexcept
{
  std::lock_guard<std::mutex> lock(m_leftIrReadingMutex);
  m_leftIrReading = leftIrReading;
}

void Behavior::setRightIr(opendlv::proxy::VoltageReading const &rightIrReading) noexcept
{
  std::lock_guard<std::mutex> lock(m_rightIrReadingMutex);
  m_rightIrReading = rightIrReading;
}




void Behavior::step(float time) noexcept
{
  opendlv::proxy::DistanceReading frontUltrasonicReading;
  opendlv::proxy::DistanceReading rearUltrasonicReading;
  opendlv::proxy::VoltageReading leftIrReading;
  opendlv::proxy::VoltageReading rightIrReading;
  {
    std::lock_guard<std::mutex> lock1(m_frontUltrasonicReadingMutex);
    std::lock_guard<std::mutex> lock2(m_rearUltrasonicReadingMutex);
    std::lock_guard<std::mutex> lock3(m_leftIrReadingMutex);
    std::lock_guard<std::mutex> lock4(m_rightIrReadingMutex);

    frontUltrasonicReading = m_frontUltrasonicReading;
    rearUltrasonicReading = m_rearUltrasonicReading;
    leftIrReading = m_leftIrReading;
    rightIrReading = m_rightIrReading;



  }
  
  float t1= 3.0f;
  float t2= 10.0f;
  float v0= 0.5f;
  float r_wheel = 0.04f;

  float valueLeft;
  float valueRight;

  if(time <= t1 && time >=0)
  {
    valueLeft = 0;
    valueRight = (v0*time/t1)/r_wheel;
  }
  else if (time <= t2 && time >t1)
  {
    valueLeft = (v0*(time-t1)/t2)/r_wheel;
    valueRight = v0/r_wheel;
  }
  else
  {
    valueLeft=0;
    valueRight=0;
  }


  {
    std::lock_guard<std::mutex> lock1(m_wheelSpeedRequestLeftMutex);
    std::lock_guard<std::mutex> lock2(m_wheelSpeedRequestRightMutex);

    opendlv::proxy::WheelSpeedRequest wheelSpeedRequestLeft;
    wheelSpeedRequestLeft.wheelSpeed(valueLeft);
    m_wheelSpeedRequestLeft = wheelSpeedRequestLeft ;

    opendlv::proxy::WheelSpeedRequest wheelSpeedRequestRight;
    wheelSpeedRequestRight.wheelSpeed(valueRight);
    m_wheelSpeedRequestRight = wheelSpeedRequestRight;
  }
}

// TODO: This is a rough estimate, improve by looking into the sensor specifications.
double Behavior::convertIrVoltageToDistance(float voltage) const noexcept
{
  double voltageDividerR1 = 1000.0;
  double voltageDividerR2 = 1000.0;

  double sensorVoltage = (voltageDividerR1 + voltageDividerR2) / voltageDividerR2 * voltage;
  double distance = (2.5 - sensorVoltage) / 0.07;
  return distance;
}
