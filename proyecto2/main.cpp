#include "Auto.h"
#include <iostream> // liberia leer y escribir
#include <fstream>
#include <string>
#include <cctype> // Para isdigit()
#include <limits> // Para std::numeric_limits
#include <cstdlib> // Para system()
#include <cctype> // Para tolower()



using namespace std;


// Función que verifica si una cadena representa un número entero válido
bool es_numerico(const string& numero) {
    if (numero.empty()) return false; // Cadena vacía no es numérica

    size_t inicio = 0;

    // Permitir un signo '+' o '-' al inicio
    if (numero[0] == '+' || numero[0] == '-') {
        if (numero.size() == 1) return false; // Solo un signo no es válido
        inicio = 1; // Saltamos el primer carácter
    }

    // Verificar que el resto de caracteres sean dígitos
    for (size_t i = inicio; i < numero.size(); i++) {
        if (!isdigit(numero[i])) return false;
    }
    return true;
}

// Función que convierte una cadena a número entero
int convertir_numero(const string& numero) {
    if (!es_numerico(numero)) return -1; // Si no es numérico, retorna -1
    try {
        return stoi(numero); // Convierte el número
    } catch (const out_of_range&) {
        return -1; // Si el número es demasiado grande o pequeño para int, retorna -1
    }
}

int leer_int(const string& mensaje) {
    string valor;
    int convertido;
    while (true) {
        cout << mensaje; // Muestra el mensaje al usuario
        cin >> valor;

        // Limpiar el búfer de entrada después de leer
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (es_numerico(valor)) { // Intenta leer un entero
            convertido = convertir_numero(valor);
            break; // Valor válido, salir del bucle
        } else {
            cout << "Error: Entrada no valida. Debe ingresar un numero entero. Intente de nuevo.\n";
            cin.clear(); // Limpia el estado de error de cin
        }
    }
    return convertido; // Retorna el valor válido
}
// Función para leer una cadena evitando problemas con el buffer
string leer_string(string mensaje) {
    string entrada;
    while (true) {
        cout << mensaje;
        getline(cin, entrada);
        if (!entrada.empty()) {
            // Si la cadena no está vacía, salimos del bucle
            break;
        }
    }
    return entrada;
}

bool validacion_continuar(const string& mensaje) {
    string continua;
    while (true) {
        cout << mensaje; // Muestra el mensaje al usuario
        getline(cin, continua); // Lee la entrada completa

        // Convierte la entrada a minúsculas para simplificar la validación
        for (char& c : continua) {
            c = tolower(c);
        }

        // Validación de la entrada
        if (continua == "s") {
            return true;
        } else if (continua == "n") {
            return false;
        } else {
            cout << "Error: Ingrese una opción válida (S/N)." << endl;
        }
    }
}


void ingresar_auto(){
    string codigo = "A11111111";
    string nombre;
    int velocidad;
    int caballos_fuerza;
    string equipo;
    int costo;
    string id_registro;
    system("cls");
    cout << "================================================"<< endl;
    cout << "INGRESAR AUTO A INVENTARIO"<< endl;
    cout << "================================================"<< endl;
    cout << "Codigo de auto: " << codigo << "<-- (Generado automaticamente)"<< endl;
    nombre = leer_string("Nombre del Auto (modelo/marca): ");
    velocidad = leer_int("Velocidad Maxima (km/h): ");
    caballos_fuerza = leer_int("Caballos de Fuerza (HP): ");
    equipo = leer_string("Equipo/Propetario: ");
    costo = leer_int("Costo del Auto: ");
    id_registro = leer_string("Numero de identificacion de quien registra el auto: ");

    Auto nuevo_auto(codigo, nombre, velocidad, caballos_fuerza, equipo, 250000.0, id_registro);
    system("cls");
    nuevo_auto.mostrarInformacion();

    if (validacion_continuar ("¿Esta seguro de que desea registrar este auto? (S/N): ")){
        cout << "Guardar" << endl;
    } else {
        return;
    }


}

void consultar_autos(){
}

void modificar_auto(){
}

void eliminar_auto(){
}

void menu_autos(){
    bool continuar = true;
    int opcion_ingresada_num = 0;
    string opcion_ingresada = "";
    while(continuar){
        system("cls");
        cout << "=============================" << endl;
        cout << "1. Ingresar auto al inventario." << endl;
        cout << "2. Consultar auto del inventario" << endl;
        cout << "3. Modificar auto del inventario" << endl;
        cout << "4. Eliminar auto del inventario" << endl;
        cout << "5. Salir del menu" << endl;
        cout << "=============================" << endl;
        opcion_ingresada = leer_string("Ingrese una opcion: ");

        if(es_numerico(opcion_ingresada)){
            opcion_ingresada_num = convertir_numero(opcion_ingresada);
            switch (opcion_ingresada_num){
                case 1:{
                    ingresar_auto();
                    cout << "// menu_autos();" << endl;
                    break;
                }
                case 2:{
                    consultar_autos();
                    cout << "// menu_competencias();"<< endl;
                    break;
                }
                case 3:{
                    modificar_auto();
                    cout << "// inventario();"<< endl;
                    break;
                }
                case 4:{
                    eliminar_auto();
                    cout << "// reporte_competencias();"<< endl;
                    break;
                }
                case 5:{
                    return;
                }
                default:{
                    cout << "Opcion invalida, vuelva a intentarlo." << endl;
                }
            }
        }
        else{
            cout << "Opcion invalida, vuelva a intentarlo." << endl;
        }
    }
}

void menu(){
    bool continuar = true;
    int opcion_ingresada_num = 0;
    string opcion_ingresada = "";
    while(continuar){
        cout << "=============================" << endl;
        cout << "1. Inventario de Autos" << endl;
        cout << "2. Registro de Competencias" << endl;
        cout << "3. Reporte de Autos en Inventario" << endl;
        cout << "4. Reporte de Competencias" << endl;
        cout << "5. Salir del programa" << endl;
        cout << "=============================" << endl;
        opcion_ingresada = leer_string("Ingrese una opcion: ");

        if(es_numerico(opcion_ingresada)){
            opcion_ingresada_num = convertir_numero(opcion_ingresada);
            switch (opcion_ingresada_num){
                case 1:{
                    menu_autos();
                    break;
                }
                case 2:{
                    // menu_compentencias();
                    cout << "// menu_competencias();"<< endl;
                    break;
                }
                case 3:{
                    // reporte_inventario();
                    cout << "// inventario();"<< endl;
                    break;
                }
                case 4:{
                    // reporte_competencias();
                    cout << "// reporte_competencias();"<< endl;
                    break;
                }
                case 5:{
                    continuar = false;
                    cout << "Gracias por usar nuestro sistema" << endl;
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



int main() {
    // Crear un objeto Auto
    // Auto miAuto("A12345678", "Ferrari 488 GTB", 330.5, 660, "Scuderia Ferrari", 250000.0, "ID12345");

    // Mostrar la información del auto
    // miAuto.mostrarInformacion();
    menu();

    return 0;
}
