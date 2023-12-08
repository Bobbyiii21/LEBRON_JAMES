#include "vex.h"

void default_constants()
{
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

void odom_constants()
{
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

void skills()
{
  // Goal of this Autonomus is to score as many points as possible by shooting many balls across the field then scoring them by going across the field
  // intake_air.set(false); //intake is down
  rightDrive.setStopping(brake);
  leftDrive.setStopping(brake);
  rightDrive.stop();
  leftDrive.stop();
  odom_constants();
  // chassis.set_coordinates(0, 0, -108);
  chassis.set_coordinates(0, 0, 135);
  telemetry.broadcast();
  Intake.spinFor(-90, degrees);
  rear_jack.set(false);
  wait(1, timeUnits::sec);

  chassis.left_swing_to_angle(65);
  vex::task::sleep(1);
  rear_jack.set(true);
  LiftToggle("up");
  A_CallBack();
  Puncher.spinFor(forward, 55, rotationUnits::rev, 600, velocityUnits::rpm, true); // activate puncher
  wait(1, sec);
  LiftToggle("down");
  A_CallBack();
  wait(.5, sec);
  rear_jack.set(false);
  wait(300, timeUnits::msec);
  chassis.turn_to_angle(-70);
  wait(200, msec);
  // drive to other side of field
  chassis.drive_distance(-9, -70);
  wait(200, msec);
  chassis.turn_to_angle(-88);
  chassis.drive_distance(-50, chassis.desired_heading, 11, chassis.heading_max_voltage);
  // intake_air.set(true); //intake is up
  chassis.left_swing_to_angle(-180);
  wait(1, msec);
  wingValve(true);
  chassis.drive_distance(-15, chassis.desired_heading, 12, chassis.heading_max_voltage);
  wait(1, msec);
  wingValve(false);

  chassis.drive_distance(17);
  left_wing.set(false);
  wait(1, msec);
  chassis.turn_to_angle(-205);
  wait(1, msec);
  chassis.drive_distance(-35, chassis.desired_heading, 11, chassis.heading_max_voltage);
  wait(1, msec);
  chassis.right_swing_to_angle(-90);
  wait(1, msec);
  wingValve(true);
  chassis.drive_distance(-14, chassis.desired_heading, 12, chassis.heading_max_voltage);
  wait(1, msec);
}

void newCloseSide()
{
  rear_jack.set(false);

  rightDrive.setStopping(brake);
  leftDrive.setStopping(brake);
  rightDrive.stop();
  leftDrive.stop();
  odom_constants();
  chassis.set_coordinates(0, 0, 114);
  telemetry.broadcast();

  // Time for the fun stuff
  int timeout = 1500;

  A_CallBack();
  chassis.turn_to_angle(90);
  task::sleep(500);
  chassis.drive_distance(5, 90, chassis.drive_max_voltage,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         timeout);
  A_CallBack();
  chassis.drive_distance(-5,
                         90,
                         chassis.drive_max_voltage,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         timeout);
  chassis.turn_to_angle(135,
                        chassis.swing_max_voltage,
                        chassis.turn_settle_error,
                        chassis.turn_settle_time,
                        timeout,
                        chassis.turn_kp,
                        chassis.turn_ki,
                        chassis.turn_kd,
                        chassis.turn_starti);
  task::sleep(500);
  Y_CallBack();
  chassis.drive_distance(-9,
                         135,
                         chassis.drive_max_voltage,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         timeout);
  task::sleep(1);
  chassis.right_swing_to_angle(180,
                               chassis.swing_max_voltage,
                               chassis.swing_settle_error,
                               chassis.swing_settle_time,
                               timeout,
                               chassis.swing_kp,
                               chassis.swing_ki,
                               chassis.swing_kd,
                               chassis.swing_starti);
  task::sleep(1);
  chassis.drive_distance(-11,
                         180,
                         12,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         timeout);
  task::sleep(1);
  Y_CallBack();
  chassis.drive_distance(11,
                         180,
                         chassis.drive_max_voltage,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_error,
                         timeout);
  task::sleep(1);
  chassis.right_swing_to_angle(135,
                               chassis.swing_max_voltage,
                               chassis.swing_settle_error,
                               chassis.swing_settle_time,
                               chassis.swing_timeout,
                               chassis.swing_kp,
                               chassis.swing_ki,
                               chassis.swing_kd,
                               chassis.swing_starti);
  task::sleep(1);
  // A_CallBack();
  chassis.drive_distance(10,
                         135,
                         chassis.drive_max_voltage,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         chassis.drive_timeout);
  task::sleep(1);
  // A_CallBack();
  chassis.turn_to_angle(100,
                        chassis.swing_max_voltage,
                        chassis.turn_settle_error,
                        chassis.turn_settle_time,
                        chassis.turn_timeout, chassis.turn_kp,
                        chassis.turn_ki,
                        chassis.turn_kd,
                        chassis.turn_starti);
  task::sleep(1);
  // intake_air.set(true);
  chassis.drive_distance(25,
                         100,
                         10,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         chassis.drive_timeout);
  Intake.spinFor(-90, degrees);
}

// void farSide()
// {
//   // setting up the robot
//   rear_jack.set(false);

//   rightDrive.setStopping(brake);
//   leftDrive.setStopping(brake);
//   rightDrive.stop();
//   leftDrive.stop();
//   odom_constants();
//   chassis.set_coordinates(0, 0, -90);
//   telemetry.broadcast();

//   // Time for the fun stuff
//   int timeout = 1250;
//   // Intake.spinFor(-90, degrees);
//   // wait(200, msec);
//   intakeInEvent.broadcast();
//   chassis.drive_distance(6,-90, chassis.drive_max_voltage, chassis.heading_max_voltage, chassis.drive_settle_error, chassis.drive_settle_time, timeout);
//   vex::task::sleep(2000);
//   chassis.drive_distance(3,
//                          -90,
//                          chassis.drive_max_voltage,
//                          chassis.heading_max_voltage,
//                          chassis.drive_settle_error,
//                          chassis.drive_settle_time,
//                          timeout);
//   vex::task::sleep(1);
//   chassis.drive_distance(-24,
//                          -90,
//                          chassis.drive_max_voltage,
//                          chassis.heading_max_voltage,
//                          chassis.drive_settle_error,
//                          chassis.drive_settle_time,
//                          timeout);
//   vex::task::sleep(1);
//   chassis.left_swing_to_angle(-135);
//   vex::task::sleep(1);
//   Y_CallBack();
//   chassis.drive_distance(-5,
//                          -135,
//                          chassis.drive_max_voltage,
//                          chassis.heading_max_voltage,
//                          chassis.drive_settle_error,
//                          chassis.drive_settle_time,
//                          timeout);
//   vex::task::sleep(1);
//   chassis.turn_to_angle(-160,
//                         chassis.swing_max_voltage,
//                         chassis.turn_settle_error,
//                         chassis.turn_settle_time,
//                         timeout,
//                         chassis.turn_kp,
//                         chassis.turn_ki,
//                         chassis.turn_kd,
//                         chassis.turn_starti);
//   vex::task::sleep(1);
//   chassis.drive_distance(-14,
//                          -180,
//                          12,
//                          chassis.heading_max_voltage,
//                          chassis.drive_settle_error,
//                          chassis.drive_settle_time,
//                          timeout);
//   vex::task::sleep(1);
//   chassis.drive_distance(16,
//                          chassis.desired_heading,
//                          chassis.drive_max_voltage,
//                          chassis.heading_max_voltage,
//                          chassis.drive_settle_error,
//                          chassis.drive_settle_time,
//                          timeout);
//   vex::task::sleep(1);
//   chassis.turn_to_angle(20,
//                         chassis.swing_max_voltage,
//                         chassis.turn_settle_error,
//                         chassis.turn_settle_time,
//                         timeout,
//                         chassis.turn_kp,
//                         chassis.turn_ki,
//                         chassis.turn_kd,
//                         chassis.turn_starti);
//   vex::task::sleep(1);
//    quitEvent();
//   Intake.spinFor(5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
//   vex::task::sleep(500);
//   chassis.turn_to_angle(-160,
//                         chassis.swing_max_voltage,
//                         chassis.turn_settle_error,
//                         chassis.turn_settle_time,
//                         timeout,
//                         chassis.turn_kp,
//                         chassis.turn_ki,
//                         chassis.turn_kd,
//                         chassis.turn_starti);
//   vex::task::sleep(1);
//   chassis.drive_distance(-14,
//                          -180,
//                          12,
//                          chassis.heading_max_voltage,
//                          chassis.drive_settle_error,
//                          chassis.drive_settle_time,
//                          timeout);
//   vex::task::sleep(1);
//   chassis.drive_distance(16,
//                          chassis.desired_heading,
//                          chassis.drive_max_voltage,
//                          chassis.heading_max_voltage,
//                          chassis.drive_settle_error,
//                          chassis.drive_settle_time,
//                          timeout);
//   vex::task::sleep(1);
//   chassis.turn_to_angle(-45,
//                         chassis.swing_max_voltage,
//                         chassis.turn_settle_error,
//                         chassis.turn_settle_time,
//                         timeout,
//                         chassis.turn_kp,
//                         chassis.turn_ki,
//                         chassis.turn_kd,
//                         chassis.turn_starti);
//   vex::task::sleep(1);
//   intakeInEvent.broadcast();
//   chassis.drive_distance(10,
//                          chassis.desired_heading,
//                          chassis.drive_max_voltage,
//                          chassis.heading_max_voltage,
//                          chassis.drive_settle_error,
//                          chassis.drive_settle_time,
//                          timeout);
// }

void farSide()
{
  int MAXVOLTAGE = 12;
  // setting up the robot
  rear_jack.set(false);

  rightDrive.setStopping(brake);
  leftDrive.setStopping(brake);
  rightDrive.stop();
  leftDrive.stop();
  odom_constants();
  chassis.set_coordinates(0, 0, -90);
  telemetry.broadcast();

  // Time for the fun stuff
  int timeout = 900;

  Intake.spinFor(-10, rotationUnits::rev, 100, velocityUnits::pct, false);
  vex::task::sleep(1200);
  Intake.stop();
  chassis.drive_distance(-18, -90, MAXVOLTAGE, chassis.heading_max_voltage, chassis.drive_settle_error, chassis.drive_settle_time, timeout);
  chassis.left_swing_to_angle(-120,
                              chassis.swing_max_voltage,
                              chassis.swing_settle_error,
                              chassis.swing_settle_time,
                              800,
                              chassis.swing_kp,
                              chassis.swing_ki,
                              chassis.swing_kd,
                              chassis.swing_starti);
  Y_CallBack();
  chassis.drive_distance(-10,
                         -120,
                         MAXVOLTAGE,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         timeout);
  chassis.turn_to_angle(-160,
                        12,
                        chassis.turn_settle_error,
                        chassis.turn_settle_time,
                        timeout,
                        chassis.turn_kp,
                        chassis.turn_ki,
                        chassis.turn_kd,
                        chassis.turn_starti);
  Y_CallBack();
  chassis.drive_distance(-14,
                         chassis.desired_heading,
                         12,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         timeout);
  chassis.turn_to_angle(0,
                        12,
                        chassis.turn_settle_error,
                        chassis.turn_settle_time,
                        timeout,
                        chassis.turn_kp,
                        chassis.turn_ki,
                        chassis.turn_kd,
                        chassis.turn_starti);
  Intake.spinFor(5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  chassis.drive_distance(-14,
                         chassis.desired_heading,
                         12,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         timeout);
  chassis.turn_to_angle(-160,
                        12,
                        chassis.turn_settle_error,
                        chassis.turn_settle_time,
                        timeout,
                        chassis.turn_kp,
                        chassis.turn_ki,
                        chassis.turn_kd,
                        chassis.turn_starti);
  chassis.drive_distance(-15,
                         chassis.desired_heading,
                         12,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         timeout);
  chassis.left_swing_to_angle(-90,
                              12,
                              chassis.swing_settle_error,
                              chassis.swing_settle_time,
                              timeout,
                              chassis.swing_kp,
                              chassis.swing_ki,
                              chassis.swing_kd,
                              chassis.swing_starti);
  Intake.spinFor(-55, rotationUnits::rev, 100, velocityUnits::pct, false);
  chassis.drive_distance(30,
                         -75,
                         12,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         timeout);
  vex::task::sleep(900);
  Intake.stop();
  chassis.turn_to_angle(75,
                        12,
                        chassis.turn_settle_error,
                        chassis.turn_settle_time,
                        timeout,
                        chassis.turn_kp,
                        chassis.turn_ki,
                        chassis.turn_kd,
                        chassis.turn_starti);
Intake.spinFor(10, rotationUnits::rev, 100, velocityUnits::pct, false);
  chassis.drive_distance(14,
                         chassis.desired_heading,
                         12,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         timeout);
}

void roscoeDash(){
  // setting up the robot
  rear_jack.set(false);

  rightDrive.setStopping(brake);
  leftDrive.setStopping(brake);
  rightDrive.stop();
  leftDrive.stop();
  odom_constants();
  chassis.set_coordinates(0, 0, -90);
  telemetry.broadcast();

  // Time for the fun stuff
  int timeout = 1250;
  
}