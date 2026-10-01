/*
Codigo de 4 digitos y 10 intentos
y los puntos estan dados en base a que esta en el intento 10 = 10points, y asi sucesivamente descendiendo hasta que llegue a 0 donde ya perdio el juego

F - esta pero en la posicion incorrecta
C - esta en la posicion correcta
X - no esta
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits>
using namespace std;

int main(){
    srand(time(0));
    bool seguir = true;
    do{
        int intentos = 10;
        string codigoPartes = "123456"; int n = codigoPartes.length();
        for (int i = n - 1; i > 0; i--){
            int j = rand() % (i + 1);
            char temp = codigoPartes[i];
            codigoPartes[i] = codigoPartes[j];
            codigoPartes[j] = temp;
        }
        string codigo = codigoPartes.substr(0, 4);
        cout << "Bienvenido al juego MasterMind. Deberas adivinar el codigo de 4 digitos, tendras 10 intentos." << endl;
        while (intentos != 0){
            cout << endl;
            cout << "Digite su intento: ";
            string codigoUsuario;
            getline(cin, codigoUsuario);

            bool todosDigitos = true, uniqueDigits = true, encontrado = false;
            for (int i = 0; i < codigoUsuario.length(); i++){
                if (!isdigit(codigoUsuario[i])){
                    todosDigitos = false;
                    break;
                }
                for (int j = i + 1; j < codigoUsuario.length(); j++){
                    if (codigoUsuario[i] == codigoUsuario[j]){
                        uniqueDigits = false;
                        break;
                    }
                }
                if (!uniqueDigits){ break; }
            }

            if (codigoUsuario.length() != 4 || !todosDigitos || !uniqueDigits){
                cout << "El codigo debe tener 4 digitos y deben ser distintos." << endl;
                continue;
            }
            for (int i = 0; i < 4; i++){
                encontrado = false;
                if (codigoUsuario[i] == codigo[i]){
                    cout << "C";
                }
                else{
                    for (int j = 0; j < 4; j++){
                        if (codigoUsuario[i] == codigo[j]){
                            encontrado = true;
                            break;
                        }
                    }
                    if (encontrado){
                        cout << "F";
                    }
                    else{
                        cout << "X";
                    }
                }
            }
            cout << endl;
            if (codigoUsuario == codigo){
                cout << "\nFelicidades, adivinaste el codigo!\n"
                     << "Puntos obtenidos: " << intentos << endl;
                break;
            }
            intentos--;
        }
        if(intentos == 0)cout << "Se te acabaron los intentos, el codigo era: " << codigo << endl;
        do{
            cout << "Deseas jugar de nuevo? (s/n): ";
            string respuesta;
            getline(cin, respuesta);
            if (tolower(!respuesta.empty() && respuesta[0]) == 's') { seguir = true;}
            else if (respuesta.empty() || tolower(respuesta[0]) == 'n') { cout << "Gracias por jugar!" << endl; exit(0); }
            else { cout << "Respuesta invalida, intente de nuevo." << endl; seguir = false; }
        } while (!seguir);
    } while (seguir);
    return 0;
}