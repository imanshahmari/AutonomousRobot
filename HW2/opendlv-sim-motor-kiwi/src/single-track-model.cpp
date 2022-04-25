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

#include <cmath>
#include <iostream>

#include "single-track-model.hpp"

SingleTrackModel::SingleTrackModel() noexcept:
  m_wheelSpeedRequestLeftMutex{},
  m_wheelSpeedRequestRightMutex{},
  m_longitudinalSpeed{0.0f},
  m_lateralSpeed{0.0f},
  m_yawRate{0.0f},
  m_wheelSpeedRequestLeft{0.0f},
  m_wheelSpeedRequestRight{0.0f}
{
}

void SingleTrackModel::setWheelSpeedRequestLeft(opendlv::proxy::WheelSpeedRequest const &wheelSpeedRequestLeft) noexcept
{
  std::lock_guard<std::mutex> lock(m_wheelSpeedRequestLeftMutex);
  m_wheelSpeedRequestLeft = wheelSpeedRequestLeft.wheelSpeed();
}

void SingleTrackModel::setWheelSpeedRequestRight(opendlv::proxy::WheelSpeedRequest const &wheelSpeedRequestRight) noexcept
{
  std::lock_guard<std::mutex> lock(m_wheelSpeedRequestRightMutex);
  m_wheelSpeedRequestRight = wheelSpeedRequestRight.wheelSpeed();
}

opendlv::sim::KinematicState SingleTrackModel::step() noexcept
{

  float r_robot = 0.12f;
  float r_wheel = 0.04f;  

  m_lateralSpeed = 0;
  m_longitudinalSpeed = (m_wheelSpeedRequestLeft + m_wheelSpeedRequestRight)*r_wheel/2.0;
  m_yawRate = (m_wheelSpeedRequestRight - m_wheelSpeedRequestLeft)*r_wheel/(2*r_robot);

  opendlv::sim::KinematicState kinematicState;
  kinematicState.vx(static_cast<float>(m_longitudinalSpeed));
  kinematicState.vy(static_cast<float>(m_lateralSpeed));
  kinematicState.yawRate(static_cast<float>(m_yawRate));

  return kinematicState;
}
