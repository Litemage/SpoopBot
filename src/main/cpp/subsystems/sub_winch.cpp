// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/sub_winch.h"

sub_winch::sub_winch(const int motorID)
: m_winchMotor{motorID} {

}

// This method will be called once per scheduler run
void sub_winch::Periodic() {}
