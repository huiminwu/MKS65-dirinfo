#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int dir(char * path){
	
	DIR * d;

    if (!opendir(path)) {
        perror("Path failed");
        return 0;
    }

	d = opendir(path);

    int numDirs = 0;

    int numFiles = 0;

    int totsize = 0;

	struct dirent * entry = readdir(d);

	while(entry) {

        struct stat * stbf = malloc(sizeof(struct stat));
        char * pathfile = malloc(sizeof(entry->d_name) + sizeof(path) + sizeof("/"));
        strcpy(pathfile, path);
        if(path[strlen(path) - 1] != '/') {
            strcat(pathfile, "/");
        }
        strcat(pathfile, entry->d_name);
        

        stat(pathfile, stbf);

		if(entry->d_type == 4) {
            numDirs++;
    	} else if(entry->d_type == 8) {
            int s = stbf->st_size;
            totsize += s;
            numFiles++;
        }
        
        free(stbf);
        free(pathfile);
        entry = readdir(d);
	}

    printf("\nTotal Directory Size: ");
    if(totsize > 1000000000) {
        printf("%lf GB\n", totsize / 1000000000.0);
    } else if (totsize > 1000000) {
        printf("%lf MB\n", totsize/1000000.0);
    } else if (totsize > 1000) {
        printf("%lf KB\n", totsize/1000.0);
    } else {
        printf("%d B\n", totsize);
    }
    
    char ** arrDirs = malloc(numDirs * sizeof(char*));
    char ** arrFiles = malloc(numFiles * sizeof(char*));

    char permissions[8][4] = {"---","--x","-w-","-wx","r--","r-x","rw-","rwx"};

    rewinddir(d);
    int di = 0;
    int fi = 0;
    int fileSizes[numFiles];
    char * permOfFiles[numFiles];
    entry = readdir(d);

    while(entry) {
        if(entry->d_type == 4) {
            arrDirs[di] = entry->d_name;
            di++; 
        } else if(entry->d_type == 8) {
            arrFiles[fi] = entry->d_name;

            struct stat * stbf = malloc(sizeof(struct stat));
            char * pathfile = malloc(sizeof(entry->d_name) + sizeof(path) + sizeof("/"));
            strcpy(pathfile, path);
            if(path[strlen(path) - 1] != '/') {
                strcat(pathfile, "/");
            }
            strcat(pathfile, entry->d_name);
            stat(pathfile, stbf);

            fileSizes[fi] = stbf->st_size;
            int totoctal = stbf->st_mode;
            int uperm = (totoctal/64) % 8; //gets rid of first 6 digs & converts to dec
            int gperm = (totoctal/8)  % 8; //gets rid of first 3 dig & last 
            int operm = totoctal      % 8; //gets last 3 dig and converts to dec
            
            char * perms = malloc(3*sizeof(permissions[1][1]));
            strcat(perms, permissions[uperm]);
            strcat(perms, permissions[gperm]);
            strcat(perms, permissions[operm]);
            permOfFiles[fi] = perms;
            free(stbf);
            free(pathfile);
            fi++;
        }
        entry = readdir(d);
    }

    printf("\n");

    int i;
    printf("Directories: \n");
    for(i = 0; i < numDirs; i++) {
        printf("\t%s\n", arrDirs[i]);
    }

    free(arrDirs);

    printf("\n");
    
    printf("Files: \n");
    
    for(i = 0; i < numFiles; i++) {
        printf("%-10s\t %-10d\t %s\t \n", permOfFiles[i], fileSizes[i], arrFiles[i]); 
        free(permOfFiles[i]);
    }

    printf("\n");

    free(arrFiles);
    
	closedir(d);

    return 0;
}
