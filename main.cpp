//LIBRERIAS
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//MACROS
#define LONGITUD_PORTAAVIONES 5
#define ANCHURA_PORTAAVIONES 2
#define SIMBOLO_PORTAAVIONES 'P'

#define LONGITUD_ACORAZADO 4
#define ANCHURA_ACORAZADO 1
#define SIMBOLO_ACORAZADO 'A'

#define LONGITUD_BUQUE 3
#define ANCHURA_BUQUE 1
#define SIMBOLO_BUQUE 'B'

#define LONGITUD_DESTRUCTOR 3
#define ANCHURA_DESTRUCTOR 1
#define SIMBOLO_DESTRUCTOR 'D'

#define LONGITUD_FRAGATA 2
#define ANCHURA_FRAGATA 1
#define SIMBOLO_FRAGATA 'F'

#define LONGITUD_LANCHA_RAPIDA 1
#define ANCHURA_LANCHA_RAPIDA 1
#define SIMBOLO_LANCHA_RAPIDA 'L'

#define ARCHIVO "estadisticas.csv"

// FUNCIONES
void menu_principal();
void juego();
void nueva_partida();
void mostrar_tablero();
void mostrar_tablero_oculto();
void generar_barco(int, int, char);
int calculo_puntuacion();
void verificar_barco_destruido(char);
void verificar_archivo_estadisticas();
void leer_estadisticas();
void guardar_estadisticas();
void partida_ganada();
void partida_cancelada();

// VARIABLES GLOBALES
char Tablero[14][14];
char Tablero_Oculto[14][14];
int wins = 0, canceled = 0, puntuacion_final = 0;


using namespace std;

void menu_principal() {
    int puntaje = 0;
    char Opcion = ' ';
    do{
        system("clear");  
        cout<<"\t***************************************"<<endl;
        cout<<"\t*                                     *"<<endl;
        cout<<"\t*        SELECCIONE UNA OPCION        *"<<endl;
        cout<<"\t*                                     *"<<endl;
        cout<<"\t***************************************"<<endl;
        cout<<endl;
        cout<<"\t\t***********************"<<endl;
        cout<<"\t\t* (A) INICIAR PARTIDA *"<<endl;
        cout<<"\t\t* (B) ESTADISTICAS    *"<<endl;
        cout<<"\t\t* (C) SALIR           *"<<endl;
        cout<<"\t\t***********************"<<endl;
        cout<<"\n\t>> ";
        cin>>Opcion;
        Opcion = toupper(Opcion);
        cout<<endl;
        
        switch(Opcion){
            case 'A':
                nueva_partida();
                juego();
                break;
            case 'B':
                leer_estadisticas();
                system("read -p 'Press Enter to continue...' var");
                break;
            case 'C':
                cout <<"Saliendo..."<<endl;
                exit(0);
                break;
            default:
                cout<<"Opcion invalida."<<endl;
                break;
        }
    }while(Opcion!='C');
}

void nueva_partida() {
    for(int x = 0; x<14; x++) {
        for(int y = 0; y<14; y++) {
            Tablero[x][y] = '_';
            Tablero_Oculto[x][y] = '_';
        }
    }
    generar_barco(LONGITUD_PORTAAVIONES, ANCHURA_PORTAAVIONES, SIMBOLO_PORTAAVIONES);
    generar_barco(LONGITUD_ACORAZADO, ANCHURA_ACORAZADO, SIMBOLO_ACORAZADO);
    generar_barco(LONGITUD_BUQUE, ANCHURA_BUQUE, SIMBOLO_BUQUE);
    generar_barco(LONGITUD_DESTRUCTOR, ANCHURA_DESTRUCTOR, SIMBOLO_DESTRUCTOR);
    generar_barco(LONGITUD_FRAGATA, ANCHURA_FRAGATA, SIMBOLO_FRAGATA);
    generar_barco(LONGITUD_LANCHA_RAPIDA, ANCHURA_LANCHA_RAPIDA, SIMBOLO_LANCHA_RAPIDA);
}

void juego() {
    char X, barco_impactado;
    int Y, X_int, aciertos = 0;
    system("clear");
    do {
        //mostrar_tablero(); 
        mostrar_tablero_oculto();
        cout<<"\'S\' para cancelar la partida."<<endl;
        do {
            cout<<"Ingrese coordenadas X (A-N): ";
            cin>>X;
            X = toupper(X);
            if(X=='S') { 
                partida_cancelada();
                guardar_estadisticas();
                system("clear");
                cout<<"Partida Cancelada.\n";
                system("read -p 'Press Enter to continue...' var");
                menu_principal();
            }
        }while(X < 'A' || X > 'N');
        
        do {
            cout<<"Ingrese coordenadas Y (1-14): ";
            cin>>Y;
        }while(Y < 1 || Y > 14);
        
        X_int = X - '0' - 17;
        Y--;
        
        system("clear");
        
        if(Tablero[X_int][Y] != '_' && Tablero_Oculto[X_int][Y] != 'X') {
            cout<<"Barco Impactado!"<<endl;
            barco_impactado = Tablero[X_int][Y];
            Tablero_Oculto[X_int][Y] = 'O';
            aciertos += 1;
        }else{
            cout<<"Tiro Fallido :("<<endl;
            Tablero_Oculto[X_int][Y] = 'X';
        }
        
        verificar_barco_destruido(barco_impactado);
        
        cout<<endl;
        system("read -p 'Press Enter to continue...' var");
        system("clear");
    }while(aciertos < 32);
    cout<<endl;
    
    if(aciertos == 32) {
        partida_ganada();
        system("clear");
        cout<<"\nGanaste! Has hundido todos los barcos!"<<endl;
        cout<<"Su puntaje es: "<<puntuacion_final<<endl;
        mostrar_tablero();
        mostrar_tablero_oculto();
        guardar_estadisticas();
    }
    system("read -p 'Press Enter to continue...' var");
}

void mostrar_tablero() {
    cout<<"\t****************************************"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t*      ESTE ES EL TABLERO DE JUEGO     *"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t****************************************"<<endl;
    cout<<"\t      A B C D E F G H I J K L M N"<<endl;
    for(int y = 0; y<14; y++) {
        cout<<"\t     ";
        for(int x = 0; x<14; x++) {
            cout<<"|"<<Tablero[x][y];
        }  
        cout<<"|";
        cout<<y+1<<endl;
    }
    cout<<endl;
}

void mostrar_tablero_oculto() {
    cout<<"\t****************************************"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t*      ESTE ES EL TABLERO DE JUEGO     *"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t****************************************"<<endl;
    cout<<"\t      A B C D E F G H I J K L M N"<<endl;
    for(int y = 0; y<14; y++) {
        cout<<"\t     ";
        for(int x = 0; x<14; x++) {
            cout<<"|"<<Tablero_Oculto[x][y];
        }  
        cout<<"|";
        cout<<y+1<<endl;
    }
    cout<<endl;
}

void generar_barco(int a, int b, char ship) {
    srand(time(NULL));
    bool barco_colocado, espacios_vacios;
    int fila_rand, columna_rand, orientacion_rand;
    do {
        orientacion_rand = rand() % 2; // 0 Vertical - 1 Horizontal
        if(orientacion_rand == 0) {
            fila_rand = rand() % 14;
            columna_rand = rand() % (14-a);
        }
        else{
            fila_rand = rand() % (14-a);
            columna_rand = rand() % (14-b);
        }
    
        espacios_vacios = true;
        for(int j = -1; j < b+1; j++) {
            for (int i = -1; i < a+1; i++) {
                if (orientacion_rand == 0) {
                    if (Tablero[fila_rand+j][columna_rand+i] != '_'){
                        espacios_vacios = false;
                        break;
                    }
                } 
                else {
                    if (Tablero[fila_rand+i][columna_rand+j] != '_') {
                        espacios_vacios = false;
                        break;
                    }
                }
            }
        }
        if (espacios_vacios) {
            for (int j = 0; j < b; j++) {
                for(int i = 0; i < a; i++) {
                    if (orientacion_rand == 0) {
                        Tablero[fila_rand+j][columna_rand+i] = ship;
                    } 
                    else {
                        Tablero[fila_rand+i][columna_rand+j] = ship;
                    }
                }
                barco_colocado = true;
            }
        }
        else {
            barco_colocado = false;
        }
    } while (barco_colocado == false);
}

void verificar_barco_destruido(char barco_impactado) {
    bool barco_destruido = false;
    for(int x = 0; x<14; x++) {
        for(int y = 0; y<14; y++) {
            if(Tablero[x][y] == barco_impactado) { 
                if(Tablero_Oculto[x][y] == 'O') {
                    barco_destruido = true;
                }
                else {
                    barco_destruido = false;
                    break;
                }
            }
        }
    }
    if(barco_destruido){
        if(barco_impactado == 'P') {
            cout<<"Portaaviones destruido!"<<endl;
        }
        else if(barco_impactado == 'A') {
            cout<<"Acorazado destruido!"<<endl;
        }
        else if(barco_impactado == 'B') {
            cout<<"Buque destruido!"<<endl;
        }
        else if(barco_impactado == 'D') {
            cout<<"Destructor destruido!"<<endl;
        }
        else if(barco_impactado == 'F') {
            cout<<"Fragata destruida!"<<endl;
        }
        else if(barco_impactado == 'L') {
            cout<<"Lancha Rapida destruida!"<<endl;
        }
    }
}

int calculo_puntuacion () {
    int tiros_fallidos = 0;
    for(int x = 0; x<14; x++) {
        for(int y = 0; y<14; y++) {
            if(Tablero_Oculto[x][y] == 'X') {
                tiros_fallidos++;
            }
        }
    }
    return(196-tiros_fallidos);
} 

int main() {
    verificar_archivo_estadisticas();
    menu_principal();
    return 0;
}

void verificar_archivo_estadisticas() {
    ifstream archivo(ARCHIVO);
    if (!archivo.is_open()) {
        // El archivo no existe, crearlo con los valores iniciales en 0
        ofstream nuevoArchivo("estadisticas.csv");
        if (nuevoArchivo.is_open()) {
            nuevoArchivo << "0,0,0,0,0\n";
            nuevoArchivo << "0\n";
            nuevoArchivo << "0\n";
            nuevoArchivo.close();
        } 
    }
    archivo.close();
}

void guardar_estadisticas() {
    int previous_wins = 0, previous_canceled = 0;
    int puntuaciones[5] = {0,0,0,0,0};
    ifstream archivo(ARCHIVO);
    if (archivo.is_open()) {
        string linea;
        char delimitador = ',';

        // Leer las estadísticas actuales
        getline(archivo, linea);
        stringstream stream(linea);
        string puntuacion, partidas_ganadas, partidas_canceladas;

        // Extraer los valores de la línea
        for (int i = 0; i < 5; i++) {
            getline(stream, puntuacion, delimitador);
            puntuaciones[i] = stoi(puntuacion);
        }
        getline(archivo, partidas_ganadas);
        getline(archivo, partidas_canceladas);

        previous_wins = stoi(partidas_ganadas);
        previous_canceled = stoi(partidas_canceladas);

        archivo.close();
    }
    
    wins += previous_wins;
    canceled += previous_canceled;
    
    // Actualizar el top de puntuaciones
    for (int i = 0; i < 5; i++) {
        if (puntuacion_final > puntuaciones[i]) {
            // Desplazar los valores existentes hacia abajo
            for (int j = 4; j > i; j--) {
                puntuaciones[j] = puntuaciones[j - 1];
            }
            // Insertar la nueva puntuación en la posición correcta
            puntuaciones[i] = puntuacion_final;
            break;
        }
    }


    // Escribir las estadísticas actualizadas en el archivo
    ofstream archivo_salida(ARCHIVO);
    if (archivo_salida.is_open()) {
        for(int i = 0; i < 5; i++) {
            archivo_salida << puntuaciones[i] << ",";
        }
        archivo_salida << "\n" <<wins << "\n";
        archivo_salida << canceled << "\n";
        archivo_salida.close();
    }  
  wins = 0;
  canceled = 0; 
  puntuacion_final = 0;
}

void partida_ganada() {
    wins++;
    puntuacion_final = calculo_puntuacion();
}

void partida_cancelada() {
    canceled++;
    puntuacion_final = 0;
}

void leer_estadisticas() {
    ifstream archivo("estadisticas.csv");
    if (archivo.is_open()) {
        string linea;
        char delimitador = ',';

        cout << "Top Puntuaciones" << endl;
        getline(archivo, linea);
        stringstream stream(linea); // Convertir la cadena a un stream
        string puntuacion;
        for (int i = 0; i < 5; i++) {
            getline(stream, puntuacion, delimitador);
            cout << puntuacion << endl;
        }

        cout << "Partidas Ganadas: ";
        getline(archivo, linea);
        cout << linea << endl;

        cout << "Partidas Canceladas: ";
        getline(archivo, linea);
        cout << linea << endl;

        archivo.close();
    }
}
