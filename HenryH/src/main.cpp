/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      4/17/2025, 4:34:17 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
brain Brain;
 motor LF  (PORT6, ratio6_1, false);
 motor LB  (PORT11, ratio6_1, false);
 motor RF  (PORT9, ratio6_1, true);
 motor RB  (PORT20, ratio6_1, true);
 inertial gyr (PORT8);
competition Competition;
float D = 3.25;
float G = 0.6;
float P = M_PI;
// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
void drawOnScreen () {

Brain.Screen.print("The champions have risen");
Brain.Screen.printAt(60, 68, "Henry is King!!!!");
Brain.Screen.printAt(300, 68,  "Tianrui is King!!!!");
Brain.Screen.printAt(60, 203,  "Bradan:) is King!!!!");
Brain.Screen.printAt(300, 203,  "Henry is King!!!!");
Brain.Screen.printAt(160, 135,  "Soryra has always fallen!!!!");

}
int drawShape(){
  Brain.Screen.setPenWidth(20);
  Brain.Screen.setPenColor(purple);
  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(50, 50, 50, 50);
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(purple);
  Brain.Screen.setPenWidth(7);
  Brain.Screen.drawCircle(79, 79, 15);
  return 0;
}
void move(int lspeed, int rspeed, int wt){
  LF.spin(forward, lspeed, pct);
  LB.spin(forward, lspeed, pct);
  RF.spin(forward, rspeed, pct);
  RB.spin(forward, rspeed, pct);
  wait (wt, msec);
}
void stop(){
  LF.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);
}
<<<<<<< HEAD
void move_better(int tar){
float x = 0;
float err = tar - x;
float kp = 3.0;
float speed = err * kp;
RB.setPosition(0, rev);
while (fabs(err) > 0.25){
  move(speed, speed, 10);
  x = RB.position(rev)*D*G*P;
  float err = tar - x;
  float speed = err * kp;
}
stop();
}
=======

void Pturn(float targetDegrees) {
  float heading = gyr.rotation(deg);
  float error = targetDegrees - heading;
  float Kp = 0.5;
  float speed = Kp * error;

  while(fabs(error)> 5){//tolerance

  LF.spin(forward, -speed, pct);
  LB.spin(forward, -speed, pct);
  RF.spin(forward, speed, pct );
  RB.spin(forward, speed, pct);
wait
  heading = gyr.rotation(deg);
  error = heading - targetDegrees;
  speed = error * Kp;

  
  }
}



void move_better(float tar){
float p = M_PI;
float d = 3.25;
float g = 0.6;
float x = 0;
float err = tar - x;
float kp = 3.0;
float spe = kp*err;
LF.resetPosition();
while (fabs (err) > 0.5){
  move(spe, spe, 10);
  x = LF.position(rev)*p*d*g;
  err = tar - x;
  spe = kp*err;
}
stop();
}
void pri_gyr(){
  Brain.Screen.printAt(10, 20, "Headings = %0.1f", gyr.heading(deg));
  Brain.Screen.printAt(10, 40, "Rotaion = %0.1f", gyr.rotation(deg));
  Brain.Screen.printAt(10, 60, "Yaw = %0.1f", gyr.yaw(deg));
  Brain.Screen.printAt(10, 20, "Roll = %0.1f", gyr.roll(deg));
  Brain.Screen.printAt(10, 20, "Pitch = %0.1f", gyr.pitch(deg));
}
void turn(float deeg){
  if (deeg < 0){
    
    move(50, -  50, 30);
  }
  else if (deeg > 0){
    while(gyr.rotation(deg)<deeg){
    move(-50, 50, 30);
    
  }}
  stop();
  
}
>>>>>>> 96755f9f69753489ba905664c1a27c98f5374935
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
while(gyr.isCalibrating())wait(200, msec);


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
// ..........................................................................
Pturn(90);
wait(1000, msec)  ;
Pturn(-90);
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
    pri_gyr();
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

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
