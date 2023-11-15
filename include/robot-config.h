using namespace vex;

extern brain Brain;

extern motor leftFront;
extern motor leftMiddle;
extern motor leftBack;
extern motor rightFront;
extern motor rightMiddle;
extern motor rightBack;

extern motor_group leftDrive;
extern motor_group rightDrive;

extern controller Controller1;

extern motor Lift;
extern motor Puncher;
extern inertial Inertial;

extern motor Intake;

extern triport ThreeWirePort;

extern digital_out Wing;
extern digital_out Foot;

// VEXcode devices

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );