#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void dir(char * path){
	
	DIR * d;

	d = opendir(path);

    int numDirs = 0;

    int numFiles = 0;

	struct dirent * entry = readdir(d);

	while(entry) {

		printf("%s : ", entry->d_name);


		if(entry->d_type == 4) {
            numDirs++;
			printf("Directory");
    	} else if(entry->d_type == 8) {
            numFiles++;
        }

        printf("\n");
		entry = readdir(d);
	}

    char ** arrDirs = malloc(numDirs*sizeof(char));
    char ** arrFiles = malloc(numFiles*sizeof(char));

    rewinddir(d);
    int di = 0;
    int fi = 0;

    while(entry) {
       
        if(entry->d_type == 4) {
            arrDirs[di] = entry->d_name;
            di++; 
        } else if(entry->d_type == 8) {
            arrFiles[fi] = entry->d_name;
            fi++;
        }
    }
     

	closedir(d);
}


