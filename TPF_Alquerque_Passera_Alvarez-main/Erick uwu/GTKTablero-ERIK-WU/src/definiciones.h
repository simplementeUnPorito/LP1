/*
 ============================================================================
 Name        : GTKTablero.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in GTK+
 ============================================================================
 */

#include <gtk/gtk.h>

#define MAX_FILA 9
#define MAX_COLUMNA 9
#define ORDEN 5

//Un vector de Strings, almacena ubicacion de imagenes
/*char *imagenes[] = {imagenes[1],
					imagenes[0]};*/

struct jugador
{
	// El 0 representa un lugar vacio, el 1 representa a las blancas y el 2 a las negras
	int ficha;
	// El 0 representa a un jugador humano y el 1 a una computadora
	int tipo;
	// La cantidad de fichas que hay en el tablero para el jugador
	int nFichas;
};
typedef struct jugador Jugador;

// La ficha que se desea mover y el conjunto de sus movimientos
struct jugada
{
	// Entero en donde la decena representa la fila y la unidad representa la columna
	int posficha;
	// Conjunto de movimientos que realiza la ficha
	char direcciones[ORDEN*ORDEN/2+1];
	// Si para realizar ls movimientos necesito realizar un salto o no
	int saltos[ORDEN*ORDEN/2];
};
typedef struct jugada Jugada;

// jugador1 son las blancas, jugador2 son las negras
Jugador jugador1, jugador2;
// turno es el jugador que juega actualmente, oponente es el rival actual
Jugador *turno,*oponente;
// Tablero
int tablero[ORDEN][ORDEN];
// Lista de vectores directores de los movimientos con sus respectivas variaciones de filas y columnas
int movimiento[8][2] = {{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};



GtkWidget *label_turno;
GtkWidget *label_estado;
GtkWidget *GTKtablero;
GtkWidget *box_tablero;

GtkWidget *window;
GtkWidget *window_menu;
GtkWidget *window_creditos;
GtkWidget *window_config;
GtkWidget *imagenes[5][5];

GtkWidget *btn_jugar;
GtkWidget *btn_creditos;
GtkWidget *btn_salir;
GtkWidget *btn_volver;
GtkWidget *btn_atras;
GtkWidget *btn_play;


void funcbtn_play(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	 gtk_widget_hide (window_config);
	 gtk_widget_show_all (window);
}

void funcbtn_atras(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	 gtk_widget_hide (window_config);
	 gtk_widget_show_all (window_menu);
}

void funcbtn_jugar(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	 gtk_widget_hide (window_menu);
	 gtk_widget_show_all (window_config);
}

void funcbtn_creditos(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	 gtk_widget_hide (window_menu);
	 gtk_widget_show_all (window_creditos);
}

void funcbtn_volver(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	 gtk_widget_hide (window_creditos);
	 gtk_widget_show_all (window_menu);
}

void funcbtn_salir(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	 gtk_widget_destroy (window_menu);
}

void tablero_cb(GtkWidget *event_box, GdkEventButton *event, gpointer data){
	guint x,y;
	GtkWidget *imagen;

	x = (GUINT_FROM_LE(event->y) / 50); //las imagenes tienen son 50x50pixeles
	y = (GUINT_FROM_LE(event->x) / 50);
	//gtk_image_set_from_file(GtkImage(imagenes[0]),x,y);
	g_print("%d",x);
	g_print("%d",y);


	/*if (x % 2 == 0 && y % 2 == 0)
	{
		x = x / 2;
		y = y / 2;
		if(tablero[x][y] != 0)
		{

		}
	}
	else
	{
		g_print("No se selecciono una ficha");
	}

	Jugada j;

	j.posficha = x * 10 + y;
	g_print("\n%d", j.posficha);

	if(jugada_valida(&j) == 0)
	{
		g_print("\nJugada invalida!!!");
	}
	else
	{
		g_print("\nJugada correcta!!!");

	}
	//realizar_jugada(j); // Marcar el tablero de acuerdo a la estrategia validada

	/*gchar *temp = g_strdup_printf("Presiono la imagen coordenada [%d,%d]", i,j);

	gtk_label_set_text(GTK_LABEL(label_estado), temp);

	int dado = rand() % 6;
	temp = g_strdup_printf("Tiramos el dado y obtenemos: %d", dado + 1);
	gtk_label_set_text(GTK_LABEL(label_turno), temp);
	if(dado + 1 > 3){
		gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(GTKtablero),j,i)), "IMG/indice.png");
	}

	g_free(temp);*/

}
GtkWidget *crear_tablero(){
	int i, j;
	//GtkWidget *imagen; //auxiliar para cargar la imagen
	GtkWidget *eventbox;
	eventbox = gtk_event_box_new();
	GTKtablero = gtk_grid_new();
	char *fichas[3] = {"./IMG/indice.png","./IMG/indice.png","./IMG/indice.png"};


	for (i = 0; i < MAX_FILA; i++)
	{
		for (j = 0; j < MAX_COLUMNA; j++) {
			imagenes[i][j] = gtk_image_new_from_file(fichas[0]);
			gtk_grid_attach(GTK_GRID(GTKtablero), GTK_WIDGET(imagenes[i][j]), i, j, 1, 1);

		}

			//if(i % 2 == 0 && j % 2 == 0)
		//	{

				/*if(i < 4)
				{

					imagenes[i][j] = gtk_image_new_from_file(fichas[0]);
					gtk_grid_attach(GTK_GRID(GTKtablero), GTK_WIDGET(imagenes[i][j]), j, i, 1, 1);
				}
				else if(i > 4)
				{
					imagenes[i][j] = gtk_image_new_from_file(fichas[1]);
					gtk_grid_attach(GTK_GRID(GTKtablero), GTK_WIDGET(imagenes[i][j]), j, i, 1, 1);
				}
				else if (j < 4)
				{
					imagenes[i][j] = gtk_image_new_from_file(fichas[0]);
					gtk_grid_attach(GTK_GRID(GTKtablero), GTK_WIDGET(imagenes[i][j]), j, i, 1, 1);
				}
				else if (j > 4)
				{
					imagenes[i][j] = gtk_image_new_from_file(fichas[1]);
					gtk_grid_attach(GTK_GRID(GTKtablero), GTK_WIDGET(imagenes[i][j]), j, i, 1, 1);
				}
				else
				{
					imagenes[i][j] = gtk_image_new_from_file(fichas[2]);
					gtk_grid_attach(GTK_GRID(GTKtablero), GTK_WIDGET(imagenes[i][j]), j, i, 1, 1);
				}
			}
			else if((i + j) % 2 == 0)
			{
				if((i + j) / 2 % 2 == 0)
				{
					imagenes[i][j] = gtk_image_new_from_file(fichas[2]);
					gtk_grid_attach(GTK_GRID(GTKtablero), GTK_WIDGET(imagenes[i][j]), j, i, 1, 1);
				}
				else
				{
					imagenes[i][j] = gtk_image_new_from_file(fichas[2]);
					gtk_grid_attach(GTK_GRID(GTKtablero), GTK_WIDGET(imagenes[i][j]), j, i, 1, 1);
				}
			}
			else if (i % 2 == 0)
			{
				imagenes[i][j] = gtk_image_new_from_file(fichas[2]);
				gtk_grid_attach(GTK_GRID(GTKtablero), GTK_WIDGET(imagenes[i][j]), j, i, 1, 1);
			}
			else if (j % 2 == 0)
			{
				imagenes[i][j] = gtk_image_new_from_file(fichas[2]);
				gtk_grid_attach(GTK_GRID(GTKtablero), GTK_WIDGET(imagenes[i][j]), j, i, 1, 1);
			}*/
	}

	gtk_container_add(GTK_CONTAINER(eventbox), GTKtablero);
	g_signal_connect(eventbox, "button-press-event", G_CALLBACK(tablero_cb), GTKtablero);
	return eventbox;
}
/*
void jugada_humano(int m, int n)
{
	Jugada j;
	char m1,n1;

	m1 = m1 + '0';
	n1 = n1 + '0';
	char aux[2];
	aux[0] = m1;
	aux[1] = n1;

	j.posficha = atoi(aux);
	g_print("%d", j.posficha);


	do
	{
		g_print("\nElija la ficha que desee mover(FilaColumna): ");
		scanf("%d", &j.posficha);
		g_print("\nIngrese las direcciones: \n0 - Arriba Izquierda\n1 - Arriba\n2 - Arriba Derecha\n3 - Derecha\n4 - Abajo Derecha\n5 - Abajo\n6 - Abajo Izquierda\n7 - Izquierda");
		g_print("\nIngrese los datos de la jugada: ");
		scanf("%s", j.direcciones);
	}
	while(jugada_valida(&j) == 0);// Realiza la jugada verificando si es posible realizarla y deshaciendola al final
	realizar_jugada(j); // Marcar el tablero de acuerdo a la estrategia validada
}*/
/*int estaEnElTablero(int fil, int col)
{
	g_print("LLEGO");

	return fil >=0 && fil < ORDEN && col >=0 && col < ORDEN;
}*/
int jugada_valida(Jugada *j)
{
	int fil1,fil2,fil3,col1,col2,col3;
	int m, dir,validacion = 1;

	fil1 = j->posficha / 10; // Las decenas de posficha es la fila
	col1 = j->posficha % 10; // Las unidades de posficha es la columna


		g_print("LLEGO");

	if(turno->tipo == 0) // Si el jugador es humano muestra el error
	{
		g_print("\nLa posicion elegida no se encuentra dentro del tablero...\nPor favor intente de nuevo con otra ficha!!!\n");
	}
	validacion = 0;
	return validacion;
	if (tablero[fil1][col1] != turno->ficha) // Si no es la ficha del jugador retorna 0
	{
		if(turno->tipo == 0) // Si el jugador es humano muestra el error
		{
			g_print("\nLa ficha elegida no se puede mover...\nPor favor intente de nuevo con otra ficha!!!\n");
		}
		validacion = 0;
		return validacion;
	}

	for(m = 0; j->direcciones[m] != '\0' && validacion == 1; m++) // Validacion de los movimientos de la ficha elegida
	{
		dir = j->direcciones[m] - 48; // Conversion de ASCII a numerico

		if ((fil1 + col1) % 2 == 1 && dir % 2 == 0) // definicion de diagonales y verificacion de diagonales disponibles para el juego
		{
			if(turno->tipo == 0) // Si el jugador es humano muestra el error
			{
				g_print("\nEl movimiento elegido no es valido...\nPor favor intente de nuevo con otra ficha!!!\n");
			}
			validacion = 0;
			break;
		}

		fil2 = fil1 + movimiento[dir][0]; // Fila adyacente de fil1
		col2 = col1 + movimiento[dir][1]; // Columna adyacente de col1
		fil3 = fil2 + movimiento[dir][0]; // Fila que nos movemos si es que tenemos que comer una ficha
		col3 = col2 + movimiento[dir][1]; // Columna que nos movemos si es que tenemos que comer una ficha


		if(turno->tipo == 0) // Si el jugador es humano muestra el error y retorna 0
		{
			g_print("\nEl movimiento elegido no es valido...\nPor favor intente de nuevo con otra ficha!!!\n");
		}
		validacion = 0;

		if(tablero[fil2][col2] == 0) // Movimiento simple a la celda adyacente sin salto
		{
			tablero[fil1][col1] = 0;
			fil1 = fil2;
			col1 = col2;
			tablero[fil1][col1] = turno->ficha;
			j->saltos[m] = 0;
		}
		else if(tablero[fil2][col2] != turno->ficha)
		{
			if(!estaEnElTablero(fil3,col3))
			{
				if(turno->tipo == 0)
				{
					g_print("\nEl movimiento elegido no es valido...\nPor favor intente de nuevo con otra ficha!!!\n");
				}
				validacion = 0;
				break;
			}
			else if(tablero[fil3][col3] != 0)
			{
				if(turno->tipo == 0)
				{
					g_print("\nEl movimiento elegido no es valido...\nPor favor intente de nuevo con otra ficha!!!\n");
				}
				validacion = 0;
				break;
			}
			else // Movimiento con salto comiendo una ficha
			{
				tablero[fil1][col1] = 0;
				fil1 = fil3;
				col1 = col3;
				tablero[fil1][col1] = turno->ficha;
				tablero[fil2][col2] = 0;
				j->saltos[m] = 1;
			}
		}
		else
		{
			if(turno->tipo == 0)
			{
				g_print("\nEl movimiento elegido no es valido...\nPor favor intente de nuevo con otra ficha!!!\n");
			}
			validacion = 0;
			break;
		}
	}
	for(m = m-1; m >= 0; m--) // Deshacer la jugada
	{

		dir = j->direcciones[m] - 48;
		fil2 = fil1 - movimiento[dir][0];
		col2 = col1 - movimiento[dir][1];
		fil3 = fil2 - movimiento[dir][0];
		col3 = col2 - movimiento[dir][1];

		tablero[fil1][col1] = 0;
		if(j->saltos[m] == 0)
		{
			fil1 = fil2;
			col1 = col2;
		}
		else
		{
			fil1 = fil3;
			col1 = col3;
			tablero[fil2][col2] = oponente->ficha;
		}
		tablero[fil1][col1] = turno->ficha;
	}
	return validacion;
}

void realizar_jugada(Jugada j)
{
	int fil1,fil2,fil3,col1,col2,col3;
	int m, dir;

	fil1 = j.posficha / 10; // Las decenas de posficha es la fila
	col1 = j.posficha % 10; // Las unidades de posficha es la columna

	for(m = 0; j.direcciones[m] != '\0';m++)
	{
		dir = j.direcciones[m] - 48;
		fil2 = fil1 + movimiento[dir][0]; // Fila adyacente de fil1
		col2 = col1 + movimiento[dir][1]; // Columna adyacente de col1
		fil3 = fil2 + movimiento[dir][0]; // Fila que nos movemos si es que tenemos que comer una ficha
		col3 = col2 + movimiento[dir][1]; // Columna que nos movemos si es que tenemos que comer una ficha

		tablero[fil1][col1] = 0; // Quita la ficha que se va a mover del tablero
		if(j.saltos[m] == 0) // Definir la nueva posicion de la ficha sin salto
		{
			fil1 = fil2;
			col1 = col2;
		}
		else if(j.saltos[m] == 1) // Definir la nueva posicion de la ficha haciendo un salto y comiendo una ficha
		{
			fil1 = fil3;
			col1 = col3;
			tablero[fil2][col2] = 0; // Quitar la ficha del tablero del oponente que fue comida
			oponente->nFichas--;  // Disminuir la cantidad de fichas del oponente en el tablero
		}
		tablero[fil1][col1] = turno->ficha; // Coloca la ficha movida nuevamente en el tablero
	}
}





 int main (int argc, char *argv[])
 {
    //Para el GtkBuilder
    guint ret;
    GtkBuilder *builder;
    GError *error = NULL;

    gtk_init (&argc, &argv);

	builder = gtk_builder_new();
	//Se carga el builder
	ret = gtk_builder_add_from_file(builder, "tablero.glade", &error);
	if (ret == 0) {
		g_print("Error en la función gtk_builder_add_from_file:\n%s", error->message);
		return 1;
	}

	//Ventana principal
	window = GTK_WIDGET(gtk_builder_get_object(builder, "ventana"));
	window_menu = GTK_WIDGET(gtk_builder_get_object(builder, "window_menu"));
	window_creditos = GTK_WIDGET(gtk_builder_get_object(builder, "window_creditos"));
	window_config = GTK_WIDGET(gtk_builder_get_object(builder, "window_config"));

	btn_jugar = GTK_WIDGET(gtk_builder_get_object(builder, "btn_jugar"));
	btn_creditos = GTK_WIDGET(gtk_builder_get_object(builder, "btn_creditos"));
	btn_salir = GTK_WIDGET(gtk_builder_get_object(builder, "btn_salir"));
	btn_volver = GTK_WIDGET(gtk_builder_get_object(builder, "btn_volver"));
	btn_atras = GTK_WIDGET(gtk_builder_get_object(builder, "btn_atras"));
	btn_play = GTK_WIDGET(gtk_builder_get_object(builder, "btn_play"));



	//Box donde estara el Tablero
	box_tablero = GTK_WIDGET(gtk_builder_get_object(builder, "box_tablero"));

	//Labels
	label_turno = GTK_WIDGET(gtk_builder_get_object(builder, "label_turno"));
	label_estado = GTK_WIDGET(gtk_builder_get_object(builder, "label_estado"));

	gtk_box_pack_start(GTK_BOX(box_tablero), crear_tablero(), TRUE, FALSE, 20);

    /* Connect the destroy signal of the window to gtk_main_quit
     * When the window is about to be destroyed we get a notification and
     * stop the main GTK+ loop
     */
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect(btn_jugar, "button-press-event", G_CALLBACK(funcbtn_jugar), NULL);
	g_signal_connect(btn_creditos, "button-press-event", G_CALLBACK(funcbtn_creditos), NULL);
	g_signal_connect(btn_volver, "button-press-event", G_CALLBACK(funcbtn_volver), NULL);
	g_signal_connect(btn_salir, "button-press-event", G_CALLBACK(funcbtn_salir), NULL);
	g_signal_connect(btn_atras, "button-press-event", G_CALLBACK(funcbtn_atras), NULL);
	g_signal_connect(btn_play, "button-press-event", G_CALLBACK(funcbtn_play), NULL);






    /* make sure that everything, window and label, are visible */
    gtk_widget_show_all (window_menu);

    /* start the main loop, and let it rest there until the application is closed */
    gtk_main ();

    return 0;
 }
