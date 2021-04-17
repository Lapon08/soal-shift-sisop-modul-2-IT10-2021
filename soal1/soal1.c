#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>
#include <string.h>
#include<sys/stat.h>

int main(int argc, char *argv[]) {
    pid_t pid, sid;
    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
    umask(0);
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }
    close(STDIN_FILENO);
    close(STDERR_FILENO);
    close(STDOUT_FILENO);
    // 6 jam sebelum Ulang Tahun
    // 1617960120
    time_t t = time(NULL);
        // soal 1e
        while (t !=1617960120)
        {
          t = time(NULL);
        }
        
        pid_t child_id;
        
        // masuk folder demo
        if ((chdir("demo")) < 0) {
        exit(EXIT_FAILURE);
        }
        // mkdir (soal 1a) 
        child_id = fork();

        if (child_id == 0) {
        char *argv[] = {"mkdir", "Musyik","Fylm","Pyoto",NULL};
        execv("/bin/mkdir",argv);
        }
        while(wait(NULL) != child_id);
        // download file (soal 1b)
        child_id = fork();

        if (child_id == 0) {
            
        char *argv2[] = {"wget", "--no-check-certificate","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download","-O", "MUSIK.zip","-a","log",NULL};
        execv("/usr/bin/wget",argv2);
        }
        while(wait(NULL) != child_id);

        child_id = fork();

        if (child_id == 0) {
            
        char *argv3[] = {"wget", "--no-check-certificate","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download","-O","FILM.zip","-a","log",NULL};
        execv("/usr/bin/wget",argv3);
        }
        while(wait(NULL) != child_id);

        child_id = fork();

        if (child_id == 0) {
            
        char *argv4[] = {"wget","--no-check-certificate","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download","-O", "FOTO.zip","-a","log",NULL};
        execv("/usr/bin/wget",argv4);
        }
        
        while(wait(NULL) != child_id);
        // unzip file (soal 1c)
        child_id = fork();

        if (child_id == 0) {
        char *argv5[] = {"/bin/unzip","*",NULL};
        execv("/bin/unzip",argv5);
        }   
        while(wait(NULL) != child_id); 
        sleep(5);
        //mv file (soal 1d)
        child_id = fork();

        if (child_id == 0) {
        char *argv8[] = {"find","FOTO","-type","f","-name","*","-exec","mv","-t","Pyoto/","{}","+",NULL};
        execv("/bin/find",argv8);
        }

        while(wait(NULL) != child_id);
            child_id = fork();

        if (child_id == 0) {
        char *argv9[] = {"find","MUSIK","-type","f","-name","*","-exec","mv","-t","Musyik/","{}","+",NULL};
        execv("/bin/find",argv9);
        }  
        while(wait(NULL) != child_id);

            child_id = fork();

        if (child_id == 0) {
        char *argv10[] = {"find","FILM","-type","f","-name","*","-exec","mv","-t","Fylm/","{}","+",NULL};
        execv("/bin/find",argv10);
        }
        while(wait(NULL) != child_id);
        // soal 1f
        // WAKTU ULANG TAHUN
        // 1617981720
        while (t !=1617981720)
        {
          t = time(NULL);
        }
        
            child_id = fork();

        if (child_id == 0) {
        char *argv10[] = {"/bin/zip","-rm","Lopyu_Stevany.zip","Musyik","Pyoto","Fylm",NULL};
        execv("/bin/zip",argv10);
        } 
            while(wait(NULL) != child_id);
            child_id = fork();

        if (child_id == 0) {
        char *argv10[] = {"/bin/rm","-r","FOTO","MUSIK","FILM","FOTO.zip","MUSIK.zip","FILM.zip","log",NULL};
        execv("/bin/rm",argv10);
        } 

}
