//
//  main.c
//  t1c1e1
//
//  Created by Vicente Cubells Nonell on 06/08/12.
//  Copyright (c) 2012 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[])
{
    
    char  nombre[5], apellidos[30];
    int edad;
    /*
    for (i = 0; i < argc; ++i) {
        printf("Arg # %d = %s \t", i, argv[i]);
    }
     */
    
        //Leer por tecldo
    
    printf("Entra el nombre: ");
    scanf("%s-%s", nombre, apellidos);
          
    printf("\n Entra la edad: ");
    scanf("%d", &edad);
    
    printf("%s - %d \n", nombre, edad);
    
    return 0;
}
