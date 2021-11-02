// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/sub_Drive.h"

sub_Drive::sub_Drive(const int leftID, const int rightID)
: m_left(leftID)
, m_right(rightID) {
  m_left.SetInverted(true);
}

void sub_Drive::DriveMotors(const double left, const double right){
  m_left.Set(ControlMode::PercentOutput, left);
  m_right.Set(ControlMode::PercentOutput, right);
}

// This method will be called once per scheduler run
void sub_Drive::Periodic()  {}
