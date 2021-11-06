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
constexpr double sensitivitiyModifier = 0.45;

//TODO change these to the port values
constexpr int winchPort = 4;
constexpr int intakePort = 3;

constexpr double winchSpeed = 0.2;
constexpr double intakeSpeed = 1;

RobotContainer::RobotContainer()
: m_drive{2, 1}
, m_controller{0}
, m_winch{winchPort}
, m_intake{intakePort}{

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
        bool c_rightBumper = m_controller.GetRawButton(static_cast<int>(frc::XboxController::Button::kBumperRight));

        //xyab buttons
        bool c_X = m_controller.GetXButton();
        bool c_Y = m_controller.GetYButton();
        bool c_A = m_controller.GetAButton();
        bool c_B = m_controller.GetBButton();

        //sensitivity modifier
        if(!c_rightBumper){
          c_leftY*=sensitivitiyModifier;
          c_rightX*=sensitivitiyModifier;
        }

        //drive function
        m_drive.DriveMotors(c_leftY + c_rightX, c_leftY - c_rightX);

        //winch logic
        if (c_Y){
          m_winch.DriveWinch(winchSpeed);
        } else if (c_A){
          m_winch.DriveWinch(-winchSpeed);
        } else {
          m_winch.DriveWinch(0);
        }

        //winch logic
        if (c_X){
          m_intake.DriveIntake(-intakeSpeed);
        } else if (c_B){
          m_intake.DriveIntake(intakeSpeed);
        } else {
          m_intake.DriveIntake(0);
        }

        //debugging stuff
        frc::SmartDashboard::PutBoolean("c_rightBumper", c_rightBumper);
        frc::SmartDashboard::PutNumber("c_leftY", c_leftY);
        frc::SmartDashboard::PutNumber("c_rightX", c_rightX);
        frc::SmartDashboard::PutNumber("c_X", c_X);
        frc::SmartDashboard::PutNumber("c_Y", c_Y);
        frc::SmartDashboard::PutNumber("c_A", c_A);
        frc::SmartDashboard::PutNumber("c_B", c_B);

  }, {&m_drive}));

  // Configure the button bindings
  ConfigureButtonBindings();
}

double RobotContainer::deadband(const double input, const double threshold){
  if (std::abs(input) < threshold){
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
