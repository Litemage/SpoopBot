// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/RunCommand.h>
#include <frc/smartdashboard/SmartDashboard.h>

//globals
//note: use const expr for globals in the future.
constexpr double thresh = 0.2;
constexpr bool isTankDrive = false;

RobotContainer::RobotContainer()
: m_drive{2, 1}
, m_controller{0}{

  //set our default command (default commands basically run on start on the program)
  //setDefaultCommand() function is located in the subsystem class
  //take the parameters: (command, required ssubsystems) required subsystems can be in the form of an init list.
  m_drive.SetDefaultCommand(
    frc2::RunCommand(
      [this]{
        //make a point to explain what the cast is doing.
        //TODO see if we need to invert the axis input at all
        double c_leftY = deadband(m_controller.GetRawAxis(static_cast<int>(frc::XboxController::Axis::kLeftY)) * -1, thresh);
        double c_rightX = deadband(m_controller.GetRawAxis(static_cast<int>(frc::XboxController::Axis::kRightX)), thresh);
        //need inverted?
        double c_rightY = deadband(m_controller.GetRawAxis(static_cast<int>(frc::XboxController::Axis::kRightY)), thresh);

        //call our drive function
        if(isTankDrive)
          m_drive.DriveMotors(c_leftY, c_rightY);
        else
          m_drive.DriveMotors(c_leftY + c_rightX, c_leftY - c_rightX);

  }, {&m_drive}));

  // Configure the button bindings
  ConfigureButtonBindings();
}

double RobotContainer::deadband(const double input, const double threshold){
  if (abs(input) < threshold){
    return 0;
  }
  return input;
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return nullptr;
}
