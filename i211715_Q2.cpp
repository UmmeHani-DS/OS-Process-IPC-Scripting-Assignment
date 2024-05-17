#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <cstring>
#include <sys/wait.h>
#include <stdlib.h>
#include <fstream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>

using namespace std;

int main()
{
    //Problem

    //Shared memory can lead to data corruption as multiple process will be reading and writng to memory
    

    key_t key = ftok("q1file", 65); // creates a key for shared memory using ftok function
    
    int id = shmget(key, 1024, 0666|IPC_CREAT); // creates a shared memory of size 1024 with unique key identifiers

    for(int i = 0; i < 10 ; i++)
    {
        char * str = (char*) shmat(id,NULL,0); // Attach the shared memory segment to the address space of the current process using shmat this is to read and write to the shared memory.
        
        int status = 0;

        pid_t C;
        
        C = fork();

        if(C == 0)
        {
            cout << str << endl;
            if(str[0] == 'l')
            {
                execl ("bin/ls" , "ls", NULL);
            }
              if((i %2) == 1)
            {
                cout << "reading message for " << i << " process " << endl << str << endl;
                shmdt(str);
            }
            
        }
        else
        {
            char* str = (char* )shmat(id,NULL,0);

            if((i % 2)==0)
            {
                cin >> ws;
                char* process = new char[100];
                cin >> process;
                strncpy(str,process, 1024);
                cout << "Write to memory " << endl;
                shmdt(str);
            }
            
            wait(&status);
            exit(0);
        }
    }
    shmctl(id,IPC_RMID,NULL);

    return 0;

}
        
    
    
    




