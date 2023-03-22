//#include <kipr/wombat.h>

int main
{
    //IMPORTANT ~ ~ ~
    int L = 10;
    /*SET THIS TO LENGTH OF ARM SEGMENT IN CM -- USE ONLY CM FOR MoveArm() FUNCTIONS!!!!*/
    
    //Variable placeholders
    int s1t = 0;
    int s2t = 0;
    int s3t = 0;
    int hyp = 1;
    int alpha = 1;
    int tanAlpha = 0;
    int servoANGL = 0;

    //Other Variables
    int s1 = 0;
    int s2 = 1;
    int s3 = 2;
    int s4 = 3;
    int servoMult = 0;

    //Startup
    enable_servos();
    
    servoStartup();
    printf("attempted servo startup - function complete\n");
    msleep(5000); 

    disable_servos ();
    return 0;

}

void initateMove(int servo1, int servo2, int servo3)
{
    set_servo_deg(s1, s1t);
        msleep(100);
    set_servo_deg(s2, s2t);
        msleep(100);
    set_servo_deg(s3, s3t);
    msleep(700);
}

void servoStartup()
{
    printf("begenning servo startup\n")
    set_servo_deg(s1, 90);
    msleep(1000);
    set_servo_deg(s2, 90);
    msleep(1000);
    set_servo_deg(s3, 90);
    msleep(1000);
    ClwO();
    msleep(500);
    ClWC();
    msleep(500);
}

void set_servo_deg(int portNum, int angleDeg)
{
    servoANGL = angleDeg * servoMult
    set_servo_position(portNum, servoANGL)
}


void moveArm(int x, int y)
{   
    //Calculations (dont touch em)
    hyp = sqrt(pow(x, 2)+pow(y, 2));
    alpha = deg(acos(hyp/(2*L)));
    tanAlpha = deg(atan(y/x));

    s1t = (tanAlpha)+(alphaRAD);
    s2t = deg(180-(2*deg(alphaRAD)));
    s3t = (270 - s1t - s2t);

    //Moving servos to correct angles
    set_servo_deg(s1, s1t);
        msleep(100);
    set_servo_deg(s2, s2t);
        msleep(100);
    set_servo_deg(s3, s3t);
    msleep(700);
}

void Xslide(int dist)
{
    alpha = deg(acos(dist/(2*L)));
    beta = 180 - (2*alpha);
    s3t = (270 - s1t - s2t);

    set_servo_deg(s1, alpha);
    set_servo_deg(s2, beta);
    set_servo_deg(s3, s3t);
    msleep(1000);
}

void Yslide(int dist)
{
    alpha = 90 + (deg(acos(dist/(2*L))));
    beta = 180 - (2*alpha);
    s3t = (270 - s1t - s2t);

    set_servo_deg(s1, alpha);
    set_servo_deg(s2, beta);
    set_servo_deg(s3, s3t);
    msleep(1000);
}

void ClwO()
{
    set_servo_deg(s4, 30);
    msleep(100);
}

void ClwC()
{
    set_servo_deg(s4, 100);
    msleep(100);
}

void ClwDeg(int angle)
{
    set_servo_deg(s4, angle);
    msleep(100);
}

void deg(int radians)
{
    return radians * (180.0 / M_PI);
}