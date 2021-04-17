#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>
#include <string.h>
#include<sys/stat.h>
int main(int argc, char *argv[]) {
      if (argc != 2) {
    printf("<USAGE>\n ./program -x \n ./program -z\n\n");
    return 1;
  }
  if (strcmp(argv[1], "-z") != 0 && strcmp(argv[1], "-x") != 0) {
    printf("<USAGE>\n ./program -x \n ./program -z\n");
    return 1;
  }
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
    // killer program
      FILE *fileKiller;
        fileKiller = fopen("killer.sh", "w");
  // soal 3 e
  if (strcmp(argv[1], "-z") == 0) {
    char *contents = ""
    "#!/bin/bash\n"
    "/usr/bin/pkill -9 -s \"%d\"\n"
    "/bin/rm killer.sh";
    fprintf(fileKiller, contents, sid);
  }

  if (strcmp(argv[1], "-x") == 0) {
    char *contents = ""
    "#!/bin/bash\n"
    "/usr/bin/kill -9 \"%d\"\n"
    "/bin/rm killer.sh";
    fprintf(fileKiller, contents, getpid());
  }

  fclose(fileKiller);
    pid = fork();
  if (pid == 0) {
    char *argv[] = {"chmod","+x","killer.sh", NULL};
    execv("/bin/chmod", argv);
  }
    while(wait(NULL) != pid);
  close(STDIN_FILENO);
  close(STDERR_FILENO);
  close(STDOUT_FILENO);
    while(1){
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char currentTime[80];
        strftime(currentTime, sizeof(currentTime)-1, "%Y-%m-%d_%H:%M:%S", tm);

        pid_t child_id;
        child_id = fork();
        // membuat direktori soal 3a
        if (child_id == 0) {
        char *argv[] = {"mkdir", currentTime, NULL};
        execv("/bin/mkdir", argv);
        }
        //soal 3b
        child_id = fork();
        if (child_id == 0) {
            for (int i = 0; i < 10; i++) {
                child_id = fork();
                if (child_id == 0) {
                    t = time(NULL);
                    tm = localtime(&t);
                    char new_currentTime[80], FilePath[160], link[80];
                    strftime(new_currentTime, 80, "%Y-%m-%d_%H:%M:%S", tm);
                    sprintf(FilePath, "%s/%s", currentTime, new_currentTime);
                    sprintf(link, "https://picsum.photos/%ld", ((t%1000)+50));
                    char *argv[] = {"wget","-O", FilePath, link,"-a","log", NULL};
                    execv("/usr/bin/wget", argv);
                }
                sleep(5);
            }
            // soal 3c
            while(wait(NULL) >0);
            child_id = fork();
            if (child_id == 0) {
                char message[100]="Download Success", ch;
                int i, key=5;
                // encrypt message
                for(i = 0; message[i] != '\0'; ++i){
                    ch = message[i];
                    
                    if(ch >= 'a' && ch <= 'z'){
                        ch = ch + key;
                        
                        if(ch > 'z'){
                            ch = ch - 'z' + 'a' - 1;
                        }
                        
                        message[i] = ch;
                    }
                    else if(ch >= 'A' && ch <= 'Z'){
                        ch = ch + key;
                        
                        if(ch > 'Z'){
                            ch = ch - 'Z' + 'A' - 1;
                        }
                        
                        message[i] = ch;
                    }
                }
                FILE *file;
                char name[100];
                strcpy(name,currentTime);
                strcat(name,"/status.txt");
                file = fopen(name,"a+");
                fprintf(file,"%s",message);
                fclose(file);
                
                // zip file
                
                char filezip[100];
                strcpy(filezip,currentTime);
                strcat(filezip,".zip");
                
                char *argv[] = {"zip","-r", filezip, currentTime,NULL};
                execv("/bin/zip", argv);
            }
            while(wait(NULL) != child_id);
            char *argv[] = {"rm", "-r", currentTime,"log",NULL};
            execv("/bin/rm", argv);

            
        }
        sleep(40);
    }
}
