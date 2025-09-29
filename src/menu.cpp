#include "menu.hpp"
#include <limits>
#include <iostream>

Menu::Menu() {}

int Menu::leerEntero(const std::string& mensaje) const {
    int valor;
    std::cout << mensaje;
    while (!(std::cin >> valor)) {
        std::cout << "Entrada invalida. " << mensaje;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return valor;
}

std::string Menu::leerCadena(const std::string& mensaje) const {
    std::string valor;
    std::cout << mensaje;
    std::getline(std::cin, valor);
    return valor;
}

void Menu::pausar() const {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.get();
}

void Menu::mostrarLista() const {
    // Para limpiar la pantalla de forma portable
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif

    std::cout << "\n=== RADIODIFUSORA - CATALOGO DE CANCIONES ===\n";
    if (canciones.vacia()) {
        std::cout << "El catalogo esta vacio.\n";
    } else {
        std::cout << "Total de canciones: " << (canciones.ultimo() + 1) << "\n";
        std::cout << "Estado ordenamiento por nombre: " << (canciones.isSort(compararPorNombre) ? "ORDENADO" : "NO ORDENADO") << "\n";
        std::cout << "Estado ordenamiento por interprete: " << (canciones.isSort(compararPorInterprete) ? "ORDENADO" : "NO ORDENADO") << "\n\n";
        std::cout << canciones.toString();
    }
    std::cout << "============================================\n";
}

void Menu::agregarCancion() {
    if (canciones.llena()) {
        std::cout << "El catalogo esta lleno.\n";
        return;
    }
    std::string nombre = leerCadena("Nombre de la cancion: ");
    std::string autor = leerCadena("Autor: ");
    std::string interprete = leerCadena("Interprete: ");
    int ranking = leerEntero("Posicion en ranking: ");
    std::string archivo = leerCadena("Nombre del archivo MP3: ");

    Cancion nueva(nombre, autor, interprete, ranking, archivo);
    canciones.inserta(canciones.ultimo() + 1, nueva);
    std::cout << "Cancion agregada exitosamente.\n";
}

void Menu::insertarCancionEn() {
    if (canciones.llena()) {
        std::cout << "El catalogo esta lleno.\n";
        return;
    }
    mostrarLista();
    int posicion = leerEntero("Posicion donde insertar (1-" + std::to_string(canciones.ultimo() + 2) + "): ");
    posicion--; 

    if (posicion < 0 || posicion > canciones.ultimo() + 1) {
        std::cout << "Posicion invalida.\n";
        return;
    }
    
    std::string nombre = leerCadena("Nombre de la cancion: ");
    std::string autor = leerCadena("Autor: ");
    std::string interprete = leerCadena("Interprete: ");
    int ranking = leerEntero("Posicion en ranking: ");
    std::string archivo = leerCadena("Nombre del archivo MP3: ");
    
    Cancion nueva(nombre, autor, interprete, ranking, archivo);
    canciones.inserta(posicion, nueva);
    std::cout << "Cancion insertada exitosamente.\n";
}

void Menu::eliminarCancion() {
    if (canciones.vacia()) {
        std::cout << "El catalogo esta vacio.\n";
        return;
    }
    mostrarLista();
    int posicion = leerEntero("Posicion a eliminar (1-" + std::to_string(canciones.ultimo() + 1) + "): ");
    posicion--; 

    if (posicion < 0 || posicion > canciones.ultimo()) {
        std::cout << "Posicion invalida.\n";
        return;
    }
    canciones.elimina(posicion);
    std::cout << "Cancion eliminada exitosamente.\n";
}

void Menu::limpiarLista() {
    canciones.anula();
    std::cout << "El catalogo ha sido limpiado.\n";
}

void Menu::guardarLista() {
    if(canciones.vacia()){
        std::cout << "El catalogo esta vacio, no hay nada que guardar.\n";
        return;
    }
    std::string nombreArchivo = leerCadena("Ingrese el nombre del archivo para guardar (ej. catalogo.txt): ");
    try {
        canciones.guardarEnArchivo(nombreArchivo);
        std::cout << "Catalogo guardado exitosamente en '" << nombreArchivo << "'\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void Menu::cargarLista() {
    std::string nombreArchivo = leerCadena("Ingrese el nombre del archivo para cargar (ej. catalogo.txt): ");
    try {
        canciones.cargarDesdeArchivo(nombreArchivo);
        std::cout << "Catalogo cargado exitosamente desde '" << nombreArchivo << "'\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void Menu::cargarDatosEjemplo() {
    if(!canciones.vacia()) {
        std::cout << "¿Desea limpiar el catalogo actual antes de cargar los datos de ejemplo?\n";
        std::cout << "1. Si, limpiar y cargar\n2. No, agregar a los existentes\n3. Cancelar\n";
        int opcion = leerEntero("Seleccione: ");
        if(opcion == 1) {
            canciones.anula();
        } else if(opcion == 3) {
            std::cout << "Operacion cancelada.\n";
            return;
        }
    }
    
    if(canciones.llena()) {
        std::cout << "El catalogo esta lleno, no se pueden cargar datos de ejemplo.\n";
        return;
    }
    
    canciones.inserta(-1, Cancion("Amor Eterno", "Juan Gabriel", "Juan Gabriel", 1, "amor_eterno_juanga.mp3"));
    canciones.inserta(-1, Cancion("La Llorona", "Tradicional", "Chavela Vargas", 2, "la_llorona_chavela.mp3"));
    canciones.inserta(-1, Cancion("Besame Mucho", "Consuelo Velazquez", "Andrea Bocelli", 3, "besame_mucho_bocelli.mp3"));
    canciones.inserta(-1, Cancion("Cielito Lindo", "Quirino Mendoza", "Pedro Infante", 4, "cielito_lindo_pedro.mp3"));
    canciones.inserta(-1, Cancion("La Bikina", "Ruben Fuentes", "Vicente Fernandez", 5, "la_bikina_vicente.mp3"));
    canciones.inserta(-1, Cancion("El Rey", "Jose Alfredo Jimenez", "Vicente Fernandez", 6, "el_rey_vicente.mp3"));
    canciones.inserta(-1, Cancion("Volver Volver", "Fernando Z. Maldonado", "Vicente Fernandez", 7, "volver_volver_vicente.mp3"));
    canciones.inserta(-1, Cancion("Paloma Negra", "Tomas Mendez", "Lola Beltran", 8, "paloma_negra_lola.mp3"));
    canciones.inserta(-1, Cancion("Cucurrucucu Paloma", "Tomas Mendez", "Caetano Veloso", 9, "cucurrucucu_caetano.mp3"));
    canciones.inserta(-1, Cancion("La Malagueña", "Elpidio Ramirez", "Miguel Aceves Mejia", 10, "la_malaguena_miguel.mp3"));
    canciones.inserta(-1, Cancion("Granada", "Agustin Lara", "Placido Domingo", 11, "granada_placido.mp3"));
    canciones.inserta(-1, Cancion("Maria Bonita", "Agustin Lara", "Pedro Vargas", 12, "maria_bonita_pedro.mp3"));
    canciones.inserta(-1, Cancion("Solamente Una Vez", "Agustin Lara", "Luis Miguel", 13, "solamente_una_vez_luis.mp3"));
    canciones.inserta(-1, Cancion("Veracruz", "Agustin Lara", "Toña la Negra", 14, "veracruz_tona.mp3"));
    canciones.inserta(-1, Cancion("Noche de Ronda", "Agustin Lara", "Nat King Cole", 15, "noche_ronda_nat.mp3"));
    canciones.inserta(-1, Cancion("Contigo Aprendi", "Armando Manzanero", "Christina Aguilera", 16, "contigo_aprendi_christina.mp3"));
    canciones.inserta(-1, Cancion("Esta Tarde Vi Llover", "Armando Manzanero", "Eydie Gorme", 17, "esta_tarde_eydie.mp3"));
    canciones.inserta(-1, Cancion("Somos Novios", "Armando Manzanero", "Luis Miguel", 18, "somos_novios_luis.mp3"));
    canciones.inserta(-1, Cancion("Por Debajo de la Mesa", "Armando Manzanero", "Luis Miguel", 19, "por_debajo_mesa_luis.mp3"));
    canciones.inserta(-1, Cancion("La Puerta", "Luis Demetrio", "Luis Miguel", 20, "la_puerta_luis_miguel.mp3"));
    canciones.inserta(-1, Cancion("Quizas Quizas Quizas", "Osvaldo Farres", "Nat King Cole", 21, "quizas_quizas_nat.mp3"));
    canciones.inserta(-1, Cancion("Aquellos Ojos Verdes", "Nilo Menendez", "Nat King Cole", 22, "aquellos_ojos_nat.mp3"));
    canciones.inserta(-1, Cancion("Te Quiero Dijiste", "Maria Teresa Lara", "Nat King Cole", 23, "te_quiero_dijiste_nat.mp3"));
    canciones.inserta(-1, Cancion("Sabor a Mi", "Alvaro Carrillo", "Los Panchos", 24, "sabor_a_mi_panchos.mp3"));
    canciones.inserta(-1, Cancion("Rayito de Luna", "Jose Antonio Mendez", "Los Panchos", 25, "rayito_luna_panchos.mp3"));
    canciones.inserta(-1, Cancion("Sin Ti", "Pepe Guizar", "Los Panchos", 26, "sin_ti_panchos.mp3"));
    canciones.inserta(-1, Cancion("Historia de un Amor", "Carlos Eleta Almaran", "Los Panchos", 27, "historia_amor_panchos.mp3"));
    canciones.inserta(-1, Cancion("La Flor de la Canela", "Chabuca Granda", "Susana Baca", 28, "la_flor_canela_susana.mp3"));
    canciones.inserta(-1, Cancion("Alfonsina y el Mar", "Ariel Ramirez", "Mercedes Sosa", 29, "alfonsina_mercedes.mp3"));
    canciones.inserta(-1, Cancion("Como Han Pasado los Años", "Armando Dominguez", "Rocio Durcal", 30, "como_han_pasado_rocio.mp3"));
    canciones.inserta(-1, Cancion("Corazon Espinado", "Fher Olvera", "Santana ft. Mana", 31, "corazon_espinado_santana.mp3"));
    canciones.inserta(-1, Cancion("Bidi Bidi Bom Bom", "Selena Quintanilla", "Selena", 32, "bidi_bidi_selena.mp3"));
    canciones.inserta(-1, Cancion("Como la Flor", "A.B. Quintanilla", "Selena", 33, "como_la_flor_selena.mp3"));
    canciones.inserta(-1, Cancion("Despacito", "Luis Fonsi", "Luis Fonsi ft. Daddy Yankee", 34, "despacito_fonsi.mp3"));
    canciones.inserta(-1, Cancion("Bamboleo", "Tonino Baliardo", "Gipsy Kings", 35, "bamboleo_gipsy.mp3"));
    
    std::cout << "Se han cargado canciones de ejemplo al catalogo.\n";
    std::cout << "NOTA: Los datos estan SIN ORDENAR - ideal para probar algoritmos de ordenamiento.\n";
}

void Menu::mostrarMenuBusqueda() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif

    std::cout << "\n=== MENU DE BUSQUEDA ===\n";
    std::cout << "1. Buscar por nombre de cancion\n";
    std::cout << "2. Buscar por interprete\n";
    std::cout << "3. Volver al menu principal\n";
    std::cout << "========================\n";
}

void Menu::buscarPorNombre() {
    if(canciones.vacia()) {
        std::cout << "El catalogo esta vacio.\n";
        return;
    }
    
    std::string nombre = leerCadena("Ingrese el nombre de la cancion a buscar: ");
    Cancion cancionBusqueda;
    cancionBusqueda.setNombre(nombre);
    
    std::cout << "\n=== METODOS DE BUSQUEDA ===\n";
    std::cout << "1. Busqueda lineal\n";
    std::cout << "2. Busqueda binaria";
    
    bool ordenada = canciones.isSort(compararPorNombre);
    if(!ordenada) {
        std::cout << " (ADVERTENCIA: Lista NO ordenada por nombre)";
    } else {
        std::cout << " (Lista ordenada por nombre - OK)";
    }
    std::cout << "\n============================\n";
    
    int opcion = leerEntero("Seleccione el metodo: ");
    
    int posicion = -1;
    std::string metodo = "";
    
    if(opcion == 1) {
        posicion = canciones.busquedaLineal(cancionBusqueda, compararPorNombre);
        metodo = "Busqueda Lineal";
    } else if(opcion == 2) {
        if(!ordenada) {
            std::cout << "\nADVERTENCIA: La busqueda binaria requiere que la lista este ordenada por nombre.\n";
            std::cout << "La lista actualmente NO esta ordenada por nombre.\n";
            std::cout << "¿Desea continuar de todas formas? (puede dar resultados incorrectos)\n";
            std::cout << "1. Si, continuar\n2. No, regresar\n";
            int continuar = leerEntero("Seleccione: ");
            if(continuar != 1) {
                std::cout << "Operacion cancelada.\n";
                return;
            }
        }
        posicion = canciones.busquedaBinaria(cancionBusqueda, compararPorNombre);
        metodo = "Busqueda Binaria";
    } else {
        std::cout << "Opcion invalida.\n";
        return;
    }
    
    std::cout << "\n=== RESULTADO DE " << metodo << " ===\n";
    if(posicion != -1) {
        try {
            Cancion encontrada = canciones.recupera(posicion);
            std::cout << "¡Cancion encontrada en la posicion " << (posicion + 1) << "!\n";
            std::cout << encontrada.toString() << "\n";
            std::cout << "\nArchivo MP3: " << encontrada.getArchivoMP3() << "\n";
        } catch(const std::exception& e) {
            std::cout << "Error al recuperar la cancion: " << e.what() << "\n";
        }
    } else {
        std::cout << "Cancion no encontrada en el catalogo.\n";
        if(opcion == 2 && !ordenada) {
            std::cout << "NOTA: La lista no esta ordenada. Use ordenamiento antes de busqueda binaria.\n";
        }
    }
}

void Menu::buscarPorInterprete() {
    if(canciones.vacia()) {
        std::cout << "El catalogo esta vacio.\n";
        return;
    }
    
    std::string interprete = leerCadena("Ingrese el nombre del interprete a buscar: ");
    Cancion cancionBusqueda;
    cancionBusqueda.setInterprete(interprete);
    
    std::cout << "\n=== METODOS DE BUSQUEDA ===\n";
    std::cout << "1. Busqueda lineal\n";
    std::cout << "2. Busqueda binaria";
    
    bool ordenada = canciones.isSort(compararPorInterprete);
    if(!ordenada) {
        std::cout << " (ADVERTENCIA: Lista NO ordenada por interprete)";
    } else {
        std::cout << " (Lista ordenada por interprete - OK)";
    }
    std::cout << "\n============================\n";
    
    int opcion = leerEntero("Seleccione el metodo: ");
    
    int posicion = -1;
    std::string metodo = "";
    
    if(opcion == 1) {
        posicion = canciones.busquedaLineal(cancionBusqueda, compararPorInterprete);
        metodo = "Busqueda Lineal";
    } else if(opcion == 2) {
        if(!ordenada) {
            std::cout << "\nADVERTENCIA: La busqueda binaria requiere que la lista este ordenada por interprete.\n";
            std::cout << "La lista actualmente NO esta ordenada por interprete.\n";
            std::cout << "¿Desea continuar de todas formas? (puede dar resultados incorrectos)\n";
            std::cout << "1. Si, continuar\n2. No, regresar\n";
            int continuar = leerEntero("Seleccione: ");
            if(continuar != 1) {
                std::cout << "Operacion cancelada.\n";
                return;
            }
        }
        posicion = canciones.busquedaBinaria(cancionBusqueda, compararPorInterprete);
        metodo = "Busqueda Binaria";
    } else {
        std::cout << "Opcion invalida.\n";
        return;
    }
    
    std::cout << "\n=== RESULTADO DE " << metodo << " ===\n";
    if(posicion != -1) {
        try {
            Cancion encontrada = canciones.recupera(posicion);
            std::cout << "¡Cancion encontrada en la posicion " << (posicion + 1) << "!\n";
            std::cout << encontrada.toString() << "\n";
            std::cout << "\nArchivo MP3: " << encontrada.getArchivoMP3() << "\n";
        } catch(const std::exception& e) {
            std::cout << "Error al recuperar la cancion: " << e.what() << "\n";
        }
    } else {
        std::cout << "No se encontraron canciones de este interprete.\n";
        if(opcion == 2 && !ordenada) {
            std::cout << "NOTA: La lista no esta ordenada. Use ordenamiento antes de busqueda binaria.\n";
        }
    }
}

void Menu::buscarCancion() {
    int opcion;
    do {
        mostrarMenuBusqueda();
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1:
                buscarPorNombre();
                break;
            case 2:
                buscarPorInterprete();
                break;
            case 3:
                std::cout << "Regresando al menu principal...\n";
                break;
            default:
                std::cout << "Opcion invalida.\n";
                break;
        }

        if (opcion != 3) {
            pausar();
        }

    } while (opcion != 3);
}

void Menu::mostrarMenuOrdenamiento() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif

    std::cout << "\n=== MENU DE ORDENAMIENTO ===\n";
    std::cout << "1. Ordenar por nombre de cancion\n";
    std::cout << "2. Ordenar por interprete\n";
    std::cout << "3. Ordenar por autor\n";
    std::cout << "4. Ordenar por ranking\n";
    std::cout << "5. Volver al menu principal\n";
    std::cout << "============================\n";
}

void Menu::mostrarMenuAlgoritmo() {
    std::cout << "\n=== ALGORITMOS DE ORDENAMIENTO ===\n";
    std::cout << "1. Burbuja (Bubble Sort)\n";
    std::cout << "2. Seleccion (Selection Sort)\n";
    std::cout << "3. Insercion (Insertion Sort)\n";
    std::cout << "4. Shell Sort\n";
    std::cout << "===================================\n";
}

void Menu::ordenarCatalogo() {
    if(canciones.vacia()) {
        std::cout << "El catalogo esta vacio.\n";
        return;
    }
    
    int opcionCriterio;
    int opcionAlgoritmo;
    
    do {
        mostrarMenuOrdenamiento();
        opcionCriterio = leerEntero("Seleccione el criterio de ordenamiento: ");
        
        if (opcionCriterio >= 1 && opcionCriterio <= 4) {
            mostrarMenuAlgoritmo();
            opcionAlgoritmo = leerEntero("Seleccione el algoritmo: ");
            
            std::cout << "\nOrdenando catalogo...\n";
            
            // Puntero a la función de comparación
            int (*comparador)(const Cancion&, const Cancion&) = nullptr;

            switch(opcionCriterio) {
                case 1: comparador = compararPorNombre; break;
                case 2: comparador = compararPorInterprete; break;
                case 3: comparador = compararPorAutor; break;
                case 4: comparador = compararPorRanking; break;
            }

            switch(opcionAlgoritmo) {
                case 1: canciones.sortBubble(comparador); break;
                case 2: canciones.sortSelect(comparador); break;
                case 3: canciones.sortInsert(comparador); break;
                case 4: canciones.sortShell(comparador); break;
                default: 
                    std::cout << "Algoritmo invalido.\n"; 
                    pausar();
                    continue; // Vuelve al inicio del do-while
            }
            
            std::cout << "Catalogo ordenado exitosamente!\n";
            mostrarLista();

        } else if (opcionCriterio == 5) {
            std::cout << "Regresando al menu principal...\n";
        } else {
            std::cout << "Opcion invalida.\n";
        }
        
        if(opcionCriterio != 5) {
            pausar();
        }
        
    } while(opcionCriterio != 5);
}


void Menu::ejecutar() {
    int opcion;
    do {
        mostrarLista();
        std::cout << "\n1. Agregar cancion al final\n";
        std::cout << "2. Insertar cancion en posicion\n";
        std::cout << "3. Eliminar cancion\n";
        std::cout << "4. Buscar cancion\n";
        std::cout << "5. Ordenar catalogo\n";
        std::cout << "6. Cargar datos de ejemplo\n";
        std::cout << "7. Limpiar catalogo\n";
        std::cout << "8. Guardar catalogo en archivo\n";
        std::cout << "9. Cargar catalogo desde archivo\n";
        std::cout << "10. Salir\n";
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: agregarCancion(); break;
            case 2: insertarCancionEn(); break;
            case 3: eliminarCancion(); break;
            case 4: buscarCancion(); break;
            case 5: ordenarCatalogo(); break;
            case 6: cargarDatosEjemplo(); break;
            case 7: limpiarLista(); break;
            case 8: guardarLista(); break;
            case 9: cargarLista(); break;
            case 10: std::cout << "Saliendo del sistema...\n"; break;
            default: std::cout << "Opcion invalida.\n"; break;
        }

        if (opcion != 10) {
            pausar();
        }

    } while (opcion != 10);
}