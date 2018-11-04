#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
	
	DIR * d;

	d = opendir("./");

    int numDirs = 0;

    int numFiles = 0;

    int totsize;


	struct dirent * entry = readdir(d);

	while(entry) {

        struct stat * stbf = malloc(sizeof(struct stat *));

        char * path = malloc(sizeof(entry->d_name));
        path = entry->d_name;

        stat(path, stbf);

		if(entry->d_type == 4) {
            numDirs++;
    	} else if(entry->d_type == 8) {
            numFiles++;
            int s = stbf->st_size;
            totsize += s;
            free(stbf);
        }
        
		entry = readdir(d);
	}

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

    int i;
    printf("Directories: \n");
    for(i = 0; i < numDirs; i++) {
        printf("\t%s\n", *arrDirs);
        arrDirs++;
    }
    
    printf("Files: \n");
    
    for(i = 0; i < numFiles; i++) {
        printf("\t%s\n", *arrFiles); //odd that arrFiles[i] only prints every other
        arrFiles++;
    }
    
	closedir(d);
	return 0;
}
