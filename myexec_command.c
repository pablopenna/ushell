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
//----------------------------------------------------
//mypwd

void mypwd()
{

		char currentDir [1024];
		printf("%s\n",getcwd(currentDir,1024));

		return;
}
//----------------------------------------------------
//mycd
void mycd(char * dirToGo)
{
	int s = chdir(dirToGo);

	if(s==0)
	{
		printf("Directory successfully changed\n");
	}
	else
	{
		printf("ERROR: Could not change the directory\n");
	}
	
	return;
}
	
//----------------------------------------------------
//mycat
void mycat (char * fileToShow)
{
	int fd = open(fileToShow,O_RDONLY);

	if(fd==-1)
	{
		printf("ERROR: Could not open the file\n");
		return;
	}
	else
	{
		//Need to know the size of the file
		int fileSize = lseek(fd,0,SEEK_END);
		//map the file in memory
		char * map = mmap(0, fileSize, PROT_READ, MAP_PRIVATE,fd, 0);
		int i;
		for(i=0;i<fileSize;i++)
		{
			printf("%c",map[i]);
		}
	
		int m=munmap(map, fileSize);
		if(m==0)
			printf("mmap closed succesfully\n");
		if(m==-1)
			printf("ERROR: Could not close the mmap\n");
		
		int c= close(fd);
		if(c==0)
			printf("file descriptor closed succesfully\n");
		if(c==-1)
			printf("ERROR: Could not close the file descriptor\n");
	}
	
	return;
}
	
//----------------------------------------------------
//mycp
void mycp (char * sourceFile, char * destinationFile)
{
	int sourceFD = open(sourceFile,O_RDONLY);
	/*We open the first file specified, 
	the one we are going to copy to the other file */
	
	if(sourceFD==-1)//CHECK
	{
		printf("ERROR: Could not open the source file\n");
		return;
	}
	
	int sourceFileSize = lseek(sourceFD,0,SEEK_END);
	/*Get the size of the source file, the 
	one we are going to copy.
	
	We have to be careful here since we 
	place the pointer of the file at the end of it,
	so to dont mess things up on coming operations,
	we should place the pointer back at the beginning of the file*/
	lseek(sourceFD,0,SEEK_SET);
	/*We place the curesor of the file back at
	the beginning of it*/
	
	char buffer [sourceFileSize];
	/*This will store the content of the file 
	we want to copy into the another file*/
	
	int r = read(sourceFD, buffer, sourceFileSize);
	
	if(r==-1)
	{
		printf("ERROR: Could not read the file\n");
		return;
	}
		printf("Reading the source file:\n");
	int i;
	for(i=0;i<sourceFileSize;i++)
	 
	lseek(sourceFD,0,SEEK_SET);
	/*We place again the cursor of the source
	file at the beginning*/
	//Lets work now with the target file
	int targetFD = open(destinationFile, O_CREAT | O_RDWR, 00666);
	/*O_CREAT creates a new file if the specified one
	does not exist. the number in the next field specifies
	permissions of the new created file.
	*/
	if(targetFD==-1)//CHECKING
	{
		printf("FATAL ERROR: Could not open nor create target file\n");
		return;
	}
		

	/*Once we have got both the source and 
	target files opened, we will now pass to 
	copy source into target.
		
	We already got the content of the source file
	inside the variable buffer.*/
		


	int w =  write(targetFD, buffer, sourceFileSize);

	if(w>=0)
		printf("File succesfully copied\n");
	else
		printf("File could not be copied\n");

	close(sourceFD);
	close(targetFD);
	return;
}
	

//----------------------------------------------------
//mymkdir
void mymkdir (char * dirToCreate)
{
	int s=mkdir(dirToCreate,511);//511 = 777 for permissions
	/*Create a folder with xwr permissions
	for everyone*/
	if(s==0)
	{
		printf("Directory successfully created\n");
	}
	else
	{
		printf("ERROR: Could not create a directory\n");
	}
	return;
}
//----------------------------------------------------
//myrmdir
void myrmdir (char * dirToDelete)
{
	int s=rmdir(dirToDelete);
	if(s==0)
	{
		printf("Directory successfully erased\n");
	}
	else
	{
		printf("ERROR: Could not erase the directory\n");
	}

	return;
}
//----------------------------------------------------
//myrm

void myrm (char * fileToDelete)
{		
	
		
	int u = unlink(fileToDelete);
	
	switch(u)
	{
		case -1:
			printf("ERROR: Could not erase the specified file\n");
			break;
		case 0:
			printf("Success at erasing the file\n");
			break;
	}
	
	return;
}
//----------------------------------------------------
//myls
void myls (char * pathToShow, bool detailed)
{
	if(pathToShow==NULL)
	{
		printf("Invalid directory.\n");
		return;
	}
	//printf("executing myls\n");
	//printf("D = %d\n",detailed);
		
	DIR * folder = opendir(pathToShow);
	
	if(folder==NULL)
	{
		printf("Could not open the dir.\n");
		return;
	}

	struct dirent * info = readdir(folder);
	
	while(info != NULL)
	{
		if(!detailed)
		{
			printf("%s\n",info->d_name);
		}
		if(detailed)
		{	
			struct stat buf;
			stat(info->d_name,&buf);
			printf("-----> %15s",info->d_name);
			printf("\t Owner: %ld", (long) buf.st_uid);
			printf("\t Group: %ld", (long) buf.st_gid);
			
			/*File Type - Copied from internet*/

			printf("\tPermissions: ");
			if(S_ISBLK(buf.st_mode))
				printf("b");
			else if (S_ISCHR(buf.st_mode))
				printf("c");
			else if (S_ISDIR(buf.st_mode))
				printf("d");
			else if (S_ISFIFO(buf.st_mode))	//pipe?
				printf("p");
			else if (S_ISLNK(buf.st_mode))
				printf("l");
			else if (S_ISSOCK(buf.st_mode))
				printf("s");
			else
				printf("-");
			
			/*Permissions - also had to look for it
			and copy it from internet*/
			
			printf((buf.st_mode & S_IRUSR) ? "r" : "-");
			printf((buf.st_mode & S_IWUSR) ? "w" : "-");
			printf((buf.st_mode & S_IXUSR) ? "x" : "-");
			printf((buf.st_mode & S_IRGRP) ? "r" : "-");
			printf((buf.st_mode & S_IWGRP) ? "w" : "-");
			printf((buf.st_mode & S_IXGRP) ? "x" : "-");
			printf((buf.st_mode & S_IROTH) ? "r" : "-");
			printf((buf.st_mode & S_IWOTH) ? "w" : "-");
			printf((buf.st_mode & S_IXOTH) ? "x" : "-");
			
			//printf("\t Protection: %lo(octal)",(unsigned long)buf.st_mode);
			//printf("\t device ID: %d", (int)buf.st_rdev);
			//printf("ID of dev:\t %d\n", (int)buf.st_dev);
			//printf("Nº of hard links:\t %d\n", (int)buf.st_nlink);
			printf("\t Size: %d", (int)buf.st_size);
			//printf("I-node number:\t %d\n", (int)buf.st_ino);
			printf("\t Last file mod: %s\n", ctime(&buf.st_mtime));
		}
		
		info = readdir(folder);
	}
	
	return;
}

