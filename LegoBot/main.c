#include <kipr/wombat.h>
//TODO - don't put arm down for rack a stack until 

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
int armPort = 3;
int armFreeze = 0;
int clawPort = 0;
//port the left drive motor is in
int lDrive = 0;
//port the right drive motor is in
int rDrive = 1;
//port the IR sensor for line following is in
int ir = 0;
int ir2 = 1;
int ir3 = 3;
int btn = 0;

//Function prototypes:
void intake(int preset);
void arm(int preset);
void claw(int preset);
void move_servo(int pos, int port, int delay);
//distance in cm
void drive(double distance, int speed);
//angle in deg - positive = ccw & negative = cw
void turn(double angle, int speed);
void line(double distance, int speed);
void reverse_line(double distance, int speed);

int main()
{
    //turn on servos
    enable_servos();
    arm(0);
    msleep(1000);
    set_servo_position(pomPort, 100);
    claw(1);
    //wait until lights are turned on to start moving (light sensor in port 1)
    wait_for_light(5);
    //msleep(5000);
	//shut down after 2 minutes
    shut_down_in(120);
    //open intake to collect red poms then drive forward
    intake(2);
    drive(10, 2000);
    //close intake then drive back
    intake(0);
    drive(-15, 2000);
    //turn towards green poms on left
    turn(15, 1000);
    //msleep(5000);
    //drive forward
    drive(15, 2000);
    //push both sets of poms against intake walls
    intake(2);
    intake(0);
    //turn back towards green pair on the right
    turn(-80, 2000);
    //msleep(5000);
    //drive forward
    drive(12, 2000);
    intake(2);
    //back up and position bot on line
    drive(-12, 2000);
    turn(7, 2000);
    drive(7, 2000);
    turn(-7, 2000);
    //msleep(5000);
    //drive forward along line and sort red 4-stack
    line(16, 1000);
    intake(0);
    //continue towards last pom stack
    line(17, 1000);
    freeze(lDrive);
    freeze(rDrive);
    intake(2);
    drive(5, 2000);
    //poms in center (bottom arm left, top arm right)
    //drive forward
    //turn around: second pom run
    drive(25, 2000);
    drive(-7, 500);
    turn(126, 500);
    arm(1);
    claw(0);
    drive(-14.5, 2000);
    //get firewall
    claw(1);
    msleep(500);
    drive(10, 2000);
    arm(0);
    turn(12, 2000);
    //drive forward sorting poms along the way
    intake(2);
    //---------------------------insert alarm code--------------------
    line(5, 2000);
    double dist = 5;
    while(analog(ir2)<1000){
    	line(0.25, 2000);
        dist += 0.25;
    }
    reverse_line(dist, 2000);
    arm(0);
    arm(3);
    armFreeze = 1;
    while(analog(ir2)>1000){
    	turn(0.1, 500);
    }
    turn(2, 500);
    drive(-16, 2000);
    //msleep(5000);
    arm(0);
    line(12, 2000);
   /* while(analog(ir) < 1000){
    	drive(0.5, 2000);
    }*/
    //----------------------------------------------------------------
    //line(69, 2000);
    while(analog(ir3) < 1000){
    	line(0.25, 2000);
    }
    while(analog(ir3) > 1000){
    	line(0.25, 2000);
    }
    intake(0);
    turn(-2, 1000);
    line(6, 2000);
    intake(0);
    line(14, 2000);
    intake(2);
    line(14, 2000);
    intake(0);
    //old code for last two poms
    /*line(18, 2000);
    intake(2);
    line(16.75, 2000);
    intake(0);*/
    line(13, 2000);
    intake(2);
    turn(15, 2000);
    while(analog(ir2)<1000){
    	turn(0.25, 1000);
    }
    //arm down and back into ENC
    arm(1);
    intake(0);
    //intake(2);
    //intake(0);
    turn(-1, 2000);
    reverse_line(17, 1500);
    claw(0);
    intake(1);
    turn(3, 2000);
    turn(-3, 2000);
    turn(3, 2000);
    turn(-3, 2000);
    turn(2, 1000);
    turn(-2, 1000);
    freeze(lDrive);
    freeze(rDrive);
    //msleep(500);
    intake(0);
    /*int turned = 0;
    if(analog(ir) < 1000){
    	turn(5, 2000);
        turned = 1;
    }*/
    drive(10, 2000);
    line(10, 2000);
    intake(2);
    intake(0);
    /*if(turned == 1){
		turn(-5, 2000);    
    }*/
    //turn towards analysis lab
    arm(0);
    turn(-45, 2000);
    //drive towards analysis lab
    drive(17, 2000);
    drive(-15, 2000);
    drive(15, 2000);
    drive(-15, 2000);
    drive(15, 2000);
    turn(5, 2000);
    while(analog(ir) < 1000){
    	mav(lDrive, -2000);
        mav(rDrive, -2000);
        msleep(10);
    }
    drive(3, 2000);
    turn(45, 2000);
    line(45, 2000);
    turn(-15, 2000);
    drive(45, 2000);
    intake(2);
    drive(-20, 2000);
    drive(20, 2000);
    //reverse_line(5, 2000);
    turn(-20, 2000);
    while(analog(ir) < 1000){
    	mav(lDrive, -2000);
        mav(rDrive, -2000);
        msleep(10);
    }
    //drive(2, 2000);
    //turn(-2, 2000);
    reverse_line(40, 1400);
    while(analog(ir) < 1000){
    	turn(0.5, 1000);
    }
    line(10, 2000);
    turn(15, 2000);
    while(analog(ir2) < 1000){
    	turn(0.25, 1000);
    }
    intake(0);
    claw(1);
    arm(0);
    arm(5);
    armFreeze = 1;
    reverse_line(7.5, 2000);
    /*while(analog(ir2) > 1000){
    	turn(-1, 2000);
    }
    turn(-30, 2000);
    while(analog(ir2) < 1000){
        turn(-0.25, 2000);
    }*/
    turn(-100, 2000);
    turn(45, 2000);
    while(analog(ir2) < 1000){
    	turn(0.5, 1000);
    }
    claw(2);
    drive(-7, 1000);
    claw(3);
    msleep(500);
    arm(4);
    drive(10, 2000);
    turn(-30, 2000);
    while(analog(ir2) < 1000){
    	turn(-0.5, 2000);
    }
    turn(7, 2000);
    arm(1);
    claw(0);
    turn(2, 2000);
    arm(0);
    while(analog(ir2) < 1000){
    	turn(-0.5, 2000);
    }
    drive(-5, 2000);
    while(analog(ir2) < 1000){
    	turn(0.5, 2000);
    }
    reverse_line(5, 2000);
    while(analog(ir3) < 1000){
   		reverse_line(0.5, 2000);
    }
    turn(45, 1000);
    drive(-15, 1000);
    ao();
   	disable_servos();
    return 0;
}

//move the intake to a preset position
void intake(int preset){
    //bottom right, center, left
    int pos[3] = {1000, 600, 100};
	move_servo(pos[preset], pomPort, 5);
}

void arm(int preset){
    //up, down, rack-a-stack, alarm, remove noodle
	if(preset == 0){
        while(digital(btn) == 0){
    		mav(armPort, 500);
            msleep(10);
        }
        while(digital(btn) == 1){
    		mav(armPort, -100);
        }
        cmpc(armPort);
        ao();
    }
    else if(preset == 1){
    	while(gmpc(armPort) > -480){
        	mav(armPort, -500);
            msleep(10);
        }
        ao();
    }
    else if(preset == 2){
    	while(gmpc(armPort) > -330){
        	mav(armPort, -500);
            msleep(10);
        }
        ao();
    }
    else if(preset == 3){
    	while(gmpc(armPort) > -247){
        	mav(armPort, -500);
            msleep(10);
        }
        ao();
    }
    else if(preset == 4){
    	while(digital(btn) == 0){
    		mav(armPort, 1500);
            mav(lDrive, -100);
            mav(rDrive, -100);
            msleep(10);
        }
        while(digital(btn) == 1){
    		mav(armPort, -100);
        }
        cmpc(armPort);
        ao();
    }
    else if(preset == 5){
    	while(gmpc(armPort) > -300){
        	mav(armPort, -500);
            msleep(10);
        }
        ao();
    }
}

void claw(int preset){
	//open (fw), closed (fw), open (b drive), closed (b drive)
    int pos[4] = {450, 900, 800, 1150};
    move_servo(pos[preset], clawPort, 10);
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
            mav(lDrive, speed/**1.045*/);
            mav(rDrive, speed);
            if(armFreeze == 1){
                freeze(armPort);
            }
            msleep(10);
        }
        ao();
    }
    else{
        while(get_motor_position_counter(lDrive) > distance*90.90909){
            mav(lDrive, -speed/**1.045*/);
            mav(rDrive, -speed);
            if(armFreeze == 1){
                freeze(armPort);
            }
            msleep(10);
        }
        ao();
    }
}

//turn at a set angle and speed
void turn(double angle, int speed){
    clear_motor_position_counter(lDrive);
	clear_motor_position_counter(rDrive);
    if(angle > 0){
        while(-get_motor_position_counter(lDrive) < angle*13.0719){
            mav(lDrive, -speed/**1.045*/);
            mav(rDrive, speed);
            if(armFreeze == 1){
                freeze(armPort);
            }
            msleep(10);
        }
        ao();
    }else{
        while(-get_motor_position_counter(lDrive) > angle*13.0719){
            mav(lDrive, speed/**1.045*/);
            mav(rDrive, -speed);
            if(armFreeze == 1){
                freeze(armPort);
            }
            msleep(10);
        }
       	ao();
    }
}

//line following: turn back and forth whenever a change in color is detected under the robot to stay centered on the line
void line(double distance, int speed){
    clear_motor_position_counter(lDrive);
    while(abs(get_motor_position_counter(lDrive)) < distance*90.90909){
        if(analog(ir) < 1000){
			mav(lDrive, speed/4);
            mav(rDrive, speed);
            if(armFreeze == 1){
                freeze(armPort);
            }
            msleep(10);
            
        }
        if(analog(ir) >= 1000){
        	mav(lDrive, speed);
            mav(rDrive, speed/4);
            if(armFreeze == 1){
                freeze(armPort);
            }
            msleep(10);
        }
    }
    ao();
}

void reverse_line(double distance, int speed){
	cmpc(lDrive);
    while(abs(gmpc(lDrive))< distance*90.91){
    	if(analog(ir2)>1000){
            mav(rDrive, -speed/2);
            mav(lDrive, -speed);
            if(armFreeze == 1){
                freeze(armPort);
            }
            msleep(10);
        }
        if(analog(ir2)<1000){
            mav(lDrive, -speed/2);
            mav(rDrive, -speed);
            if(armFreeze == 1){
                freeze(armPort);
            }
            msleep(10);
        }
    }
    ao();
}
