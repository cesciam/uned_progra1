#include <iostream>

using namespace std;


void menu(){

    bool continuar = true;
    int opcion_ingresada = 0;

    while(continuar){

        cout << "=============================" << endl;
        cout << "SISTEMA DE ENTRENAMIENTO POKEMON" << endl;
        cout << "1. Registrar un Pokemon" << endl;
        cout << "2. Entrenar un Pokemon" << endl;
        cout << "3. Mostrar el equipo Pokemon" << endl;
        cout << "4. Mostrar el Pokemon mas fuerte" << endl;
        cout << "5. Salir del programa" << endl;
        cout << "=============================" << endl;
        cin >> opcion_ingresada;

        switch (opcion_ingresada){
            case 1:{
                cout << "opcion1" << endl;
                break;
            }
            case 2:{
                //registrar_pokemon();
                break;
            }
            case 3:{
                //registrar_pokemon();
                break;
            }
            case 4:{
                //registrar_pokemon();
                break;
            }
            case 5:{
                continuar = false;
                cout << "Gracias por usar nuestro sistema Pokemon!" << endl;
                break;
            }
        }

    }


}

int main()
{
    menu();
    return 0;
}
