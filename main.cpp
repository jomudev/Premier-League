/*
	Proyecto programa que simule la liga de Inglaterra, torneo llamado Premiere League
	el cual consiste en una disputa de 20 equipos por 1 título, el ganador se define
	por el mayor puntaje

	Fecha: Lunes 4 de Marzo del 2023

	Elaborado por: - Joann Murillo
	               - Emerson Jiménez

	Versión: 1.0
*/
#include <random>
#include <cstdlib>
#include <iostream>
#include <clocale>
#include <cmath>
using namespace std;

string equipos[20] = { "Arsenal",	"Liverpool", "Manchester City",	"A Villa", "Tottenham",	"Manchester United",
                       "West Ham", "Brighton", "Wolves", "Newcastle",	"Chelsea", "Fulham", "Bournemouth",
                       "Crystal Palace", "Brentford", "Everton", "Nott'm Forest", "Luton",	"Burnley", "Sheffield Utd" };

int jornadas[38][10][2], resultados[38][10][2], puntuaciones[20], partidosGanados[20], partidosEmpatados[20], totalGoles[20], partidosJugados[20], clasificacion[20];

void imprimirLineaDeDivision() {
    cout << "============================================" << endl;
    cout << "==                                        ==" << endl;
    cout << "============================================" << endl;
}

void inicializarMatrices () {
    for (int indiceEquipo = 0; indiceEquipo < 20; indiceEquipo ++) {
        puntuaciones[indiceEquipo] = 0;
        partidosEmpatados[indiceEquipo] = 0;
        partidosGanados[indiceEquipo] = 0;
        totalGoles[indiceEquipo] = 0;
        partidosJugados[indiceEquipo] = 0;
    }
}

string posicionSufijo(int posicion) {
    // posicion > 0
    string posicionSufijo;
    int decenas = posicion / 10;
    if (decenas == 0) {
        if (posicion == 1 || posicion == 3) posicionSufijo = "er";
        if (posicion == 2) posicionSufijo = "do";
        if (posicion > 3 && posicion < 7) posicionSufijo = "to";
        if (posicion == 7) posicionSufijo = "mo";
        if (posicion == 8) posicionSufijo = "vo";
        if (posicion == 9) posicionSufijo = "no";
    } else {
        int unidades = posicion - decenas * 10;
        if (unidades >= 0 && unidades < 3) posicionSufijo = "mo";
        if (unidades == 3) posicionSufijo = "er";
        if (unidades > 3 && unidades < 7) posicionSufijo = "to";
        if (unidades == 7) posicionSufijo = "mo";
        if (unidades == 8) posicionSufijo = "vo";
        if (unidades == 9) posicionSufijo = "no";
    }
    return to_string(posicion) + posicionSufijo;
}

// Función para generar un numero aleatorio entre 0 y 4 usada para determinar los goles de cada equipo
int generarGoles() {
    return random() % (5);
}

void evaluarPartido (int idEquipo1, int golesEquipo1, int idEquipo2, int golesEquipo2) {
    if (golesEquipo1 == golesEquipo2) {
        partidosEmpatados[idEquipo1] += 1;
        partidosEmpatados[idEquipo2] += 1;
        puntuaciones[idEquipo1] += 1;
        puntuaciones[idEquipo2] += 1;
    }
    if (golesEquipo1 > golesEquipo2) {
        partidosGanados[idEquipo1] += 1;
        puntuaciones[idEquipo1] += 3;
        return;
    }
    partidosGanados[idEquipo2] += 1;
    puntuaciones[idEquipo2] += 3;
}

void clasificar() {
    bool omitir[20] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

    for (int posicion = 0; posicion < 20; posicion ++ ) {
        int indiceMayor = 0;
        int puntuacionMayor = 0;
        for (int indiceEquipo = 0; indiceEquipo < 20; indiceEquipo ++ ) {
            if (!omitir[indiceEquipo]) {
                if (puntuaciones[indiceEquipo] > puntuacionMayor) {
                    puntuacionMayor = puntuaciones[indiceEquipo];
                    indiceMayor = indiceEquipo;
                }
            }
        }
        clasificacion[posicion] = indiceMayor;
        omitir[indiceMayor] = true;
    }
}

void inicializarPuntuaciones() {
    for (int indiceJornada = 0; indiceJornada < 38; indiceJornada++) {
        for (int indicePartido = 0; indicePartido < 10; indicePartido++) {
            int equipo1 = jornadas[indiceJornada][indicePartido][0];
            int equipo2 = jornadas[indiceJornada][indicePartido][1];
            int golesEquipo1 = resultados[indiceJornada][indicePartido][0];
            int golesEquipo2 = resultados[indiceJornada][indicePartido][1];
            evaluarPartido(equipo1, golesEquipo1, equipo2, golesEquipo2);
        }
    }
}

void limpiarBufferDeEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void imprimirNombreEquipos() {
    for (int indiceEquipo = 0; indiceEquipo < 20; indiceEquipo ++) {
        cout << (indiceEquipo + 1) << ". " << equipos[indiceEquipo] << endl;
    }
    limpiarBufferDeEntrada();
}

// Función que retorna un número entre el 0 y el 19
int seleccionarEquipo() {
    return rand() % 20;
}

// revisar que todos los partidos estan efectuados
bool partidosEstanCompletos(const bool *partidos_a_verificar) {
    bool resultado = true;
    for (int conteoPartidos = 0; conteoPartidos < 20; conteoPartidos ++) {
        if (!partidos_a_verificar[conteoPartidos]) {
            resultado = false;
            break;
        }
    }
    return resultado;
}

void generarPartidos(int indexJornada) {
    // Arreglo que almacena la cantidad de partidos jugados por equipo para que el algoritmo lo tenga presente.
    // Template [ indice: indiceEquipo => valor: participación ];
    bool participacionDeEquipos[20] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
    // Ciclo para crear los partidos
    // conteo de partidos empieza en cero; conteo es menor que el tamaño de los partidos, o sea menor a diez (10)
    for (int conteoPartidos = 0; conteoPartidos < 10 && !partidosEstanCompletos(participacionDeEquipos); conteoPartidos ++) {
        // Selección del primer equipo
        int primerEquipoSeleccionado = seleccionarEquipo();
        int equipo1YaParticipo = participacionDeEquipos[primerEquipoSeleccionado];
        bool equipo1NoPuedeSerSeleccionado = equipo1YaParticipo > 0 && !partidosEstanCompletos(participacionDeEquipos);
        // ciclo se ejecuta en caso de que el equipo ya haya sido seleccionado previamente
        while (equipo1NoPuedeSerSeleccionado) {
            primerEquipoSeleccionado = seleccionarEquipo();
            equipo1YaParticipo = participacionDeEquipos[primerEquipoSeleccionado];
            equipo1NoPuedeSerSeleccionado = equipo1YaParticipo && !partidosEstanCompletos(participacionDeEquipos);
        }
        participacionDeEquipos[primerEquipoSeleccionado] = true;

        // Selección del segundo equipo
        int segundoEquipoSeleccionado = seleccionarEquipo();
        int equipo2YaParticipo = participacionDeEquipos[segundoEquipoSeleccionado];
        bool equipo2NoPuedeSerSeleccionado = equipo2YaParticipo > 0 || !partidosEstanCompletos(participacionDeEquipos);
        // ciclo se ejecuta en caso de que el equipo ya haya sido seleccionado previamente o sea el mismo que su equipo contrincante
        while (equipo2NoPuedeSerSeleccionado) {
            segundoEquipoSeleccionado = seleccionarEquipo();
            equipo2YaParticipo = participacionDeEquipos[segundoEquipoSeleccionado];
            equipo2NoPuedeSerSeleccionado = equipo2YaParticipo || partidosEstanCompletos(participacionDeEquipos);
        }
        participacionDeEquipos[segundoEquipoSeleccionado] = true;

        partidosJugados[primerEquipoSeleccionado] += 1;
        partidosJugados[segundoEquipoSeleccionado] += 1;

        // asigna el partido
        jornadas[indexJornada][conteoPartidos][0] = primerEquipoSeleccionado;
        jornadas[indexJornada][conteoPartidos][1] = segundoEquipoSeleccionado;
    }
}
void imprimirEquipo(int equipo, int indiceEquipo, int jornada, int partido) {
    cout << "== " << equipos[indiceEquipo] << endl;
    cout << "== Goles: " << resultados[jornada][partido][equipo] <<endl;
}

void imprimirGanador(int jornada, int partido) {
    int equipo1 = jornadas[jornada][partido][0];
    int equipo2 = jornadas[jornada][partido][1];
    string ganador = "Ganador : " + equipos[equipo2];
    int golesEquipo1 = resultados[jornada][partido][0];
    int golesEquipo2 = resultados[jornada][partido][1];
    if (golesEquipo1 == golesEquipo2) {
        ganador = "Empate";
    }
    if (golesEquipo1 > golesEquipo2) {
        ganador = "Ganador: " + equipos[equipo1];
    }
    cout << "== Resultado " << endl;
    cout << "== " << ganador << endl;
}

void imprimirPartido(int jornada, int partido) {
    int equipo1 = jornadas[jornada][partido][0];
    int equipo2 = jornadas[jornada][partido][1];
    cout << "====================================" << endl;
    cout << "==  JORNADA : " << (jornada + 1) << endl;
    cout << "==  PARTIDO : " << (partido + 1) << endl;
    cout << "==--------------------------------==" << endl;
    cout << "==            EQUIPOS             ==" << endl;
    cout << "==--------------------------------==" << endl;
    imprimirEquipo(0, equipo1, jornada, partido);
    cout << "==--------------------------------==" << endl;
    imprimirEquipo(1, equipo2, jornada, partido);
    cout << "==--------------------------------==" << endl;
    imprimirGanador(jornada, partido);
    cout << "==--------------------------------==" << endl;
    cout << "====================================" << endl << endl;

}

void imprimirJornada(int indiceJornada) {
    for (int indicePartidoDeJornada = 0; indicePartidoDeJornada < 10; indicePartidoDeJornada++) {
        imprimirPartido(indiceJornada, indicePartidoDeJornada);
    }
}

void generarResultados(int indiceJornada) {
    for (int indicePartido = 0; indicePartido < 10; indicePartido ++) {
        int equipo1 = jornadas[indiceJornada][indicePartido][0];
        int equipo2 = jornadas[indiceJornada][indicePartido][1];
        int golesEquipo1 = generarGoles();
        int golesEquipo2 = generarGoles();

        resultados[indiceJornada][indicePartido][0] = golesEquipo1;
        resultados[indiceJornada][indicePartido][1] = golesEquipo2;

        totalGoles[equipo1] += golesEquipo1;
        totalGoles[equipo2] += golesEquipo2;
    }
}

void generarJornadas() {
    for (int indiceJornada = 0; indiceJornada < 38; indiceJornada ++) {
        generarPartidos(indiceJornada);
        generarResultados(indiceJornada);
    }
}

void mostrarMenuPrincipal() {
    cout<<"Para continuar seleccione una opción"<<endl;

    cout<<" ============================================"<<endl;
    cout<<" ==              Menu Principal            =="<<endl;
    cout<<" ==    1. Iniciar Liga                     =="<<endl;
    cout<<" ==    2. Mostrar lista de participantes   =="<<endl;
    cout<<" ==    3. Salir                            =="<<endl;
    cout<<" ============================================"<<endl;
    cout<<" Por favor seleccione la opción a elegir\t:\t";
}

int repetirSeleccion(int opcionDeMenu) {
    while ((opcionDeMenu < 1) || (opcionDeMenu > 3)) {
        limpiarBufferDeEntrada();
        imprimirLineaDeDivision();
        cout << "Error seleccione una opción valida : " << endl;
        cin >> opcionDeMenu;
        imprimirLineaDeDivision();
    }
    return opcionDeMenu;
}

void imprimirClasificacionEquipo (int posicion) {
    int equipo = clasificacion[posicion];
    int puntos = puntuaciones[equipo];
    int goles = totalGoles[equipo];
    int pGanados = partidosGanados[equipo];
    int pEmpatados = partidosEmpatados[equipo];
    imprimirLineaDeDivision();
    cout << "======= " << posicionSufijo(posicion + 1) << " lugar con " << puntos << "pts =======" << endl;
    cout << "== Equipo: " << equipos[equipo] << endl;
    cout << "== Goles: " << goles << endl;
    cout << "== Partidos Ganados: " << pGanados << endl;
    cout << "== Partidos Empatados: " << pEmpatados << endl;
}

void mostrarTablaDePosiciones() {
    for (int posicion = 0; posicion < 20; posicion ++) {
        imprimirClasificacionEquipo(posicion);
    }
    system("pause");
}

void iniciarLiga() {
    generarJornadas();
    inicializarPuntuaciones();
    clasificar();
}

void mostrarMenuResultados() {
    cout << "============================================" << endl;
    cout << "==              Menú de Resultados        ==" << endl;
    cout << "==    1. Resultados por equipo            ==" << endl;
    cout << "==    2. Mostrar jornada                  ==" << endl;
    cout << "==    3. Tabla de Posiciones              ==" << endl;
    cout << "==    4. Salir                            ==" << endl;
    cout << "============================================" << endl;
    cout << "Por favor seleccione la opción a elegir: "<< endl;
}

void imprimirResultadosDeEquipo(int equipo) {
    equipo = equipo -1;
    imprimirLineaDeDivision();
    cout << "Nombre: " << equipos[equipo] << endl;
    cout << "Puntos: " << puntuaciones[equipo] << endl;
    cout << "Partidos Ganados: " << partidosGanados[equipo] << endl;
    cout << "Partidos Empatados: " << partidosEmpatados[equipo] << endl;
}

void imprimirMenuJornada() {
    cout << "============================================" << endl;
    cout << "==    Menú de Resultados de Jornada       ==" << endl;
    cout << "==    1. Resultados por Partido           ==" << endl;
    cout << "==    2. Mostrar jornada Completa         ==" << endl;
    cout << "==    3. Salir                            ==" << endl;
    cout << "============================================" << endl;
    cout << "Por favor seleccione la opción a elegir: " << endl;
}

void menuJornada (int indiceJornada) {
    int opcion = 0;
    imprimirMenuJornada();
    cin >> opcion;
    imprimirLineaDeDivision();
    while (opcion != 3) {
        switch (opcion) {
            case 1:
                seleccionPartido:
                    int partido;
                    cout << "Ingrese el número del partido que desea visualizar: " << endl;
                    cin >> partido;
                    imprimirLineaDeDivision();
                    if (partido < 0 || partido > 38) {
                        goto seleccionPartido;
                    }
                    imprimirPartido(indiceJornada, (partido - 1));
                    system("pause");
                break;
            case 2 :
                imprimirJornada(indiceJornada);
                system("pause");
                break;
            default:
                cout << "Opción no válida, intenta de nuevo" << endl;
                break;
        }
        limpiarBufferDeEntrada();
        imprimirMenuJornada();
        cin >> opcion;
    }
}

void menuResultados() {
    int opcionResultados;
    do {
        mostrarMenuResultados();
        cin >> opcionResultados;

        switch (opcionResultados) {
            case 1:
                int indiceEquipo;
                imprimirNombreEquipos();
                cout << "Ingrese el índice del equipo para ver los resultados: ";
                cin >> indiceEquipo;
                if (indiceEquipo >= 1 && indiceEquipo <= 20) {
                    imprimirResultadosDeEquipo(indiceEquipo);
                    system("pause");
                } else {
                    cout << "Índice de equipo no válido." << endl;
                }
                break;
            case 2:
                int indiceJornada;
                cout << "Ingrese el índice de la jornada para ver los resultados: ";
                cin >> indiceJornada;
                if (indiceJornada >= 1 && indiceJornada <= 38) {
                    cout << "Resultados de la jornada " << indiceJornada << ":" << endl;
                    menuJornada(indiceJornada - 1);
                    system("pause");
                } else {
                    cout << "Índice de jornada no válido." << endl;
                }
                break;
            case 3:
                mostrarTablaDePosiciones();
                break;
            case 4:
                cout << "Volviendo al menú principal." << endl;
                return;
            default:
                cout << "Opción no válida. Por favor, intente de nuevo." << endl;
                break;
        }
        imprimirLineaDeDivision();
    } while (opcionResultados != 4);
}



void ejecutarOpcion(int opcionDeMenu) {
    // reinicializar la generación de números aleatorios
    srand(rand());
    //
    switch(opcionDeMenu) {
        case 1:
            imprimirLineaDeDivision();
            cout<<"Bienvenido"<<endl;
            cout<<"Disfruta de la mejor liga, la liga de Inglaterra"<<endl;
            cout<<"Liga virtual generada exitosamente."<<endl<<endl;
            inicializarMatrices();
            iniciarLiga();
            menuResultados();
            imprimirLineaDeDivision();
            break;
        case 2:
            imprimirLineaDeDivision();
            imprimirNombreEquipos();
            imprimirLineaDeDivision();
            system("pause");
            break;
        case 3:
            cout<<"Gracias por usar este programa"<<endl;
            cout<<"Ten feliz día/noche"<<endl;
            break;
        default:
            cout<<"Opción no válida, intenta de nuevo"<<endl;
            limpiarBufferDeEntrada();
            break;
    }
    imprimirLineaDeDivision();
}

int main() {
    setlocale(LC_CTYPE, "spanish");
    int opcionDeMenu = 1;

    imprimirLineaDeDivision();
    cout<<"Bienvenido a la Premiere League"<<endl;
    cout<<"Autores: Hector Murillo y Emerson Jimenez"<<endl;
    MenuPrincipal:
        mostrarMenuPrincipal();
        cin>>opcionDeMenu;
        opcionDeMenu = repetirSeleccion(opcionDeMenu);
        if (opcionDeMenu != 3) {
            ejecutarOpcion(opcionDeMenu);
            limpiarBufferDeEntrada();
            goto MenuPrincipal;
        }
    system("pause");
    return 0;
}
