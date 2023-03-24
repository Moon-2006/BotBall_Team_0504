#include <kipr/wombat.h>


    //IMPORTANT ~ ~ ~
    int L = 27;
    /*SET THIS TO LENGTH OF ARM SEGMENT IN CM -- USE ONLY CM FOR MoveArm() FUNCTIONS!!!!*/
    
    //Variable placeholders
    int s0t = 0; //Base Rotation Horizontal
    int s1t = 0; //Base Joint Vertical
    int s2t = 0; //Elbow Joint
    int s3t = 0; //Wrist joint?
    int hyp = 1;
    int alphaRAD = 1;
    int tanAlpha = 0;
    int servoANGL = 0;

    //Other Variables
    int s0 = 4;
    int s1 = 0;
    int s2 = 1;
    int s3 = 2;
    int s4 = 3;
    int servoMult = 0;


int main()
{
 
    enable_servos();
    
    moveArm(20, 20);
    
    disable_servos();
    return 0;
}


int moveArm(int x, int y)
{   
    //Calculations (dont touch em)
    hyp = sqrt(pow(x, 2)+pow(y, 2));
    alphaRAD = acos(hyp/(2*L));
    tanAlpha = atan(y/x);

    s1t = (tanAlpha)+(alphaRAD);
    s2t = 180-(2*alphaRAD);
    s3t = (270 - s1t - s2t);
    
    printf("S1t: %d\n", s1t);
    printf("S2t: %d\n", s2t);
    printf("S3t: %d\n", s3t);

    //Moving servos to correct angles
    
}


void set_position(int speed, int pos[4])
{
    int delta[4] = {(pos[0] - get_servo_position(0)),(pos[1] - get_servo_position(1)),(pos[2] - get_servo_position(2)),(pos[3] - get_servo_position(3))};
    int posCompletion[4] = {0, 0, 0, 0};

    while(sum(posCompletion) < 4)
    {
        int port = 0;
        while(port < 4)
        {
            if(delta[port] > speed){
                set_servo_position(port, get_servo_position(port)+speed);
            }
            if(delta[port] < -speed){
                set_servo_position(port, get_servo_position(port)-speed);
            }
            if(abs(delta[port]) <= speed){
                set_servo_position(port, pos[port]);
                posCompletion[port] = 1;
                printf("completed port - %d\n", port);
            }
            delta[port] = (pos[port] - get_servo_position(port));
            port++;
            msleep(5);
        }
    }
}

int c(port)
{
    return get_servo_position(port);
}

int sum(int array[])
{
    int i = 0;
    int result = 0;
    while(i < sizeof(array))
    {
        result += array[i];
        i++;
    }
    return result;
}