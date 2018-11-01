#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

int main()
{
	
	DIR * d;

	d = opendir("./");

	struct dirent * entry = readdir(d);

	while(entry) {

		printf("%s : ", entry->d_name);

		if(entry->d_type == 4) {
			printf("Directory\n");
		} else {
			printf("File of size %d\n", entry->t_size);
		}


		entry = readdir(d);
	}

	closedir(d);


	return 0;
}