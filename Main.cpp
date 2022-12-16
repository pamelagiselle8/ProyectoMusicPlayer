#include <iostream>
#include <vector>
using namespace std;

#include "Object.cpp"
#include "Genero.cpp"
#include "GeneroFile.cpp"
#include "Playlist.cpp"
#include "PlaylistFile.cpp"
#include "SongInfo.cpp"
#include "SongInfoFile.cpp"
#include "TDAArchivo.cpp"

vector<Genero> generos;
vector<SongInfo> canciones;
vector<Playlist> playlists;

void menuGeneros() {
    string op = "";
    while (op != "3") {
        cout << "\n\t--- Generos ---" 
            << "\n1. Crear"
            << "\n2. Listar"
            << "\n3. Salir"
            << "\nIngrese una opcion: ";
        cin >> op;
        if (op == "1") {
            // Crear genero
            string nom = "";
            cout << "\nIngrese el nombre del genero: ";
            cin >> nom;
            generos.push_back(Genero(nom));
            cout << "\nGenero agregado exitosamente.\n";
            break;
        }
        else if (op == "2") {
            // Listar generos
            cout << endl;
            if(!generos.empty())
                for (Genero genero : generos)
                    cout << "- " << genero.toString() << endl;
            else
                cout << "Aun no hay generos registrados.\n";
            break;
        }
        else if (op == "3") { break; }
        else { cout << "\nIngrese una opcion valida\n"; }
    }
}

void menuCanciones() {
    string op = "";
    while (op != "3") {
        cout << "\t\n--- Canciones ---" 
            << "\n1. Crear"
            << "\n2. Listar"
            << "\n3. Salir"
            << "\nIngrese una opcion: ";
        cin >> op;
        if (op == "1") {
            // Crear cancion
            
            break;
        }
        else if (op == "2") {
            // Listar canciones
            
            break;
        }
        else if (op == "3") { break; }
        else { cout << "\nIngrese una opcion valida\n"; }
    }
}

void menuPlaylist() {
    string op = "";
    while (op != "3") {
        cout << "\t\n--- Playlist ---" 
            << "\n1. Crear"
            << "\n2. Agregar cancion"
            << "\n3. Salir"
            << "\nIngrese una opcion: ";
        cin >> op;
        if (op == "1") {
            // Crear playlist
            
            break;
        }
        else if (op == "2") {
            // Agregar cancion
            
            break;
        }
        else if (op == "3") { break; }
        else { cout << "\nIngrese una opcion valida\n"; }
    }
}

void reproducirCancion() {
    string op = "";
    while (op != "2") {
        cout << "\n1. Pausar"
            << "\n2. Salir"
            << "\nIngrese una opcion: ";
        cin >> op;
        if (op == "1") {
            // Pausar cancion
            
            break;
        }
        else if (op == "2") { break; }
        else { cout << "\nIngrese una opcion valida\n"; }
    }
}

void reproducirPlaylist() {
    string op = "";
    while (op != "3") {
        cout << "\n1. Siguiente"
            << "\n2. Pausar"
            << "\n3. Salir"
            << "\nIngrese una opcion: ";
        cin >> op;
        if (op == "1") {
            // Siguiente cancion
            
            break;
        }
        else if (op == "2") {
            // Pausar cancion
            
            break;
        }
        else if (op == "3") { break; }
        else { cout << "\nIngrese una opcion valida\n"; }
    }
}

void menuReproduccion() {
    string op = "";
    while (op != "3") {
        cout << "\n1. Cancion"
            << "\n2. Playlist"
            << "\n3. Salir"
            << "\nIngrese una opcion: ";
        cin >> op;
        if (op == "1") {
            // Reproducir cancion
            reproducirCancion();
            break;
        }
        else if (op == "2") {
            // Reproducir playlist
            reproducirPlaylist();
            break;
        }
        else if (op == "3") { break; }
        else { cout << "\nIngrese una opcion valida\n"; }
    }
}

string menuPrincipal() {
    string opMenu = "";
    cout << "\n\t--- Menu Principal ---" 
        << "\n1. Generos"
        << "\n2. Canciones"
        << "\n3. Playlist"
        << "\n4. Reproducir"
        << "\n5. Salir del programa"
        << "\nIngrese una opcion: ";
    cin >> opMenu;
    return opMenu;
}

int main() {
    string opMenu = menuPrincipal();
    while (opMenu != "5") {
        if (opMenu == "1") {
            // Generos
            menuGeneros();
        }
        else if (opMenu == "2") {
            // Canciones
            
        }
        else if (opMenu == "3") {
            // Playlist
            
        }
        else if (opMenu == "4") {
            // Reproducir
            
        }
        else if (opMenu == "5") { break; }
        else { cout << "\nIngrese una opcion valida.\n"; }
        opMenu = menuPrincipal();
    }
    
    return 0;
}

/*GeneroFile* generoFile = new GeneroFile("./Genero.txt");

    if (generoFile->Abrir())
        generoFile->Leer();
        generoFile->Cerrar();

    generoFile->agregarGenero(new Genero("Clasica"));
    generoFile->agregarGenero(new Genero("Rock"));
    generoFile->agregarGenero(new Genero("Jazz"));
    generoFile->agregarGenero(new Genero("Clasica"));

    cout << "\nImprimir generos\n";
    for (Genero* gen : generoFile->getGeneros())
        cout << gen->getNombre() << endl;

    delete generoFile;*/