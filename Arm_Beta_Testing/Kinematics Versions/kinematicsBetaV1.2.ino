#include <math.h>
#include <Servo.h>

    // IMPORTANT ~ ~ ~
    float L = 10.5;
    /*SET THIS TO LENGTH OF ARM SEGMENT IN CM -- USE ONLY CM FOR MoveArm() FUNCTIONS!!!!*/
    
    //Variable placeholders
    float s0t = 0; //Base Rotation Horizontal
    float s1t = 0; //Base Joint Vertical
    float s2t = 0; //Elbow Joint
    float s3t = 0; //Wrist joint?
    float s1tD = 0; //Base Joint Vertical (Degrees)
    float s2tD = 0; //Elbow Joint
    float s3tD = 0; //Wrist joint?
    float hyp = 1;
    float alphaRAD = 1;
    float tanAlpha = 0;
    float servoANGL = 0;

    //Offset angles (for if you're lazy like me)

    float s1tOffset = 18;
    float s2tOffset = 30;
    float s3tOffset = 0;

    //Other Variables
    int s0 = 4;
    int s1 = 0;
    int s2 = 1;
    int s3 = 2;
    int s4 = 3;
    int servoMult = 0;

    Servo servo1;
    Servo servo2;
    

void setup(){
  
   Serial.begin(9600);

   //ARM POSITIONING --------------
   moveArm(10.5, 10.5);
   
   servo1.attach(8);
   servo2.attach(9);

  delay(500);
  Serial.println("Positioning in 3");
  delay(500);
  Serial.println("Positioning in 2");
  delay(500);
  Serial.println("Positioning in 1");
  delay(500);
  Serial.println("Positioning NOW");
  servo1.write(s1tD);
  servo2.write(s2tD);
  delay(3000);
    
}
void loop(){
  delay(500);
  servo1.write(s1tD);
  servo2.write(s2tD);
  delay(1000);
}


int moveArm(float x, float y) {   
    //Calculations (dont touch em)
    hyp = sqrt(pow(x, 2)+pow(y, 2));
    alphaRAD = acos(hyp/(2*L));
    tanAlpha = atan(y/x);

    s1t = (tanAlpha)+(alphaRAD);
    s2t = (M_PI)-(2*alphaRAD);
    s3t = (((3*M_PI)/2) - s1t - s2t);

    s1tD = deg(s1t) + s1tOffset;
    s2tD = 180- (deg(s2t) * 1.2 + 10);
    s3tD = deg(s3t) + s3tOffset;

    Serial.println("Values:");
    Serial.println(s1t);
    Serial.println(s2t);
    Serial.println(s3t);
    Serial.print("servo 1 Desired: ");    
    Serial.println(deg(s1t));
    Serial.print("servo 2 Desired: ");    
    Serial.println(deg(s2t));
    Serial.print("servo 3 Desired: ");    
    Serial.println(deg(s3t));    
    Serial.print("servo 1: ");    
    Serial.println(s1tD);
    Serial.print("servo 2: ");    
    Serial.println(s2tD);
    Serial.print("servo 3: ");    
    Serial.println(s3tD);


    //Moving servos to correct angles
    
}

double deg(double radians) {
  return radians * 180 / M_PI;
}
