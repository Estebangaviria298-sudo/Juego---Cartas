#include "Juego.h"
#include <iostream>
#include <fstream>

using namespace std;

Juego::Juego()
{
    jugadores[0] = Jugador("Jugador 1");
    jugadores[1] = Jugador("Jugador 2");
    jugadores[2] = Jugador("Jugador 3");
    jugadores[3] = Jugador("Jugador 4");

    numeroRonda = 1;
}

void Juego::iniciar()
{
    int opcion;

    cout << "==========================" << endl;
    cout << "       JUEGO DE CARTAS" << endl;
    cout << "==========================" << endl;

    cout << "\n1. Nueva partida" << endl;
    cout << "2. Cargar partida" << endl;
    cout << "\nSeleccione una opcion: ";
    cin >> opcion;

    if (opcion == 2)
    {
        cargarPartida();
    }
    else
    {
        mazo.crearMazo();
        mazo.barajar();

        // Repartir 4 cartas a cada jugador
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                jugadores[j].recibirCarta(
                    mazo.sacarCarta());
            }
        }
    }

    mostrarEstadoJugadores();

    cout << "\nCartas restantes en el mazo: "
         << mazo.cantidadCartas()
         << endl;

    bool continuar = true;

    while (continuar)
    {
        reponerCartas();

        cout << "\n==========================" << endl;
        cout << "         RONDA "
             << numeroRonda
             << endl;
        cout << "==========================" << endl;

        solicitarCondicion();

        jugarRonda();

        char respuestaGuardar;

        cout << "\nDesea guardar la partida? (s/n): ";
        cin >> respuestaGuardar;

        if (respuestaGuardar == 's' ||
            respuestaGuardar == 'S')
        {
            guardarPartida();
        }

        char respuesta;

        cout << "\nDesea jugar otra ronda? (s/n): ";
        cin >> respuesta;

        if (respuesta == 's' ||
            respuesta == 'S')
        {
            numeroRonda++;
        }
        else
        {
            continuar = false;
        }
    }

    cout << "\n==========================" << endl;
    cout << "       FIN DEL JUEGO" << endl;
    cout << "==========================" << endl;

    cout << "\nPuntajes finales:" << endl;

    for (int i = 0; i < 4; i++)
    {
        cout << jugadores[i].getNombre()
             << ": "
             << jugadores[i].getPuntos()
             << " puntos"
             << endl;
    }
}

void Juego::solicitarCondicion()
{
    bool condicionValida = false;

    while (!condicionValida)
    {
        cout << "\nIngrese el color solicitado (rojo/azul): ";
        cin >> colorSolicitado;

        cout << "Ingrese la definicion (bajo/alto): ";
        cin >> definicion;

        if ((colorSolicitado == "rojo" ||
             colorSolicitado == "azul") &&
            (definicion == "bajo" ||
             definicion == "alto"))
        {
            condicionValida = true;
        }
        else
        {
            cout << "\nCondicion no valida." << endl;

            cout << "Use solamente:" << endl;
            cout << "rojo bajo" << endl;
            cout << "rojo alto" << endl;
            cout << "azul bajo" << endl;
            cout << "azul alto" << endl;
        }
    }

    cout << "\nCondicion seleccionada: "
         << colorSolicitado
         << " "
         << definicion
         << endl;
}

void Juego::jugarRonda()
{
    cartasJugadas.clear();
    jugadoresQueJugaron.clear();

    cout << "\n--- CARTAS JUGADAS ---" << endl;

    for (int i = 0; i < 4; i++)
    {
        bool encontroCarta = false;

        for (int j = 0;
             j < jugadores[i].cantidadCartas();
             j++)
        {
            Carta carta =
                jugadores[i].obtenerCarta(j);

            if (carta.getColor() == colorSolicitado)
            {
                Carta cartaJugadas =
                    jugadores[i].jugarCarta(j);

                cartasJugadas.push_back(
                    cartaJugadas);

                jugadoresQueJugaron.push_back(i);

                cout << jugadores[i].getNombre()
                     << " juega: "
                     << cartaJugadas.getNumero()
                     << " - "
                     << cartaJugadas.getColor()
                     << endl;

                encontroCarta = true;

                break;
            }
        }

        if (!encontroCarta)
        {
            cout << jugadores[i].getNombre()
                 << " no tiene una carta "
                 << colorSolicitado
                 << endl;
        }
    }

    determinarGanador();

    mostrarEstadoJugadores();

    cout << "\nCartas restantes en el mazo: "
         << mazo.cantidadCartas()
         << endl;

    mostrarResumenRonda();

    mostrarTablaPuntajes();
}

void Juego::determinarGanador()
{
    if (cartasJugadas.size() == 0)
    {
        cout << "\nNo se jugaron cartas." << endl;
        return;
    }

    int posicionGanadora = 0;

    for (int i = 1;
         i < cartasJugadas.size();
         i++)
    {
        if (definicion == "bajo" &&
            cartasJugadas[i].getNumero() <
            cartasJugadas[posicionGanadora].getNumero())
        {
            posicionGanadora = i;
        }

        if (definicion == "alto" &&
            cartasJugadas[i].getNumero() >
            cartasJugadas[posicionGanadora].getNumero())
        {
            posicionGanadora = i;
        }
    }

    int jugadorGanador =
        jugadoresQueJugaron[posicionGanadora];

    int puntosRonda = 0;

    for (int i = 0;
         i < cartasJugadas.size();
         i++)
    {
        puntosRonda +=
            cartasJugadas[i].getNumero();
    }

    jugadores[jugadorGanador]
        .sumarPuntos(puntosRonda);

    for (int i = 0;
         i < cartasJugadas.size();
         i++)
    {
        jugadores[jugadorGanador]
            .recibirCartaGanada(
                cartasJugadas[i]);
    }

    cout << "\n--- GANADOR ---" << endl;

    cout << "Ganador: "
         << jugadores[jugadorGanador].getNombre()
         << endl;

    cout << "Carta ganadora: "
         << cartasJugadas[posicionGanadora].getNumero()
         << " - "
         << cartasJugadas[posicionGanadora].getColor()
         << endl;

    cout << "Puntos de la ronda: "
         << puntosRonda
         << endl;

    cout << "Puntos acumulados de "
         << jugadores[jugadorGanador].getNombre()
         << ": "
         << jugadores[jugadorGanador].getPuntos()
         << endl;

    cout << "\n--- CARTAS GANADAS ---" << endl;

    for (int i = 0; i < 4; i++)
    {
        if (jugadores[i].getPuntos() > 0)
        {
            jugadores[i].mostrarCartasGanadas();
            cout << endl;
        }
    }
}

void Juego::mostrarEstadoJugadores()
{
    cout << "\n--- ESTADO DE LOS JUGADORES ---"
         << endl;

    for (int i = 0; i < 4; i++)
    {
        cout << "\nJugador: "
             << jugadores[i].getNombre()
             << endl;

        cout << "Cartas en mano: "
             << jugadores[i].cantidadCartas()
             << endl;

        jugadores[i].mostrarMano();

        cout << "Puntos: "
             << jugadores[i].getPuntos()
             << endl;
    }
}

void Juego::reponerCartas()
{
    cout << "\n--- REPOSICION DE CARTAS ---" << endl;

    for (int i = 0; i < 4; i++)
    {
        while (jugadores[i].cantidadCartas() < 4 &&
               mazo.cantidadCartas() > 0)
        {
            Carta carta =
                mazo.sacarCarta();

            jugadores[i].recibirCarta(carta);

            cout << jugadores[i].getNombre()
                 << " recibe: "
                 << carta.getNumero()
                 << " - "
                 << carta.getColor()
                 << endl;
        }
    }
}

void Juego::mostrarResumenRonda()
{
    cout << "\n==========================" << endl;
    cout << "     RESUMEN DE RONDA" << endl;
    cout << "==========================" << endl;

    cout << "Ronda: "
         << numeroRonda
         << endl;

    cout << "Condicion: "
         << colorSolicitado
         << " "
         << definicion
         << endl;

    if (cartasJugadas.size() > 0)
    {
        int posicionGanadora = 0;

        for (int i = 1;
             i < cartasJugadas.size();
             i++)
        {
            if (definicion == "bajo" &&
                cartasJugadas[i].getNumero() <
                cartasJugadas[posicionGanadora].getNumero())
            {
                posicionGanadora = i;
            }

            if (definicion == "alto" &&
                cartasJugadas[i].getNumero() >
                cartasJugadas[posicionGanadora].getNumero())
            {
                posicionGanadora = i;
            }
        }

        int jugadorGanador =
            jugadoresQueJugaron[posicionGanadora];

        cout << "Ganador: "
             << jugadores[jugadorGanador].getNombre()
             << endl;

        cout << "Carta ganadora: "
             << cartasJugadas[posicionGanadora].getNumero()
             << " - "
             << cartasJugadas[posicionGanadora].getColor()
             << endl;
    }
    else
    {
        cout << "No hubo cartas jugadas."
             << endl;
    }

    cout << "Cartas restantes en el mazo: "
         << mazo.cantidadCartas()
         << endl;
}

void Juego::mostrarTablaPuntajes()
{
    cout << "\n==========================" << endl;
    cout << "      TABLA DE PUNTAJES" << endl;
    cout << "==========================" << endl;

    for (int i = 0; i < 4; i++)
    {
        cout << jugadores[i].getNombre()
             << ": "
             << jugadores[i].getPuntos()
             << " puntos"
             << endl;
    }
}

void Juego::guardarPartida()
{
    ofstream archivo("partida.dat", ios::binary);

    if (!archivo)
    {
        cout << "\nNo se pudo guardar la partida." << endl;
        return;
    }

    archivo.write((char*)&numeroRonda,
                  sizeof(numeroRonda));

    int longitudColor = colorSolicitado.size();

    archivo.write((char*)&longitudColor,
                  sizeof(longitudColor));

    archivo.write(colorSolicitado.c_str(),
                  longitudColor);

    int longitudDefinicion =
        definicion.size();

    archivo.write((char*)&longitudDefinicion,
                  sizeof(longitudDefinicion));

    archivo.write(definicion.c_str(),
                  longitudDefinicion);

    vector<Carta> cartasMazo =
        mazo.getCartas();

    int cantidadMazo =
        cartasMazo.size();

    archivo.write((char*)&cantidadMazo,
                  sizeof(cantidadMazo));

    for (Carta carta : cartasMazo)
    {
        int numero =
            carta.getNumero();

        int longitudColorCarta =
            carta.getColor().size();

        archivo.write((char*)&numero,
                     sizeof(numero));

        archivo.write((char*)&longitudColorCarta,
                     sizeof(longitudColorCarta));

        archivo.write(carta.getColor().c_str(),
                     longitudColorCarta);
    }

    for (int i = 0; i < 4; i++)
    {
        string nombre =
            jugadores[i].getNombre();

        int longitudNombre =
            nombre.size();

        archivo.write((char*)&longitudNombre,
                     sizeof(longitudNombre));

        archivo.write(nombre.c_str(),
                     longitudNombre);

        int puntos =
            jugadores[i].getPuntos();

        archivo.write((char*)&puntos,
                     sizeof(puntos));

        vector<Carta> mano =
            jugadores[i].getMano();

        int cantidadMano =
            mano.size();

        archivo.write((char*)&cantidadMano,
                     sizeof(cantidadMano));

        for (Carta carta : mano)
        {
            int numero =
                carta.getNumero();

            int longitudColorCarta =
                carta.getColor().size();

            archivo.write((char*)&numero,
                         sizeof(numero));

            archivo.write((char*)&longitudColorCarta,
                         sizeof(longitudColorCarta));

            archivo.write(carta.getColor().c_str(),
                         longitudColorCarta);
        }

        vector<Carta> cartasGanadas =
            jugadores[i].getCartasGanadas();

        int cantidadGanadas =
            cartasGanadas.size();

        archivo.write((char*)&cantidadGanadas,
                     sizeof(cantidadGanadas));

        for (Carta carta : cartasGanadas)
        {
            int numero =
                carta.getNumero();

            int longitudColorCarta =
                carta.getColor().size();

            archivo.write((char*)&numero,
                         sizeof(numero));

            archivo.write((char*)&longitudColorCarta,
                         sizeof(longitudColorCarta));

            archivo.write(carta.getColor().c_str(),
                         longitudColorCarta);
        }
    }

    archivo.close();

    cout << "\nPartida guardada correctamente."
         << endl;
}

void Juego::cargarPartida()
{
    ifstream archivo("partida.dat", ios::binary);

    if (!archivo)
    {
        cout << "\nNo se encontro una partida guardada."
             << endl;

        return;
    }

    archivo.read((char*)&numeroRonda,
                 sizeof(numeroRonda));

    int longitudColor;

    archivo.read((char*)&longitudColor,
                 sizeof(longitudColor));

    colorSolicitado.resize(longitudColor);

    archivo.read(&colorSolicitado[0],
                 longitudColor);

    int longitudDefinicion;

    archivo.read((char*)&longitudDefinicion,
                 sizeof(longitudDefinicion));

    definicion.resize(longitudDefinicion);

    archivo.read(&definicion[0],
                 longitudDefinicion);

    vector<Carta> cartasMazo;

    int cantidadMazo;

    archivo.read((char*)&cantidadMazo,
                 sizeof(cantidadMazo));

    for (int i = 0;
         i < cantidadMazo;
         i++)
    {
        int numero;
        int longitudColorCarta;

        archivo.read((char*)&numero,
                     sizeof(numero));

        archivo.read((char*)&longitudColorCarta,
                     sizeof(longitudColorCarta));

        string color;

        color.resize(longitudColorCarta);

        archivo.read(&color[0],
                     longitudColorCarta);

        cartasMazo.push_back(
            Carta(numero, color));
    }

    mazo.cargarCartas(cartasMazo);

    for (int i = 0; i < 4; i++)
    {
        string nombre;

        int longitudNombre;

        archivo.read((char*)&longitudNombre,
                     sizeof(longitudNombre));

        nombre.resize(longitudNombre);

        archivo.read(&nombre[0],
                     longitudNombre);

        int puntos;

        archivo.read((char*)&puntos,
                     sizeof(puntos));

        vector<Carta> mano;

        int cantidadMano;

        archivo.read((char*)&cantidadMano,
                     sizeof(cantidadMano));

        for (int j = 0;
             j < cantidadMano;
             j++)
        {
            int numero;
            int longitudColorCarta;

            archivo.read((char*)&numero,
                         sizeof(numero));

            archivo.read((char*)&longitudColorCarta,
                         sizeof(longitudColorCarta));

            string color;

            color.resize(longitudColorCarta);

            archivo.read(&color[0],
                         longitudColorCarta);

            mano.push_back(
                Carta(numero, color));
        }

        vector<Carta> cartasGanadas;

        int cantidadGanadas;

        archivo.read((char*)&cantidadGanadas,
                     sizeof(cantidadGanadas));

        for (int j = 0;
             j < cantidadGanadas;
             j++)
        {
            int numero;
            int longitudColorCarta;

            archivo.read((char*)&numero,
                         sizeof(numero));

            archivo.read((char*)&longitudColorCarta,
                         sizeof(longitudColorCarta));

            string color;

            color.resize(longitudColorCarta);

            archivo.read(&color[0],
                         longitudColorCarta);

            cartasGanadas.push_back(
                Carta(numero, color));
        }

        jugadores[i].cargarDatos(
            nombre,
            puntos,
            mano,
            cartasGanadas);
    }

    archivo.close();

    cout << "\nPartida cargada correctamente."
         << endl;
}