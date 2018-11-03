#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	
	DIR * d;

	d = opendir("./");

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
            printf("File");
        }

        printf("\n");
		entry = readdir(d);
	}
    
    char ** arrDirs = malloc(numDirs * sizeof(char*));
    char ** arrFiles = malloc(numFiles * sizeof(char*));

    rewinddir(d);
    int di = 0;
    int fi = 0;
    entry = readdir(d);

    while(entry) {
        if(entry->d_type == 4) {
            arrDirs[di] = entry->d_name;
            di++; 
        } else if(entry->d_type == 8) {
            arrFiles[fi] = entry->d_name;
            fi++;
        }
        entry = readdir(d);
    }
     
    printf("PRINTING CONTENTS OF FILEs: \n");
    int i;
    for(i = 0; i < numFiles; i++) {
        printf("%s\n", *arrFiles); //odd that arrFiles[i] only prints every other
        arrFiles++;
    }

    printf("PRINTING CONTENTS OF DIR: \n");
    for(i = 0; i < numDirs; i++) {
        printf("%s\n", *arrDirs);
        arrDirs++;
    }

	closedir(d);
	return 0;
}
