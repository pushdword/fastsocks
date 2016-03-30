/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   regutil.h
 * Author: pushdword
 *
 * Created on March 29, 2016, 11:52 PM
 */

#ifndef REGUTIL_H
#define REGUTIL_H

#ifndef STRING_SIZE 
    #define STRING_SIZE 256
#endif
#ifndef REG_SIZE 
    #define REG_SIZE 12
#endif
#include <mysql/mysql.h>//for structs here
unsigned int gen32int(void);
int isRegExist(char *regnr,MYSQL *conn);
char* isTokenExists(MYSQL *conn,char *token);
int db_regClient(char *token,char *regnr,MYSQL *conn);

#endif /* REGUTIL_H */

