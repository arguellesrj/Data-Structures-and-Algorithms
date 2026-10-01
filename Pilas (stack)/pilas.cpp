/*
Una pila (stack) es una estructura de datos en donde el último en entrar es el primero en salir.
Construir un programa C++ que simule una pila, utilizando una estructura de datos como la que
sigue para los nodos:

struct Pila {
int dato;
Pila *next;
};

RESTRICCIONES:
A. La pila debe poder realizar las operaciones de Push y Pop.
B. Tener en consideración de desplegar un mensaje de “Empty Stack”, cuando se trate de
hacer un Pop cuando la pila este vacía.
C. El programa debe tener un menú para realizar las operaciones de Push, Pop y Desplegar
toda la pila realizando Pops hasta el último nodo. Además, debe tener una opción de
salir del programa.
*/
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <cctype> 
using namespace std;

struct Pila{
    int dato;
    Pila *next;
};
Pila *cima = nullptr;
void pausar(){
    cout << "Presione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void limpiarPantalla(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void push(){
    cout << "Introduzca el valor a agregar a la pila: ";
    string dato; getline(cin, dato); int nDato = 0;
    stringstream ss(dato); ss >> nDato;
    if(ss.fail()){
        cout << "Entrada no valida. Por favor, ingrese un dato valido." << endl;
        pausar(); return;
    }
    Pila *nuevoNodo = new Pila();
    nuevoNodo->dato = nDato; 
    nuevoNodo->next = cima; cima = nuevoNodo;
    cout << "\nEl valor se agrego " << nuevoNodo->dato << " correctamente." << endl;
    pausar(); return;
}
void pop(){
    if (cima != nullptr){
        Pila *aux = cima;
        cima = cima->next;
        cout << "El valor " << aux->dato << " se elimino correctamente." << endl;
        delete aux;
        pausar(); 
    }else{
        cout << "Empty Stack" << endl;
        pausar(); return;
    }
}
void desplegarPila(){
    if (cima == nullptr){
        cout << "La pila esta vacia." << endl;
        pausar(); return;
    }
    else{
        Pila *aux = cima;
        cout << "Vaciando la pila: " << endl;
        while (cima != nullptr){
            cima = cima->next;
            cout <<"Se elimino el valor " << aux->dato << endl;
            delete aux;
            aux = cima;
        }
        pausar(); return;
    }
}
int main()
{
    bool seguir = true;
    while (seguir){
        limpiarPantalla();
        string opcion;
        int opcionInt = 0;
        cout << "Bienvenido al programa de simulacion de una pila (stack).\n" << endl;
        cout << "Seleccione una opcion del menu: \n1. Push (Agregar un elemento a la pila)\n2. Pop (Eliminar el elemento superior de la pila)\n3. Desplegar toda la pila\n"
             << "4. Salir" << endl;
        getline(cin, opcion);
        if(opcion.empty() || !all_of(opcion.begin(), opcion.end(), ::isdigit)){
            cout << "Entrada no valida. Por favor, ingrese un numero valido." << endl;
            pausar(); limpiarPantalla(); continue;
        }
        stringstream ss(opcion); ss >> opcionInt;
        switch (opcionInt){
            case 1: { // Push
                push();
                break;
            }
            case 2: { // Pop
                pop();
                break;
            }
            case 3: {
                desplegarPila();
                break;
            }
            case 4: {
                cout << "Programa terminado." << endl;
                seguir = false;
                break;
            }
            default: {
                cout << "Opcion no valida. Por favor, seleccione una opcion del menu.\n" << endl;
                pausar();
                break;
            }
        }
    }
    return 0;
}