#include <ros/ros.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>

#define SPACEBAR 32
#define T 116
#define W 119
#define A 97
#define S 115
#define D 100
#define R 114
#define C 99
#define ENTER 10


int main(int argc, char **argv)
{
    ros::init(argc, argv, "jhdrone");

    ros::NodeHandle nh;
            
    while(ros::ok())
    {
    int c;
    
    struct termios oldattr, newattr;

    // 1개의 키 입력 부분 (ubuntu terminal의 키입력(canonical, echo)를 끄고 키를 입력받아 변수 c에 저장)
    tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
    newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
    newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
    c = getchar();                       // 키보드 입력 읽음
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구

    // spacebar키 입력의 명령 처리 : Guided모드 설정 및 arming
    if(c>0){
        ROS_INFO("%d", c);
        printf("printf test");}
    ros::spinOnce();
    }
    return 0;
}
