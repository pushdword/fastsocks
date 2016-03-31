/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "regutil.h"
#include "regmacros.h"
#include "debug.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef __APPLE__
    #include <mysql.h> //or mysql/mysql.h
#elif defined(__linux__)
    #include <mysql/mysql.h>
#else
    #include <mysql/mysql.h>
#endif


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
      _debugd(" mysql_stmt_init(), out of memory\n");
      return NULL;
    }

    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
      _debugd(" mysql_stmt_prepare(), INSERT failed\n");
      _debugd(" %s\n", mysql_stmt_error(stmt));
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
      _debugd(" mysql_stmt_bind_param() failed\n");
      _debugd(" %s\n", mysql_stmt_error(stmt));
      return NULL;
    }

    /* Bind the results buffer */
    if (mysql_stmt_bind_result(stmt, result) != 0) {
      _debugd(" mysql_stmt_bind_result() failed\n");
      _debugd(" %s\n", mysql_stmt_error(stmt));
      return NULL;
    }

    /* Specify the parameter that we send to the query */
    strncpy(str_data, token, STRING_SIZE);
    str_length= strlen(str_data);

    /* Execute the statement */
    if (mysql_stmt_execute(stmt)) {
      _debugd(" mysql_stmt_execute(), failed\n");
      _debugd(" %s\n", mysql_stmt_error(stmt));
      return NULL;
    }

    /* Print our results */
    if(mysql_stmt_fetch (stmt) != 0) {
      return NULL;
    } 

    /* Close the statement */
    if (mysql_stmt_close(stmt)) {
      _debugd(" failed while closing the statement\n");
      _debugd(" %s\n", mysql_stmt_error(stmt));
      return NULL;
    }
    char *ret = (char*)malloc(strlen(result_data)+1);
    strncpy(ret,result_data,strlen(result_data)+1);
    return ret;
}
int isRegExist(char *regnr,MYSQL *conn){
    MYSQL_STMT *stmt;
    MYSQL_BIND param[1];
    const char *sql;
    char reg_query[REG_SIZE];
    sql = "SELECT Count(*) FROM `registed` WHERE `REGNR` = ?";
    unsigned long reg_len=REG_SIZE;

    /* Initialize our statement */
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
      _debugd(" mysql_stmt_init(), out of memory\n");
      return -1;
    }

    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
      _debugd(" mysql_stmt_prepare(), INSERT failed\n");
      _debugd(" %s\n", mysql_stmt_error(stmt));
      return -1;
    }

    /* Zero out both the param and result data structures */
    memset(param, 0, sizeof(param));

    /* STRING PARAM */
    param[0].buffer_type = MYSQL_TYPE_STRING;
    param[0].buffer = (char *)reg_query;
    param[0].buffer_length = REG_SIZE;
    param[0].is_null = 0;
    param[0].length = &reg_len;

    /* Bind the parameters buffer */
    if (mysql_stmt_bind_param(stmt, param)) {
      _debugd(" mysql_stmt_bind_param() failed\n");
      _debugd(" %s\n", mysql_stmt_error(stmt));
      return -1;
    }
    
    /* Specify the parameter that we send to the query */
    strncpy(reg_query, regnr, REG_SIZE);
    /* Execute the statement */
    if (mysql_stmt_execute(stmt)) {
      _debugd(" mysql_stmt_execute(), failed\n");
      _debugd(" %s\n", mysql_stmt_error(stmt));
      return -1;
    }

    /* Print our results */
    int r=mysql_stmt_fetch (stmt);

    /* Close the statement */
    if (mysql_stmt_close(stmt)) {
      _debugd(" failed while closing the statement\n");
      _debugd(" %s\n", mysql_stmt_error(stmt));
      return -1;
    }
    return r;
}
//return affected rows - 0 if not success or 1 on success
int db_regClient(char *token,char *regnr,MYSQL *conn){
    MYSQL_STMT *stmt;
    MYSQL_BIND insert[2];
    char token_s[STRING_SIZE];
    char regnr_s[REG_SIZE];
    char *SQL_Q="INSERT INTO registed(REGNR,Token) VALUES(?,?)";
    uint64_t regnr_s_len=REG_SIZE,token_s_len=strlen(token);
    memset(token_s,0,STRING_SIZE);
    memset(regnr_s,0,REG_SIZE);
    memset(insert,0,sizeof(insert));
    stmt = mysql_stmt_init(conn);
    if(!stmt){
        _debugd("mysql_stmt_init() failed\n");
        _debugd("Errno:%u\n%s\n",mysql_stmt_errno(stmt),mysql_stmt_error(stmt));
        exit(1);
    }
    
    insert[0].buffer=regnr_s;
    insert[1].buffer=token_s;
    insert[0].buffer_length=REG_SIZE;
    insert[1].buffer_length=STRING_SIZE;
    insert[0].is_null=0;
    insert[1].is_null=0;
    insert[0].buffer_type=MYSQL_TYPE_STRING;
    insert[1].buffer_type=MYSQL_TYPE_STRING;
    insert[0].length=&regnr_s_len;
    insert[1].length=&token_s_len;
    
    /*
     * Bind stuff
     */
    strncpy(regnr_s,regnr,REG_SIZE);
    strncpy(token_s,token,strlen(token));
    
    if (mysql_stmt_prepare(stmt, SQL_Q, strlen(SQL_Q))){
      _debugd("\n mysql_stmt_prepare(), INSERT failed");
      _debugd("\n %s", mysql_stmt_error(stmt));
      exit(1);
    }
    
    
    if(mysql_stmt_bind_param(stmt,insert)){
        _debugd("mysql_stmt_bind_param(), BIND failed\n");
        _debugd("Errno:%u\n%s\n",mysql_stmt_errno(stmt),mysql_stmt_error(stmt));
        exit(1);
    }
    if(mysql_stmt_execute(stmt)){
        _debugd("mysql_stmt_execute(), EXECUTE failed\n");
        _debugd("Errno:%u\n%s\n",mysql_stmt_errno(stmt),mysql_stmt_error(stmt));
        exit(1);
    }
    int f=mysql_stmt_affected_rows(stmt);
    _debugd("Rows affected:%d\n",f);
    return f;
}
int isAClient(MYSQL *conn,uint32_t ip,uint16_t port){
    MYSQL_STMT *stmt;
    MYSQL_BIND input[2];
    
    char *SQL_Q = "SELECT Count(*) FROM clients WHERE ip = ? AND port = ?";
    
    uint32_t ip_in;
    uint16_t port_in;
    
    memset(input,0,sizeof(input));
    
    stmt = mysql_stmt_init(conn);
    if(!stmt){
        _debugd("mysql_stmt_init(), failed\n");
        _debugd("%s\n",mysql_stmt_error(stmt));
        exit(1);
    }
    
    input[0].buffer=(void*)&ip_in;
    input[0].buffer_length=0;
    input[0].is_null=0;
    input[0].buffer_type=MYSQL_TYPE_LONG;
    input[0].is_unsigned=1;
    
    input[1].buffer=(void*)&port_in;
    input[1].buffer_length=0;
    input[1].is_null=0;
    input[1].buffer_type=MYSQL_TYPE_SHORT;
    input[1].is_unsigned=1;
    
    if(mysql_stmt_prepare(stmt,SQL_Q,strlen(SQL_Q))){
        _debugd("mysql_stmt_prepare(), failed\n");
        _debugd("%s\n",mysql_stmt_error(stmt));
        exit(1);
    }
    ip_in=ip;
    port_in=port;
    if(mysql_stmt_bind_param(stmt,input)){
        _debugd("mysql_stmt_bind_param(), failed\n");
        _debugd("%s\n",mysql_stmt_error(stmt));
        exit(1);
    }
    
    if(mysql_stmt_execute(stmt)){
        _debugd("mysql_stmt_execute(), failed\n");
        _debugd("%s\n",mysql_stmt_error(stmt));
        exit(1);
    }
    switch(mysql_stmt_fetch(stmt)){
        case 0:
            if (mysql_stmt_close(stmt)) {
                _debugd(" failed while closing the statement\n");
                _debugd(" %s\n", mysql_stmt_error(stmt));
                return -1;
            }
            return 1;//yes
            break;
        case 1:
            _debugd("mysql_stmt_fetch(), failed\n");
            _debugd("%s\n", mysql_stmt_error(stmt));
            return -1;
        case MYSQL_NO_DATA:
            _debugd("0MYSQL_NO_DATA\n");
            return 1;
        case MYSQL_DATA_TRUNCATED:
            _debugd("0MYSQL_DATA_TRUNCATED\n");
            return 1;
    }

    return -1;
}
int db_authClient(MYSQL *conn,uint32_t ip,uint16_t port,char *token){
    MYSQL_STMT *stmt;
    MYSQL_BIND input[3];
    char *SQL_Q = "INSERT INTO clients(Token,ip,port) VALUES(?,?,?)";
    char token_in[STRING_SIZE];
    uint64_t token_in_len=STRING_SIZE;
    uint32_t ip_in;
    uint16_t port_in;
    memset(input,0,sizeof(input));
    stmt = mysql_stmt_init(conn);
    if(!stmt){
        _debugd("mysql_stmt_init(), failed\n");
        _debugd("%s\n",mysql_stmt_error(stmt));
        exit(1);
    }
    
    /*
     * GenToken
     */
    
    snprintf(token_in,STRING_SIZE,"%u.%u.%u.%u.%u",gen32int(),gen32int(),gen32int(),gen32int(),gen32int());
    strncpy(token,token_in,STRING_SIZE);
    
    input[0].buffer=(void*)&token_in;
    input[0].buffer_length=STRING_SIZE;
    input[0].is_null=0;
    input[0].buffer_type=MYSQL_TYPE_STRING;
    input[0].length=&token_in_len;
    
    input[1].buffer=(void*)&port_in;
    input[1].buffer_length=0;
    input[1].is_null=0;
    input[1].buffer_type=MYSQL_TYPE_LONG;
    input[1].is_unsigned=1;
    
    input[2].buffer=(void*)&port_in;
    input[2].buffer_length=0;
    input[2].is_null=0;
    input[2].buffer_type=MYSQL_TYPE_SHORT;
    input[2].is_unsigned=1;
    
    ip_in=ip;
    port_in=port;
    
    if(mysql_stmt_prepare(stmt,SQL_Q,strlen(SQL_Q))){
        _debugd("mysql_stmt_prepare(), failed\n");
        _debugd("%s\nerrno:%d",mysql_stmt_error(stmt),mysql_stmt_errno(stmt));
        exit(1);
    }

    if(mysql_stmt_bind_param(stmt,input)){
        _debugd("mysql_stmt_bind_param(), failed\n");
        _debugd("%s\n",mysql_stmt_error(stmt));
        exit(1);
    }
    
    if(mysql_stmt_execute(stmt)){
        _debugd("mysql_stmt_execute(), failed\n");
        _debugd("%s\n",mysql_stmt_error(stmt));
        exit(1);
    }
    switch(mysql_stmt_affected_rows(stmt)){
        case 0:
            return 0;//yes
            break;
        case -1:
            _debugd("mysql_stmt_fetch(), failed\n");
            _debugd("%s\nErrno:%d\n", mysql_stmt_error(stmt),mysql_stmt_errno(stmt));
            return -1;
    }
    return -1;
}