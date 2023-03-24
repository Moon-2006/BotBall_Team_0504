//#include <kipr/wombat.h>


    //IMPORTANT ~ ~ ~
    int L = 27;
    /*SET THIS TO LENGTH OF ARM SEGMENT IN CM -- USE ONLY CM FOR MoveArm() FUNCTIONS!!!!*/
    
    //Variable placeholders
    int s0t = 0; //Base Rotation Horizontal
    double s1t = 0; //Base Joint Vertical
    double s2t = 0; //Elbow Joint
    double s3t = 0; //Wrist joint?
    double hyp = 1;
    double alphaRAD = 1;
    double tanAlpha = 0;
    double servoANGL = 0;

    //Other Variables
    int s0 = 4;
    int s1 = 0;
    int s2 = 1;
    int s3 = 2;
    int s4 = 3;
    int servoMult = 0;


int main()
{    
    moveArm(20, 20);
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

}
