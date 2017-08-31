#include "readchar_R.h"
#include <sys/syscall.h> //sys calls
#include <unistd.h>	//sys calls
#include <stdio.h>	//printf and so on


char readchar_R(int fd, int pos)
/*We already get the file opened,
so we get the file descriptor*/
{
	int filesize = lseek(fd,0,SEEK_END);
	//We calculate size of the opened file
	if(pos > filesize)
	{
		printf("\n---POSITION EXCEEDS FILE SIZE---\n");
		return -1;
	}

	lseek(fd,pos,SEEK_SET);
	/*We place the cursor at the beginning
	of the file, and add an offset of "pos".
	So we place the curser at the desired position*/

	char R;
		
	int r = read(fd,&R,1);
	/*We read 1 char from the file
	at current cursor location and 
	store it at R*/

	if(r<1)
	{
		printf("\n---POSITION NOT VALID---\n");
		return -1;
	}
	
	//printf("\nChar at pos<%d> is -> %c",pos,R);

	return R;
}

