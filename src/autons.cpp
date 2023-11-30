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

void farSide()
{
  rear_jack.set(false);
  // intake_air.set(false);
  odom_constants();
  chassis.set_coordinates(0, 0, -15);
  telemetry.broadcast();
  // Time for the fun stuff

  // Dash to the first triball
  intakeInEvent.broadcast();
  chassis.drive_distance(52, -15);
  wait(200, msec);
  // chassis.drive_distance(-10);
  // wait(700, msec);
  chassis.turn_to_angle(90);
  wait(200, msec);
  // chassis.drive_distance(1);
  // wait(100, msec);
  // intake_air.set(true);
  Intake.spinFor(forward, -6, turns, 400, velocityUnits::rpm, false);
  wait(50, msec);

  chassis.drive_distance(17);
  wait(100, msec);
  chassis.drive_distance(-8);
  wait(100, msec);
  // chassis.turn_to_angle(-65);
  chassis.left_swing_to_angle(-45);
  // intake_air.set(false);
  wait(100, msec);
  // intakeEvent.broadcast();
  chassis.drive_distance(16);
  wait(100, msec);
  chassis.turn_to_angle(90);
  wait(200, msec);
  // intake_air.set(true);
  Intake.spinFor(forward, -6, turns, 400, velocityUnits::rpm, false);
  chassis.drive_distance(30);
  wait(100, msec);
  chassis.drive_distance(-3);
  wait(100, msec);
  chassis.turn_to_angle(225);
  wait(200, msec);
  chassis.drive_distance(15);
  wait(100, msec);
  // intake_air.set(false);
  chassis.drive_to_point(-27, 19);
  wait(100, msec);
  driveMotor.spinFor(forward, 4, turns, 600, velocityUnits::rpm, true);
  A_CallBack();
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
  chassis.set_coordinates(0, 0, -108);
  telemetry.broadcast();
  wait(1, timeUnits::sec);
  Puncher.spinFor(forward, 60, rotationUnits::rev, 600, velocityUnits::rpm, true); //activate puncher
  //  wait(200, timeUnits::msec);
  // cataReset(100);// cata reset
  LiftToggle("down");
  rear_jack.set(false);
  wait(300, timeUnits::msec);
  chassis.turn_to_angle(-70);
  wait(200, msec);
  // drive to other side of field
  chassis.drive_distance(-20, -70);
  wait(200, msec);
  chassis.turn_to_angle(-88);
  chassis.drive_distance(-75, chassis.desired_heading, 11, chassis.heading_max_voltage);
  //intake_air.set(true); //intake is up
  chassis.left_swing_to_angle(-180);
  wait(1, msec);
  wingValve(true);
  chassis.drive_distance(-24, chassis.desired_heading, 12, chassis.heading_max_voltage);
  wait(1, msec);
  wingValve(false);

  chassis.drive_distance(24);
  left_wing.set(false);
  wait(1, msec);
  chassis.turn_to_angle(-205);
  wait(1, msec);
  chassis.drive_distance(-50, chassis.desired_heading, 11, chassis.heading_max_voltage);
  wait(1, msec);
  chassis.right_swing_to_angle(-90);
  wait(1, msec);
  wingValve(true);
  chassis.drive_distance(-24, chassis.desired_heading, 12, chassis.heading_max_voltage);
  wait(1, msec);

  // chassis.turn_to_angle(-125);
  // wait(100, msec);
  // chassis.drive_distance(-15);
  // wait(100, msec);
  // chassis.drive_distance(17);
  // wait(100, msec);
  // chassis.turn_to_angle(-210);
  // wait(100, msec);
  // chassis.drive_distance(-10);
  // wait(100, msec);
  // chassis.right_swing_to_angle(-125);
  // wait(100, msec);
  // chassis.turn_to_angle(-125);
  // wait(100, msec);
  // chassis.drive_distance(-15);
  // wait(100, msec);
  // chassis.drive_distance(17);
  // wait(100, msec);

  // right swing to face goal
  //  chassis.right_swing_to_angle(-180);
  //  wait(200,msec);
  //  //deploy wings and run into goal
  //  wingValve(true);
  //  chassis.drive_distance(-20);
  //  wait(200,msec);
  //  chassis.drive_distance(20);
  //  wait(200,msec);
  //  //turn tangent to goal
  //  chassis.turn_to_angle(-235);
  //  wait(200,msec);
  //  //drive then swing around goal
  //  chassis.drive_distance(-15);
  //  wait(200,msec);
  //  chassis.left_swing_to_angle(-90);
  //  wait(200,msec);
}

// void skills()
// {

//   // rear_jack.set(false);
//   intake_air.set(false);
//   rightDrive.setStopping(brake);
//   leftDrive.setStopping(brake);
//   rightDrive.stop();
//   leftDrive.stop();
//   odom_constants();
//   chassis.set_coordinates(0, 0, -108);
//   telemetry.broadcast();
//   wait(1, timeUnits::sec);
//   // cataMotor.spinFor(forward, 70, rotationUnits::rev, 600, velocityUnits::rpm, true);
//   // cataMotor.spinFor(forward, 60, rotationUnits::rev, 600, velocityUnits::rpm, true);
//   wait(200, timeUnits::msec);
//   cataReset(100);
//   rear_jack.set(false);
//   wait(300, timeUnits::msec);
//   chassis.drive_distance(-15, -108);
//   wait(1, timeUnits::msec);
//   chassis.turn_to_angle(10);
//   wait(1, timeUnits::msec);
//   // chassis.drive_distance(70);
//   spinChassisMAX(900);
//   wait(1, timeUnits::msec);
//   chassis.turn_to_angle(90);
//   wait(1, timeUnits::msec);
//   chassis.drive_distance(70,
//                          chassis.desired_heading,
//                          12,
//                          chassis.heading_max_voltage,
//                          chassis.drive_settle_error,
//                          chassis.drive_settle_time,
//                          chassis.drive_timeout);
//   wait(1, timeUnits::msec);
//   chassis.turn_to_angle(-90);
//   intakeReverse(true);
//   wait(1, timeUnits::msec);
//   wingValve(true);
//   wait(1, timeUnits::msec);
//   // chassis.drive_distance(-30);
//   spinChassisReverseMAX(900);
//   wait(1, timeUnits::msec);
//   wingValve(false);
//   chassis.drive_distance(30);
//   wait(1, timeUnits::msec);
//   chassis.turn_to_angle(-100);
//   wait(1, timeUnits::msec);
//   wingValve(true);
//   // chassis.drive_distance(-30);
//   spinChassisReverseMAX(900);
//   wait(1, timeUnits::msec);
// }

void closeSide()
{
  rear_jack.set(false);
  // intake_air.set(false);
  rightDrive.setStopping(brake);
  leftDrive.setStopping(brake);
  rightDrive.stop();
  leftDrive.stop();
  odom_constants();
  chassis.set_coordinates(0, 0, 135);
  telemetry.broadcast();

  // Time for the fun stuff
  int timeout = 2000;

  Y_CallBack();
  chassis.drive_distance(-15,
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
  chassis.drive_distance(-12,
                         180,
                         12,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         timeout);
  task::sleep(1);
  Y_CallBack();
  chassis.drive_distance(13,
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
  A_CallBack();
  chassis.drive_distance(13,
                         135,
                         chassis.drive_max_voltage,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         chassis.drive_timeout);
  task::sleep(1);
  A_CallBack();
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
  chassis.drive_distance(43,
                         100,
                         10,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         chassis.drive_timeout);
}

void newCloseSide(){
  rear_jack.set(false);

  rightDrive.setStopping(brake);
  leftDrive.setStopping(brake);
  rightDrive.stop();
  leftDrive.stop();
  odom_constants();
  chassis.set_coordinates(0, 0, 115);
  telemetry.broadcast();

  // Time for the fun stuff
  int timeout = 2000;
  
  A_CallBack();
  chassis.turn_to_angle(90);
  task::sleep(500);
  // chassis.drive_distance(10,90);
  A_CallBack();
  chassis.right_swing_to_angle(115);
  task::sleep(500);
  Y_CallBack();
  chassis.drive_distance(-15,
                         115,
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
  chassis.drive_distance(-12,
                         180,
                         12,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         timeout);
  task::sleep(1);
  Y_CallBack();
  chassis.drive_distance(13,
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
  A_CallBack();
  chassis.drive_distance(13,
                         135,
                         chassis.drive_max_voltage,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         chassis.drive_timeout);
  task::sleep(1);
  A_CallBack();
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
  chassis.drive_distance(43,
                         100,
                         10,
                         chassis.heading_max_voltage,
                         chassis.drive_settle_error,
                         chassis.drive_settle_time,
                         chassis.drive_timeout);

}