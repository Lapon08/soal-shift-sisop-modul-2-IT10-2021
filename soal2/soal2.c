#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <dirent.h>
#include <errno.h>

int main(){
    char pathdirectory[] = "/home/nop/sistemoperasi/modul2/soal-shift-sisop-modul-2-IT10-2021/soal2/petshop/";
    pid_t child_id;
    if ((chdir(pathdirectory)) < 0) {
        exit(EXIT_FAILURE);
    }
    child_id = fork();
    // soal 2a
    if (child_id == 0) {
        char filename[50]="pets.zip";
        char *argv[] = {"unzip","-q", filename, NULL};
        execv("/bin/unzip", argv);
    }
    while(wait(NULL) != child_id);
    child_id = fork();
    if (child_id == 0) {
        char *argv[] = {"rm", "pets.zip", NULL};
        execv("/bin/rm", argv);
    }
    while(wait(NULL) != child_id);
    
    DIR *dp;
    struct dirent *ep;
    char f_name[1000];
    memset(f_name, 0, sizeof f_name);
    dp = opendir(pathdirectory);

    if (dp != NULL)
    {
      while ((ep = readdir (dp))) {
        if (strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0) {
            continue;
        }
         sprintf(f_name+strlen(f_name), "%s\n", ep->d_name);
          
      }
      (void) closedir (dp);
    } else perror ("Couldn't open the directory");

    char *token = strtok(f_name, "\n");
    char **filenamepath = malloc(55*sizeof(char *));
    char **filenamepathtemp = malloc(55*sizeof(char *));
    
    int num=0;
    while (token != NULL) {
        // puts(token);
        char location[256];
        struct stat location_stat;
        strcpy(location,pathdirectory);
        strcat(location,token);
        
        stat(location, &location_stat);

        // direktori
        
        if (S_ISDIR(location_stat.st_mode)) {
            child_id = fork();
            if (child_id == 0) {
                char *argv[] = {"rm","-r", token, NULL};
                execv("/bin/rm", argv);
            }
        while(wait(NULL) != child_id);
        
        }else{
            if (strstr (token,"_") != NULL)
            {  
                filenamepath[num] = token;  
                filenamepathtemp[num]= token;
                num++;
                filenamepath[num] = token; 
                filenamepathtemp[num]= token;  
                num++;
            }else{
                filenamepath[num] = token; 
                filenamepathtemp[num]= token;  
                num++;
                
            }

        }
        token = strtok(NULL, "\n");
     }

            char kategori[num][100];
            char nama[num][100];
            char umur[num][100];
            int i=0;
            int k =0;
            while(i < num)
            {
                if (strstr (filenamepath[i],"_") != NULL)
                {
                    char temp[100];
                    strcpy(temp,filenamepathtemp[i]);

                    char *token2  = strtok(temp,";");
                        while (token2 != NULL) {

                            strcpy(kategori[i],token2);
                            token2 = strtok(NULL,";");                            

                            strcpy(nama[i],token2);
                            token2 = strtok(NULL,"_");

                            strcpy(umur[i],token2);
                            i = i+1;
                            token2 = strtok(NULL,";");

                            strcpy(kategori[i],token2);
                            token2 = strtok(NULL,";");

                            strcpy(nama[i],token2);
                            token2 = strtok(NULL,";");

                            strncpy(umur[i],token2,strlen(token2)-4);
                            
                            token2 = NULL;
                            
                        }
                }else{
                    char temp[100];
                    strcpy(temp,filenamepathtemp[i]);
                    char *token2  = strtok(temp,";");
                        while (token2 != NULL) {

                            strcpy(kategori[i],token2);
                            token2 = strtok(NULL,";");

                            strcpy(nama[i],token2);
                            token2 = strtok(NULL,";");

                            strncpy(umur[i],token2,strlen(token2)-4);
                            
                            token2 = NULL;
                            
                        } 
                }
                i = i+1;
            }
            // soal 2b,c,d,e
            for (int j = 0; j < num; j++)
            {

                    char direktori[100];
                    strcpy(direktori,kategori[j]); 
                    DIR* dir = opendir(direktori);
                    if (dir) {
                        closedir(dir);
                    } else if (ENOENT == errno) {
                        child_id = fork();
                        if (child_id == 0) {
                            char *argv[] = {"mkdir", direktori, NULL};
                            execv("/bin/mkdir", argv);
                        }
                        while(wait(NULL) != child_id);
                    }
                    if (strstr (filenamepath[j],"_") != NULL){
                        child_id = fork();
                        if (child_id == 0) {
                            char path[100];
                            strcpy(path,direktori);
                            strcat(path,"/");
                            strcat(path,nama[j]);
                            strcat(path,".jpg");
                            char *argv[] = {"cp", filenamepath[j],path, NULL};
                            execv("/bin/cp", argv);
                        }
                            while(wait(NULL) != child_id);
                            FILE *pFile;
                            char pathketerangan[100];
                            strcpy(pathketerangan,kategori[j]);
                            strcat(pathketerangan,"/keterangan.txt");
                            pFile = fopen(pathketerangan, "a+");
                                char *inp = ""
                                "nama: %s\n"
                                "umur: %s tahun\n\n";
                            fprintf(pFile, inp, nama[j],umur[j]);
                            fclose(pFile);
                        j = j+1;
                        child_id = fork();
                        if (child_id == 0) {
                            char path[100];
                            strcpy(path,kategori[j]);
                            strcat(path,"/");
                            strcat(path,nama[j]);
                            strcat(path,".jpg");
                            char *argv[] = {"mv", filenamepath[j],path, NULL};
                            execv("/bin/mv", argv);
                        }
                            while(wait(NULL) != child_id);
                    }else{
                        child_id = fork();
                        if (child_id == 0) {
                            char path[100];
                            strcpy(path,direktori);
                            strcat(path,"/");
                            strcat(path,nama[j]);
                            strcat(path,".jpg");
                            char *argv[] = {"mv", filenamepath[j],path, NULL};
                            execv("/bin/mv", argv);
                        }
                            while(wait(NULL) != child_id);
                    }
                    
                    FILE *pFile;
                    char pathketerangan[100];
                    strcpy(pathketerangan,kategori[j]);
                    strcat(pathketerangan,"/keterangan.txt");
                    pFile = fopen(pathketerangan, "a+");
                        char *inp = ""
                        "nama: %s\n"
                        "umur: %s tahun\n\n";
                    fprintf(pFile, inp, nama[j],umur[j]);
                    fclose(pFile);
            }
            
    return 0;
}
