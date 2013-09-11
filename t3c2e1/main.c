#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

char gettipo(mode_t modo);

int main(int argc, char **argv)
{
	DIR *dp;
	struct dirent *ep;
	struct stat f;
	char tipo;
	
	time_t tiempo;
	
	char * buffer;
	buffer = getcwd(NULL, 0);
	
	printf("El directorio actual es: %s \n", buffer);
	
	/*buffer = "/etc";
	if ( chdir(buffer) == 0)
		printf("cambiando al directorio: %s ...\n", buffer );
	*/
	
	dp = opendir("/home/alumno");
	if (dp != NULL)
	{
		while ( ep = readdir(dp) )
		{
			stat(ep->d_name, &f);
			
			tipo = gettipo(f.st_mode);
			
			printf("%c %30s %10d %10d %10d %10s \n", tipo, ep->d_name, f.st_size, f.st_uid, f.st_gid, ctime(&f.st_ctim.tv_sec));

		}
		closedir(dp);
	}
	else {
		perror("Error al abrir el directorio");
	}
	
	return 0;
}

char gettipo(mode_t modo)
{
	char tipo = ' ';
	if ( S_ISDIR(modo ) != 0  ) tipo = 'd';
	else if (S_ISCHR(modo) != 0 ) tipo = 'c';
	else if (S_ISBLK(modo) != 0 ) tipo = 'b';
	else if (S_ISREG(modo) != 0 ) tipo = 'f';
	else if (S_ISFIFO(modo) != 0 ) tipo = 'p';
	else if (S_ISSOCK(modo) != 0 ) tipo = 's';
	else if (S_ISLNK(modo) != 0 ) tipo = 'l';
	else tipo = '*';
	   
	return tipo;
}

