/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "regutil.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
//#define _DEBUG_
uint32_t gen32int(void){
    time_t t;
    
    uint32_t rnd;
    int fd=open("/dev/urandom",O_RDONLY);
    read(fd,(void*)&rnd,sizeof(rnd));   
    close(fd);
    srand((unsigned)rnd);
    uint32_t x=rand()%899+100;
#ifdef _DEBUG_
    fprintf(stdout,"x=rand:%x\n",x);
#endif
    x<<=(rand()%3);
#ifdef _DEBUG_
    fprintf(stdout,"x<<=rand\%3:%x\n",x);
#endif
    if(x==0) //shouldnt.
        x=~x;
#ifdef _DEBUG_
    printf("NOT?:%x\n",x);
#endif
    x<<=22;
#ifdef _DEBUG_
    printf("shift 22 left:%x\n",x);
#endif
    x>>=22;
#ifdef _DEBUG_
    printf("shift 22 right:%x\n",x);
#endif
    return x;
}
