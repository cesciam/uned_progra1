#include <iostream>

using namespace std;

int verifica_tipo_pokemon(){
    bool continuar = true;
    int tipo;
    while(continuar){
        cout << "1. Fuego " << endl;
        cout << "2. Agua " << endl;
        cout << "3. Planta " << endl;
        cout << "4. Electrico " << endl;
        cout << "Ingrese el tipo del pokemon: ";
        cin >> tipo;

        if (tipo>4 || tipo <1 ){
            cout << "Seleccione una opcion correcta" << endl;
        } else{
            continuar = false;
        }
    }
    return tipo;
}

string verifica_id_pokemon(){
    bool continuar = true;
    bool esNumerico = false;
    string id;
    while(continuar){
        cout << "Ingrese el identificador del pokemon: ";
        cin >> id;
        // Se verifica que lo ingresado sea de tipo numerico
        try{
            //string to int
            stoi(id);
            esNumerico = true;
        } catch(const std::invalid_argument&){
            //Este error salta cuando lo ingresado no es de tipo string
            cout << "El ID debe tener solamente digitos numericos." << endl;
            esNumerico = false;
        }
        if (id.length() != 6){
            cout << "El ID debe tener solamente 6 digitos." << endl;
        } else if(esNumerico){
            continuar = false;
        }
    }
    return id;
}

int verifica_poder_pokemon(){
    bool continuar = true;
    int poder;
    while(continuar){
        cout << "Ingrese el poder del pokemon(1-100): ";
        cin >> poder;

        if (poder >100 || poder < 1){
            cout << "Ingrese un numero dentro del rango 1-100." << endl;
        } else{
            continuar = false;
        }
    }
    return tipo;
}

void registrar_pokemon(){
    string nombre;
    string id;
    int tipo;
    int poder;
    cout << "Ingrese el nombre del pokemon: ";
    cin >> nombre;
    id = verifica_id_pokemon();
    tipo = verifica_tipo_pokemon();
    poder = verifica_poder_pokemon();
}

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
                registrar_pokemon();
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
