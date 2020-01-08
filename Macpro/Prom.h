//
//  Prom.h
//  Macpro
//
//  Created by Tiko on 2018/4/20.
//  Copyright © 2018年 twx. All rights reserved.
//

#ifndef Prom_h
#define Prom_h
#import <Foundation/Foundation.h>
#import <sys/sysctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "List.h"

ListElemt* runningPro(){
    ListElemt *list=NULL;
    ListElemt firElemt;
    list=&firElemt;
    listInit(list);
    
    //指定名字参数，按照顺序第一个元素指定本请求定向到内核的哪个子系统，第二个及其后元素依次细化指定该系统的某个部分。
    //CTL_KERN，KERN_PROC,KERN_PROC_ALL 正在运行的所有进程
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL ,0};
    
    
    size_t miblen = 4;
    //值-结果参数：函数被调用时，size指向的值指定该缓冲区的大小；函数返回时，该值给出内核存放在该缓冲区中的数据量
    //如果这个缓冲不够大，函数就返回ENOMEM错误
    size_t size;
    //返回0，成功；返回-1，失败
    
    int st = sysctl(mib, (int)miblen, NULL, &size, NULL, 0);
    
    struct kinfo_proc * process = NULL;
    struct kinfo_proc * newprocess = NULL;
    do{
        size += size / 10;
        newprocess = realloc(process, size);
        if (!newprocess){
            if (process){
                free(process);
                process = NULL;
            }
            
        }
        process = newprocess;
        st = sysctl(mib, (int)miblen, process, &size, NULL, 0);
    } while (st == -1 && errno == ENOMEM);
    
    if (st == 0){
        if (size % sizeof(struct kinfo_proc) == 0){
            int nprocess =(int) size / sizeof(struct kinfo_proc);
            if (nprocess){
                for (int i = nprocess - 1; i >= 0; i--){
                    list->Pid = process[i].kp_proc.p_pid;
                    list->Pname = process[i].kp_proc.p_comm;
                    list = addElemt(list);
                }
                
                free(process);
                process = NULL;
            }
        }
    }
    list = list->forw;//回退指针
    printList(list);
    return list;
}

void creatAPro(){
    int error=0;
    printf("Please input the path of the app you want to open: ");
    NSString* com = @"cd ~";
    error=system([com UTF8String]);
    NSString *com1=@"open ";
    char ccom2[1000]={0};
    scanf("%s",ccom2);
    NSString* com2 = [NSString stringWithUTF8String:ccom2];
    com = [com1 stringByAppendingString:com2];
    error=system([com UTF8String]);
    if(error==0) printf("Path:%s had been opened.\n",ccom2);
    else printf("Error!\n");
}

void endAPro(){
    int pid=0;
    int error=0;
    printf("Please input the Pid you want to kill: ");
    scanf("%d",&pid);
    NSString* com1=@"kill ";
    NSString* com2=[NSString stringWithFormat:@"%d",pid];
    NSString* com = [com1 stringByAppendingString:com2];
    error=system([com UTF8String]);
    if(error==0) printf("Pid:%d had been killed.\n",pid);
    else printf("Error!\n");
}

#endif /* Prom_h */
