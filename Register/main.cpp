
/* 
 * File:   main.cpp
 * Author: pushdword
 *
 * Created on March 28, 2016, 12:08 AM
 */

#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#ifdef __APPLE__
    #include <mysql.h> //or mysql/mysql.h
#endif
#ifdef __linux__
    #include <mysql/mysql.h>
#endif
using namespace std;

const char *srv = "localhost";
const char *user= "fastsocks";
const char *pass="1q2w3e4r";
const char *db="register";
const unsigned int port = 3306;

const char *nixsocket = NULL;

unsigned int flag =0;

enum cmd{
    sol, //solicitation. it returns an registation number if sucessed.
    ack  //ack of solicitation
};


/*
 * Testing register API
 */

void displayActiveReg(MYSQL *conn){
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    mysql_query(conn,"SELECT REGNR,Token FROM registed;");
    
    res = mysql_store_result(conn);
    
    while(row = mysql_fetch_row(res)){
        printf("REG: %s | Token: %s\n",row[0],row[1]);
    }
    mysql_free_result(res);
}
char* regSol(char token,MYSQL *conn){
    MYSQL_RES *res;
    MYSQL_ROW row;
    
   /*
    * Validation
    */
}
int main(int argc, char** argv) {
    
    /*
     input validation
     * top 3 arguments
     */
    
    
    
    MYSQL *conn;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn,srv,user,pass,db,port,nixsocket,flag)){
        fprintf(stderr,"0Error %s %d \n",mysql_error(conn),mysql_errno(conn));
        exit(1);
    }
    else{
        printf("1OK\n");
        //displayActiveReg(conn);
    }
    if(atoi(argv[1])==cmd.sol && (strlen(argv[2])<=255 && strlen(argv[2])>=128)){
        //ok. its a solicitation.
        if(regSol(argv[2],conn)!=NULL){
            //registed.
            //
        }
    }
    mysql_close(conn);
    return 0;
}

