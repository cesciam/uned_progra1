#include <iostream>
#include <vector>

using namespace std;
vector<string> ids_pokemon;
vector<string> nombres_pokemon;
vector<int> tipos_pokemon;
vector<int> poderes_pokemon;


int verifica_tipo_pokemon(){
    bool continuar = true;
    int tipo;
    while(continuar){
        cout << "1. Fuego " << endl;
        cout << "2. Agua " << endl;
        cout << "3. Planta " << endl;
        cout << "4. Electrico " << endl;
        cout << "Ingrese el tipo del pokemon (1-4): ";
        cin >> tipo;

        if (tipo>4 || tipo <1 ){
            cout << "Seleccione una opcion correcta (1-4)." << endl;
        } else{
            continuar = false;
        }
    }
    return tipo;
}

string verifica_id_pokemon(){
    bool continuar = true;
    bool esNumerico = false;
    string id_ingresado;
    while(continuar){
        cout << "Ingrese el identificador del pokemon: ";
        cin >> id_ingresado;
        // Se verifica que lo ingresado sea de tipo numerico
        try{
            //string to int
            stoi(id_ingresado);
            esNumerico = true;
        } catch(const std::invalid_argument&){
            //Este error salta cuando lo ingresado no es de tipo string
            cout << "El ID debe tener solamente digitos numericos." << endl;
            esNumerico = false;
        }
        if (id_ingresado.length() != 6){
            cout << "El ID debe tener solamente 6 digitos." << endl;
            continuar = true;
        } else if(esNumerico){
            continuar = false;
        }

        if(!continuar){
            //Este ciclo verifica que el ID no haya sido registrado anteriormente
            for (string i : ids_pokemon){
                if (i == id_ingresado){
                    cout << "El ID de registro ya ha sido utilizado. Por favor ingrese otro." << endl;
                    continuar = true;
                } else {
                    continuar = false;
                }
            }
        }
    }
    return id_ingresado;
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
    return poder;
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

    ids_pokemon.push_back(id);
    tipos_pokemon.push_back(tipo);
    nombres_pokemon.push_back(nombre);
    poderes_pokemon.push_back(poder);

}

void listar_pokemones(){

    if(ids_pokemon.size() > 0){
        cout << "=============================" << endl;
        cout << "EQUIPO POKEMON" << endl;
        cout << "=============================" << endl;

        for (int i = 0; i < ids_pokemon.size(); i++){
            cout << "- Nombre: " << nombres_pokemon[i] <<endl;
            cout << "ID: " << ids_pokemon[i] <<endl;
            cout << "Tipo: " << tipos_pokemon[i] <<endl;
            cout << "Nivel de poder: " << poderes_pokemon[i] <<endl;
            cout << "-------------------------" << endl;
        }
    } else {
        cout << "No hay Pokemon registrados aun." << endl;

    }
}

int buscar_pokemon(string id){
    for(int i = 0; i < ids_pokemon.size(); i++){
        if(ids_pokemon[i] == id){
            return i;
        } else {
            return -1;
        }
    }
}

void verifica_tipo_entrenamiento(){
    bool continuar = true;
    int tipo;
    while(continuar){
        cout << "(1. Combateen gimnasio." << endl;
        cout << "2. Batalla con otro entrenador." << endl;
        cout << "3. Practica de habilidades." << endl;
        cout << "Ingrese el tipo de entrenamiento (1-3): ";
        cin >> tipo;

        if (tipo>3 || tipo <1 ){
            cout << "Seleccione una opcion correcta (1-3)." << endl;
        } else{
            continuar = false;
        }
    }
}


void entrenar_pokemon(){
    cout << "Ingrese el identificador del pokemon: ";
    cin >> id_ingresado;

    int posicion_pokemon = buscar_pokemon(id_ingresado);

    if (posicion_pokemon > 0){
        verifica_tipo_entrenamiento();

    } else {
        cout << "No existe un pokemon con el ID ingresado." << endl;
    }
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
                entrenar_pokemon();
                break;
            }
            case 3:{
                listar_pokemones();
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
