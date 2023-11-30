using namespace vex;
#include <string>

extern brain Brain;

extern motor leftFront;
extern motor leftMiddle;
extern motor leftBack;
extern motor rightFront;
extern motor rightMiddle;
extern motor rightBack;
extern motor_group driveMotor;

extern motor_group leftDrive;
extern motor_group rightDrive;

extern controller Controller1;

extern motor Lift;
extern motor Puncher;
extern inertial Inertial;

extern motor Intake;

extern digital_out left_wing;
extern digital_out right_wing;
extern digital_out rear_jack;

extern void X_CallBack();
extern void Y_CallBack();
extern void A_CallBack();
extern void B_CallBack();
extern digital_out liftLocker;
extern digital_out hanger;

extern void phoneHome();
extern vex::event telemetry;

extern void intakeUntilObject();
extern event intakeEvent;

extern void LiftToggle(std::string state);
extern void wingValve(bool state);

extern event intakeInEvent;
extern event intakeOutEvent;

// VEXcode devices

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );