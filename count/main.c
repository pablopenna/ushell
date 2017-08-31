#include <stdio.h>
#include <stdlib.h> // for atoi()
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "readchar_R.h"
#include "count_M.h"

int main(int argc, char ** argv)
{

	
	
	if(argc!=4)
	{
		printf("Number of arguments is wrong\n");
	}
	else
	{
		printf("\n\tWELCOME\n");
	
		printf("trying to open file: %s\n",argv[2]);
		int fd = open(argv[2],O_RDONLY);
		if(fd!=-1)
		{
			printf("Opening successful\n");
		}	
		else
		{
			printf("Error at opening the file\n");
			return -1;	
		}


		if(strcmp("R",argv[1])==0)
		{
			printf("\nUsing readchar_R\n");
			printf("File specified: %s\n",argv[2]);
			printf("Char to look for is: %c\n", argv[3][0]);
			
			char searchedChar = argv[3][0];
			
			int fileSize = lseek(fd,0,SEEK_END);
			int i;
			
			int counter=0;

			for(i=0;i<fileSize;i++)
			{
				if(searchedChar==readchar_R(fd,i))
					counter++;
			}
			printf("Counter: %d\n\n", counter);
		}
		else
		{
			if(strcmp("M",argv[1])==0)
			{
				printf("\nUsing count_M\n");
				printf("File specified: %s\n",argv[2]);
				printf("Char to seek is: %c\n",argv[3][0]);
				int counter = count_M(fd, argv[3][0]);
				printf("Counter: %d\n\n", counter);
			}
			else
			{
				printf("\nInvalid first argument\n");
				return -1;
			}
		}
	}
	return 0;
}
