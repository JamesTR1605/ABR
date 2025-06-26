#include <iostream>        // Librer�a para entrada y salida est�ndar
#include <string>          // Librer�a para manipular cadenas de texto (string)
using namespace std;       // Uso del espacio de nombres est�ndar

// Estructura para representar una persona en el �rbol geneal�gico
struct Persona {
    int id;                        // Identificador �nico de la persona
    string nombreCompleto;         // Nombre completo de la persona
    string fechaNacimiento;        // Fecha de nacimiento
    char sexo;                     // Sexo ('M' o 'F')
    string estadoCivil;            // Estado civil

    // Punteros para �rbol binario de b�squeda
    Persona* izquierda;            // Hijo izquierdo
    Persona* derecha;              // Hijo derecho

    // Relaciones familiares
    Persona* padre;                // Puntero al padre
    Persona* madre;                // Puntero a la madre
    Persona* hijos[10];            // Arreglo de punteros a hijos (m�ximo 10)
    int numHijos;                  // Cantidad actual de hijos

    // Constructor
    Persona(int _id, string _nombre, string _fecha, char _sexo, string _estadoCivil = "Soltero") {
        id = _id;
        nombreCompleto = _nombre;
        fechaNacimiento = _fecha;
        sexo = _sexo;
        estadoCivil = _estadoCivil;
        izquierda = NULL;
        derecha = NULL;
        padre = NULL;
        madre = NULL;
        numHijos = 0;
        for(int i = 0; i < 10; i++) {
            hijos[i] = NULL;
        }
    }
};

// Clase que representa el �rbol geneal�gico
class ArbolGenealogico {
private:
    Persona* raiz;              // Nodo ra�z del �rbol
    bool diosCreado;            // Bandera para saber si 'Dios' ya fue creado
    bool tatarabuelosCreados;   // Bandera para los tatarabuelos (no usada)

    // Inserta recursivamente una persona en el �rbol (por ID)
    Persona* insertarRecursivo(Persona* nodo, Persona* nuevaPersona) {
        if (nodo == NULL) {
            return nuevaPersona;
        }
        if (nuevaPersona->id < nodo->id) {
            nodo->izquierda = insertarRecursivo(nodo->izquierda, nuevaPersona);
        } else if (nuevaPersona->id > nodo->id) {
            nodo->derecha = insertarRecursivo(nodo->derecha, nuevaPersona);
        }
        return nodo;
    }

    // Busca recursivamente una persona por su ID
    Persona* buscarRecursivo(Persona* nodo, int id) {
        if (nodo == NULL || nodo->id == id) {
            return nodo;
        }
        if (id < nodo->id) {
            return buscarRecursivo(nodo->izquierda, id);
        }
        return buscarRecursivo(nodo->derecha, id);
    }

    // Recorrido inorden: izquierda, ra�z, derecha
    void inordenRecursivo(Persona* nodo) {
        if (nodo != NULL) {
            inordenRecursivo(nodo->izquierda);
            cout << "ID: " << nodo->id << " - " << nodo->nombreCompleto 
                 << " (" << nodo->sexo << ") - " << nodo->fechaNacimiento
                 << " - Estado Civil: " << nodo->estadoCivil;
            if (nodo->padre != NULL || nodo->madre != NULL) {
                cout << " [Padres: ";
                if (nodo->padre != NULL) cout << "P:" << nodo->padre->nombreCompleto;
                if (nodo->padre != NULL && nodo->madre != NULL) cout << ", ";
                if (nodo->madre != NULL) cout << "M:" << nodo->madre->nombreCompleto;
                cout << "]";
            }
            cout << endl;
            inordenRecursivo(nodo->derecha);
        }
    }

    // Recorrido preorden: ra�z, izquierda, derecha
    void preordenRecursivo(Persona* nodo) {
        if (nodo != NULL) {
            cout << "ID: " << nodo->id << " - " << nodo->nombreCompleto 
                 << " (" << nodo->sexo << ") - " << nodo->fechaNacimiento
                 << " - Estado Civil: " << nodo->estadoCivil;
            if (nodo->padre != NULL || nodo->madre != NULL) {
                cout << " [Padres: ";
                if (nodo->padre != NULL) cout << "P:" << nodo->padre->nombreCompleto;
                if (nodo->padre != NULL && nodo->madre != NULL) cout << ", ";
                if (nodo->madre != NULL) cout << "M:" << nodo->madre->nombreCompleto;
                cout << "]";
            }
            cout << endl;
            preordenRecursivo(nodo->izquierda);
            preordenRecursivo(nodo->derecha);
        }
    }

    // Recorrido postorden: izquierda, derecha, ra�z
    void postordenRecursivo(Persona* nodo) {
        if (nodo != NULL) {
            postordenRecursivo(nodo->izquierda);
            postordenRecursivo(nodo->derecha);
            cout << "ID: " << nodo->id << " - " << nodo->nombreCompleto 
                 << " (" << nodo->sexo << ") - " << nodo->fechaNacimiento
                 << " - Estado Civil: " << nodo->estadoCivil;
            if (nodo->padre != NULL || nodo->madre != NULL) {
                cout << " [Padres: ";
                if (nodo->padre != NULL) cout << "P:" << nodo->padre->nombreCompleto;
                if (nodo->padre != NULL && nodo->madre != NULL) cout << ", ";
                if (nodo->madre != NULL) cout << "M:" << nodo->madre->nombreCompleto;
                cout << "]";
            }
            cout << endl;
        }
    }

    // Encuentra el nodo con valor m�nimo (para eliminar)
    Persona* encontrarMinimo(Persona* nodo) {
        while (nodo->izquierda != NULL) {
            nodo = nodo->izquierda;
        }
        return nodo;
    }

    // Elimina un nodo del �rbol por ID
    Persona* eliminarRecursivo(Persona* nodo, int id) {
        if (nodo == NULL) {
            return nodo;
        }
        if (id < nodo->id) {
            nodo->izquierda = eliminarRecursivo(nodo->izquierda, id);
        } else if (id > nodo->id) {
            nodo->derecha = eliminarRecursivo(nodo->derecha, id);
        } else {
            // No se pueden eliminar Dios ni los tatarabuelos
            if (id >= 0 && id <= 4) {
                cout << "Error: No se pueden eliminar la entidad suprema o los Abuelo fundadores ." << endl;
                return nodo;
            }
            if (nodo->izquierda == NULL) {
                Persona* temp = nodo->derecha;
                delete nodo;
                return temp;
            } else if (nodo->derecha == NULL) {
                Persona* temp = nodo->izquierda;
                delete nodo;
                return temp;
            }
            Persona* temp = encontrarMinimo(nodo->derecha);
            nodo->id = temp->id;
            nodo->nombreCompleto = temp->nombreCompleto;
            nodo->fechaNacimiento = temp->fechaNacimiento;
            nodo->sexo = temp->sexo;
            nodo->estadoCivil = temp->estadoCivil;
            nodo->derecha = eliminarRecursivo(nodo->derecha, temp->id);
        }
        return nodo;
    }

public:
    // Constructor
    ArbolGenealogico() {
        raiz = NULL;
        diosCreado = false;
        tatarabuelosCreados = false;
    }

    // Crear la entidad suprema 'Dios' con ID 0
    void crearDios() {
        if (diosCreado) {
            cout << "La entidad suprema 'Dios' ya ha sido creada." << endl;
            return;
        }
        Persona* dios = new Persona(0, "Dios", "Desde el principio", 'M', "Eterno");
        raiz = insertarRecursivo(raiz, dios);
        diosCreado = true;
        cout << "Entidad suprema 'Dios' creada como ra�z del arbol genealogico." << endl;
    }

    // Verifica si 'Dios' ha sido creado
    bool verificarDios() {
        return diosCreado && (buscarPersona(0) != NULL);
    }

    // Verifica si los 4 tatarabuelos ya han sido creados
    bool verificarTatarabuelos() {
        int contador = 0;
        for (int i = 1; i <= 4; i++) {
            if (buscarPersona(i) != NULL) {
                contador++;
            }
        }
        return contador == 4;
    }

    // Crear tatarabuelo con datos del usuario
    void crearTatarabuelo(int id) {
        if (!verificarDios()) {
            cout << "Error: Primero debe crear la entidad suprema 'Dios'." << endl;
            return;
        }
        if (id < 1 || id > 4) {
            cout << "Error: Los Abuelo deben tener ID del 1 al 4" << endl;
            return;
        }
        if (buscarPersona(id) != NULL) {
            cout << "Error: Ya existe un Abuelo con ID " << id << endl;
            return;
        }

        string nombre, fecha, estadoCivil;
        char sexo;

        cout << "\n=== CREANDO Abuelo " << id << " ===" << endl;
        cout << "Ingrese nombre completo: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "Ingrese fecha de nacimiento (DD/MM/AAAA): ";
        getline(cin, fecha);
        cout << "Ingrese sexo (M/F): ";
        cin >> sexo;
        cout << "Ingrese estado civil (Soltero/Casado/Viudo/Divorciado): ";
        cin.ignore();
        getline(cin, estadoCivil);

        insertarPersonaConPadres(id, nombre, fecha, sexo, estadoCivil, 0, 0);
        cout << "Abuelo creado exitosamente: " << nombre << endl;
        cout << "Creado como descendiente de la entidad suprema." << endl;
    }

    // Insertar persona con referencias a sus padres
    void insertarPersonaConPadres(int id, string nombre, string fecha, char sexo, string estadoCivil, int idPadre, int idMadre) {
        if (buscarPersona(id) != NULL) {
            cout << "Error: Ya existe una persona con ID " << id << endl;
            return;
        }

        Persona* padre = NULL;
        Persona* madre = NULL;

        if (idPadre != 0) {
            padre = buscarPersona(idPadre);
            if (padre == NULL) {
                cout << "Error: No se encontro el padre con ID " << idPadre << endl;
                return;
            }
            if (padre->sexo != 'M' && idPadre != 0) {
                cout << "Error: El padre debe ser de sexo masculino (M)" << endl;
                return;
            }
        }

        if (idMadre != 0) {
            madre = buscarPersona(idMadre);
            if (madre == NULL) {
                cout << "Error: No se encontro la madre con ID " << idMadre << endl;
                return;
            }
            if (madre->sexo != 'F') {
                cout << "Error: La madre debe ser de sexo femenino (F)" << endl;
                return;
            }
        }

        Persona* nuevaPersona = new Persona(id, nombre, fecha, sexo, estadoCivil);

        if (padre != NULL) {
            nuevaPersona->padre = padre;
            if (padre->numHijos < 10) {
                padre->hijos[padre->numHijos] = nuevaPersona;
                padre->numHijos++;
            }
        }

        if (madre != NULL) {
            nuevaPersona->madre = madre;
            if (madre->numHijos < 10) {
                madre->hijos[madre->numHijos] = nuevaPersona;
                madre->numHijos++;
            }
        }

        raiz = insertarRecursivo(raiz, nuevaPersona);

        cout << "Persona agregada exitosamente: " << nombre << endl;
        if (padre != NULL) cout << "Padre: " << padre->nombreCompleto << endl;
        if (madre != NULL) cout << "Madre: " << madre->nombreCompleto << endl;
    }

// Buscar persona por ID
// Llama a la funci�n recursiva que busca a la persona dentro del �rbol geneal�gico
Persona* buscarPersona(int id) {
    return buscarRecursivo(raiz, id);
}

// Eliminar persona por ID
void eliminarPersona(int id) {
    // Validaci�n: no se permite eliminar ni a Dios (ID 0) ni a los abuelos fundadores (ID 1�4)
    if (id >= 0 && id <= 4) {
        cout << "Error: No se pueden eliminar la entidad suprema o los Abuelo fundadores ." << endl;
        return;
    }

    // Buscar a la persona antes de intentar eliminarla
    Persona* persona = buscarPersona(id);
    if (persona != NULL) {
        cout << "Eliminando: " << persona->nombreCompleto << endl;
        // Llama a la funci�n recursiva para eliminar al nodo del �rbol
        raiz = eliminarRecursivo(raiz, id);
    } else {
        cout << "Persona con ID " << id << " no encontrada." << endl;
    }
}

// Mostrar informaci�n detallada de una persona seg�n su ID
void mostrarInfoPersona(int id) {
    Persona* persona = buscarPersona(id);
    if (persona != NULL) {
        cout << "\n=== INFORMACION PERSONAL ===" << endl;
        cout << "ID: " << persona->id << endl;
        cout << "Nombre: " << persona->nombreCompleto << endl;
        cout << "Fecha de nacimiento: " << persona->fechaNacimiento << endl;
        cout << "Sexo: " << (persona->sexo == 'M' ? "Masculino" : "Femenino") << endl;
        cout << "Estado civil: " << persona->estadoCivil << endl;

        // Mostrar informaci�n de los padres si existen
        if (persona->padre != NULL) {
            cout << "Padre: " << persona->padre->nombreCompleto << " (ID: " << persona->padre->id << ")" << endl;
        }
        if (persona->madre != NULL) {
            cout << "Madre: " << persona->madre->nombreCompleto << " (ID: " << persona->madre->id << ")" << endl;
        }

        // Mostrar todos los hijos registrados
        if (persona->numHijos > 0) {
            cout << "Hijos (" << persona->numHijos << "): ";
            for (int i = 0; i < persona->numHijos; i++) {
                cout << persona->hijos[i]->nombreCompleto << " (ID: " << persona->hijos[i]->id << ")";
                if (i < persona->numHijos - 1) cout << ", ";
            }
            cout << endl;
        }
    } else {
        cout << "Persona no encontrada." << endl;
    }
}

// Mostrar todos los posibles padres disponibles para asignar a una nueva persona
void mostrarPosiblesPadres() {
    cout << "\n=== POSIBLES PADRES DISPONIBLES ===" << endl;
    mostrarPosiblesPadresRecursivo(raiz);
}

// Recorre el �rbol en inorden y muestra a cada persona como posible padre/madre
void mostrarPosiblesPadresRecursivo(Persona* nodo) {
    if (nodo != NULL) {
        mostrarPosiblesPadresRecursivo(nodo->izquierda);
        cout << "ID: " << nodo->id << " - " << nodo->nombreCompleto 
             << " (" << (nodo->sexo == 'M' ? "Masculino" : "Femenino") << ")"
             << " - Estado Civil: " << nodo->estadoCivil << endl;
        mostrarPosiblesPadresRecursivo(nodo->derecha);
    }
}

// Mostrar recorrido inorden (izquierda, ra�z, derecha)
void mostrarInorden() {
    cout << "\n=== �RBOL GENEALOGICO (INORDEN) ===" << endl;
    inordenRecursivo(raiz);
}

// Mostrar recorrido preorden (ra�z, izquierda, derecha)
void mostrarPreorden() {
    cout << "\n=== �RBOL GENEALOGICO (PREORDEN) ===" << endl;
    preordenRecursivo(raiz);
}

// Mostrar recorrido postorden (izquierda, derecha, ra�z)
void mostrarPostorden() {
    cout << "\n=== �RBOL GENEALOGICO (POSTORDEN) ===" << endl;
    postordenRecursivo(raiz);
}

// Mostrar �rbol por niveles (BFS - Breadth First Search)
void mostrarPorNiveles() {
    if (raiz == NULL) return;

    cout << "\n=== ARBOL GENEALOGICO (POR NIVELES) ===" << endl;

    Persona* cola[1000]; // Cola para recorrido nivel por nivel
    int frente = 0, final = 0;
    int nivelActual = 0;

    cola[final++] = raiz;
    cola[final++] = NULL; // Marcador de fin de nivel

    while (frente < final) {
        Persona* actual = cola[frente++];

        if (actual == NULL) {
            nivelActual++;
            if (frente < final && cola[frente] != NULL) {
                cola[final++] = NULL;
            }
            cout << "\nGeneracion " << nivelActual << ":\n";
            continue;
        }

        // Mostrar datos de la persona
        cout << "  ID: " << actual->id << " - " << actual->nombreCompleto 
             << " (" << actual->sexo << ") - " << actual->estadoCivil;

        // Mostrar los padres si existen
        if (actual->padre != NULL || actual->madre != NULL) {
            cout << " [Padres: ";
            if (actual->padre != NULL) cout << "P:" << actual->padre->nombreCompleto;
            if (actual->padre != NULL && actual->madre != NULL) cout << ", ";
            if (actual->madre != NULL) cout << "M:" << actual->madre->nombreCompleto;
            cout << "]";
        }
        cout << endl;

        // Agregar hijos al recorrido
        if (actual->izquierda != NULL) cola[final++] = actual->izquierda;
        if (actual->derecha != NULL) cola[final++] = actual->derecha;
    }
}

// Buscar y mostrar los padres (ancestros directos) de una persona
void buscarAncestros(int id) {
    Persona* persona = buscarPersona(id);
    if (persona != NULL) {
        cout << "\n=== ANCESTROS DE " << persona->nombreCompleto << " ===" << endl;

        if (persona->padre != NULL)
            cout << "Padre: " << persona->padre->nombreCompleto << " (ID: " << persona->padre->id << ")" << endl;
        if (persona->madre != NULL)
            cout << "Madre: " << persona->madre->nombreCompleto << " (ID: " << persona->madre->id << ")" << endl;

        if (persona->padre == NULL && persona->madre == NULL)
            cout << "No se han registrado ancestros directos." << endl;
    } else {
        cout << "Persona no encontrada." << endl;
    }
}

// Mostrar �rbol por generaciones
void mostrarPorGeneraciones() {
    cout << "\n=== ARBOL POR GENERACIONES ===" << endl;

    // Mostrar entidad suprema
    Persona* dios = buscarPersona(0);
    if (dios != NULL) {
        cout << "ENTIDAD SUPREMA:" << endl;
        cout << "  ID 0: " << dios->nombreCompleto << " (" << dios->sexo << ") - " << dios->estadoCivil << endl;
    }

    // Mostrar abuelos
    cout << "\n ABUELOS (Generaci�n 1):" << endl;
    for (int i = 1; i <= 4; i++) {
        Persona* p = buscarPersona(i);
        if (p != NULL) {
            cout << "  ID " << i << ": " << p->nombreCompleto << " (" << p->sexo << ") - " << p->estadoCivil << endl;
        }
    }

    // Mostrar descendientes
    cout << "\nDESCENDIENTES:" << endl;
    mostrarDescendientesRecursivo(raiz, 2);
}

// Funci�n recursiva para mostrar descendientes (ID > 4)
void mostrarDescendientesRecursivo(Persona* nodo, int generacion) {
    if (nodo != NULL) {
        mostrarDescendientesRecursivo(nodo->izquierda, generacion);

        if (nodo->id > 4) {
            cout << "  Generacion " << generacion << " - ID " << nodo->id << ": " 
                 << nodo->nombreCompleto << " (" << nodo->sexo << ") - " << nodo->estadoCivil;
            if (nodo->padre != NULL || nodo->madre != NULL) {
                cout << " [Hijo de: ";
                if (nodo->padre != NULL) cout << nodo->padre->nombreCompleto;
                if (nodo->padre != NULL && nodo->madre != NULL) cout << " y ";
                if (nodo->madre != NULL) cout << nodo->madre->nombreCompleto;
                cout << "]";
            }
            cout << endl;
        }

        mostrarDescendientesRecursivo(nodo->derecha, generacion);
    }
}

// Funci�n para mostrar el men� de opciones
void mostrarMenu() {
    cout << "\n=== SISTEMA DE ARBOL GENEALOGICO ===" << endl;
    cout << "0. Crear entidad suprema 'Dios' (Raiz principal)" << endl;
    cout << "1. Crear Abuelo" << endl;
    cout << "2. Agregar persona (descendiente)" << endl;
    cout << "3. Buscar persona" << endl;
    cout << "4. Eliminar persona" << endl;
    cout << "5. Mostrar informacion de persona" << endl;
    cout << "6. Mostrar posibles padres disponibles" << endl;
    cout << "7. Mostrar arbol (inorden)" << endl;
    cout << "8. Mostrar arbol (preorden)" << endl;
    cout << "9. Mostrar arbol (postorden)" << endl;
    cout << "10. Mostrar arbol (por niveles)" << endl;
    cout << "11. Buscar ancestros" << endl;
    cout << "12. Mostrar por generaciones" << endl;
    cout << "99. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

// Funci�n principal
int main() {
    ArbolGenealogico arbol;
    int opcion;

    cout << "=== BIENVENIDO AL SISTEMA DE ARBOL GENEALOGICO ===" << endl;
    cout << "IMPORTANTE:" << endl;
    cout << "1. Primero debe crear la entidad suprema 'Dios' (ID 0)." << endl;
    cout << "2. Luego crear los 4 Abuelos (IDs 1 a 4)." << endl;
    cout << "3. Finalmente, agregar los descendientes." << endl;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 0:
                arbol.crearDios();
                break;
            case 1: {
                int id;
                cout << "Ingrese ID del Abuelo a crear (1 al 4): ";
                cin >> id;
                arbol.crearTatarabuelo(id);
                break;
            }
            case 2: {
                if (!arbol.verificarDios()) {
                    cout << "Error: Primero debe crear la entidad suprema 'Dios'." << endl;
                    break;
                }
                if (!arbol.verificarTatarabuelos()) {
                    cout << "Error: Debe crear los 4 abuelos (IDs 1 al 4)." << endl;
                    break;
                }

                int id, idPadre, idMadre;
                string nombre, fecha, estadoCivil;
                char sexo;

                cout << "Ingrese ID del nuevo descendiente (mayor a 4): ";
                cin >> id;
                if (id <= 4) {
                    cout << "Error: El ID debe ser mayor a 4." << endl;
                    break;
                }
                if (arbol.buscarPersona(id) != NULL) {
                    cout << "Error: Ya existe una persona con ese ID." << endl;
                    break;
                }

                cin.ignore();
                cout << "Nombre completo: ";
                getline(cin, nombre);
                cout << "Fecha de nacimiento (DD/MM/AAAA): ";
                getline(cin, fecha);
                cout << "Sexo (M/F): ";
                cin >> sexo;
                cin.ignore();
                cout << "Estado civil: ";
                getline(cin, estadoCivil);

                cout << "�Desea ver los posibles padres? (S/N): ";
                char ver;
                cin >> ver;
                if (ver == 'S' || ver == 's') arbol.mostrarPosiblesPadres();

                cout << "ID del padre (0 si no hay): ";
                cin >> idPadre;
                cout << "ID de la madre (0 si no hay): ";
                cin >> idMadre;

                arbol.insertarPersonaConPadres(id, nombre, fecha, sexo, estadoCivil, idPadre, idMadre);
                break;
            }
            case 3: {
                int id;
                cout << "Ingrese ID a buscar: ";
                cin >> id;
                Persona* p = arbol.buscarPersona(id);
                if (p != NULL)
                    cout << "Persona encontrada: " << p->nombreCompleto << endl;
                else
                    cout << "Persona no encontrada." << endl;
                break;
            }
            case 4: {
                int id;
                cout << "Ingrese ID de persona a eliminar: ";
                cin >> id;
                arbol.eliminarPersona(id);
                break;
            }
            case 5: {
                int id;
                cout << "Ingrese ID para mostrar informaci�n: ";
                cin >> id;
                arbol.mostrarInfoPersona(id);
                break;
            }
            case 6:
                arbol.mostrarPosiblesPadres();
                break;
            case 7:
                arbol.mostrarInorden();
                break;
            case 8:
                arbol.mostrarPreorden();
                break;
            case 9:
                arbol.mostrarPostorden();
                break;
            case 10:
                arbol.mostrarPorNiveles();
                break;
            case 11: {
                int id;
                cout << "Ingrese ID para buscar ancestros: ";
                cin >> id;
                arbol.buscarAncestros(id);
                break;
            }
            case 12:
                arbol.mostrarPorGeneraciones();
                break;
            case 99:
                cout << "Gracias por usar el sistema." << endl;
                break;
            default:
                cout << "Opci�n no v�lida." << endl;
        }

        if (opcion != 99) {
            cout << "Presione Enter para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (opcion != 99); // Fin del ciclo principal

    return 0;
}



