#include "Auto.h"
#include <iostream> // liberia leer y escribir
#include <fstream>
#include <string>
#include <cctype> // Para isdigit()
#include <limits> // Para std::numeric_limits
#include <cstdlib> // Para system()
#include <cctype> // Para tolower()
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <vector>
using namespace std;

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

Auto parsear_linea_a_auto(const string& linea) {
    string codigo, nombre, equipo, id_registro;
    int velocidad, caballos_fuerza, costo;

    size_t pos = linea.find(',');
    codigo = linea.substr(0, pos);
    string resto = linea.substr(pos + 1);

    pos = resto.find(',');
    nombre = resto.substr(0, pos);
    resto = resto.substr(pos + 1);

    pos = resto.find(',');
    velocidad = stoi(resto.substr(0, pos));
    resto = resto.substr(pos + 1);

    pos = resto.find(',');
    caballos_fuerza = stoi(resto.substr(0, pos));
    resto = resto.substr(pos + 1);

    pos = resto.find(',');
    equipo = resto.substr(0, pos);
    resto = resto.substr(pos + 1);

    pos = resto.find(',');
    costo = stoi(resto.substr(0, pos));
    resto = resto.substr(pos + 1);

    id_registro = resto;

    return Auto(codigo, nombre, velocidad, caballos_fuerza, equipo, costo, id_registro);
}

bool validacion_continuar(const string& mensaje) {
    string continua;
    while (true) {
        cout << "================================================"<< endl;
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
            cout << "Error: Ingrese una opcion valida (S/N)." << endl;
        }
    }
}


void consultar_autos() {
    ifstream archivo("AUTOS.TXT");
    if (!archivo) { // Verificar si el archivo se abrió correctamente
        cout << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    string codigo_busqueda;
    cout << "================================================"<< endl;
    cout << "CONSULTAR AUTO EN INVENTARIO"<< endl;
    cout << "================================================"<< endl;
    codigo_busqueda = leer_string("Ingrese el codigo del auto a buscar: ");

    cout << "Buscando auto con codigo: " << codigo_busqueda << "..."<<endl;

    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) { // Leer cada línea del archivo
        size_t pos = linea.find(',');
        if (pos != string::npos && linea.substr(0, pos) == codigo_busqueda) {
            // Parsear la línea y crear un objeto Auto
            Auto auto_encontrado = parsear_linea_a_auto(linea);
            // Mostrar la información del auto
            cout << "================================================"<< endl;
            cout << "Datos del auto encontrado:"<< endl;
            cout << "================================================"<< endl;
            auto_encontrado.mostrarInformacion();
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontro un auto con el codigo " << codigo_busqueda << "." << endl;
    }

    archivo.close(); // Cerrar el archivo después de usarlo

    // Limpiar el búfer de entrada antes de llamar a validacion_continuar
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (validacion_continuar("Desea volver al menu principal? (S/N): ")) {
        return; // Volver al menú principal
    } else {
        consultar_autos(); // Volver a consultar otro auto
    }
}

void guardar_auto(const Auto& nuevo_auto) {
    ofstream archivo("AUTOS.TXT", ios::app); // Abre el archivo en modo append
    if (archivo.is_open()) {
        archivo << nuevo_auto.getCodigoAuto()
        << "," << nuevo_auto.getNombreAuto()
        << "," << nuevo_auto.getVelocidadMaxima()
        << "," << nuevo_auto.getCaballosFuerza()
        << "," << nuevo_auto.getEquipoPropietario()
        << "," << nuevo_auto.getCostoAuto()
        << ","<< nuevo_auto.getIdRegistrador() << endl;
        archivo.close();
    } else {
        cout << "Error: No se pudo abrir el archivo AUTOS.TXT." << endl;
        if (validacion_continuar ("Desea volver a intentarlo? (S/N): ")){
            guardar_auto(nuevo_auto);
        } else {
            return;
        }
    }
}

// Función para generar un código aleatorio en formato A00000000
string generar_codigo_auto() {
    string codigo = "A"; // El código siempre empieza con "A"
    for (int i = 0; i < 8; i++) {
        codigo += to_string(rand() % 10); // Agrega un dígito aleatorio (0-9)
    }
    return codigo;
}

// Función para verificar si un código ya existe en el archivo AUTOS.TXT
bool codigo_existe(const string& codigo) {
    ifstream archivo("AUTOS.TXT");
    string linea;
    while (getline(archivo, linea)) {
        size_t pos = linea.find(','); // Busca la primera coma (el código está antes de la primera coma)
        if (pos != string::npos && linea.substr(0, pos) == codigo) {
            return true; // El código ya existe
        }
    }
    return false; // El código no existe
}

// Función para generar un código único
string generar_codigo_unico() {
    string codigo;
    do {
        codigo = generar_codigo_auto(); // Genera un código aleatorio
    } while (codigo_existe(codigo));   // Verifica que no exista en el archivo
    return codigo;
}

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
        cout << mensaje;
        cin >> valor;

        if (es_numerico(valor)) {
            convertido = convertir_numero(valor);
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar solo si la entrada es válida
            return convertido;
        }

        cout << "Error: Entrada no válida. Debe ingresar un número entero. Intente de nuevo.\n";
        cin.clear(); // Limpia estado de error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia cualquier residuo
    }
}

bool validar_id_registro(const string& id) {
    if (id.length() != 9) return false; // Verifica la longitud
    for (char c : id) {
        if (!isdigit(c)) return false; // Verifica que todos los caracteres sean dígitos
    }
    return true;
}

void ingresar_auto(){
    string codigo = generar_codigo_unico();
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

    while (!validar_id_registro(id_registro)){
        cout << "El numero de identificacion solo puede tener 9 digitos numericos. "<< endl;
        id_registro = leer_string("Numero de identificacion de quien registra el auto: ");
    }

    Auto nuevo_auto(codigo, nombre, velocidad, caballos_fuerza, equipo, costo, id_registro);
    system("cls");
    nuevo_auto.mostrarInformacion();

    if (validacion_continuar ("¿Esta seguro de que desea registrar este auto? (S/N): ")){
        guardar_auto(nuevo_auto);
    } else {
        return;
    }
}


void modificar_auto(){
    ifstream archivo("AUTOS.TXT");
    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    cout << "================================================"<< endl;
    cout << "Modificar auto en inventario"<< endl;
    cout << "================================================"<< endl;

    string codigo_busqueda;
    codigo_busqueda = leer_string("Ingrese el codigo del auto a modificar: ");

    cout << ""<< endl;
    cout << "Buscando auto con codigo: "<<codigo_busqueda << "..."<<endl;

    string linea;
    vector<string> lineas_archivo; // Almacenar todas las líneas del archivo
    bool encontrado = false;

    while (getline(archivo, linea)) {
        size_t pos = linea.find(',');
        if (pos != string::npos && linea.substr(0, pos) == codigo_busqueda) {
            // Parsear la línea y crear un objeto Auto
            Auto auto_encontrado = parsear_linea_a_auto(linea);

            cout << "================================================"<< endl;
            cout << "Datos del Auto Encontrado"<< endl;
            cout << "================================================"<< endl;
            auto_encontrado.mostrarInformacion();

            // Solicitar nuevos valores
            cout << "================================================"<< endl;
            if(validacion_continuar("Desea modificar la velocidad maxima y los caballos de fuerza? (S/N): ")){
                int nueva_velocidad = leer_int("Nueva velocidad maxima (km/h): ");
                int nuevos_caballos_fuerza = leer_int("Nuevos caballos de fuerza (HP): ");
                cout << "================================================"<< endl;

                // Actualizar el auto
                auto_encontrado.setVelocidadMaxima(nueva_velocidad);
                auto_encontrado.setCaballosFuerza(nuevos_caballos_fuerza);

                // Reconstruir la línea con los nuevos valores
                string nueva_linea = auto_encontrado.getCodigoAuto() + "," +
                                     auto_encontrado.getNombreAuto() + "," +
                                     to_string(auto_encontrado.getVelocidadMaxima()) + "," +
                                     to_string(auto_encontrado.getCaballosFuerza()) + "," +
                                     auto_encontrado.getEquipoPropietario() + "," +
                                     to_string(auto_encontrado.getCostoAuto()) + "," +
                                     auto_encontrado.getIdRegistrador();

                lineas_archivo.push_back(nueva_linea); // Guardar la línea modificada
                encontrado = true;
                cout << "================================================"<< endl;
                cout << "Los datos han sido actualizados exitosamente."<< endl;
                cout << "================================================"<< endl;
                cout << "Los cambios se han guardado en el archivo AUTOS.TXT"<< endl;
                auto_encontrado.mostrarInformacion();
            }{
                lineas_archivo.push_back(linea); // Guardar la línea sin modificar
                return;
            }

        } else {
            lineas_archivo.push_back(linea); // Guardar la línea sin modificar
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "No se encontro un auto con el codigo " << codigo_busqueda << "." << endl;
    } else {
        // Guardar todas las líneas en el archivo
        ofstream archivo_salida("AUTOS.TXT");
        for (const string& l : lineas_archivo) {
            archivo_salida << l << endl;
        }
        archivo_salida.close();
        cout << "Auto modificado exitosamente." << endl;
    }

    if (validacion_continuar("Desea volver al menu principal? (S/N): ")) {
        return; // Volver al menú principal
    } else {
        modificar_auto(); // Volver a modificar otro auto
    }
}

void eliminar_auto(){
        ifstream archivo("AUTOS.TXT");
    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    string codigo_busqueda;
    cout << "Ingrese el codigo del auto a eliminar: ";
    cin >> codigo_busqueda;

    string linea;
    vector<string> lineas_archivo; // Almacenar todas las líneas del archivo
    bool encontrado = false;

    while (getline(archivo, linea)) {
        size_t pos = linea.find(',');
        if (pos != string::npos && linea.substr(0, pos) == codigo_busqueda) {
            cout << "\nAuto encontrado y eliminado:\n";
            Auto auto_encontrado = parsear_linea_a_auto(linea); // Función para convertir línea a objeto Auto
            auto_encontrado.mostrarInformacion();
            encontrado = true;
        } else {
            lineas_archivo.push_back(linea); // Guardar la línea si no es el auto a eliminar
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "No se encontro un auto con el codigo " << codigo_busqueda << "." << endl;
    } else {
        // Guardar todas las líneas en el archivo (excepto la eliminada)
        ofstream archivo_salida("AUTOS.TXT");
        for (const string& l : lineas_archivo) {
            archivo_salida << l << endl;
        }
        archivo_salida.close();
        cout << "Auto eliminado exitosamente." << endl;
    }

    // Limpiar el búfer de entrada antes de llamar a validacion_continuar
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (validacion_continuar("Desea volver al menu principal? (S/N): ")) {
        return; // Volver al menú principal
    } else {
        eliminar_auto(); // Volver a eliminar otro auto
    }
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
