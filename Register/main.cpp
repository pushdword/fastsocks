
/* 
 * File:   main.cpp
 * Author: pushdword
 *
 * Created on March 28, 2016, 12:08 AM
 */

/*
 * 0 ERROR
 * 1 OK
 * 2 REGISTED;REGNR
 * 3 ACKWAIT;REGNR
 */





//#define _DEBUG_
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifdef __APPLE__
    #include <mysql.h> //or mysql/mysql.h
#endif
#ifdef __linux__
    #include <mysql/mysql.h>
#endif
#define STRING_SIZE 256
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

/*
 * Thanks to http://www.erickcantwell.com/2011/08/mysql-prepared-statements-in-c/
 * 
 */
char* isTokenExists(MYSQL *conn,char *token){
    MYSQL_STMT *stmt;
    MYSQL_BIND param[1], result[1];
    const char *sql;
    
   sql = "SELECT `REGNR` FROM `registed` WHERE `token` = ?";

    int           param_count;
    short         small_data;
    int           int_data;
    char          str_data[STRING_SIZE];
    char          result_data[STRING_SIZE];
    unsigned long str_length;
    unsigned long data_length;
    my_bool       is_null;


    /* Initialize our statement */
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
      fprintf(stderr, " mysql_stmt_init(), out of memory\n");
      return NULL;
    }

    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
      fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      return NULL;
    }

    /* Zero out both the param and result data structures */
    memset(param, 0, sizeof(param));
    memset(result, 0, sizeof(result));

    /* STRING PARAM */
    param[0].buffer_type = MYSQL_TYPE_STRING;
    param[0].buffer = (char *)str_data;
    param[0].buffer_length = STRING_SIZE;
    param[0].is_null = 0;
    param[0].length = &str_length;

    result[0].buffer_type= MYSQL_TYPE_VAR_STRING;
    result[0].buffer = result_data;
    result[0].buffer_length = STRING_SIZE;
    result[0].is_null = 0;
    result[0].length = &data_length;

    /* Bind the parameters buffer */
    if (mysql_stmt_bind_param(stmt, param)) {
      fprintf(stderr, " mysql_stmt_bind_param() failed\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      return NULL;
    }

    /* Bind the results buffer */
    if (mysql_stmt_bind_result(stmt, result) != 0) {
      fprintf(stderr, " mysql_stmt_bind_result() failed\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      return NULL;
    }

    /* Specify the parameter that we send to the query */
    strncpy(str_data, token, STRING_SIZE);
    str_length= strlen(str_data);

    /* Execute the statement */
    if (mysql_stmt_execute(stmt)) {
      fprintf(stderr, " mysql_stmt_execute(), failed\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      return NULL;
    }

    /* Print our results */
    if(mysql_stmt_fetch (stmt) != 0) {
      return NULL;
    } 

    /* Close the statement */
    if (mysql_stmt_close(stmt)) {
      fprintf(stderr, " failed while closing the statement\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      return NULL;
    }
    char *ret = (char*)malloc(strlen(result_data)+1);
    strncpy(ret,result_data,strlen(result_data)+1);
    return ret;
}

char* regSol(char* token,MYSQL *conn,char *b){
    char regnr[STRING_SIZE]; //maximum size.
    char *tmp=isTokenExists(conn,token);
    if(tmp!=NULL){
        strncpy(regnr,tmp,strlen(tmp)+1);
        free(tmp);
    }
    else{
        free(tmp);
        return NULL; //didnt find token is db means client must ask for a reg number.
    }
    strncpy(b,regnr,strlen(regnr));//regnr can't be more than string_size
    return regnr;//pointer is not null.
}

int isTokenNotFromThisGuy(char *token,uint32_t hostIP,uint16_t port,MYSQL *conn){
    
#ifdef _DEBUG_

    fprintf(stdout,"DEBUG:token:%s IPv4:%u Port:%u\n",token,hostIP,port);

#endif    
    
    
    MYSQL_STMT *stmt;
    MYSQL_BIND param[3], result[1];
    const char *sql;
    sql = "SELECT `Token` FROM `clients` WHERE `ip` = ? AND `port` = ? AND `Token` = ?";
    char result_data[STRING_SIZE];
    unsigned long data_length;
    char str_data[STRING_SIZE];
    unsigned long str_length;
    /* Initialize our statement */
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
      fprintf(stderr, " mysql_stmt_init(), out of memory\n");
      return 1;
    }

    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
      fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      return 1;
    }

    /* Zero out both the param and result data structures */
    memset(param, 0, sizeof(param));
    memset(result, 0, sizeof(result));

    /* STRING PARAM */
    param[0].buffer_type = MYSQL_TYPE_LONG;
    param[0].buffer = (void *)&hostIP;
    param[0].is_null = 0;
    param[0].length = 0;
    param[0].is_unsigned=1;
    
    param[1].buffer_type = MYSQL_TYPE_LONG;
    param[1].buffer = (void *)&port;
    param[1].is_null = 0;
    param[1].length = 0;
    param[1].is_unsigned=1;
    
    param[2].buffer_type = MYSQL_TYPE_STRING;
    param[2].buffer = (char *)str_data;
    param[2].buffer_length = STRING_SIZE;
    param[2].is_null = 0;
    param[2].length = &str_length;
    
    result[0].buffer_type= MYSQL_TYPE_VAR_STRING;
    result[0].buffer = result_data;
    result[0].buffer_length = STRING_SIZE;
    result[0].is_null = 0;
    result[0].length = &data_length;

    /* Bind the parameters buffer */
    if (mysql_stmt_bind_param(stmt, param)) {
      fprintf(stderr, " mysql_stmt_bind_param() failed\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      return 1;
    }

    /* Bind the results buffer */
    if (mysql_stmt_bind_result(stmt, result) != 0) {
      fprintf(stderr, " mysql_stmt_bind_result() failed\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      return 1;
    }

    strncpy(str_data,token,strlen(token));
    str_length=strlen(str_data);
    /* Execute the statement */
    if (mysql_stmt_execute(stmt)) {
      fprintf(stderr, " mysql_stmt_execute(), failed\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      return 1;
    }

    /* Print our results */
    switch(mysql_stmt_fetch (stmt)){
        case 0:
            break;
        case 1:
            fprintf(stderr, " failed while fetching stmt\n");
            fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
            return 1;
        case MYSQL_NO_DATA:
            fprintf(stderr,"0MYSQL_NO_DATA\n");
            return 1;
        case MYSQL_DATA_TRUNCATED:
            fprintf(stderr,"0MYSQL_DATA_TRUNCATED\n");
            return 1;
    }

    /* Close the statement */
    if (mysql_stmt_close(stmt)) {
      fprintf(stderr, " failed while closing the statement\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      return 1;
    }
    if(strlen(result_data)>0){
        return 0;//found token
    }else{
        return -1;
    }
    return 0;
}

void doNewRegistation(char *token){
    /*
     * Generate a new reg number and put it into db. return to stdout the new Reg.
     * This call is only called when client is authed.
     * Authed is only and ONLY when his IP port and src Port number matches his connection into fastcocks service.
     * This service is the only one that can call this program
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
        fprintf(stderr,"0Error %s %u \n",mysql_error(conn),mysql_errno(conn));
        exit(1);
    }
    fprintf(stdout,"1OK\n");//connected
    
    switch(atoi(argv[1])){
        case 1:{//option is used when a client with a token wants to register into our db.
            if(!(strlen(argv[2])<=255 && strlen(argv[2])>=8)){fprintf(stdout,"0Need token,please auth\n");break;}
            char buffer[STRING_SIZE];
            memset(buffer,0,STRING_SIZE);
            if(regSol(argv[2],conn,buffer)!=NULL){
                fprintf(stdout,"2REGISTED;%s\n",buffer);
                return 0;
            }
            else{
                /*
                 * NULL returned. It is not registed. 
                 */
                if(argc!=5){
                    fprintf(stderr,"0Please provide the correct arguments\n");
                    exit(1);
                }
                //validation first.
                //from IP address and port number is matched the token provided?
                int r=isTokenNotFromThisGuy(argv[2],(uint32_t)strtoul(argv[3],0,10),(uint16_t)strtoul(argv[4],0,10),conn);
                if(r==-1){
                    fprintf(stderr,"0This client timed out or is trying to hack\n");
                    return 1;
                }
                else if(r==0){
                    /*
                     * this clients is authed now register.
                     */
                    doNewRegistation(argv[2]);
                    fprintf(stdout,"Registation completed?\n");
                    return 0;
                }
                
                //create a 3 random 3 digit number like XYZ-ABC-PTR
                char regnr[STRING_SIZE];
                
            }
            break;
        }
        case 2:{//option is used to auth a client into our db. ;)
            
            break;
        }
        default:
            fprintf(stderr,"0Error, invalid argument %s\n",argv[1]);
            break;
    }
    
    if(atoi(argv[1])==1 && (strlen(argv[2])<=255 && strlen(argv[2])>=8)){
        
        
    }
    mysql_close(conn);
    return 0;
}

