#include <sstream>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <iostream>


int key_input(){
        struct termios oldattr, newattr;
        int c;

        // 1개의 키 입력 부분 (ubuntu terminal의 키입력(canonical, echo)를 끄고 키를 입력받아 변수 c에 저장)
        tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
        newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
        newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
        c = getchar();                       // 키보드 입력 읽음
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구

        return c;
}