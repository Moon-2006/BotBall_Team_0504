#include <kipr/wombat.h>


void driveCM(int dist, int speed);
void turnLDeg(int dist, int speed);   
void turnRDeg(int dist, int speed);   
void fwd2tape();
void trnL2tape();
void trnR2tape();

int anglCount = 0;
int rM = 0;
int lM = 0;

int main()
{
    create_connect();
    
    fwd2tape();
    trnR2tape();
    
    
    create_disconnect();

    return 0;
}

void driveCM(int dist, int speed){
    set_create_distance(0);
    dist = (dist * 1) * 10;
    while(abs(get_create_distance()) < dist)
    {
        create_drive_direct(speed, speed);
        msleep(10);
        printf("driving\n");
        printf("dist: %d\n", dist);
        printf("dist: %d\n", (dist - get_create_distance()));
    }
}

void turnLDeg(int dist, int speed){
    set_create_total_angle(0);
    while(get_create_total_angle() < dist)
    {
        create_drive_direct(-speed, speed);
        msleep(10);
        printf("driving\n");
        printf("dist: %d\n", dist);
        printf("dist: %d\n", (dist - get_create_distance()));
    }
}

void turnRDeg(int dist, int speed)
{
    set_create_total_angle(0);
    while(abs(get_create_total_angle()) < abs(dist))
    {
        create_drive_direct(speed, -speed);
        msleep(10);
        printf("driving\n");
        printf("dist: %d\n", dist);
        printf("dist: %d\n", (dist - get_create_distance()));
    }
}

void fwd2tape()
{
    while(get_create_lcliff_amt()>2000 || get_create_rcliff_amt()>2000)
    {
        rM = 0;
        lM = 0;
        if(get_create_rcliff_amt()>2000)
        {
            rM = 1;
        }
        if(get_create_lcliff_amt()>2000)
        {
            lM = 1;
        }
        create_drive_direct((75 * lM), (75 * rM));
        printf("sensor reads %d\n", get_create_lfcliff_amt());
        msleep(10);
    }
    driveCM(7, 100);
}
void trnL2tape()
{
    create_drive_direct(-100, 100);
    msleep(500);
    while(get_create_lfcliff_amt()>2000)
    {
        create_drive_direct(-100, 100);
        printf("sensor reads %d\n", get_create_lfcliff_amt());
        msleep(10);
    }
}
void trnR2tape()
{
    create_drive_direct(100, -100);
    msleep(500);
    while(get_create_lfcliff_amt()>2000)
    {
        create_drive_direct(100, -100);
        printf("sensor reads %d\n", get_create_lfcliff_amt());
        msleep(10);
    }
    set_create_total_angle(0);
    while(get_create_rfcliff_amt()>2000)
    {
        create_drive_direct(-100, 100);
        printf("sensor reads %d\n", get_create_lfcliff_amt());
        msleep(10);
        anglCount ++;
    }
    turnRDeg((anglCount/2), 100);
}
