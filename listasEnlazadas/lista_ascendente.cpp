/*
Realizar un programa C++ que simule una Lista Enlazada (Linked List).
Una Lista Enlazada (Linked List) es una estructura de datos en donde cada nodo apunta a uno siguiente y
de esta manera se mantiene un enlace entre los nodos. Para nuestro caso, haremos el problema un poco
más real exigiendo que al insertar cada nodo, este se inserte de manera ordenada (ascendente) de modo
que los nodos se indexen según su dato.
RESTRICCIONES:
A. La Lista Enlazada (Linked List) debe poder realizar las operaciones Insertar, Buscar, Eliminar y Mostrar
la Lista Enlazada.
B. Al insertar un nuevo nodo el programa debe contemplar realizar la inserción del nodo donde le
corresponda, ya que la lista debe estar ordenada en forma ascendente según su dato.
C. El programa deberá tener un menú con las opciones para Insertar, Buscar, Eliminar y Mostrar la Lista
Enlazada y Salir.
D. Las entradas de datos del usuario deben ser debidamente validas.
E. El programa debe ser lo suficientemente especializado para informar al usuario cuando la Lista
Enlazada (Linked List) está vacía.
*/
#include <iostream>
#include <string>
#include <algorithm> 
#include <limits>    
using namespace std;
struct NodoL{
    int dato;
    NodoL *next;
};
struct searchResult{
    NodoL *anterior;
    NodoL *actual;
    int pos;
    bool found;
};
NodoL *first = nullptr, *last = nullptr;
string errorDato = "Ingrese un numero entero. Ni deje el campo vacio.", errorMenu = "Opcion no valida. Ingrese una opción del menú. Ni deje el campo vacio.";
int validateDato(string msj, string error){
    while(true){
        cout << msj; 
        string input; getline(cin, input);
        if(!all_of(input.begin(), input.end(), ::isdigit) || input.empty()){ cout << error << endl; cout << endl; continue; }
        int option = stoi(input);
        return option;
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

searchResult buscar(int num){
    searchResult sr{nullptr, first, 0, false};
    while(sr.actual != nullptr && sr.actual->dato < num){
        sr.anterior = sr.actual; sr.actual = sr.actual->next; sr.pos++; 
    }
    sr.found = (sr.actual != nullptr); return sr;
}
void insertar(){
    int num = validateDato("Ingrese el numero a insertar: ", errorDato);
    searchResult sr = buscar(num); 
    if(sr.found){cout << "El numero " << num << " se encuentra en la lista." << endl; return;}
    NodoL *nuevoNodo = new NodoL();
    nuevoNodo->dato = num;
    nuevoNodo->next = nullptr;
    if(first == nullptr){ first = nuevoNodo; last = nuevoNodo; cout << "Se agrego el numero " << nuevoNodo->dato << " correctamente." << endl; return;}
    else if(nuevoNodo->dato < first->dato){
        nuevoNodo->next = first;
        first = nuevoNodo; 
        cout << "Se agrego el numero " << nuevoNodo->dato << " correctamente." << endl; return;
    }else if(last->dato < nuevoNodo->dato){
        last->next = nuevoNodo; last = nuevoNodo;
    }
    NodoL *aux = first;
    while(aux->next != nullptr && aux->next->dato < nuevoNodo->dato){ aux = aux->next; }
    nuevoNodo->next = aux->next;
    aux->next = nuevoNodo;
    if(nuevoNodo->next == nullptr) { last = nuevoNodo; }
    cout << "Se agrego el numero " << nuevoNodo->dato << " correctamente." << endl; return;
}
void buscarMenu(){
    int num = validateDato("Ingrese el numero a buscar: ", errorDato);
    searchResult sr = buscar(num);
    if(sr.found){
        cout << "El numero " << num << " se encuentra en la lista. En la posicion " << sr.pos << "." << endl;
    }else{
        cout << "El numero " << num << " no se encuentra en la lista." << endl;
    }
}
void eliminar(){
    int num = validateDato("Ingrese el numero a eliminar: ", errorDato);
    searchResult sr = buscar(num);
    if(sr.found){
        if(sr.anterior == nullptr){ first = sr.actual->next; }
        else{ sr.anterior->next = sr.actual->next; }
        if(sr.actual == last){ last = sr.anterior; }
        cout << "Se elimino el numero " << num << " correctamente." << endl;
        delete sr.actual;
    }else{cout << "El numero " << num << " no se encuentra en la lista." << endl;}
}
void mostrar(){
    cout << "Desplegando la lista: " << endl;
    NodoL *aux = first;
    while(aux != nullptr){
        cout << aux->dato << " ";
        aux = aux->next;
    }
    cout << endl; return;
}
int main(){
    bool seguir = true;
    while (seguir){
        limpiarPantalla();
        cout << "Desplegando Menu de Lista Enlazada (Ascendente):" << endl;
        cout << "1. Insertar elemento a la lista\n"
            << "2. Buscar elemento en la lista\n"
            << "3. Eliminar elemento de la lista\n"
            << "4. Mostrar elementos de la lista\n"
            << "5. Salir" << endl;
        int option = validateDato("Seleccione una de las opciones: ", errorMenu);
        switch (option){
            case 1:
                insertar(); pausar();
                break;
            case 2:
                buscarMenu(); pausar();
                break;
            case 3:
                eliminar(); pausar();
                break;
            case 4:
                mostrar(); pausar();
                break;
            case 5:
                cout << "Saliendo del programa..." << endl; pausar();
                seguir = false;
                break;
            default:
                cout << errorMenu << endl;
                break;
        }
    }
    return 0;
}