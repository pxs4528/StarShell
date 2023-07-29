// The MIT License (MIT)
// 
// Copyright (c) 2016 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 5     // Mav shell only supports four arguments

#define N 15                    // max history


//Global variables for easy access

char *history[N];               //history array
char *pids[N];                  //pid array
int hist_last = 0;              //last index of history array
int pid_last = 0;               //last index of pid array


void add_to_history(char *command)
{
    //keep track of last 15 commands
    if(hist_last == N)
    {
      hist_last = 0;
    }
    history[hist_last] = (char*)malloc(MAX_COMMAND_SIZE);
    strcpy(history[hist_last], command);
    hist_last++;
}
void add_to_pids(char *pid)
{
    //keep track of last 15 pids
    if(pid_last == N)
    {
      pid_last = 0;
    }
    pids[pid_last] = (char*)malloc(MAX_COMMAND_SIZE);
    strcpy(pids[pid_last], pid);
    pid_last++;
}
void print_history()
{
    int i = 0;
    int p = 0;
    int j = hist_last;
    while(i < N)
    {
        if(history[j] != NULL)
        {
            printf("%d. %s", p, history[j]);
            p++;
        }
        j++;
        if(j == N)
        {
            j = 0;
        }
        i++;
    }
}

void print_history_with_pid()
{
    int i = 0;
    int p = 0;
    int j = pid_last;
    while(i < N)
    {
        if(history[j] != NULL)
        {
            printf("%d. %s", p, history[j]);
            printf("pid: %s\n", pids[p]);
            p++;
        }
        j++;
        if(j == N)
        {
            j = 0;
        }
        i++;
    }
}
int main()
{
  char * command_string = (char*)malloc(MAX_COMMAND_SIZE);
  char * command_string_n = (char*)malloc(MAX_COMMAND_SIZE);

  while(1)
  {
    char * path1 = (char*)malloc(255);
    strcpy(path1, "/bin/");
    char * path2 = (char*)malloc(255);
    strcpy(path2, "/usr/bin/");
    char * path3 = (char*)malloc(255);
    strcpy(path3, "/usr/local/bin/");
    // Print out the msh prompt

    // Read the command from the commandline.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something since fgets returns NULL when there
    // is no input
    
    if(command_string_n[0] != 0)
      {
        strcpy(command_string, command_string_n);
        command_string_n[0] = 0;
      }
      else
      {
        printf ("msh> ");
        while(!fgets (command_string, MAX_COMMAND_SIZE, stdin));
      }   

    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];

    for(int i = 0; i < MAX_NUM_ARGUMENTS; i++)
    {
      token[i] = NULL;
    }

    int token_count = 0;                                 
                                                           
    // Pointer to point to the token
    // parsed by strsep
    char *argument_ptr = NULL;                                         
                                                           
    char *working_string = strdup(command_string);                

    // we are going to move the working_string pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *head_ptr = working_string;

    // Tokenize the input strings with whitespace used as the delimiter
    while (((argument_ptr = strsep(&working_string, WHITESPACE)) != NULL) 
    && (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup(argument_ptr, MAX_COMMAND_SIZE);
      if(strlen(token[token_count]) == 0)
      {
        token[token_count] = NULL;
      }
      token_count++;
    }
    if(token[0] == NULL)
    {
      continue;
    }
    else
    {
      strcat(path1, token[0]);
      strcat(path2, token[0]);
      strcat(path3, token[0]);
      if(token[0][0] == '!')
      {
        int n = atoi(&token[0][1]);
        if(n < 0 || n > 14)
        {
          printf("Invalid command number.\n");
        }
        else
        {
          int i = 0;
          int j = hist_last;
          while(i < N)
          {
            if(history[j] != NULL)
            {
              if(n == 0)
              {
                printf("%s", history[j]);
                strcpy(command_string_n, history[j]);
                break;
              }
              n--;
            }
            j++;
            if(j == N)
            {
              j = 0;
            }
            i++;
          }
        }
      }
      else if(strcmp(token[0], "history") == 0)
      {
        char *pid3 = "-1";
        add_to_pids(pid3);
        add_to_history(command_string);
        if (token[1] != NULL)
        {
          if(strcmp(token[1], "-p") == 0)
          {
            print_history_with_pid();
          }
          else
          {
            printf("Invalid argument.\n");
          }
        }
        else
        {
          print_history();
        }
      }
      else if(strcmp(token[0], "exit") == 0 || strcmp(token[0], "quit") == 0)
      {
        return 0;
      }
      else if(!(strcmp(token[0], "exit") == 0 || strcmp(token[0], "quit") == 0  || strcmp(token[0], "ls") == 0 || 
      strcmp(token[0], "cd") == 0 || strcmp(token[0], "rmdir") == 0 || strcmp(token[0], "mkdir") == 0 || strcmp(token[0], "rm") == 0 
      || strcmp(token[0], "touch") == 0 || strcmp(token[0], "cp") == 0 || strcmp(token[0], "history") == 0 
      || strcmp(token[0], "./a.out") == 0 || strcmp(token[0], "diff") == 0 || access(path1, F_OK) == 0
      || access(path2, F_OK) == 0 || access(path3, F_OK) == 0))
      {
        pid_t pid_invalid = fork( );
        char *mypid = (char*)malloc(255);
        sprintf(mypid, "%d", pid_invalid);
        add_to_pids(mypid);
        if(pid_invalid == 0)
        {
          printf("%s: Command not found.\n", token[0]);
          exit(0);
        }
        else
        {
          wait(NULL);
        }
        add_to_history(command_string);
      }     
      else
      {
        add_to_history(command_string);
        pid_t pid = fork( );
        if (strcmp(token[0], "cd") != 0)
        {
          char *mypid1 = (char*)malloc(255);
          sprintf(mypid1, "%d", pid);
          add_to_pids(mypid1);
        }
        if(pid == 0 && strcmp(token[0], "cd") != 0)
        {
          char *arguments[4];
          if(token[1] == NULL)
          {
            arguments[0] = (char*) malloc( strlen(token[0]));
            strncpy( arguments[0], token[0], strlen(token[0]));
            arguments[1] = NULL;
          }
          else if(token[2] == NULL)
          {
            arguments[0] = (char*) malloc( strlen(token[0]));
            arguments[1] = (char*) malloc( strlen(token[1]));

            strncpy(arguments[0], token[0], strlen(token[0]));
            strncpy(arguments[1], token[1], strlen(token[1]));
            arguments[2] = NULL;
          }
          else if(token[3] == NULL)
          {
            arguments[0] = (char*) malloc(strlen(token[0]));
            arguments[1] = (char*) malloc(strlen(token[1]));
            arguments[2] = (char*) malloc(strlen(token[2]));

            strncpy(arguments[0], token[0], strlen(token[0]));
            strncpy(arguments[1], token[1], strlen(token[1]));
            strncpy(arguments[2], token[2], strlen(token[2]));

            arguments[3] = NULL;
          }
          // Notice you can add as many NULLs on the end as you want
          int ret = execvp( arguments[0], &arguments[0] );  
          if( ret == -1 )
          {

          }
        }
        else
        {
          if (strcmp(token[0], "cd") == 0)
          {
            char *pid4 = "-1";
            add_to_pids(pid4);
            chdir(token[1]);
          }
          int status;
          wait( & status );
        }
      }      //if the user entered ls then lets list the files in the current directory
    }
    // Cleanup allocated memory
    for(int i = 0; i < MAX_NUM_ARGUMENTS; i++)
    {
      if(token[i] != NULL)
      {
        free(token[i]);
      }
    }
    free(head_ptr);
  }
  free( command_string );
  return 0;
  // e2520ca2-76f3-90d6-0242ac120003
}