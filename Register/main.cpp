
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
char* regSol(char* token,MYSQL *conn){
    
    /*
     * Needs to be completed. I have no idea why I can make this work
     * Tested a lot of functions and got some SEGVs and 0 rows.
     * And results that aren't even in the database
     */
    
    char* regnr;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    unsigned long str_length;
    my_bool    is_null[3];
   /*
    * Validation
    */
    stmt = mysql_stmt_init(conn);
    char *sql="SELECT REGNR FROM registed WHERE Token=?";
    /*
     * Prepare the statement !
     */
    if(mysql_stmt_prepare(stmt,sql,strlen(sql))){
        fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(1);
    }
    
    /*
     * Once is prepared, now we need to bind to ? inputs.
     */
    memset(bind, 0, sizeof(bind)); //clears the structure.
    
    bind[0].buffer=(char*)token;
    bind[0].buffer_type=MYSQL_TYPE_STRING;
    bind[0].buffer_length=strlen(token);
    bind[0].is_null=0;
    bind[0].length=0;
    /*
     * Now we need to use what is above to BIND the input to the query
     * Somehow we need to fetch the results later.
     */
    if(mysql_stmt_bind_param(stmt,bind))
    {
      fprintf(stderr, " mysql_stmt_bind_result(), failed\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      exit(1);
    }    
    /*
     * Now execute.
     */
    int status=mysql_stmt_execute(stmt);
    fprintf(stdout,"Status:%d\n",status);
    
    do {
        int i;
        int num_fields;       /* number of columns in result */
        MYSQL_FIELD *fields;  /* for result set metadata */
        MYSQL_BIND *rs_bind;  /* for output buffers */

        /* the column count is > 0 if there is a result set */
        /* 0 if the result is only the final status packet */
        num_fields = mysql_stmt_field_count(stmt);

        if (num_fields > 0)
        {
          /* there is a result set to fetch */
          printf("Number of columns in result: %d\n", (int) num_fields);

          /* what kind of result set is this? */
          printf("Data: ");


          MYSQL_RES *rs_metadata = mysql_stmt_result_metadata(stmt);

          fields = mysql_fetch_fields(rs_metadata);

          rs_bind = (MYSQL_BIND *) malloc(sizeof (MYSQL_BIND) * num_fields);
          if (!rs_bind)
          {
            printf("Cannot allocate output buffers\n");
            exit(1);
          }
          memset(rs_bind, 0, sizeof (MYSQL_BIND) * num_fields);

          /* set up and bind result set output buffers */
          for (i = 0; i < num_fields; ++i)
          {
            rs_bind[i].buffer_type = fields[i].type;
            rs_bind[i].is_null = &is_null[i];

            switch (fields[i].type)
            {
              case 253:
                rs_bind[i].buffer = (char *) (token);
                rs_bind[i].buffer_length = sizeof (token);
                break;

              default:
                fprintf(stderr, "ERROR: unexpected type: %d.\n", fields[i].type);
                exit(1);
            }
          }

          status = mysql_stmt_bind_result(stmt, rs_bind);


          /* fetch and display result set rows */
          while (1)
          {
            status = mysql_stmt_fetch(stmt);

            if (status == 1 || status == MYSQL_NO_DATA)
              break;

            for (i = 0; i < num_fields; ++i)
            {
              switch (rs_bind[i].buffer_type)
              {
                case 253:
                  if (*rs_bind[i].is_null)
                    printf(" val[%d] = NULL;", i);
                  else
                    printf(" val[%d] = %s;",
                           i, ((char *) rs_bind[i].buffer));
                  break;

                default:
                  printf("  unexpected type (%d)\n",
                    rs_bind[i].buffer_type);
              }
            }
            printf("\n");
          }

          mysql_free_result(rs_metadata); /* free metadata */
          free(rs_bind);                  /* free output buffers */
        }
        else
        {
          /* no columns = final status packet */
          printf("End of procedure output\n");
        }

        /* more results? -1 = no, >0 = error, 0 = yes (keep looking) */
        status = mysql_stmt_next_result(stmt);
    } while (status == 0);
    
    return NULL;
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

