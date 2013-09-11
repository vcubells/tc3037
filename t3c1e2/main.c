#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	DIR *dp;
	struct dirent *ep;

	FILE *fd;
	
	
	char * buffer;
	buffer = getcwd(NULL, 0);
	
	printf("El directorio actual es: %s \n", buffer);
	
	/*buffer = "/etc";
	if ( chdir(buffer) == 0)
		printf("cambiando al directorio: %s ...\n", buffer );
	*/
	//mkdir("./tmp", 777);
	fd = fopen("./tmp/p1.txt", "w");
	fclose(fd);
	
	link("./tmp/p1.txt", "./p2.txt");
	symlink("./tmp/p1.txt", "./p3.txt");
	
	
	dp = opendir("./");
	if (dp != NULL)
	{
		while ( ep = readdir(dp) )
		{
			puts (ep -> d_name);
		}
		closedir(dp);
	}
	else {
		perror("Error al abrir el directorio");
	}
	
	return 0;
}

