//
//  main.m
//  Macpro
//
//  Created by Tiko on 2018/4/20.
//  Copyright © 2018年 twx. All rights reserved.
//


#include "Prom.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        int command=0;
        int flag=1;
        
        while(flag==1){
            printf("\n");
            printf("\n");
            printf(" -----------------------------------------------\n");
            printf("|\t\t1.输出当前进程列表\t\t\t\t\t\t\t|\n");
            printf("|\t\t2.退出\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t3.创建一个进程\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t4.输出当前进程pid\t\t\t\t\t\t\t|\n");
            printf("|\t\t5.结束一个进程\t\t\t\t\t\t\t\t|\n");
            printf(" -----------------------------------------------\n");
            
            printf("Please input your command: ");
            scanf("%d",&command);
            
            switch(command){
                case 1: runningPro();break;
                case 2: flag=0;break;
                case 3: creatAPro();break;
                case 4: printf("当前进程pid为%d",getpid());break;
                case 5: endAPro();break;
                default: printf("Command error!\n");
            }
        }
    }
    return 0;
}
