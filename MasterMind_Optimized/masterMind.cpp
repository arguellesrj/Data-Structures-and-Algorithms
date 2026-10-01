/*
Codigo de 4 digitos y 10 intentos
y los puntos estan dados en base a que esta en el intento 10 = 10points, y asi sucesivamente descendiendo hasta que llegue a 0 donde ya perdio el juego

F - esta pero en la posicion incorrecta
C - esta en la posicion correcta
X - no esta 
*/
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <cctype>
#include <set>
#include <limits>
using namespace std;

int main(){
    bool seguir = true;
    do{
        int intentos = 10;
        string codigoPartes = "123456";
        shuffle(codigoPartes.begin(), codigoPartes.end(), default_random_engine(random_device()()));
        string codigo = codigoPartes.substr(0, 4);

        cout << "Bienvenido al juego MasterMind. Deberas adivinar el codigo de 4 digitos, tendras 10 intentos." << endl;
        while (intentos != 0){
            cout << endl;
            cout << "Digite su intento: ";
            string codigoUsuario;
            getline(cin, codigoUsuario);
            codigoUsuario.erase(remove(codigoUsuario.begin(), codigoUsuario.end(), ' '), codigoUsuario.end());
            set<char> uniqueDigits(codigoUsuario.begin(), codigoUsuario.end());

            if (codigoUsuario.length() != 4 || !all_of(codigoUsuario.begin(), codigoUsuario.end(), ::isdigit) || uniqueDigits.size() != 4){
                cout << "El codigo debe tener 4 digitos y deben ser distintos." << endl;
                continue;
            }
            for (int i = 0; i < 4; i++){
                if (codigoUsuario[i] == codigo[i]){ cout << "C"; }
                else if (codigo.find(codigoUsuario[i]) != string::npos){ cout << "F"; }
                else{ cout << "X"; }
            }
            cout << endl;
            if (codigoUsuario == codigo){
                cout << "\nFelicidades, adivinaste el codigo!\n"
                     << "Puntos obtenidos: " << intentos << endl;
                return 0;
            }
            intentos--;
        }
        if (intentos == 0) cout << "Se te acabaron los intentos, el codigo era: " << codigo << endl;
        do{
            cout << "Deseas jugar de nuevo? (s/n): ";
            string respuesta;
            getline(cin, respuesta);
            if (tolower(!respuesta.empty() && respuesta[0]) == 's') { seguir = true; } 
            else if (!respuesta.empty() && tolower(respuesta[0]) == 'n') { cout << "Gracias por jugar!" << endl; exit(0); }
            else { cout << "Respuesta invalida, intente de nuevo." << endl; seguir = false; }
        } while (!seguir);
    } while (seguir);
    return 0;
}