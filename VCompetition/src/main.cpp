/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      4/17/2025, 4:44:40 PM                                     */
/*    Description:  teamprep bot                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
motor LF (PORT2, ratio6_1, false);
motor LB (PORT12, ratio6_1, false);
motor RF (PORT5, ratio6_1, true);
motor RB (PORT11, ratio6_1, true);
inertial rol (PORT3);
/*lebron james is the goat slurp boba tea slurp tesla slurp fried chicken */
float WD = 3.25;
float GR = 0.75;

void robotDrive (int lspeed, int rspeed, int duration) {
  
  LF.spin(forward, lspeed, pct);
  LB.spin(forward, lspeed, pct);
  RF.spin(forward, rspeed, pct);
  RB.spin(forward, rspeed, pct);

  wait(duration, msec);
}

void stopRobot () {
  LF.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);
}



void inchDrive(float target) {
  float error = 0;
  float Kp = 3.0; 
  LF.resetPosition();
  float x = LF.position(rev)*WD*3.14* GR;
  error = target-x; 

  while(fabs (error ) > 0.5) {
   float speed= error* Kp;

    robotDrive(speed,speed,50);
    x = LF.position(rev)*WD*3.14* GR;
    error = target - x;
    speed= error* Kp;
    
  }
  stopRobot();
  Brain.Screen.printAt(10,20, "distance = %0.1f" , x);
}
void printGyro() {
  Brain.Screen.printAt(10,20, "Heading= %0.1f", rol.heading(deg));
  Brain.Screen.printAt(10,40, "Rotation= %0.1f", rol.rotation(deg));
  Brain.Screen.printAt(10,60, "Yaw= %0.1f", rol.yaw(deg));
  Brain.Screen.printAt(10,80, "Roll= %0.1f", rol.roll(deg));
   Brain.Screen.printAt(10,100, "Pitch= %0.1f", rol.pitch(deg));
}


void turn (float target){

  if(target > 0){
  while(rol.rotation(deg)<target){
    robotDrive(50,-50,30);
  }
  }
else if (target < 0) {
  while(rol.rotation(deg)>target){
    robotDrive(-50,50,30);
}
}
  stopRobot();
}

void pTurn(float target ) {
  float x = rol.rotation(deg);
  float error = target - x;
  float Kp = 0.45; 

  float speed = 0;
  while(fabs(error) > 5) {
    speed = Kp * error;
    robotDrive(-speed, speed, 30);
    error = target - x;
  }
  stopRobot();
}
  /*float x = 0;
  float error = inches - x;
  float Kp = 3.0;
  float speed = error *Kp;

  LF.setPosition(0, rev);

  while (fabs (error) > 0.5) {
    moveRobot(speed, speed, 10);
    x = LF.position(rev)*WD*M_PI*GR;
    error = inches - x;
    speed = error * Kp;
  }
stopRobot();
*/

void drawOnScreen () {
  Brain.Screen.printAt (240, 135, "MIDDLE");

  Brain.Screen.printAt (20, 80, "Left top coner");

  Brain.Screen.printAt (325, 80, "RIght top coner");

  Brain.Screen.printAt (315, 180, "Right bottom coner");



}

int drawShapes () {
  Brain.Screen.setPenColor(green);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawCircle (380, 80, 50);

  Brain.Screen.setPenColor(yellow);
  Brain.Screen.setPenWidth(10);
  Brain.Screen.drawRectangle(325, 35, 150, 125);

  return 0;
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
while(rol.isCalibrating())wait(0.2,sec);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  
inchDrive(10);
turn(90);
wait(500,msec);
turn(-90);

//lebron can shoot 3s lebron can still dunk lebron is just having fun carrying his team
/*i'm talking about lebron in the middle */
/*yeah yeah give me some time "high pitch noise"*/
//drive straight for time sharp u turn go back start stop robot
 //drawOnScreen ();
 //wait(1, sec);
 //Brain.Screen.clearScreen();
 //drawShapes(); 
 
  
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    printGyro();
    wait(200, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
