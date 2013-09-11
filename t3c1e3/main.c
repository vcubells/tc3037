#include <stdio.h>
#include <dirent.h>
     
static int one (const struct dirent *unused)
{
	if (unused->d_type == 8)
		return 1;
		
	return 0;
}
     
int main(int argc, char **argv)
{
       struct dirent **eps;
       int n;
       int cnt;
	   
       n = scandir ("/etc", &eps, one, alphasort);
       if (n >= 0)
         {
           for (cnt = 0; cnt < n; ++cnt)
             puts (eps[cnt]->d_name);
         }
       else
         perror ("No se puede abrir el directorio");
     
       return 0;
}
