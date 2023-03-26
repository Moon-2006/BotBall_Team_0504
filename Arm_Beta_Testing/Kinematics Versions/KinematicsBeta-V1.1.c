#include <math.h>
//NOTE: THIS CODE IS FOR AN ARDUINO UNO!! Written for my test setup at home- Uses different arm lenths and runs on an arduino, but the trig is the same

    // IMPORTANT ~ ~ ~
    int L = 25.5;
    /*SET THIS TO LENGTH OF ARM SEGMENT IN CM -- USE ONLY CM FOR MoveArm() FUNCTIONS!!!!*/
    
    //Variable placeholders
    float s0t = 0; //Base Rotation Horizontal
    float s1t = 0; //Base Joint Vertical
    float s2t = 0; //Elbow Joint
    float s3t = 0; //Wrist joint?
    float hyp = 1;
    float alphaRAD = 1;
    float tanAlpha = 0;
    float servoANGL = 0;

    //Other Variables
    int s0 = 4;
    int s1 = 0;
    int s2 = 1;
    int s3 = 2;
    int s4 = 3;
    int servoMult = 0;
    

void setup(){
  
   Serial.begin(9600);
   moveArm(1, 50);
    
}
void loop(){
  
}


int moveArm(int x, int y) {   
    //Calculations (dont touch em)
    hyp = sqrt(pow(x, 2)+pow(y, 2));
    alphaRAD = acos(hyp/(2*L));
    tanAlpha = atan(y/x);

    s1t = (tanAlpha)+(alphaRAD);
    s2t = (M_PI)-(2*alphaRAD);
    s3t = (((3*M_PI)/2) - s1t - s2t);

    Serial.println("Values:");
    Serial.println(s1t);
    Serial.println(s2t);
    Serial.println(s3t);    
    Serial.println(deg(s1t));
    Serial.println(deg(s2t));
    Serial.println(deg(s3t));


    //Moving servos to correct angles
    
}

double deg(double radians) {
  return radians * 180 / M_PI;
}
