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
#include "SongxPlaylistFile.cpp"
#include "TDAArchivo.cpp"

GeneroFile* generoFile = new GeneroFile("./Generos.txt");
PlaylistFile* playlistFile = new PlaylistFile("./Playlists.txt");
SongInfoFile* songInfoFile = new SongInfoFile("./SongInfos.txt");
SongxPlaylistFile* songxPlaylistFile = new SongxPlaylistFile("./SongxPlaylist.txt");

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
                getline(cin, nom);
                cout << "\nIngrese el nombre de la cancion: ";
                getline(cin, nom);
                cout << "Ingrese el album: ";
                getline(cin, album);
                cout << "Ingrese el artista: ";
                getline(cin, artista);

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

                int codigo = songInfoFile->getCanciones().size();
                
                // Validar que no existan dos canciones con la misma ruta
                if (songInfoFile->agregarCancion(new SongInfo(nom, album, artista, genero, ruta, codigo))) {
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
            getline(cin, nom);
            cout << "\nIngrese el nombre de la playlist: ";
            getline(cin, nom);

            int codigo = playlistFile->getPlaylists().size();

            // Validar que la no exista otra playlist con el mismo nombre
            if (playlistFile->agregarPlaylist(new Playlist(nom, codigo))) {
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
                    int indicePlaylist = 0;
                    while (true) {
                        cout << "\nIngrese el indice de la playlist: ";
                        cin >> indicePlaylist;
                        indicePlaylist--;

                        // Validar indice de la playlist
                        if (indicePlaylist >= 0 && indicePlaylist < playlistFile->getPlaylists().size()) {
                            Playlist* playlist = playlistFile->getPlaylists()[indicePlaylist];
                            cout << "\nCanciones disponibles:\n";
                            listar(songInfoFile->getCanciones());
                            
                            int indiceCancion = 0;
                            cout << "\nIngrese el indice de la cancion que desea agregar: ";
                            cin >> indiceCancion;
                            indiceCancion--;

                            // Validar indice de la cancion
                            if (indiceCancion >= 0 && indiceCancion < songInfoFile->getCanciones().size()) {
                                SongInfo* cancion = songInfoFile->getCanciones()[indiceCancion];

                                cout << songInfoFile->getCanciones()[indiceCancion]->getNombre() << endl;
                                cout << songInfoFile->getCanciones()[indiceCancion]->getCodigo();

                                // Validar que la cancion no se repita
                                if (playlist->agregarCancion(cancion)) {
                                    songxPlaylistFile->setCanciones(songInfoFile->getCanciones());
                                    songxPlaylistFile->setPlaylists(playlistFile->getPlaylists());

                                    // Guardar datos en el archivo
                                    songxPlaylistFile->Abrir();
                                    if (songxPlaylistFile->Escribir())
                                        cout << "\nCancion agregada exitosamente.\n";
                                    songxPlaylistFile->Cerrar();
                                    break;
                                }
                                else {
                                    cout << "\nLa cancion ya existe en la playlist.\n";
                                    break;
                                }

                            }
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
                            cout << "\nReproduciendo " << playlist->getCanciones().at(indiceCancion)->getNombre();
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

void cargarDatos(TDAArchivo* archivo) {
    archivo->Abrir();
    archivo->Leer();
    archivo->Cerrar();
}

int main() {
    string opMenu = menuPrincipal();
    // Cargar generos
    cargarDatos(generoFile);
    // Cargar canciones
    cargarDatos(songInfoFile);
    // Cargar playlists
    cargarDatos(playlistFile);
    // Cargar canciones a playlists
    songxPlaylistFile->setPlaylists(playlistFile->getPlaylists());
    songxPlaylistFile->setCanciones(songInfoFile->getCanciones());
    cargarDatos(songxPlaylistFile);
    playlistFile->setPlaylists(songxPlaylistFile->getPlaylists());
    
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