int main{

    set_position(10, {400, 1900, c(2), c(3)})
}

void set_position(int speed, int pos[4])
{
    int delta[4] = {(pos[0] - get_servo_position(0)),(pos[1] - get_servo_position(1)),(pos[2] - get_servo_position(2)),(pos[3] - get_servo_position(3))};
    int posCompletion = 0;

    while(posCompletion < 4)
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
            if(abs(delta[port]) < speed){
                set_servo_position(port, pos[port]);
                posCompletion++;
            }
            port++;
        }
    }
}