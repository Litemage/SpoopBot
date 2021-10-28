// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/sub_intake.h"
#include <ctre/Phoenix.h>

sub_intake::sub_intake(const int motorID)
: m_inMotor{motorID}{

}

// This method will be called once per scheduler run
void sub_intake::Periodic() {}
