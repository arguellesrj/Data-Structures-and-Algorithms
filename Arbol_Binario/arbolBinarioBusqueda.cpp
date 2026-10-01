/*
Realizar un programa C++ que permita gestionar un Árbol Binario de Búsqueda. El programa
debe permitir insertar, buscar y eliminar un nodo; además de presentar (utilizando cualquiera
de los recorridos) el árbol de acuerdo a las reglas que existen para el árbol binario de búsqueda.
RESTRICCIONES:
A. El primer nodo siempre será el root.
B. Al presentar el árbol debe ser de un modo intuitivo, que muestre la topología de forma
que represente en árbol.
C. Puede utilizar cualquiera de los recorridos para arboles (InOrden, PreOrden o
PostOrden).
D. Al eliminar un nodo debe observar las reglas para la sustitución del nodo, permitiendo
así que el árbol se reconstruya.
E. Al insertar un nodo deben observarse las reglas para arboles binarios de búsqueda, es
decir, los nodos cuyo valor sea mayor que el nodo raíz a la derecha (en el subárbol
derecho), en caso contrario a la izquierda (en el subárbol izquierdo). Recordando que
deben ocupar el lugar que le corresponda según la topología del árbol.
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

struct NodoA{
    int dato;
    NodoA *izq;
    NodoA *der;
    NodoA *padre;
}; 
NodoA *arbol = nullptr; 
string errorDato = "Ingrese un numero entero. Ni deje el campo vacio.", errorMenu = "Opcion no valida. Ingrese una opción del menú. Ni deje el campo vacio.";
int validateDato(string msj, string error){
    while(true){
        cout << msj; 
        string input; getline(cin, input);
        if(!all_of(input.begin(), input.end(), ::isdigit) || input.empty()){ cout << error << endl; cout << endl; continue; }
        return stoi(input);
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
NodoA* crearNodo(int dato, NodoA *padre){
    NodoA *nuevoNodo = new NodoA();
    nuevoNodo->dato = dato;
    nuevoNodo->izq = nullptr; nuevoNodo->der = nullptr;
    nuevoNodo->padre = padre;
    return nuevoNodo;
}
void insertar(NodoA *&root, int dato, NodoA *padre){ //root es un espejo del arbol
    if(root == nullptr){ 
        root = crearNodo(dato, padre);
        if(padre == nullptr) { cout << "El arbol esta vacio. Se creara la raiz. " << dato << " se ha insertado como la raíz del árbol." << endl; }
        else { cout << "Se ha insertado el nodo " << dato << " en el árbol." << endl; }
    }
    else if(dato < root->dato){ insertar(root->izq, dato, root); }
    else if(dato > root->dato){ insertar(root->der, dato, root); }
    else{ cout << "El nodo " << dato << " ya existe en el árbol." << endl; return; }
}
NodoA* buscar(NodoA *root, int num){
    NodoA *actual = root;
    while(actual != nullptr){
        if(num == actual->dato){ return actual; }
        else if(num < actual->dato){ actual = actual->izq; }
        else{ actual = actual->der; }
    }
    return nullptr;
}
void buscarMenu(){
    if(arbol == nullptr){ cout << "El árbol está vacío. No se puede buscar ningún nodo." << endl; return; }
    int num = validateDato("Ingrese el numero a buscar: ", errorDato);
    NodoA *encontrado = buscar(arbol, num);
    if(encontrado != nullptr){ cout << "El nodo " << num << " fue encontrado en el árbol." << endl; }
    else{ cout << "El nodo " << num << " no fue encontrado en el árbol." << endl; }
}
void eliminar(NodoA *&arbol){
    if(arbol == nullptr){ cout << "El árbol está vacío. No se puede eliminar ningún nodo." << endl; return; }
    int numEliminar = validateDato("Ingrese el numero a eliminar: ", errorDato);
    NodoA *nodoAEliminar = buscar(arbol, numEliminar);
    if(nodoAEliminar == nullptr){
        cout << "El nodo " << numEliminar << " no fue encontrado en el árbol. No se puede eliminar." << endl; return;
    }
    if(nodoAEliminar->izq != nullptr && nodoAEliminar->der != nullptr){
        NodoA *reemplazo = nodoAEliminar->der;
        while(reemplazo->izq != nullptr){ reemplazo = reemplazo->izq; }
        nodoAEliminar->dato = reemplazo->dato; 
        nodoAEliminar = reemplazo;
    }
    NodoA *hijo = (nodoAEliminar->izq != nullptr) ? nodoAEliminar->izq : nodoAEliminar->der;
    if(nodoAEliminar->padre == nullptr){
        arbol = hijo;
        if(hijo != nullptr){ hijo->padre = nullptr; }
    }
    else{
        NodoA *padreDelNodo = nodoAEliminar->padre;
        if(padreDelNodo->izq == nodoAEliminar){ padreDelNodo->izq = hijo; }
        else{ padreDelNodo->der = hijo; }
        if(hijo != nullptr){ hijo->padre = padreDelNodo; }
    }
    delete nodoAEliminar;
    cout << "El nodo " << numEliminar << " ha sido eliminado del árbol." << endl;
}
void mostrarVisual(NodoA *root, int espacios = 0){
    if(root == nullptr){ return; }
    mostrarVisual(root->der, espacios + 3);
    cout << string(espacios, ' ') << root->dato << endl;
    mostrarVisual(root->izq, espacios + 3);
}
void mostrarInOrden(NodoA *root){
    if(root == nullptr){ return; }
    mostrarInOrden(root->izq);
    cout << root->dato << " ";
    mostrarInOrden(root->der);
}
void mostrarPreOrden(NodoA *root){
    if(root == nullptr){ return; }
    cout << root->dato << " ";
    mostrarPreOrden(root->izq);
    mostrarPreOrden(root->der);
}
void mostrarPostOrden(NodoA *root){
    if(root == nullptr){ return; }
    mostrarPostOrden(root->izq);
    mostrarPostOrden(root->der);
    cout << root->dato << " ";
}
void mostrarMenu(NodoA *arbol){
    if(arbol == nullptr){ cout << "El árbol está vacío. No se puede mostrar ningún nodo." << endl; return; } 
    cout << endl;
    cout << "Eliga el metodo que desea utilizar para mostrar el árbol:\n"
        << "1. Mostrar el árbol en orden (in-order)\n"
        << "2. Mostrar el árbol en preorden (pre-order)\n"
        << "3. Mostrar el árbol en postorden (post-order)\n"
        << "4. Mostrar el árbol de forma visual" << endl;    
    int option = validateDato("Seleccione una de las opciones: ", errorMenu);
    switch(option){
        case 1: mostrarInOrden(arbol); break;
        case 2: mostrarPreOrden(arbol); break;
        case 3: mostrarPostOrden(arbol); break;
        case 4: mostrarVisual(arbol); break;
    }
}
int main(){
    bool seguir = true;
    while(seguir){
        limpiarPantalla();
        cout << "-----Menú de Arbol Binario de Búsqueda-----\n"
            << "1. Insertar un nodo\n"
            << "2. Buscar un nodo\n"
            << "3. Eliminar un nodo\n"
            << "4. Mostrar el árbol\n"
            << "5. Salir" << endl;
        int option = validateDato("Seleccione una de las opciones: ", errorMenu);
        switch(option){
            case 1:
                insertar(arbol, validateDato("Ingrese el numero a insertar: ", errorDato), nullptr); pausar();
                break;
            case 2:
                buscarMenu(); pausar();
                break;
            case 3:
                eliminar(arbol); pausar();
                break;
            case 4:
                mostrarMenu(arbol); pausar();
                break;
            case 5:
                cout << "Saliendo del programa..." << endl;
                seguir = false;
                break;
            default:
                cout << errorMenu << endl; pausar(); break;
        }
    }
    return 0;
}