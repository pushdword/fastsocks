
/* 
 * File:   main.cpp
 * Author: pushdword
 *
 * Created on March 28, 2016, 12:08 AM
 */
#define _DEBUG_
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

void test(MYSQL *conn,char *token){
    
    MYSQL_STMT *stmt;
    char *sql;

    // Bind variables
    MYSQL_BIND param[1], result[1];

    char myString[12];
    my_bool is_null[1];

    sql = "select REGNR from registed where Token = ?";

    // Allocate statement handler
    stmt = mysql_stmt_init(conn);

    if (stmt == NULL) {
     fprintf(stdout, "Could not initialize statement handler");
     return;
    }

    // Prepare the statement
    if (mysql_stmt_prepare(stmt, sql, strlen(sql)) != 0) {
     fprintf(stdout, "Could not prepare statement");
     return;
    }

    // Initialize the result column structures
    memset (param, 0, sizeof (param)); /* zero the structures */
    memset (result, 0, sizeof (result)); /* zero the structures */

    // Init param structure
    // Select
    
    unsigned long int paramlen=15,resultlen=12;
    
    param[0].buffer_type     = MYSQL_TYPE_LONG;
    param[0].buffer         = (void *)token;
    param[0].is_null         = 0;
    param[0].length         = &paramlen;

    // Result
    result[0].buffer_type     = MYSQL_TYPE_LONG;
    result[0].buffer         = (void *)myString;
    result[0].is_null         = &is_null[0];
    result[0].length         = &resultlen;

    // Bind param structure to statement
    if (mysql_stmt_bind_param(stmt, param) != 0) {
     fprintf(stdout, "Could not bind parameters");
     return;
    }

    // Bind result
    if (mysql_stmt_bind_result(stmt, result) != 0) {
     fprintf(stdout, "Could not bind results");
     return;
    }

    // Set bind parameters
    //already setup?

    // Execute!!
    if (mysql_stmt_execute(stmt) != 0) {
     fprintf(stdout, "Could not execute statement");
     return;
    }

    if (mysql_stmt_store_result(stmt) != 0) {
     fprintf(stdout, "Could not buffer result set");
     return;
    }

    // Init data
    char *data = NULL;

    // Fetch
    if(mysql_stmt_fetch (stmt) == 0){
     data = myString;
    }
    fprintf(stdout,"token:%s\nDATA:%s\n\n",token,data);
    // Deallocate result set
    mysql_stmt_free_result(stmt); /* deallocate result set */

    // Close the statement
    mysql_stmt_close(stmt);
    
}

char* regSol(char* token,MYSQL *conn){
    
    test(conn,token);
    return NULL;
    
    /*
     * Needs to be completed. I have no idea why I can make this work
     * Tested a lot of functions and got some SEGVs and 0 rows.
     * And results that aren't even in the database
     */
    char* regnr;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    unsigned long int str_length=0;
   /*
    * Validation
    */
    stmt = mysql_stmt_init(conn);
    if(stmt==NULL){
        fprintf(stderr," mysql_stmt_init(), failed\n");
        fprintf(stderr, "%s\n",mysql_stmt_error(stmt));
        exit(1);
    }
    char *sql="SELECT REGNR FROM registed WHERE Token = ?";
    if(mysql_stmt_prepare(stmt,sql,strlen(sql))!=0){
        fprintf(stderr, " mysql_stmt_prepare(), SELECT failed?\n");
        fprintf(stderr, " %s %d\n", mysql_stmt_error(stmt),mysql_stmt_errno(stmt));
        exit(1);
    }

    memset(bind, 0, sizeof(bind)); //clears the structure.
    
    bind[0].buffer_type=MYSQL_TYPE_STRING;
    bind[0].buffer=(char*)token;
    bind[0].buffer_length=strlen(token)+1;
    bind[0].length= &str_length;
    bind[0].is_null=0;
    
    if(mysql_stmt_bind_param(stmt,bind)!=0)
    {
      fprintf(stderr, " mysql_stmt_bind_param(), failed\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      exit(1);
    }
    
    /*
     fetch data
     */
    
    //bind result
    
    
    MYSQL_BIND resbind[1];
    memset(resbind, 0, sizeof(resbind)); //clears the structure.
    unsigned long reslen=11; //always 11 or 0
    my_bool isnull[1];
    char mdata[11];
    resbind[0].buffer_type=MYSQL_TYPE_STRING;
    resbind[0].buffer=(void*)mdata;
    resbind[0].buffer_length=0;
    resbind[0].length=&reslen;

    if(mysql_stmt_bind_result(stmt,resbind)!=0){
        fprintf(stderr," mysql_stmt_bind_result(), failed\n");
        fprintf(stderr, "%s\n",mysql_stmt_error(stmt));
        exit(1);
    }
        
    if(mysql_stmt_execute(stmt)!=0){
        fprintf(stderr," mysql_stmt_execute(), failed\n");
        fprintf(stderr, "%s\n",mysql_stmt_error(stmt));
        exit(1);
    }
    fprintf(stdout,"Arrows:%llu\n",mysql_stmt_num_rows(stmt));
    
    if(mysql_stmt_store_result(stmt)!=0){
        fprintf(stderr," mysql_stmt_store_result(), failed\n");
        fprintf(stderr, "%s errno:%d\n",mysql_stmt_error(stmt),mysql_stmt_errno(stmt));
        exit(1);
    }

    
    
    if(mysql_stmt_fetch(stmt)==1){
        fprintf(stderr," mysql_stmt_fetch(), failed\n");
        fprintf(stderr, "%s\n",mysql_stmt_error(stmt));
        exit(1);
    }

    if (reslen>0) //size of buffer?
    {        
        if(mysql_stmt_fetch_column(stmt, bind, 0, 0)!=0){
            fprintf(stderr," mysql_stmt_fetch_column(), failed\n");
            fprintf(stderr, "%s\n",mysql_stmt_error(stmt));
            exit(1);
        }
        
        return "1";
    }
    else{
        fprintf(stdout,"No data returned\n");
        return NULL;
    }
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
    else{
        printf("1OK\n");
        //displayActiveReg(conn);
    }
#ifdef _DEBUG_
    fprintf(stdout,"DEBUG CMD:%d,TOKEN:%s\n",atoi(argv[1]),argv[2]);
#endif
    if(argc<=1){
        //ok. its a solicitation.
        if(regSol(argv[2],conn)!=NULL){
            //registed.
            fprintf(stdout,"Registed?\n");
        }
    }else{
        if(atoi(argv[1])==1 && (strlen(argv[2])<=255 && strlen(argv[2])>=8)){
            //ok. its a solicitation.
            if(regSol(argv[2],conn)!=NULL){
                //registed.
                fprintf(stdout,"Registed?\n");
            }
        }
   
        else{
#ifdef _DEBUG_
            fprintf(stderr,"DEBUG Parse incorrect!\n");
            exit(1);
#endif
        }
    }
    mysql_close(conn);
    return 0;
}

