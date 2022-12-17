#include <iostream>
#include <vector>
// #include <windows.h>
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

// Metodo para listar elementos de vectores
template <typename T> void listar(vector<T*> lista) {
    cout << endl;
    int cont = 1;
    if(!lista.empty())
        for (T* obj : lista)
            cout << cont++ << "- " << obj->toString() << endl;
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

            // Validar que no haya dos generos con el mismo nombre
            if (generoFile->agregarGenero(new Genero(nom)))
                // Guardar datos en el archivo
                if (generoFile->Escribir()) {
                    generoFile->Cerrar();
                    cout << "\nGenero agregado exitosamente.\n";
                }
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
            // Validar que hayan generos registrados
            if (!generoFile->getGeneros().empty()) {
                string nom = "", album = "", artista = "", genero = "", ruta = "";
                cout << "\nIngrese el nombre de la cancion: ";
                cin >> nom;
                cout << "Ingrese el album: ";
                cin >> album;
                cout << "Ingrese el artista: ";
                cin >> artista;

                cout << "\nGeneros registrados:\n";
                listar(generoFile->getGeneros());
                int indice = 0;
                while (true) {
                    cout << "\nIngrese el indice del genero de la cancion: ";
                    cin >> indice;
                    indice--;
                    // Validar indice del genero de la cancion
                    if (indice >= 0 && indice < generoFile->getGeneros().size()) {
                        genero = generoFile->getGeneros().at(indice)->getNombre();
                        break;
                    }
                    else { cout << "\nIndice invalido.\n"; }
                }
                
                cout << "Ingrese la ruta de la cancion: ";
                cin >> ruta;

                // Validar que no existan dos canciones con la misma ruta
                if (songInfoFile->agregarCancion(new SongInfo(nom, album, artista, genero, ruta))) {
                    // Guardar datos en el archivo
                    songInfoFile->Abrir();
                    if (songInfoFile->Escribir())
                        cout << "\nCancion agregada exitosamente.\n";
                    songInfoFile->Cerrar();
                }
                else
                    cout << "\nYa existe una cancion la ruta ingresada.\n";
                }
            else { cout << "\nAun no hay generos registrados.\n"; }
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

            // Validar que la no exista otra playlist con el mismo nombre
            if (playlistFile->agregarPlaylist(new Playlist(nom))) {
                // Guardar datos en el archivo
                playlistFile->Abrir();
                if (playlistFile->Escribir())
                    cout << "\nPlaylist agregada exitosamente.\n";
                playlistFile->Cerrar();
            }
            else
                cout << "\nYa existe una playlist con ese nombre.\n";
            break;
        }
        else if (op == "2") {
            // Agregar cancion

            // Validar que hayan canciones registradas
            if (!songInfoFile->getCanciones().empty()) {

                // Validar que hayan playlists registradas
                if (!playlistFile->getPlaylists().empty()) {
                    cout << "\nPlaylists registradas:\n";
                    listar(playlistFile->getPlaylists());
                    int indice = 0;
                    while (true) {
                        cout << "\nIngrese el indice de la playlist: ";
                        cin >> indice;
                        indice--;

                        // Validar indice de la playlist
                        if (indice >= 0 && indice < playlistFile->getPlaylists().size()) {
                            int indiceCancion = 0;
                            Playlist* playlist = playlistFile->getPlaylists().at(indice);
                            cout << "\nCanciones disponibles:\n";
                            listar(songInfoFile->getCanciones());
                            int indice = 0;
                            cout << "\nIngrese el indice de la cancion que desea agregar: ";
                            cin >> indice;
                            indice--;

                            // Validar indice de la cancion
                            if (indice >= 0 && indice < songInfoFile->getCanciones().size())
                                // Validar que la cancion no se repita
                                if (playlist->agregarCancion(songInfoFile->getCanciones().at(indice))) {
                                    
                                    // Guardar datos en el archivo
                                    playlistFile->Abrir();
                                    if (playlistFile->Escribir())
                                        cout << "\nCancion agregada exitosamente.\n";
                                    playlistFile->Cerrar();
                                    break;
                                }
                                else { cout << "\nLa cancion ya existe en la playlist.\n"; }
                            else { cout << "\nIndice invalido.\n"; }
                        }
                        else { cout << "\nIndice invalido.\n"; }
                    }
                }
                else { cout << "\nAun no hay playlists registradas.\n"; }
            }
            else { cout << "\nAun no hay canciones registradas.\n"; }
            break;
        }
        else if (op == "3") { break; }
        else { cout << "\nIngrese una opcion valida\n"; }
    }
}

void reproducirCancion() {
    // Validar que hayan canciones registradas
    if (!songInfoFile->getCanciones().empty()) {
        cout << "\nCanciones registradas:\n";
        listar(songInfoFile->getCanciones());
        int indice = 0;
        while (true) {
            cout << "\nIngrese el indice de la cancion: ";
            cin >> indice;
            indice--;
            // Validar indice de la cancion
            if (indice >= 0 && indice < songInfoFile->getCanciones().size()) {
                SongInfo* cancion =  songInfoFile->getCanciones().at(indice);
                
                // Abrir el archivo 
                // mciSendString("open \"" + cancion->getRuta() + "\" type mpegvideo alias mp3", NULL, 0, NULL);

                string op = "";
                while (op != "2") {
                    cout << "\n1. Pausar"
                        << "\n2. Salir"
                        << "\nIngrese una opcion: ";
                    cin >> op;
                    if (op == "1") {
                        // Pausar cancion
                        // mciSendString("pause mp3", NULL, 0, NULL);
                        cout << "\nCancion pausada\n";
                        // break;
                    }
                    else if (op == "2") {
                        // Salir
                        // mciSendString("close mp3", NULL, 0, NULL);
                        break;
                    }
                    else { cout << "\nIngrese una opcion valida\n"; }
                }
                break;
            }
            else { cout << "\nIndice invalido.\n"; }
        }       
    }
    else { cout << "\nAun no hay canciones registradas.\n"; }
    
}

void reproducirPlaylist() {
    // Validar que hayan playlists registradas
    if (!playlistFile->getPlaylists().empty()) {
        cout << "\nPlaylists registradas:\n";
        listar(playlistFile->getPlaylists());
        int indice = 0;
        while (true) {
            cout << "\nIngrese el indice de la playlist: ";
            cin >> indice;
            indice--;
            // Validar indice de la playlist
            if (indice >= 0 && indice < playlistFile->getPlaylists().size()) {
                int indiceCancion = 0;
                Playlist* playlist = playlistFile->getPlaylists().at(indice);
                SongInfo* cancion =  playlist->getCanciones().at(indiceCancion);
                
                // Abrir el archivo 
                // mciSendString("open \"" + cancion->getRuta() + "\" type mpegvideo alias mp3", NULL, 0, NULL);
                
                string op = "";
                while (op != "3") {
                    cout << "\n1. Siguiente"
                        << "\n2. Pausar"
                        << "\n3. Salir"
                        << "\nIngrese una opcion: ";
                    cin >> op;
                    if (op == "1") {
                        // Siguiente cancion
                        if (indiceCancion+1 < playlist->getCanciones().size()) {
                            cancion =  playlist->getCanciones().at(++indiceCancion);
                            // mciSendString("open \"" + cancion->getRuta() + "\" type mpegvideo alias mp3", NULL, 0, NULL);
                            // mciSendString("play mp3", NULL, 0, NULL);
                            cout << "\nReproduciendo...\n";
                        }
                        else {
                            cout << "\nFin de la playlist.\n";
                            // op = "3"; (salir) o indiceCancion = 0; (reiniciar playlist)
                            break;
                        }
                    }
                    else if (op == "2") {
                        // Pausar cancion
                        // mciSendString("pause mp3", NULL, 0, NULL);
                        cout << "\nCancion pausada\n";
                    }
                    else if (op == "3") {
                        // Salir
                        // mciSendString("close mp3", NULL, 0, NULL);
                        break;
                    }
                    else { cout << "\nIngrese una opcion valida\n"; }
                }

                break;
            }
            else { cout << "\nIndice invalido.\n"; }
        }

        
    }
    else { cout << "\nAun no hay playlists registradas.\n"; }
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
    // Leer los datos de los txt
    generoFile->Abrir();
    generoFile->Leer();
    generoFile->Cerrar();
    songInfoFile->Abrir();
    songInfoFile->Leer();
    songInfoFile->Cerrar();
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
            menuReproduccion();
        }
        else if (opMenu == "5") { break; }
        else { cout << "\nIngrese una opcion valida.\n"; }
        opMenu = menuPrincipal();
    }
    
    return 0;
}