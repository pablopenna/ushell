/*
    microShell.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include <unistd.h>//mypwd
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>//mmap
#include <dirent.h> //directory

#include "parser.h"
#include "myexec_command.h"

void show_command (command * C);
void exec_command (command * C);
void FINALexec_command (command * C, int * loop);

char baseDir [1024];//Used when calling mycd without arguments


int main ()
{
    command C;
    int r;
//----------------------------------------------------------
		getcwd(baseDir,1024);
		/*Setting baseDir as the dir 
		where the microshell is called*/
//----------------------------------------------------------

    printf ("Type commands (press Ctrl-D to finish)\n");

    do              // Read commands and show them
    {
        init_command (&C);

        printf ("$ ");
        r = read_command (&C, stdin);

        if (r < 0)
            fprintf (stderr, "\nError %d: %s\n",
                             -r, err_messages[-r]);
        else
            FINALexec_command (&C, &r);

        free_command (&C);
    }
    while (r==0);   // Repeat until error or EOF

    return 0;
}




void FINALexec_command(command * C, int * loop)
{
	if(C->argc==0)//To avoid segmentation fault;
	{
		return;
	}
//----------------------------------------------------
//mypwd

	if(strcmp(C->argv[0],"mypwd")==0)
	{
		if(C->argc>1)
		{
			printf("mypwd does not accept arguments\n");
			return;
		}
		else
		{
			mypwd();
		}
		return;
	}
//----------------------------------------------------
//mycd

	if(strcmp(C->argv[0],"mycd")==0)
	{
		if(C->argc==1)
		{
			mycd(baseDir);
			return;
		}
		if(C->argc==2)
		{
			mycd(C->argv[1]);
			return;
		}
		if(C->argc>2)
		{
			printf("More arguments than needed\n");
			return;
		}
		return;
	}
	
//----------------------------------------------------
//mycat

	if(strcmp(C->argv[0],"mycat")==0)
	{
		if(C->argc==1)
		{
			printf("Argument needed\n");
			return;
		}
		if(C->argc>2)
		{
			printf("More arguments than needed\n");
			return;
		}

		mycat(C->argv[1]);
		
		return;
	}
	
//----------------------------------------------------
//mycp

	if(strcmp(C->argv[0],"mycp")==0)
	{
		if(C->argc<3)//Check nº of arguments
		{
			printf("More arguments needed\n");
			return;
		}
		if(C->argc>3)//Check nº of arguments
		{
			printf("Too many arguments\n");
			return;
		}
		
		mycp(C->argv[1],C->argv[2]);
		return;
	}
	

//----------------------------------------------------
//mymkdir

	if(strcmp(C->argv[0],"mymkdir")==0)
	{
		if(C->argc==1)
		{
			printf("Argument needed\n");
			return;
		}
		if(C->argc>2)
		{
			printf("More arguments than needed\n");
			return;
		}
		
		mymkdir(C->argv[1]);

		return;
	}
//----------------------------------------------------
//myrmdir

	if(strcmp(C->argv[0],"myrmdir")==0)
	{
		if(C->argc==1)
		{
			printf("Argument needed\n");
			return;
		}
		if(C->argc>2)
		{
			printf("More arguments than needed\n");
			return;
		}
		
		myrmdir(C->argv[1]);
		return;
	}
//----------------------------------------------------
//myrm
		
	if(strcmp(C->argv[0],"myrm")==0)
	{
		if(C->argc==1)
		{
			printf("Argument needed\n");
			return;
		}
		if(C->argc>2)
		{
			printf("More arguments than needed\n");
			return;
		}
		
		myrm(C->argv[1]);
		return;
	}
//----------------------------------------------------
//myls

	if(strcmp(C->argv[0],"myls")==0)
	{
		if(C->argc>3)
		{
			printf("Incorrect number of arguments\n");
		}
		else
		{
			char currentwd [256];
			getcwd(currentwd,256);
			
			if(C->argc==1)
			{
				myls(currentwd,false);				
			}
			else
			{
				if(C->argc==2)
				{
					if(strcmp(C->argv[1],"-l")==0)
					{					
						myls(currentwd,true);
					}
					else
					{
						myls(C->argv[1],false);
					}
				}
				else
				{
					if(strcmp(C->argv[1],"-l")==0)
					{					
						myls(C->argv[2],true);
					}
					else
					{
						if(strcmp(C->argv[2],"-l")==0)
						{						
							myls(C->argv[1],true);
						}
						else
						{
							printf("One of the arguments is not valid\n");
						}					
					}	
				}	
			}
		
		}
		
		//myls(C->argv[1],false);
		//myls(C->argv[1],true);
		return;
	}

//----------------------------------------------------
//exit
	if(strcmp(C->argv[0],"exit")==0)
	{
		printf("exiting\n");
		*loop = 10;
	}
//----------------------------------------------------
//Unknown Command

	else
	{
		printf("unknown command\n");
		return;
	}
//----------------------------------------------------

}


