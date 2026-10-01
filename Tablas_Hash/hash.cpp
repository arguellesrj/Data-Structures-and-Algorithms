/*
Realizar un programa C++ que dados los IDs de su clase, asigne una silla a cada estudiante y
ubique al estudiante en el (índice) silla correspondiente. La estructura para este caso debe ser:
struct Estudiante {
int id;
string nombre;
string carrera
} hash[MAX]; // MAX es la cantidad de estudiantes de su sección
 
La tabla hash está limitada a MAX (en su caso estará limitada al número de estudiantes de su
sección de Estructuras de Datos y Algoritmos), por lo que solo aceptará los ID distintos de su
clase y asignará la posición correspondiente.
RESTRICCIONES:
1- Colecte todas los ID de su clase
2- El algoritmo hash no debe permitir generar un índice mayor a MAX (cantidad de
estudiantes en su sección).
3- Realice una función hash que le permita asignar un índice a cada estudiante, evitando
colisiones. Recuerde que el índice máximo es la cantidad de estudiante de su clase.
NOTA IMPORTANTE: La funciona hash debe tener notación Big O constante, es decir
O(1).
4- Una opción que permita generar los índices de todos los IDs suministrados, de modo
que permita insertar los datos correspondientes al registro señalado en el índice
asignado:
ID: (ID dado)
NOMBRE:
CARRERA:
5- Una opción que permita desplegar todos los registros en la tabla indicando los IDs y su
respectivo índice.
6- Una opción que permite desplegar el contenido del registro [ID, Nombre, Carrera e
índice (silla correspondiente)], dado el ID. Debe validarse que el ID suministrado debe
estar en el listado de IDs de su clase.
*/
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>
using namespace std;
struct hashNode{
    int id; //Key
    string nombre; //value
    string carrera; //value
};
const int MAX = 31; hashNode hashTable[MAX]{0};
int IDs[] = {
    1132698, 
    1131078, 
    1129398, 
    1131528, 
    1131946, 
    1131460, 
    1132521, 
    1129997, 
    1132907, 
    1131489, 
    1131689, 
    1132397, 
    1132115, 
    1132487, 
    1132141, 
    1131629, 
    1130421, 
    1132836, 
    1132449, 
    1132218, 
    1132407, 
    1133255, 
    1133244, 
    1132995, 
    1131833, 
    1132706, 
    1132305, 
    1132116, 
    1132788, 
    1131403, 
    1130761
};
string errorId = "Ingrese su ID (7 dígitos). Ni deje el campo vacio.", errorMenu = "Opcion no valida. Ingrese una opción del menú. Ni deje el campo vacio.",
       errorString = "Ingrese un nombre o carrera. Ni deje el campo vacio.", errorIdNF = "Ingrese un ID perteneciente a la clase.";

int hashFunction(int id){ return (id * 17) % MAX; }
int validateMenu(string msj, string error){
    while(true){
        cout << msj; 
        string input; getline(cin, input);
        if(!all_of(input.begin(), input.end(), ::isdigit) || input.empty()){ cout << error << endl; cout << endl; continue; }
        return stoi(input);
    }
}
int validateID(string msj, string errorId, string errorIdNF){
    while(true){
        cout << msj; 
        string input; getline(cin, input);
        if(!all_of(input.begin(), input.end(), ::isdigit) || input.empty() || input.length() != 7){ cout << errorId << endl; cout << endl; continue; }
        int num = stoi(input);
        if(find(begin(IDs), end(IDs), num) == end(IDs)){ cout << errorIdNF << endl; cout << endl; continue; }
        return num;
    }
}
string validateString(string msj, string error){
    while(true){
        cout << msj; 
        string input; getline(cin, input);
        if(all_of(input.begin(), input.end(), [](unsigned char c){return ::isspace(c); })|| 
            any_of(input.begin(), input.end(), [](unsigned char c){return ::isdigit(c); })){
            cout << error << endl; cout << endl; continue;
        }
        return input;
    }
}
void pausar(){
    cout << endl;
    cout << "Presione Enter para continuar..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void limpiarPantalla(){
    cout << "\033[2J\033[1;1H\033[3J";
}
hashNode* buscar(int id){
    int index = hashFunction(id);
    while(hashTable[index].id != 0){
        if(hashTable[index].id == id){
            return &hashTable[index];
        }
        index = (index + 1) % MAX;
    }
    return nullptr;
}
void insertar(int id, string nombre, string carrera){
    if (buscar(id) != nullptr) { cout << "Error: Este estudiante ya esta registrado." << endl; return; }
    int index = hashFunction(id);
    while(hashTable[index].id != 0){ index = (index + 1) % MAX; }
    hashTable[index].id = id;
    hashTable[index].nombre = nombre;
    hashTable[index].carrera = carrera;
}
bool estaVacio(){
    for(const auto& node : hashTable){
        if(node.id != 0){ return false; }
    }
    return true;
}
void buscarMenu(){
    if(estaVacio()){ cout << "La tabla hash está vacía. No se puede buscar ningún estudiante." << endl; return; }
    int id = validateID("Ingrese su ID (7 dígitos): ", errorId, errorIdNF);
    hashNode* encontrado = buscar(id);
    if(encontrado != nullptr){
        cout << "Índice (Silla): " << encontrado - hashTable << endl;
        cout << "ID: " << encontrado->id << endl;
        cout << "Nombre: " << encontrado->nombre << endl;
        cout << "Carrera: " << encontrado->carrera << endl;
    } else {
        cout << "El ID " << id << " no fue encontrado en la tabla hash." << endl;
    }
}
void mostrarTablaHash(){
    if(estaVacio()){ cout << "La tabla hash está vacía. No hay nodos para mostrar." << endl; return; }
    cout << "Tabla Hash:" << endl;
    for(int i = 0; i < MAX; ++i){
        if(hashTable[i].id != 0){
            cout << "Index: " << i << ". ID: " << hashTable[i].id << ", Nombre: " << hashTable[i].nombre << ", Carrera: " << hashTable[i].carrera << endl;
        }
    }
}
int main(){
    bool seguir = true;
    while(seguir){
        limpiarPantalla();
        cout << "-----Menú de Tablas Hash-----\n"
            << "1. Insertar un nodo\n"
            << "2. Buscar un nodo\n"
            << "3. Mostrar la tabla hash con la informacion completa\n"
            << "4. Salir" << endl;
        int option = validateMenu("Seleccione una de las opciones: ", errorMenu);
        switch(option){
            case 1: insertar(validateID("Ingrese su ID (7 dígitos): ", errorId, errorIdNF), validateString("Ingrese su nombre: ", errorString), validateString("Ingrese su carrera: ", errorString)); 
                pausar(); break;

            case 2: buscarMenu(); pausar(); break;
            case 3: mostrarTablaHash(); pausar(); break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                seguir = false;
                break;
            default: cout << "Opcion no valida. Ingrese una opción del menú." << endl; pausar(); break;
        }
    }
    return 0;
}