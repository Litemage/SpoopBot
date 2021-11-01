// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>

//include the xbox controller
#include <frc/XboxController.h>
//include our subsystem
#include "subsystems/sub_Drive.h"
#include "subsystems/sub_intake.h"
#include "subsystems/sub_winch.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();

 private:
  //the robots subsystems and commands are defined here.
  //declare the robot class
  frc::XboxController m_controller;
  sub_Drive m_drive;
  sub_intake m_intake;
  sub_winch m_winch;
  void ConfigureButtonBindings();
  //my input filtiring function
  static double deadband(const double input, const double threshold);
};
