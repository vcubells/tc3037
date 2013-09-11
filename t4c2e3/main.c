/* Figura 11.15: fig11_15.c
   Lectura secuencial de un archivo de acceso aleatorio */
#include <stdio.h>

/* definición de la estructura datosCliente */
struct datosCliente { 
   int numCta;          /* número de cuenta */
   char apellido[ 15 ]; /* apellido */
   char nombre[ 10 ];   /* nombre */
   double saldo;        /* saldo  */
}; /* fin de la estructura datosCliente */

int main()
{ 
   FILE *ptrCf; /* apuntador de archivo credito.dat */
	int seguir = 1;
	
    int cta = 0;
   /* crea datosCliente con información predeterminada */
   struct datosCliente cliente = { 0, "", "", 0.0 };

   /* fopen abre el archivo; si no se puede abrir, sale del archivo */
   if ( ( ptrCf = fopen( "../../t4c2e1/Debug/credito.dat", "rb" ) ) == NULL ) {
      printf( "No pudo abrirse el archivo.\n" );
   } /* fin de if */
   else { 
      printf( "%-6s%-16s%-11s%10s\n", "Cta", "Apellido",
         "Nombre", "Saldo" );
	
	do {
		// Leer un registro especifico
		printf("Entra un número de cuenta:");
		scanf("%d", &cta);
	
		fseek(ptrCf, sizeof(struct datosCliente) * (cta-1), SEEK_SET);
	
		fread( &cliente, sizeof( struct datosCliente ), 1, ptrCf );
	
		if(cliente.numCta != 0)
		{
			printf( "%-6d%-16s%-11s%10.2f\n", 
               cliente.numCta, cliente.apellido, 
               cliente.nombre, cliente.saldo );
		}
		else {
			printf("La cuenta especificada no existe \n");
		}
	
		printf("Desea buscar otra cuenta (1-Si, 0-No): ");
		scanf("%d", &seguir);
	}
	while (seguir == 1);
	
	
      /* lee todos los registro del archivo (hasta eof) */
    //  while ( !feof( ptrCf ) ) { 
     //      fread( &cliente, sizeof( struct datosCliente ), 1, ptrCf );

         /* despliega el registro */
      //   if ( cliente.numCta != 0 ) {
       //     printf( "%-6d%-16s%-11s%10.2f\n", 
       //        cliente.numCta, cliente.apellido, 
       //        cliente.nombre, cliente.saldo );
       //  } /* fin de if */

      //} /* fin de while */ 

      fclose( ptrCf ); /* fclose cierra el archivo */
   } /* fin de else */

   return 0; /* indica terminación exitosa */

} /* fin de main */

/**************************************************************************
 * (C) Copyright 1992-2004 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/

