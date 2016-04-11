/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   regmacros.h
 * Author: pushdword
 *
 * Created on March 31, 2016, 12:58 AM
 */

#ifndef REGMACROS_H
#define REGMACROS_H
#define MAX_FIELD_LEN 32
#ifndef STRING_SIZE 
    #define STRING_SIZE 255
#endif
#ifndef REG_SIZE 
    #define REG_SIZE 12
#endif
#ifndef _debugd
#define _debugd(fmt, args...) fprintf(stderr, fmt, ##args);
#endif
#ifndef _debugi
#define _debugi(fmt, args...) fprintf(stdout, fmt, ##args);
#endif
#endif /* REGMACROS_H */

