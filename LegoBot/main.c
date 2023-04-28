#include <kipr/wombat.h>
/*
* (0-15 sec) Collect/sort poms in front and to the right of start box.
* (15-30 sec) Turn around and start driving to the left side of the field
* (30-45 sec) Collect/sort poms on left side of the field
* (45-60 sec) Deliver green poms to analysis lab
* (60-75 sec) Back out of analysis lab and turn towards right side of field
* (75-90 sec) Drive back across field
* (90-105 sec) Deliver red poms to cybersecurity lab
* (105-120 sec) Back up with 10 seconds extra time as buffer
*/

//port the pom sorter intake servo is in
int pomPort = 2;
//port the left drive motor is in
int lDrive = 0;
//port the right drive motor is in
int rDrive = 1;
//port the IR sensor for line following is in
int ir = 0;

//Function prototypes:
void intake(int preset);
void move_servo(int pos, int port, int delay);
//distance in cm
void drive(double distance, int speed);
//angle in deg - positive = ccw & negative = cw
void turn(int angle, int speed);
void line(double distance, int speed);

int main()
{
    //wait until lights are turned on to start moving (light sensor in port 1)
    wait_for_light(1);
	//shut down after 2 minutes
    shut_down_in(120);
    //turn on servos
    enable_servos();
    //open intake to collect red poms then drive forward
    intake(2);
    drive(10, 2000);
    //close intake then drive back
    intake(0);
    drive(-13, 2000);
    //turn towards green poms on left
    turn(28, 2000);
    //drive forward
    drive(12, 2000);
    //push both sets of poms against intake walls
    intake(2);
    intake(0);
    //turn back towards green pair on the right
    turn(-85, 2000);
    //drive forward
    drive(15, 2000);
    intake(2);
    //back up and position bot on line
    drive(-12, 2000);
    turn(7, 2000);
    drive(7, 2000);
    turn(-7, 2000);
    //drive forward along line and sort red 4-stack
    line(20, 1000);
    intake(0);
    //continue towards last pom stack
    line(19.75, 1000);
    intake(2);
    drive(5, 2000);
    //poms in center (bottom arm left, top arm right)
    //drive forward
    //turn around: second pom run
    intake(0);
    intake(2);
    //turn around
    turn(127, 2000);
    //drive forward sorting poms along the way
    intake(2);
    line(64, 2000);
    intake(0);
    turn(-2, 1000);
    line(19, 1000);
    intake(2);
    line(19, 1000);
    intake(0);
    line(18, 2000);
    intake(2);
    line(16.75, 2000);
    intake(0);
    intake(2);
    //turn towards analysis lab
    turn(135, 2000);
    //drive towards analysis lab
    drive(20, 2000);
    //set intake to release poms (open slightly on one side to prevent any catching on the top arm)
    intake(1);
    //turn to dislodge poms
    turn(-45, 2000);
    //drive back and forth
    drive(-30, 2000);
    drive(30, 2000);
    //back out of analysis lab
    drive(-45, 2000);
    //close intake all the way
    intake(0);
    //turn towards the right end of the field
    turn(85, 2000);
    //drive across the field
    drive(120, 2000);
    //turn towards cybersecurity lab
    turn(-90, 1000);
    //drive into cybersecurity lab
    drive(50, 2000);
    //open intake
    intake(2);
    //turn to dislodge poms
    turn(45, 1000);
    //drive back and forth to dislodge more
    drive(-15, 2000);
    drive(10, 2000);
    //back up
    drive(-20, 2000);
    
    //turn off motors and servos, then end the program
    ao();
   	disable_servos();
    return 0;
}

//move the intake to a preset position
void intake(int preset){
    //bottom right, center, left
    int pos[3] = {1000, 950, 100};
	move_servo(pos[preset], pomPort, 10);
}

//move a servo at a set speed
void move_servo(int pos, int port, int delay){
    while(get_servo_position(port) < pos){
        msleep(delay);
        int newPos = get_servo_position(port)+10;
        set_servo_position(port, newPos);
    }
    while(get_servo_position(port) > pos){
        msleep(delay);
        int newPos = get_servo_position(port)-10;
        set_servo_position(port, newPos);
    }
}

//drive at a set distance and speed
void drive(double distance, int speed){
	clear_motor_position_counter(lDrive);
	clear_motor_position_counter(rDrive);
    if(distance > 0){
        while(get_motor_position_counter(lDrive) < distance*100){
            mav(lDrive, speed*1.045);
            mav(rDrive, speed);
            msleep(10);
        }
        off(lDrive);
        off(rDrive);
    }
    else{
        while(get_motor_position_counter(lDrive) > distance*90.90909){
            mav(lDrive, -speed*1.045);
            mav(rDrive, -speed);
            msleep(10);
        }
        off(lDrive);
        off(rDrive);
    }
}

//turn at a set angle and speed
void turn(int angle, int speed){
    clear_motor_position_counter(lDrive);
	clear_motor_position_counter(rDrive);
    if(angle > 0){
        while(-get_motor_position_counter(lDrive) < angle*13.0719 ){
            mav(lDrive, -speed*1.045);
            mav(rDrive, speed);
            msleep(10);
        }
        off(lDrive);
        off(rDrive);
    }else{
        while(-get_motor_position_counter(lDrive) > angle*13.0719 ){
            mav(lDrive, speed*1.045);
            mav(rDrive, -speed);
            msleep(10);
        }
        off(lDrive);
        off(rDrive);
    }
}

//line following: turn back and forth whenever a change in color is detected under the robot to stay centered on the line
void line(double distance, int speed){
    clear_motor_position_counter(lDrive);
    while(abs(get_motor_position_counter(lDrive)) < distance*90.90909){
        if(analog(ir) < 1000){
			mav(lDrive, speed*1.045/4);
            mav(rDrive, speed);
            msleep(10);
            
        }
        if(analog(ir) >= 1000){
        	mav(lDrive, speed*1.045);
            mav(rDrive, speed/4);
            msleep(10);
        }
    }
    ao();
}
