#include <iostream>
#include <vector>

using namespace std;
vector<string> ids_pokemon;
vector<string> nombres_pokemon;
vector<int> tipos_pokemon;
vector<int> poderes_pokemon;


string obtener_tipo_pokemon(int tipo) {
    switch (tipo) {
        case 1: return "Fuego";
        case 2: return "Agua";
        case 3: return "Planta";
        case 4: return "Electrico";
        default: return "Desconocido";
    }
}

bool es_numerico(string numero){
    try{
        //string to int
        stoi(numero);
        return true;
    } catch(const std::invalid_argument&){
        //Este error salta cuando el string ingresado no es un int válido
        return false;
    }
}

int convertir_numero(string numero){
    try{
        //string to int
        return stoi(numero);
    } catch(const std::invalid_argument&){
        //Este error salta cuando el string ingresado no es un int válido
        return -1;
    }
}

int verifica_tipo_pokemon(){
    bool continuar = true;
    string tipo_pokemon;
    int tipo_pokemon_num;
    while(continuar){
        cout << "1. Fuego " << endl;
        cout << "2. Agua " << endl;
        cout << "3. Planta " << endl;
        cout << "4. Electrico " << endl;
        cout << "Ingrese el tipo del pokemon (1-4): ";
        cin >> tipo_pokemon;
        // primero verifica que el dato ingresado sea numerico
        if(es_numerico(tipo_pokemon)){
            // si el dato es numero válido, lo convierte a tipo INT
            // retorna -1 en caso de no sea un valor numerico valido
            tipo_pokemon_num = convertir_numero(tipo_pokemon);
            if(tipo_pokemon_num  > 0 ){
                if (tipo_pokemon_num>4 || tipo_pokemon_num <1 ){
                        cout << "Seleccione una opcion correcta (1-4)." << endl;
                } else{
                    continuar = false;
                }
            }
        }else {
            cout << "El tipo debe tener solamente digitos numericos. (1-4)" << endl;
            continuar = true;
        }
    }
    return tipo_pokemon_num;
}

string verifica_id_pokemon(){
    bool continuar = true;
    string id_ingresado;
    while(continuar){
        cout << "Ingrese el identificador del pokemon: ";
        cin >> id_ingresado;
        // Se verifica que lo ingresado sea de tipo numerico
        if(es_numerico(id_ingresado)){
           if (id_ingresado.length() != 6){
                cout << "El ID debe tener solamente 6 digitos." << endl;
                continuar = true;
            } else {
                continuar = false;
            }
        } else{
            cout << "El ID debe tener solamente digitos numericos." << endl;
            continuar = true;
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
    string poder;
    int poder_pokemon_num;
    while(continuar){
        cout << "Ingrese el poder del pokemon(1-100): ";
        cin >> poder;

        if(es_numerico(poder)){
            // si el dato es numero válido, lo convierte a tipo INT
            // retorna -1 en caso de no sea un valor numerico valido
            poder_pokemon_num = convertir_numero(poder);
            if(poder_pokemon_num  > 0 ){
                if (poder_pokemon_num>100 || poder_pokemon_num <1 ){
                        cout << "Ingrese un numero dentro del rango 1-100." << endl;
                } else{
                    continuar = false;
                }
            }
        }else {
            cout << "El poder debe tener solamente digitos numericos. (1-4)" << endl;
            continuar = true;
        }
    }
    return poder_pokemon_num;
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

bool existen_pokemones(){
    return (ids_pokemon.size() > 0) ? true : false;
}

void listar_pokemones(){
    if(existen_pokemones()){
        cout << "=============================" << endl;
        cout << "EQUIPO POKEMON" << endl;
        cout << "=============================" << endl;

        for (int i = 0; i < ids_pokemon.size(); i++){
            cout << "- Nombre: " << nombres_pokemon[i] <<endl;
            cout << "ID: " << ids_pokemon[i] <<endl;
            cout << "Tipo: " << obtener_tipo_pokemon(tipos_pokemon[i]) <<endl;
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
        }
    }
    return -1;
}

bool verifica_rango(int valor, int valor_min, int valor_max){
    if (valor>valor_max || valor <valor_min ){
        cout << "Seleccione una opcion correcta (" << valor_min<<"-"<<valor_max<<")."<< endl;
        return false;
    } else{
        return true;
    }
}

void verifica_tipo_entrenamiento(){
    bool continuar = true;
    string tipo;
    int tipo_pokemon_num ;
    while(continuar){
        cout << "1. Combate en gimnasio." << endl;
        cout << "2. Batalla con otro entrenador." << endl;
        cout << "3. Practica de habilidades." << endl;
        cout << "Ingrese el tipo de entrenamiento (1-3): ";
        cin >> tipo;

        if(es_numerico(tipo)){
            // si el dato es numero válido, lo convierte a tipo INT
            // retorna -1 en caso de no sea un valor numerico valido
            tipo_pokemon_num = convertir_numero(tipo);
            if(tipo_pokemon_num > 0 ){
                if (verifica_rango(tipo_pokemon_num, 1, 3)){
                    continuar = false;
                }
            }
        }else {
            cout << "El tipo de entrenamiento debe tener solamente digitos numericos. (1-3)" << endl;
            continuar = true;
        }
    }
}

int verifica_dificultad(){
    bool continuar = true;
    int dificultad;
    while(continuar){
        cout << "Ingrese la dificultad del entrenamiento: ";
        cin >> dificultad;

        if (dificultad>100 || dificultad <1 ){
            cout << "Ingrese una dificultad correcta (1-100)." << endl;
        } else{
            continuar = false;
        }
    }
    return dificultad;
}

void entrenar_pokemon(){
    string id_ingresado;
    cout << "Ingrese el identificador del pokemon: ";
    cin >> id_ingresado;
    int posicion_pokemon = buscar_pokemon(id_ingresado);

    if (posicion_pokemon > -1){
        verifica_tipo_entrenamiento();
        if(poderes_pokemon[posicion_pokemon] >= verifica_dificultad()){
            cout << "El entrenamiento ha sido exitoso!" << endl;
            poderes_pokemon[posicion_pokemon] = poderes_pokemon[posicion_pokemon] + 10;
        } else {
            cout << "El entrenamiento ha fallado!" << endl;
            cout << "Cada derrota es una leccion. ¡La proxima vez seros aun mejor!" << endl;
        }
    } else {
        cout << "No existe un pokemon con el ID ingresado." << endl;
    }
}

void pokemon_fuerte(){
    if(existen_pokemones()){
        int poder_mas_fuerte = -1;
        int posicion_mas_fuerte = -1;
        for (int i = 0; i < poderes_pokemon.size(); i++){
            if(poderes_pokemon[i] > poder_mas_fuerte){
                posicion_mas_fuerte = i;
                poder_mas_fuerte = poderes_pokemon[i];
            }
        }
        cout << "=============================" << endl;
        cout << "POKEMON MAS FUERTE" << endl;
        cout << "=============================" << endl;
        cout << "- Nombre: " << nombres_pokemon[posicion_mas_fuerte] <<endl;
        cout << "ID: " << ids_pokemon[posicion_mas_fuerte] <<endl;
        cout << "Tipo: " << obtener_tipo_pokemon(tipos_pokemon[posicion_mas_fuerte]) <<endl;
        cout << "Nivel de poder: " << poderes_pokemon[posicion_mas_fuerte] <<endl;
        cout << "-------------------------" << endl;

    } else {
        cout << "No hay Pokemon registrados aun." << endl;
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
                pokemon_fuerte();
                break;
            }
            case 5:{
                continuar = false;
                cout << "Gracias por usar nuestro sistema Pokemon!" << endl;
                break;
            }
            default:{
                cout << "Ingrese una opcion correcta. (1-5)" << endl;
            }
        }
    }
}

void llenar_pokemones() {
    vector<string> ids = {"000001", "000002", "000003", "000004", "000005"};
    vector<string> nombres = {"Pikachu", "Charmander", "Bulbasaur", "Squirtle", "Eevee"};
    vector<int> tipos = {4, 1, 3, 2, 3};  // 1 = Fuego, 2 = Agua, 3 = Planta, 4 = Eléctrico
    vector<int> poderes = {80, 75, 70, 85, 90};

    for (int i = 0; i < 5; i++) {
        ids_pokemon.push_back(ids[i]);
        nombres_pokemon.push_back(nombres[i]);
        tipos_pokemon.push_back(tipos[i]);
        poderes_pokemon.push_back(poderes[i]);
    }
}

int main(){
    llenar_pokemones();
    menu();
    return 0;
}
