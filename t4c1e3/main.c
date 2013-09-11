#include <stdio.h>

int main()
{ 
   int cuenta, n_cuenta = 7;        
   char nombre[ 30 ], n_nombre[30] = "persona_nueva"; 
   double saldo, n_saldo = 0;   
   int insertado = 0;

   FILE *origen, *destino; 

    if ( ( origen = fopen( "../../t4c1e1/Debug/clientes.dat", "r" ) ) == NULL ) {
      printf( "El archivo no pudo abrirse\n" );
    } 
    else { 
		if ( ( destino = fopen( "clientes.upd", "w" ) ) == NULL ) {
			printf( "El archivo no pudo abrirse\n" );
		}

	  fscanf( origen, "%d %s %lf", &cuenta, nombre, &saldo );		

      while ( !feof( origen ) ) { 
		 if (n_cuenta < cuenta)
		 {
			fprintf( destino, "%d %s %.2f\n", n_cuenta, n_nombre, n_saldo );
			insertado = 1;	
		 }
         fprintf( destino, "%d %s %.2f\n", cuenta, nombre, saldo );
         fscanf( origen, "%d %s %lf", &cuenta, nombre, &saldo );
      }

	  /* Manejar caso extremo de que sea el último */
	  if (insertado == 0)
		 {
			fprintf( destino, "%d %s %.2f\n", n_cuenta, n_nombre, n_saldo );	
		 }
      fclose( origen ); 
	  fclose( destino );
	  
	  //remove("../../t4c1e1/Debug/clientes.dat");
   } 
   
   return 0; 
} 