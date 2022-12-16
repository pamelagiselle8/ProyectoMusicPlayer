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

GeneroFile* generoFile = new GeneroFile("./Generos.txt");
PlaylistFile* playlistFile = new PlaylistFile("./Playlists.txt");
SongInfoFile* songInfoFile = new SongInfoFile("./SongInfos.txt");
vector<Genero> generos;
vector<SongInfo> canciones;
vector<Playlist> playlists;

template <typename T> void listar(vector<T*> lista) {
    cout << endl;
    if(!lista.empty())
        for (T* obj : lista)
            cout << "- " << obj->toString() << endl;
    else
        cout << "Aun no hay elementos registrados.\n";
}

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
            if (generoFile->agregarGenero(new Genero(nom)))
                cout << "\nGenero agregado exitosamente.\n";
            else
                cout << "\nEl genero ya existe.\n";
            break;
        }
        else if (op == "2") {
            listar(generoFile->getGeneros());
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
            string nom = "", disco = "", artista = "", ruta = "";
            cout << "\nIngrese el nombre de la cancion: ";
            cin >> nom;
            cout << "Ingrese el disco: ";
            cin >> disco;
            cout << "Ingrese el artista: ";
            cin >> artista;
            cout << "Ingrese la ruta de la cancion: ";
            cin >> ruta;
            if (songInfoFile->agregarCancion(new SongInfo(nom, disco, artista, ruta)))
                cout << "\nCancion agregada exitosamente.\n";
            else
                cout << "\nYa existe una cancion la ruta ingresada.\n";
            break;
        }
        else if (op == "2") {
            // Listar canciones
            listar(songInfoFile->getCanciones());
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
            string nom = "";
            cout << "\nIngrese el nombre de la playlist: ";
            cin >> nom;
            if (playlistFile->agregarPlaylist(new Playlist(nom)))
                cout << "\nPlaylist agregada exitosamente.\n";
            else
                cout << "\nYa existe una playlist con ese nombre.\n";
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
            menuCanciones();
        }
        else if (opMenu == "3") {
            // Playlist
            menuPlaylist();
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