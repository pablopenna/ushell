//#include "count_M.h"
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
int count_M(int fd, char R)
{
	int fileSize = lseek(fd,0,SEEK_END); //We get the size of the file

	char * map = mmap(0,fileSize,PROT_READ,MAP_SHARED,fd,0);
	//We map the file in memory
	int counter=0;

	int i;
	for(i=0;i<=fileSize;i++)
	{
		if(map[i]==R)
		{
			counter++;
		}
	}
	//I check the entire the file mapped in memory 
	//And add one to counter if the character in the file at
	//the checked position is equal to the one we are looking for.
	return counter;

}
