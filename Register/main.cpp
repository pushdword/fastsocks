
/* 
 * File:   main.cpp
 * Author: pushdword
 *
 * Created on March 28, 2016, 12:08 AM
 */

#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <mysql.h> //or mysql/mysql.h
using namespace std;

const char *srv = "localhost";
const char *user= "fastsocks";
const char *pass="1q2w3e4r";
const char *db="register";
const unsigned int port = 3306;

const char *nixsocket = NULL;

unsigned int flag =0;



/*
 * Testing register API
 */

void displayActiveReg(MYSQL *conn){
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    mysql_query(conn,"SELECT REGNR,Token FROM Registed;");
    
    res = mysql_store_result(conn);
    
    while(row = mysql_fetch_row(res)){
        printf("REG: %s | Token: %s\n",row[0],row[1]);
    }
    mysql_free_result(res);
}

int main(int argc, char** argv) {
    
    
    MYSQL *conn;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn,srv,user,pass,db,port,nixsocket,flag)){
        fprintf(stderr,"\nError %s %d \n",mysql_error(conn),mysql_errno(conn));
        exit(1);
    }
    else{
        printf("Seems ok :P\n");
        displayActiveReg(conn);
    }
    
    mysql_close(conn);
    return 0;
}

