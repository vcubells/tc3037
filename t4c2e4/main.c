/* Figura 11.16: fig11_16.c
   Este programa lee de manera secuencial un archivo de acceso aleatorio, actualiza los datos
   ya escritos en el archivo, crea nuevos datos para colocarlos en el archivo, y elimina
   los datos ya existentes en el archivo. */
#include <stdio.h>

/* definición de la estructura datosCliente */
struct datosCliente { 
   int numCta;          /* número de cuenta */
   char apellido[ 15 ]; /* apellido */
   char nombre[ 10 ];   /* nombre */
   double saldo;        /* saldo */
}; /* fin de la estructura datosCliente */

/* prototipos */
int intOpcion( void );
void archivoTexto( FILE *ptrLee );
void actualizaRegistro( FILE *ptrF );
void nuevoRegistro( FILE *ptrF );
void eliminaRegistro( FILE *ptrF );

int main()
{ 
   FILE *ptrCf; /* apuntador de archivo credito.dat */
   int eleccion;  /* elección del usuario */

   /* fopen abre el archivo; si no se puede abrir, sale del archivo */
   if ( ( ptrCf = fopen( "../../t4c2e1/Debug/credito.dat", "rb+" ) ) == NULL ) {
      printf( "El archivo no pudo abrirse.\n" );
   } /* fin de if */
   else { 

      /* permite al usuario especificar una acción */
      while ( ( eleccion = intOpcion() ) != 5 ) { 

         switch ( eleccion ) { 

            /* crea el archivo desde el registro */
            case 1:
               archivoTexto( ptrCf );
               break;

            /* actualiza registro */
            case 2:
               actualizaRegistro( ptrCf );
               break;

            /* crea registro */
            case 3:
               nuevoRegistro( ptrCf );
               break;
            /* elimina el registro existente */
            case 4:
               eliminaRegistro( ptrCf );
               break;
         
            /* si el usuario no selecciona una opción válida, despliega un mensaje */
            default:
               printf( "Opcion incorrecta\n" );
               break;
       
         } /* fin de switch */

      } /* fin de while */

      fclose( ptrCf ); /* fclose cierra el archivo */
   } /* fin de else */
 
   return 0; /* indica terminación exitosa */

} /* fin de main */

  /* crea un archivo de texto con formato para impresión */ 
void archivoTexto( FILE *ptrLee )
{ 
   FILE *ptrEscribe; /* apuntador del archivo cuentas.txt */

   /* crea datosCliente con información predeterminada */
   struct datosCliente cliente = { 0, "", "", 0.0 };

   /* fopen abre el archivo; si no se puede abrir, sale del archivo */
   if ( ( ptrEscribe = fopen( "cuentas.txt", "w" ) ) == NULL ) {
      printf( "No pudo abrirse el archivo.\n" );
   } /* fin de if */
   else { 
      rewind( ptrLee ); /* establece el apuntador en el principio del archivo */
      fprintf( ptrEscribe, "%-6s%-16s%-11s%10s\n", 
         "Cta", "Apellido", "Nombre","Saldo" );

      /* copia todos los registros del archivo de acceso aleatorio dentro del archivo de texto */
      while ( !feof( ptrLee ) ) { 
         fread( &cliente, sizeof( struct datosCliente ), 1, ptrLee );

         /* escribe un registro individual en el archivo de texto */
         if ( cliente.numCta != 0 ) {
            fprintf( ptrEscribe, "%-6d%-16s%-11s%10.2f\n",
               cliente.numCta, cliente.apellido,
               cliente.nombre, cliente.saldo );
         } /* fin de if */

      } /* fin de while */

      fclose( ptrEscribe ); /* fclose cierra el archivo */
   } /* fin de else */

} /* fin de la función archivoTexto */

/* actualiza el saldo en el registro */
void actualizaRegistro( FILE *ptrF )
{ 
   int cuenta;         /* número de cuenta */
   double transaccion; /* monto de la transacción */

   /* crea datosCliente sin información  */
   struct datosCliente cliente = { 0, "", "", 0.0 };

   /* obtiene el número de cuenta para actualización */
   printf( "Introduzca cuenta para actualizacion ( 1 - 100 ): " );
   scanf( "%d", &cuenta );

   /* mueve el apuntador de archivo para corregir el registro del archivo */
   fseek( ptrF, ( cuenta - 1 ) * sizeof( struct datosCliente ), 
      SEEK_SET );

   /* lee un registro del archivo */
   fread( &cliente, sizeof( struct datosCliente ), 1, ptrF );

   /* despliega un error si la cuenta no existe */
   if ( cliente.numCta == 0 ) {
      printf( "La cuenta #%d no tiene informacion.\n", cuenta );
   } /* fin de if */
   else { /* actualiza el registro */
      printf( "%-6d%-16s%-11s%10.2f\n\n", 
         cliente.numCta, cliente.apellido, 
         cliente.nombre, cliente.saldo );
      
      /* pide al usuario el monto de la transacción */ 
      printf( "Introduzca el cargo ( + ) o el pago ( - ): " );
      scanf( "%lf", &transaccion );
      cliente.saldo += transaccion; /* actualiza el saldo del registro */
      
      printf( "%-6d%-16s%-11s%10.2f\n", 
         cliente.numCta, cliente.apellido, 
         cliente.nombre, cliente.saldo );
      
      /* mueve al apuntador de archivo al registro correcto en el archivo */
      fseek( ptrF, ( cuenta - 1 ) * sizeof( struct datosCliente ), 
         SEEK_SET );

      /* escribe el registro actualizado sobre el registro anterior en el archivo */
      fwrite( &cliente, sizeof( struct datosCliente ), 1, ptrF );
   } /* fin de else */

} /* fin de la función actualizaRegistro */

/* elimina el registro existente */
void eliminaRegistro( FILE *ptrF )
{ 

   struct datosCliente cliente; /* almacena los registros leídos en el archivo */
   struct datosCliente clienteEnBlanco = { 0, "", "", 0 }; /* cliente en blanco */
   
   int numCuenta; /* número de cuenta */

   /* obtiene el número de cuenta para eliminarlo */
   printf( "Introduzca el numero de cuenta a eliminar ( 1 - 100 ): " );
   scanf( "%d", &numCuenta );

   /* mueve el apuntador de archivo al registro correcto en el archivo */
   fseek( ptrF, ( numCuenta - 1 ) * sizeof( struct datosCliente ), 
      SEEK_SET );

   /* lee el registro del archivo */
   fread( &cliente, sizeof( struct datosCliente ), 1, ptrF );

   /* si el registro no existe, despliega un error */
   if ( cliente.numCta == 0 ) {
      printf( "La cuenta %d no existe.\n", numCuenta );
   } /* fin de if */
   else { /* elimina el registro */

      /* mueve el apuntador de archivo hacia el registro correcto en el archivo */
      fseek( ptrF, ( numCuenta - 1 ) * sizeof( struct datosCliente ), 
         SEEK_SET );

      /* reemplaza el registro existente con un registro en blanco */
      fwrite( &clienteEnBlanco, 
         sizeof( struct datosCliente ), 1, ptrF );
   } /* fin de else */

} /* fin de la función eliminaRegistro */

/* crea e inserta un registro */
void nuevoRegistro( FILE *ptrF )
{ 
   /* crea datosCliente con información predeterminada */
   struct datosCliente cliente = { 0, "", "", 0.0 };

   int numCuenta; /* número de cuenta */

   /* obtiene el número de cuenta a crear */
   printf( "Introduzca el nuevo numero de cuenta ( 1 - 100 ): " );
   scanf( "%d", &numCuenta );

   /* mueve el apuntador de archivo hacia el registro correcto en el archivo  */
   fseek( ptrF, ( numCuenta - 1 ) * sizeof( struct datosCliente ), 
      SEEK_SET );

   /* lee el registro desde el archivo */
   fread( &cliente, sizeof( struct datosCliente ), 1, ptrF );

   /* si la cuenta ya existe, despliega un error */
   if ( cliente.numCta != 0 ) {
      printf( "La cuenta #%d ya contiene informacion.\n",
              cliente.numCta );
   } /* fin de if */
   else { /* crea registro */

      /* el usuario introduce el apellido, el nombre y el saldo */
      printf( "Introduzca el apellido, el nombre, y el saldo\n? " );
      scanf("%s %s %lf", &cliente.apellido, &cliente.nombre, 
         &cliente.saldo );

      cliente.numCta = numCuenta;
      
      /* mueve el apuntador de archivo hacia el registro correcto en el archivo */
      fseek( ptrF, ( cliente.numCta - 1 ) * 
         sizeof( struct datosCliente ), SEEK_SET );

      /* inserta el registro en el archivo */
      fwrite( &cliente, 
         sizeof( struct datosCliente ), 1, ptrF );
   } /* fin de else */

} /* fin de la función nuevoRegistro */

/* inhabilita al usuario para introducir una opción de menú */
int intOpcion( void )
{ 
   int opcionMenu; /* variable para almacenar la opción del usuario */

   /* despliega las opciones disponibles */
   printf( "\nIntroduzca su opcion\n"
      "1 - almacena un archivo de texto con formato, de las cuentas llamadas\n"
      "    \"cuentas.txt\" para impresion\n"
      "2 - actualiza una cuenta\n"
      "3 - agrega una nueva cuenta\n"
      "4 - elimina una cuenta\n"
      "5 - fin del programa\n? " );

   scanf( "%d", &opcionMenu ); /* recibe la opción del usuario */

   return opcionMenu;

} /* fin de la función introduceOpcion */

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
