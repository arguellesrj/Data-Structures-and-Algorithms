/*
RESTRICCIONES

Haga un programa C++ que permita manejar la pista de aterrizaje del aeropuerto de
Ciudad Gótica, sabiendo que, el programa debe insertar (encolar = Enqueue) los vuelos
en la cola priorizada según se describió anteriormente.

1- Tenga en consideración que un dato puede aparecer más de una vez en la cola. El
programa debe permitir autorizar el aterrizaje del dato que esté en la cabeza de la
cola priorizada al seleccionar Desencolar = Dequeue.

2- En el caso de tratar de autorizar el aterrizaje cuando la cola no contenga vuelos, el
programa debe notificar al usuario de que la cola esta vacía.

3- De igual manera, el programa debe poder mostrar los vuelos según el orden en la cola
realizando dequeue. En el caso de que no haya vuelos debe notificar que la cola esta
vacía.

4- El programa debe contener un menú donde se ofrezcan las opciones para realizar las
operaciones además de la opción de salir del programa (Enqueue, Dequeue, Mostrar,
Salir).
*/
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>
using namespace std;
struct NodoL{
    int dato;
    int posicion; //Solo afeta al momento de incersion, solo dicta en que posicion sera insertado
    NodoL *next;
};
NodoL *first = nullptr; NodoL *last = nullptr;
string errorInt = "Ingrese un numero entero positivo. No deje el campo vacio";
int validateInt(string msj, string error){
    bool condition = false;
    while (!condition){
        cout << msj; 
        string input; getline(cin, input);
        if (!all_of(input.begin(), input.end(), ::isdigit) || input.empty()){
            cout << error << endl; cout << endl; continue; 
        }
        int option = stoi(input); return option;
    }
}
void pausar(){
    cout << "Presione Enter para continuar..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void limpiarPantalla(){
    cout << "\033[2J\033[1;1H\033[3J";
}
void Queue(){
    int dato = validateInt("Escriba el número de dato: ", errorInt);
    int posicion = validateInt("Digite la posicion del dato: ", errorInt);
    posicion > 16 ? posicion = 16 : posicion = posicion;
    NodoL *nuevoNodo = new NodoL();
    nuevoNodo->next = nullptr; nuevoNodo->dato = dato; nuevoNodo->posicion = posicion;
    if(first == nullptr){ 
        first = nuevoNodo; 
        last = nuevoNodo; 
        return; 
    }
    else if(nuevoNodo->posicion == 0){
        nuevoNodo->next = first;
        first = nuevoNodo;
        cout << "Se agrego el dato " << nuevoNodo->dato << " correctamente." << endl; 
        return;
    }
    else if(nuevoNodo->posicion >= 16){
        last->next = nuevoNodo; last = nuevoNodo;
        cout << "Se agrego el dato " << nuevoNodo->dato << " correctamente." << endl; return;
    }
    NodoL *aux = first; int contador = 0;
    while(aux->next != nullptr && contador < nuevoNodo->posicion - 1){ aux = aux->next; contador++; }
    nuevoNodo->next = aux->next; aux->next = nuevoNodo;
    if(nuevoNodo->next == nullptr){ last = nuevoNodo; }
    cout << "Se agrego el dato " << nuevoNodo->dato << " correctamente." << endl; return;
}
void dequeue(){
    if(first == nullptr){
        cout << "La cola esta vacia." << endl; return;
    }
    NodoL *aux = first; first = first->next;
    if(first == nullptr){ cout << "La cola se vacio. Despachando el ultimo vuelo." << endl; last = nullptr; }
    cout << "Se despacho con exito el vuelo " << aux->dato << ", de posicion " << aux->posicion << "." << endl;
    delete aux; return;
}
void mostrar(){
    if(first == nullptr){ cout << "La cola esta vacia." << endl; return; }
    NodoL *aux = first;
    cout << "Mostrando los vuelos: " << endl;
    while (aux != nullptr){
        cout << aux->dato << ", ";
        aux = aux->next;
    }
    cout << endl; return;
}
void desplegar(){
    if(first == nullptr){ cout << "La cola esta vacia." << endl; return; }
    cout << "Vaciando cola: " << endl;
    while (first != nullptr){ dequeue(); }
    return;
}
int main() {
    bool condition = true;
    while (condition){
        limpiarPantalla();
        cout << "------Centro de control Pista de Aterrizaje de Ciudad Gótica------" << endl;
        cout << "1. Permitir Aterrizaje (Encolar[Enqueue])\n"
             << "2. Permitir Despegue (Desencolar[Dequeue])\n"
             << "3. Mostrar (Enseñar toda la cola)\n"
             << "4. Desplegar (Despegue masivo[Dequeue])\n"
             << "5. Salir" << endl;
        int option = validateInt("Seleccione una de las opciones: ", errorInt);
        switch (option){
            case 1:
                Queue(); pausar();
                break;
            case 2:
                dequeue(); pausar();
                break;
            case 3:
                mostrar(); pausar();
                break;
            case 4:
                desplegar(); pausar();
                break;
            case 5:
                cout << "Saliendo del programa..." << endl;
                condition = false;
                break;
            default:
                cout << "Opcion invalida. Por favor, seleccione una opcion del menú." << endl; pausar();
                break;
        }
    }
    return 0;
}