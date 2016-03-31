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

#include <mysql/mysql.h>//for structs here
#include <stdint.h>
unsigned int gen32int(void);
int isRegExist(char *regnr,MYSQL *conn);
char* isTokenExists(MYSQL *conn,char *token);
int db_regClient(char *token,char *regnr,MYSQL *conn);
int isAClient(MYSQL *conn,uint32_t IPv4Address,uint16_t portNumber);
int db_authClient(MYSQL *conn,uint32_t ip,uint16_t port,char *token);
#endif /* REGUTIL_H */

