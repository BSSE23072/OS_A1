#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> //works with <unistd.h> as a library of flags
#include <sys/wait.h>


//dear SIR/TA i added these comments for my own help in case of viva
// hehe 😜 

int main(int argc, char *argv[]){
    int fd;
// fd stands for file descriptor and it save whatever value is returned by open system call
    fd=open("sample.txt", O_RDWR | O_CREAT);
// O_RDWR and O_CREAT are the flags came from <fcntl.h> library
// these flags mean open file in Read/Write mode and create it if doesnt exist

// now calling fork system call
    int rc=fork();
// i copied these if statements from lec  
    if (rc < 0) {  // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {  // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
     
    // now tring to access fd in child to check whether child can access the fd
        printf("Printing fd( file descriptor ) value in child, fd=%d\n", fd);

    // now writing to the one opened file concurrently by the parent and the child
    // here its the child that's writing
        write(fd, "Child is writing to file", 14);

    } else {  // parent process
        // int wc = wait(NULL);
        printf("hello, I am parent of %d and my (pid:%d)\n", rc, (int) getpid());

    // now tring to access fd in parent to check whether parent can access the fd
        printf("Printing fd( file descriptor ) value in parent, fd=%d \n", fd);

    // now writing to the one opened file concurrently by the parent and the child
    // here its the parent that's writing
        write(fd, "Parent is writing to file", 15);
    }

// my notes of observation after running code multiple times

//so after running the code multiple times i can say that open always returns 3 in fd
// and fd can be accessed by both parent and child

// ?so from internet i got these two points
// The child process inherits the parent’s file descriptor table or copy the parent's 
// file descriptor table.
// yes Both parent and child share the same FD (pointing to the same open file)

// final verdict
// after running the write() command multiple times after running fort system call the 
// output of the write command in the sample.txt file is weird and it is something like this 
// Parent is writiChild is writi
// according to my observation this shows that during execution, firstly the parent process write in the file
// but after some time the scheduler run the child process and child start writing but both parent and child
// did not finish the writing
}