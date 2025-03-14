#include <iostream>
#include <vector>

using namespace std;

// =================== DECLARACIÓN DE VARIABLES GLOBALES ===================

// Vectores para almacenar datos de los Pokémon
vector<string> ids_pokemon; // IDs únicos de cada Pokémon (6 dígitos)
vector<string> nombres_pokemon; // Nombres de los Pokémon
vector<int> tipos_pokemon; // Tipos de los Pokémon (Fuego, Agua, Planta)
vector<int> poderes_pokemon; // Nivel de poder de cada Pokémon (0-100)

// =================== FUNCIONES AUXILIARES ===================

// Verifica si existen Pokémon registrados en el sistema
bool existen_pokemones(){
    return (ids_pokemon.size() > 0) ? true : false;
}

// Obtiene el índice de un Pokémon en los vectores basado en su ID
// Retorna -1 si el ID no se encuentra
int buscar_pokemon(string id){
    for(int i = 0; i < ids_pokemon.size(); i++){
        if(ids_pokemon[i] == id){
            return i;
        }
    }
    return -1;
}

// Verifica si una cadena de texto representa un número entero
bool es_numerico(string numero){
    try{
        // Intenta convertir la cadena a número
        stoi(numero);
        return true;
    } catch(const std::invalid_argument&){
        // Retorna falso si ocurre una excepción
        return false;
    }
}

// Verifica si un número está dentro de un rango especificado
bool verifica_rango(int valor, int valor_min, int valor_max){
    if (valor>valor_max || valor <valor_min ){
        cout << "Seleccione una opcion correcta (" << valor_min<<"-"<<valor_max<<")."<< endl;
        return false;
    } else{
        return true;
    }
}

// Convierte el código de tipo al nombre completo del tipo
string obtener_tipo_pokemon(int tipo) {
    switch (tipo) {
        case 1: return "Fuego";
        case 2: return "Agua";
        case 3: return "Planta";
        case 4: return "Electrico";
        default: return "Desconocido";
    }
}

// =================== FUNCIONES PRINCIPALES ===================


int convertir_numero(string numero){
    try{
        //string to int
        return stoi(numero);
    } catch(const std::invalid_argument&){
        //Este error salta cuando el string ingresado no es un int v�lido
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
            // si el dato es numero v�lido, lo convierte a tipo INT
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
            // si el dato es numero v�lido, lo convierte a tipo INT
            // retorna -1 en caso de no sea un valor numerico valido
            poder_pokemon_num = convertir_numero(poder);
            if(poder_pokemon_num  > 0 ){
                 if (verifica_rango(poder_pokemon_num, 1, 100)){
                    continuar = false;
                }
            }
        }else {
            cout << "El poder debe tener solamente digitos numericos." << endl;
            continuar = true;
        }
    }
    return poder_pokemon_num;
}

// Registra un nuevo Pokémon en el sistema
void registrar_pokemon(){
    string nombre;
    string id;
    int tipo;
    int poder;

    // Solicita y valida el ID del Pokémon
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
            // si el dato es numero v�lido, lo convierte a tipo INT
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
    string dificultad;
    int dificultad_entrenamiento;
    while(continuar){
        cout << "Ingrese la dificultad del entrenamiento (1-100): ";
        cin >> dificultad;
        if(es_numerico(dificultad)){
            // si el dato es numero v�lido, lo convierte a tipo INT
            // retorna -1 en caso de no sea un valor numerico valido
            dificultad_entrenamiento = convertir_numero(dificultad);
            if(dificultad_entrenamiento > 0 ){
                if (verifica_rango(dificultad_entrenamiento, 1, 100)){
                    continuar = false;
                }
            }
        }else {
            cout << "El tipo de entrenamiento debe tener solamente digitos numericos." << endl;
            continuar = true;
        }
    }
    return dificultad_entrenamiento;
}

// Entrena un Pokémon incrementando su poder en 10 puntos (máximo 100)
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
            cout << "Cada derrota es una leccion. �La proxima vez seros aun mejor!" << endl;
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
    int opcion_ingresada_num = 0;
    string opcion_ingresada = "";
    while(continuar){
        cout << "=============================" << endl;
        cout << "SISTEMA DE ENTRENAMIENTO POKEMON" << endl;
        cout << "1. Registrar un Pokemon" << endl;
        cout << "2. Entrenar un Pokemon" << endl;
        cout << "3. Mostrar el equipo Pokemon" << endl;
        cout << "4. Mostrar el Pokemon mas fuerte" << endl;
        cout << "5. Salir del programa" << endl;
        cout << "=============================" << endl;
        cout << "Ingrese una opcion: " ;
        cin >> opcion_ingresada;

        if(es_numerico(opcion_ingresada)){
            opcion_ingresada_num = convertir_numero(opcion_ingresada);
            switch (opcion_ingresada_num){
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
        else{
            cout << "Ingrese una opcion correcta. (1-5)" << endl;
        }
    }
}

// Esta funcion llena los vectores con datos para realizar las pruebas
void llenar_pokemones() {
    vector<string> ids = {"000001", "000002", "000003", "000004", "000005"};
    vector<string> nombres = {"Pikachu", "Charmander", "Bulbasaur", "Squirtle", "Eevee"};
    vector<int> tipos = {4, 1, 3, 2, 3};  // 1 = Fuego, 2 = Agua, 3 = Planta, 4 = El�ctrico
    vector<int> poderes = {80, 75, 70, 85, 90};

    for (int i = 0; i < 5; i++) {
        ids_pokemon.push_back(ids[i]);
        nombres_pokemon.push_back(nombres[i]);
        tipos_pokemon.push_back(tipos[i]);
        poderes_pokemon.push_back(poderes[i]);
    }
}

int main(){
    // Descomentar la linea de abajo para cargar el programa con datos registrados
    // llenar_pokemones();
    menu();
    return 0;
}
