#include "proyecto_h.h"
/*Trabajo de diseños de base de datos
  Participantes: Albin Dario Fernandez Galeano
                  Brian Jose Vasquez Escorcia
				  Eduardo Antonio Lopez Lopez
				  Oscar Francisco Reyes Blandon*/

int main(int argc, char *argv[]) {
	int opcion,i;
	PLibro listaLibros=NULL;
	PUsuario listaUsuarios=NULL;
	PPrestamo listaPrestamos=NULL;
	

	do{
		do{
			printf("\n\tOpciones:\n");
			printf("\t1.Dar de alta libro\n");
			printf("\t2.Dar de baja libro\n");
			printf("\t3.Dar de alta usuario\n");
			printf("\t4.Dar de baja usuario\n");
			printf("\t5.Dar de alta prestamo\n");
			printf("\t6.Dar de baja prestamo\n");
			printf("\t7.Ver lista de libros\n");
			printf("\t8.ver lista de usuarios\n");
			printf("\t9.ver lista de prestamos\n");
			printf("\t10.Ver libros prestados por algun usuario\n");
			printf("\t11.Listar libros que se encuentran prestados\n");
			printf("\t12.Finalizar\n");
			printf("\tOpcion: ");
			scanf("%d",&opcion);
			if(opcion<1 || opcion>12){
				printf("\n\tOpcion incorrecta...");
				puts("\n");
			}	
		}while(opcion<1 || opcion>12);
		switch(opcion){
			case 1:
			    darDeAltaLibro(&listaLibros);
				break;
			case 2:
				darDeBajaLibro(&listaLibros,listaPrestamos);
				break;
			case 3:
				darDeAltaUsuario(&listaUsuarios);
				break;
			case 4:
				darDeBajaUsuario(&listaUsuarios,listaPrestamos);
				break;
			case 5:
				darDeAltaPrestamo(&listaPrestamos,listaLibros,listaUsuarios);
				break;
			case 6:
			     darDeBajaPrestamo(&listaPrestamos);
				 break;
			case 7:
			     verListaDeLibros(listaLibros);
				 break;
		    case 8:
		    	verListaDeUsuarios(listaUsuarios);
		    	break;
		    case 9:
		    	verListaDePrestamos(listaPrestamos);
		    	break;
		    case 10:
		    	librosPrestadosPorUsuarioDeterminado(listaPrestamos,listaUsuarios);
		    	break;
		    case 11:
		    	listaDeLibrosPrestados(listaPrestamos);
		    	break;
			case 12:
				printf("\n\tFin del programa...");
				exit(-1);
				break;
				
		}
	}while(opcion!=12);
	return 0;
}
