#include <kipr/wombat.h>
int armservo = 3;
int armposition = ;
int main()
   
{
    enable_servos();
    msleep(10);
    set_servo_position(armservo, armposition);
    msleep(5000); 
     set_servo_position(armservo, armposition);
    msleep(1000); 
    

}
