#include <kipr/wombat.h>

int main()
{
    printf("Hello World\n");
    enable_servos();
    
    int posCapsule[] = {1900, 100, c(2), c(3)};
    set_position(10, posCapsule);
    printf("turnd\n");
    
    msleep(500);
    
    posCapsule[0] = 1900;
    posCapsule[1] = 100;
    set_position(10, posCapsule);
    msleep(1000);
    printf("turnd2\n");
   
    
    disable_servos();
    return 0;
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
