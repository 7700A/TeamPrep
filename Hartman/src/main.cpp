/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Team7700                                                  */
/*    Created:      4/23/2025, 4:31:05 PM                                     */
/*    Description:  V5 project                                                */
/*    My robot is steve                                                                        */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
motor LFM(PORT2, ratio6_1, true);
motor LBM(PORT12, ratio6_1, true);
motor RFM(PORT5, ratio6_1, false);
motor RBM(PORT11, ratio6_1, false);
inertial gyropp (PORT4);
float dia = 4.00;
float GR = 1.00; 


void moverobot(int rspeed, int lspeed, int duration){
LFM.spin(forward, lspeed, pct);
LBM.spin(forward, lspeed, pct);
RFM.spin(forward, rspeed, pct);
RBM.spin(forward, rspeed, pct);

wait(duration, msec);


}


void stop(){
  LFM.stop(brake);
  LBM.stop(brake);
  RFM.stop(brake);
  RBM.stop(brake);
}

void inchDrive(int inches){
  float x = 0;
  float error = inches - x;
  float kp = 3.0;
  float speed = kp * error;

  LFM.setPosition(0, rev);

  while(fabs(error>0.5)){
    moverobot(speed, speed,5);
    x = LFM.position(rev)*3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482*dia*GR;
    error= inches-x;
    speed= kp * error;
  }
  stop();
  Brain.Screen.printAt(10, 20, "distance= %0.1f", x); 
}

void gyroprint(){
  float heading=gyropp.heading(deg);
  float rotation=gyropp.rotation(deg);
  Brain.Screen.clearScreen();
  //Brain.Screen.printAt(10,20, "Heading = %0.1f", heading);
  //Brain.Screen.printAt(10,40, "Rotation = %0.1f", rotation);
  //Brain.Screen.printAt(10,60, "Pitch = %0.1f", gyropp.pitch(deg));
  //Brain.Screen.printAt(10,80, "Yaw = %0.1f",gyropp.yaw(deg) );
  //Brain.Screen.printAt(10,100, "Heading = %0.1f", gyropp.roll(deg));
}

void gyroturn(float degrees){

  while(gyropp.rotation()<degrees){
    moverobot(-50,50,30);
   // wait(30,seconds);
  }
  stop();
}

void pturn(float degrees){
  float heading = gyropp.rotation(deg);
  float error = degrees - heading;
  float Kp = 0.5;
  float speed = error * Kp;
  gyropp.resetRotation();

  while(fabs(error)>5){
  
  moverobot(speed, - speed,30);
  heading = gyropp.rotation(deg);
  error = heading - degrees;
  speed = error * Kp;

  }
  stop();
}
  

void pre_auton(void) {

while(gyropp.isCalibrating())wait(200,msec);



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
 
 pturn(90);
 wait(1, sec);
 pturn(-90);
 gyroprint();
 //Brain.Screen.printAt(10,20, "Rotation = 90.06");
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
    
    gyroprint();

    wait(100, msec); // Sleep the task for a short amount of time to
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
