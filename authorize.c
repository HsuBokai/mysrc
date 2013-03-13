#include <stdio.h>
#include <stdlib.h>

#include <dirent.h>
#include <pthread.h>
//#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
//#include "tm_usage.h"
/*
void *myfun(void* ptr){

   printf(" in thread pid= %d\n",getpid());
   printf(" in thread ppid= %d\n",getppid());
   //execl("/home/bokai/Desktop/cryptofs-0.6.0/src/fuse/cryptofs","cryptofs","--root=/home/bokai/encrypt","/home/bokai/fuse",NULL);
   execl("/usr/local/bin/cryptofs","cryptofs","--root=/home/bokai/encrypt","/home/bokai/fuse",NULL);
   //char *args[] = {"/home/bokai/Desktop/cryptofs-0.6.0/src/fuse/cryptofs", "--root=/home/bokai/encrypt", "/home/bokai/fuse", (char *) 0 };
   //execv(args[0], args);
   //execl("/bin/ls","ls","/home/bokai",NULL);
}
*/


void performance(char* command[], char* _src, char* _dst){
	    //printf("%s\n",command[1]);
int ii = 0;
for( ;ii < 10000; ii++)
{
		char buff[1024]; 
	    int fd_src,fd_dst,i; 
        //fd_src = open(_src,O_RDONLY,0644); 
        fd_dst = open(command[1],O_RDWR|O_CREAT,0644); 
        if((fd_dst < 0)){
            printf("Open Error!Check if the file is exist and you have the permission!\n"); 
            //exit(1); 
        }
        //printf("seed_end of dst = %d\n",SEEK_END); 
        //printf("seed_cur of dst = %d\n",SEEK_CUR); 
        //printf("seed_set of dst = %d\n",SEEK_SET); 
        //printf("seed_set of dst = %d\n",lseek(fd_dst,1,SEEK_SET)); 
        //printf("seed_cur of dst = %d\n",lseek(fd_dst,0,SEEK_CUR)); 
		//off_t off = lseek(fd_dst,-1,SEEK_END);
        //printf("off of dst = %d\n",off); 
        //printf("fd_dst of dst = %d\n",fd_dst); 
/*
while((i = read(fd_src,buff,sizeof(buff)))>0) {
	printf("i= %d, buff= %s",i,buff);
	char buff2[1024];
	off_t end_dst = read(fd_dst,buff2,sizeof(buff2));
	pwrite(fd_dst,buff,i,end_dst);
}
*/
	char buff3[] = "hello_world!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	char buff2[1024];
	off_t end_dst = 0, iii;
	while((iii = read(fd_dst, buff2, sizeof(buff2))) >0) end_dst += iii;
	pwrite(fd_dst, buff3, sizeof(buff3), end_dst);
        close(fd_dst); 
        //close(fd_src);
	printf("ii= %d\n",ii);
		/*
		char* tmp = _src;
		_src = _dst;
		_dst = tmp;
		*/
}

}


int main(int argc , char* argv[])
{
//TmUsage tm;
//cerr<<"authorize is running...\n";

printf("pid= %d\n",getpid());
		char* _src = "/home/bokai/src";
		char* _dst = "/home/bokai/dst";

printf(">> ");
char input[100];
while(gets(input)){
//tm.periodStart();

	char* command[10];
	int num_command = 0;
    char* pch, *src;
	src = input;
    pch=strchr(src,' ');
	
    while (pch!=NULL) {
 	    size_t len = pch-src;
		if(len>0) {
		   command[num_command] = (char*)malloc(sizeof(char)*len);
	       memcpy(command[num_command], src, len+1);
	       command[num_command++][len]='\0';
		}
		src = pch+1;
	    pch=strchr(src,' ');
	}
	if(src!=NULL) {
	   command[num_command++] = src;
	}

	if(strcmp(command[0],"mount")==0) {
	    //printf("%s\n",command[0]);
		pid_t child_pid = vfork();
		if(child_pid==0) {
		   //system("/home/bokai/Desktop/cryptofs-0.6.0/src/fuse/cryptofs --root=/home/bokai/encrypt /home/bokai/fuse");
		   //myfun((void*)0);
           execl("/home/bokai/LVDP/main","gg",command[1],command[2],NULL);
		   exit(0);
//pthread_t thread1;
//int iret1;
//iret1 = pthread_create(&thread1, NULL, myfun, (void*)0 );
//pthread_join(thread1,NULL);
//printf("iret1 = %d \n", iret1);
		}
		else{
			sleep(1);
			waitpid(child_pid, NULL, 0);
			//printf("parent process\n"); fflush(stdout);
			//char msg[] = "parent!!\n";
			//write(0,msg,strlen(msg));
		}
	}
    else if(strcmp(command[0],"unmount")==0) {
	 if(num_command>=2) {
	    printf("%s\n",command[0]);
		char type[100];
		strcpy(type,"fusermount -u ");
		strcat(type,command[1]);
		system(type);
	 }
	 else printf("less args\n");
	}
	else if(strcmp(command[0],"ls")==0) {
	 if(num_command>=2) {
       DIR* dp = opendir(command[1]);
	   if(dp!=NULL) {
       	struct dirent* ptr;
       	int i;
       	while((ptr = readdir(dp))!=NULL) {
	      printf("%s   ",ptr->d_name);
       	}
	   	printf("\n");
       	closedir(dp);
	   }
	 }
	 else printf("less args\n");
    }
    else if(strcmp(command[0],"touch")==0) {
	    printf("%s\n",command[1]);
		char* src = command[1];
	    int fd2; 
        fd2 = open(src,O_RDWR|O_CREAT|O_TRUNC,0644); 
        if(fd2 < 0)
            printf("create error!\n"); 
		else {
	    	char content[] = "helloworld!!!\n";
        	write(fd2,content,strlen(content));
		}
        close(fd2);
	}
	else if(strcmp(command[0],"cp")==0) {
	    printf("src = %s\n bakfile = %s\n",command[1],command[2]);
		char buff[1024]; 
	    int fd1,fd2,i; 
		char* src = command[1];
		char* bakfile = command[2];
        fd1 = open(src,O_RDONLY,0755); 
        fd2 = open(bakfile,O_RDWR|O_CREAT|O_TRUNC,0755); 
        if((fd1 < 0)||(fd2 < 0))
            printf("Open Error!Check if the file is exist and you have the permission!\n"); 
		else{
        	while((i = read(fd1,buff,sizeof(buff))) > 0) { 
            	write(fd2,buff,i);
        	}
		}
        close(fd1); 
        close(fd2);
	}
    else if(strcmp(command[0],"exec")==0) {
	    printf("before vfork pid = %d\n",getpid());
		pid_t child_pid = vfork();
		if(child_pid==0) {
			switch(num_command) {
				case 2:
					execl(command[1],command[1],NULL,NULL,NULL); break;
				case 3:
					execl(command[1],command[1],command[2],NULL,NULL); break;
				case 4:
					execl(command[1],command[1],command[2],command[3],NULL); break;
			}
			exit(0);
		}
		else {
			sleep(1);
			waitpid(child_pid, NULL, 0);
	        printf("after fork pid = %d\n",getpid());
		}
	}
    else if(strcmp(command[0],"temp")==0) {
	    printf("%s\n",command[1]);
	    printf("pid = %d\n",getpid());
		execl(command[1],"temp",NULL,NULL,NULL);
	}
    else if(strcmp(command[0],"performance")==0) {
	    printf("%s\n",command[0]);
		performance(command,_src,_dst);
	}
	printf(">> ");
//tm.periodStop();
//tm.report();
}
return 0;
}
