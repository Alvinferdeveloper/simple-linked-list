#include "proyecto_h.h"

PLibro nodoLibro(void){
	PLibro nuevo;
	nuevo=(PLibro)malloc(sizeof(Libro));
	if(nuevo==NULL){
		perror("Error al asignar memoria");
		exit (-1);
	}	
	return nuevo;
	
}
PUsuario nodoUsuario(void){
	PUsuario nuevo;
	nuevo=(PUsuario)malloc(sizeof(Usuario));
	if(nuevo==NULL){
		perror("Error al asignar memoria");
		exit (-1);
	}	
	return nuevo;
	
}
PPrestamo nodoPrestamo(void){
	PPrestamo nuevo;
	nuevo=(PPrestamo)malloc(sizeof(Prestamo));
	if(nuevo==NULL){
		perror("Error al asignar memoria");
		exit (-1);
	}	
	return nuevo;
	
}

void darDeAltaLibro(PLibro* cab){
	int i;
	PLibro nuevo=nodoLibro();
	printf("\n\tTitulo del libro: ");
	fflush(stdin);
	gets(nuevo->titulo);
	cadenaMinuscula(nuevo->titulo);
	printf("\n\tAutor del libro: ");
	gets(nuevo->autor);
	printf("\n\tnumero de edicion del libro: ");
	scanf("%d",&nuevo->edicion);
	nuevo->sig=*cab;
	*cab=nuevo;
	printf("\n\t---------------Libro dado de alta exitosamente------------------\n");
	actualizarFicheroLibros(*cab);
}

void darDeBajaLibro(PLibro *cab,PPrestamo prestamos){
	int i;
	char nombreLibro[50];
	PLibro aux=*cab;
	PLibro q=*cab;
		if(*cab==NULL){
			printf("\n\tNo se encuentran libros disponibles\n");
			return;
		}
				
	   printf("\n\tIngrese el titulo del libro a eliminar: ");
	   fflush(stdin);
	   gets(nombreLibro);
	   for(i=0;i<strlen(nombreLibro);i++){
		    nombreLibro[i]=tolower(nombreLibro[i]);
	   }
	    
		while(prestamos){
			if(strcmp(nombreLibro,prestamos->titulo_libro)==0){
				printf("\n\tNo se puede dar de baja este libro ya que se encuentra prestado\n");
				return;
			}
			prestamos=prestamos->sig;
		}
		
	if(strcmp(nombreLibro,aux->titulo)==0){
		*cab=aux->sig;
		free(aux);	
		actualizarFicheroLibros(*cab);
		printf("\n\t------------Libro eliminado exitosamente---------------\n");
	}
	else{
		while(aux->sig!=NULL){
			if(strcmp(nombreLibro,aux->sig->titulo)==0){
				q=aux->sig;
				aux->sig=q->sig;
				free(q);
				actualizarFicheroLibros(*cab);
				printf("\n\t------------Libro eliminado exitosamente---------------\n");
				return;
			}
			aux=aux->sig;
		}
		if(aux->sig==NULL){
			printf("\n\tLibro no encontrado\n");
		}
	}
	
}


void actualizarFicheroLibros(PLibro cab){
	FILE *archivo=fopen("fichero_libros.txt","w");
	fputs("Tabla de libros disponibles\n\n",archivo);
	fprintf(archivo,"Titulo\tEdicion\tAutor\n");
	while(cab){
		fprintf(archivo,"%s\t%10d\t%10s\n",cab->titulo,cab->edicion,cab->autor);
		cab=cab->sig;
	}
	
	fclose(archivo);
}


void darDeAltaUsuario(PUsuario *cab){
	int i,opcion;
	PUsuario q=*cab;
	PUsuario usuario=nodoUsuario();
	printf("\n\tIngrese el nombre del usuario: ");
	fflush(stdin);
	gets(usuario->nombre);
	cadenaMinuscula(usuario->nombre);
	printf("\n\tIngrese la identificcion del usuario: ");
	gets(usuario->identificacion);
	cadenaMinuscula(usuario->identificacion);
	while(q){
		if(strcmp(q->identificacion,usuario->identificacion)==0){
			printf("\n\tEste identificacion ya existe en el sistema por favor vuelva a intentarlo...\n");
			return;
		}
		q=q->sig;
	}
	do{
	printf("\n\tTipo de usuario: ");
	printf("\n\t1.Estudiante");
	printf("\n\t2.Docente");
	printf("\n\tOpcion: ");
	scanf("%d",&opcion);
	if(opcion<1 || opcion>2){
		printf("\n\tOpcion incorrecta...");
	}
    }while(opcion<1 || opcion>2);
    switch(opcion){
    	case 1:
    		strcpy(usuario->tipo_usuario,"Estudiante");
    		break;
    	case 2:
    		strcpy(usuario->tipo_usuario,"Docente");
    		break;
	}
	usuario->sig=*cab;
	*cab=usuario;
	actualizarFicheroUsuarios(*cab);
	printf("\n\t----------------Libro dado de alta exitosamente----------------\n");
	
}

void darDeBajaUsuario(PUsuario *cab,PPrestamo prestamos){
	int i;
	PUsuario aux=*cab;
	PUsuario q=*cab;
	char nombreUsuario[50];
	if(*cab==NULL){
		printf("\n\tNo hay usuarios registrados\n");
		return;
	}
	printf("\n\tIngrese el nombre del usuario a dar de baja: ");
	fflush(stdin);
	gets(nombreUsuario);
	cadenaMinuscula(nombreUsuario);
	
		while(prestamos){
			if(strcmp(nombreUsuario,prestamos->nombre_usuario)==0){
				printf("\n\tNo se puede dar de baja a este usuario ya que posee libros prestados\n");
				return;
			}
			prestamos=prestamos->sig;
		}
		
	if(strcmp(nombreUsuario,aux->nombre)==0){
		*cab=aux->sig;
		free(aux);
		actualizarFicheroUsuarios(*cab);
		printf("\n\t------------Usuario dado de baja exitosamente---------------\n");
	}
	else{
		while(aux->sig!=NULL){
			if(strcmp(nombreUsuario,aux->sig->nombre)==0){
				q=aux->sig;
				aux->sig=q->sig;
				free(q);
				actualizarFicheroUsuarios(*cab);
				printf("\n\t------------Usuario dado de baja exitosamente---------------\n");
				return;
			}
			aux=aux->sig;
		}
		if(aux->sig==NULL){
			printf("\n\tUsuario no encontrado\n");
		}
	}
	
}


void actualizarFicheroUsuarios(PUsuario cab){
	FILE *archivo=fopen("fichero_usuarios.txt","w");
	fputs("Tabla de usuarios\n\n",archivo);
	fprintf(archivo,"Nombre\t\tIdentificacion\t\tTipo de usuario\n");
	while(cab){
		fprintf(archivo,"%s\t%15s\t%20s\n",cab->nombre,cab->identificacion,cab->tipo_usuario);
		cab=cab->sig;
	}
	
	fclose(archivo);
}


void darDeAltaPrestamo(PPrestamo *cab,PLibro libros,PUsuario usuarios){
	int i,opcion;
	PPrestamo q=*cab;
	PPrestamo prestamo=nodoPrestamo();
	if(libros==NULL){
		printf("\n\tNo puede realizar prestamos ya que no hay libros disponibles\n");
		return;
	}
	printf("\n\tIngrese titulo del libro a prestar: ");
	fflush(stdin);
	gets(prestamo->titulo_libro);
	cadenaMinuscula(prestamo->titulo_libro);
	while(libros){
		if(strcmp(libros->titulo,prestamo->titulo_libro)==0){
			printf("\n\tIngresa el nombre del usuario: ");
			gets(prestamo->nombre_usuario);
			cadenaMinuscula(prestamo->nombre_usuario);
			while(usuarios){
				if(strcmp(prestamo->nombre_usuario,usuarios->nombre)==0){
					printf("\n\tFecha de prestamo: ");
					gets(prestamo->fecha_prestamo);
					printf("\n\tFecha de devolucion: ");
					fflush(stdin);
					gets(prestamo->fecha_devolucion);
					prestamo->sig=*cab;
					*cab=prestamo;
					printf("\n\t-------------------prestamo dado de alta exitosamente-----------------------\n");
					actualizarFicheroPrestamos(*cab);
					return;
				}
				usuarios=usuarios->sig;
			}
				if(usuarios==NULL){
					printf("\n\tEl nombre de usuario no se encuentra registrado por favor registrate como nuevo usuario\n");
					return;
				}
			
		}
		libros=libros->sig;
		if(libros==NULL){
			printf("\n\tLibro no disponible...\n");
			free(prestamo);
		}
	}
	
}
void darDeBajaPrestamo(PPrestamo *cab){
	int i;
	PPrestamo q=*cab;
	PPrestamo aux=*cab;
	char nombreUsuario[30];
	char nombreLibro[30];
	if(*cab==NULL){
		printf("\n\tNo hay prestamos registrados...");
		puts("\n");
		return;
	}
	printf("\n\tIngrese el nombre del usuario del prestamo: ");
	fflush(stdin);
	gets(nombreUsuario);
	cadenaMinuscula(nombreUsuario);
	printf("\n\tIngrese el libro correspondiente al prestamo: ");
	gets(nombreLibro);
	cadenaMinuscula(nombreLibro);
	if(strcmp(q->nombre_usuario,nombreUsuario)==0 && strcmp(q->titulo_libro,nombreLibro)==0){
		*cab=q->sig;
		free(q);
		actualizarFicheroPrestamos(*cab);
		printf("\n\t-------------Prestamo dado de baja exitosamente-------------------\n");
		return;
	}
	while(q){
		if(strcmp(q->sig->nombre_usuario,nombreUsuario)==0 && strcmp(q->sig->titulo_libro,nombreLibro)==0){
			aux=q->sig;
			q->sig=aux->sig;
			free(aux);
			actualizarFicheroPrestamos(*cab);
			printf("\n\t-------------Prestamo dado de baja exitosamente-------------------\n");
			return;
		}
		q=q->sig;
	}
	
	
	
}
void actualizarFicheroPrestamos(PPrestamo cab){
	FILE *archivo=fopen("fichero_prestamos.txt","w");
	fputs("Lista de prestamos\n\n",archivo);
	fprintf(archivo,"Libro_t\t\tNombre_u\t\tFecha_p\t\tFecha_d\n");
	while(cab){
		fprintf(archivo,"%s\t\t%10s\t\t%10s\t\t%10s\n",cab->titulo_libro,cab->nombre_usuario,cab->fecha_prestamo,cab->fecha_devolucion);
		cab=cab->sig;
	}
	fclose(archivo);
	
}


void verListaDeLibros(PLibro cab){
	if(cab==NULL){
		printf("\n\tno hay libros en la lista...\n");
		return;
	}
	while(cab){
		printf("\n\tLibro:%s\tAutor:%s",cab->titulo,cab->autor);
		cab=cab->sig;	
	}
	puts("\n");
}
void verListaDeUsuarios(PUsuario cab){
	if(cab==NULL){
		printf("\n\tno hay usuarios en la lista...\n");
		return;
	}
	while(cab){
		printf("\n\tNombre:%s\tIdentificacion:%s",cab->nombre,cab->identificacion);
		cab=cab->sig;
		
	}
	puts("\n");
}

void verListaDePrestamos(PPrestamo cab){
	if(cab==NULL){
		printf("\n\tno hay prestamos en la lista...\n");
		return;
	}
	while(cab){
		printf("\n\tPrestamo por:%s\tLibro:%s\tFecha_p:%s\tfecha_d:%s",cab->nombre_usuario,cab->titulo_libro,cab->fecha_prestamo,cab->fecha_devolucion);
		cab=cab->sig;
		
	}
	puts("\n");
}


void librosPrestadosPorUsuarioDeterminado(PPrestamo prestamos,PUsuario listaUsuarios){
	char nombreUsuario[50];
	int cont=0;
	if(prestamos==NULL){
		printf("\n\tNo hay prestamos disponibles\n");
		return;
	}
	printf("\n\tIngrese el nombre de usuario a consultar: ");
	fflush(stdin);
	gets(nombreUsuario);
	cadenaMinuscula(nombreUsuario);
	while(listaUsuarios){
		if(strcmp(listaUsuarios->nombre,nombreUsuario)==0){
			break;
		}
		if(listaUsuarios->sig==NULL){
			printf("\n\tNo existe ningun usuario con este nombre\n");
			return;
		}
		listaUsuarios=listaUsuarios->sig;
	}
	printf("\n\t----------Lista de libros prestados por el usuario-------------");
	while(prestamos){
		if(strcmp(prestamos->nombre_usuario,nombreUsuario)==0){
			printf("\n\t%s",prestamos->titulo_libro);
			cont++;
		}
		prestamos=prestamos->sig;
}
puts("\n");
    if(cont==0){
	  printf("\n\tEste usuario no posee prestamos\n");		
	}

}

	
void listaDeLibrosPrestados(PPrestamo prestamos){
	if(prestamos==NULL){
		printf("\n\tNo existen prestamos...\n");
		return;
	}
	while(prestamos){
		printf("\n\tLibro:%s\tUsuario:%s",prestamos->titulo_libro,prestamos->nombre_usuario);
		prestamos=prestamos->sig;
	}
	puts("\n");
	
}
void cadenaMinuscula(char cadena[]){
	int i;
	for(i=0;i<strlen(cadena);i++){
	cadena[i]=tolower(cadena[i]);
	}
}
