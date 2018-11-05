#include "dir.c"

int main(int argc, char * argv[]) {
    
    while(!argv[1]) {
        char * path;
        FILE * stdin = 0; //STDIN_FILENO
        printf("Please input a path: \n");
        fgets(path, 100, stdin);
        printf("Thing: %s\n", path);
    }

    return 0;
}

