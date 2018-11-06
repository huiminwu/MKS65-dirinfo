#include "dir.c"
#include <unistd.h>

int main(int argc, char * argv[]) {

	char * path = malloc(sizeof(char)*100);

    printf("Please input a path: \n");

    fgets(path, 100, stdin);

    //fgets appends the '\n' to the end of the string
    //if this is what ends the fgets function

    //Remove '\n' from the end of the string if it is there
    char * c = path;
    while(*c != '\n' && *c) {
    	c++;
    }
    *c = '\0';


    dir(path);

    free(path);

    return 0;
}

