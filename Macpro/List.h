//
//  List.h
//  Macpro
//
//  Created by Tiko on 2018/4/20.
//  Copyright © 2018年 twx. All rights reserved.
//

#ifndef List_h
#define List_h

typedef struct listElemt {
    struct listElemt *forw;
    char* Pname;
    int Pid;
    struct listElemt *next;
} ListElemt;

/*删除元素*/
ListElemt* delElemt(ListElemt* list){
    ListElemt* tmp = list->forw;
    
    list->forw->next = list->next;
    
    return tmp;
}

/*初始化链表*/
void listInit(ListElemt* list){
    list->Pid = 0;
    list->Pname = 0;
    list->forw = NULL;
    list->next = NULL;
    return;
}

/*打印链表*/
void printList(ListElemt* list){
    while(list->forw!=NULL){
        printf("PID = %d   ",list->Pid);
        printf("name = %s\n",list->Pname);
        list = delElemt(list);
    }
    printf("PID = %d   ",list->Pid);
    printf("name = %s\n",list->Pname);
    //listInit(list);
}

/*添加元素*/
ListElemt* addElemt(ListElemt* list){
    NSMutableData* data = [NSMutableData dataWithLength:sizeof(ListElemt)];
    
    list->next=[data mutableBytes];
    list->next->forw=list;
    
    return list->next;
    
}

#endif /* List_h */
