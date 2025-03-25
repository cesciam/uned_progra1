#include "Auto.h"
#include "Competencia.h"
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
#include <regex>
using namespace std;

// Inicio Definicion de funciones
void menu();  // Declaracion de la funcion antes de main()
void menu_competencias();
// Fin Definicion de funciones

bool verifica_rango(int valor, int valor_min, int valor_max){
    if (valor>valor_max || valor <valor_min ){
        cout << "Seleccione una opcion correcta (" << valor_min<<"-"<<valor_max<<")."<< endl;
        return false;
    } else{
        return true;
    }
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


Auto buscar_auto(const string& codigo_busqueda) {
    ifstream archivo("AUTOS.TXT");
    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo." << endl;
        return Auto("", "", 0, 0, "", 0,"000000000"); // Retorna un Auto vacío
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t pos = linea.find(',');
        if (pos != string::npos && linea.substr(0, pos) == codigo_busqueda) {
            archivo.close();
            return parsear_linea_a_auto(linea); // Retorna el auto encontrado
        }
    }

    archivo.close();
    return Auto("", "", 0, 0, "", 0,"000000000"); // Retorna un Auto vacío
}

// Imprime mensajes con ======
void mostrar_banner(string mensaje){
    cout << "================================================"<< endl;
    cout << mensaje << endl;
    cout << "================================================"<< endl;
    cout << ""<< endl;

}

// Funcion para leer una cadena evitando problemas con el buffer
string leer_string(string mensaje) {
    string entrada;
    while (true) {
        cout << mensaje;
        if (cin.peek() == '\n') cin.ignore(); // Limpia el buffer si hay un salto de línea previo
        getline(cin, entrada);
        if (!entrada.empty()) break;
    }
    return entrada;
}

bool validacion_continuar(const string& mensaje) {
    string continua;
    while (true) {
        mostrar_banner("");
        cout << mensaje;
        getline(cin, continua); // Lee la entrada completa

        // Convierte la entrada a min�sculas para simplificar la validaci�n
        for (char& c : continua) {
            c = tolower(c);
        }

        // Validaci�n de la entrada
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
    if (!archivo) { // Verificar si el archivo se abri� correctamente
        cout << "Error: No se pudo abrir el archivo." << endl;
        return;
    }
    string codigo_busqueda;
    mostrar_banner("CONSULTAR AUTO EN INVENTARIO");
    codigo_busqueda = leer_string("Ingrese el codigo del auto a buscar: ");
    cout << "Buscando auto con codigo: " << codigo_busqueda << "..."<<endl;

    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) { // Leer cada l�nea del archivo
        size_t pos = linea.find(',');
        if (pos != string::npos && linea.substr(0, pos) == codigo_busqueda) {
            // Parsear la l�nea y crear un objeto Auto
            Auto auto_encontrado = parsear_linea_a_auto(linea);
            // Mostrar la informaci�n del auto
            mostrar_banner ("Datos del auto encontrado");
            cout << "Datos del auto encontrado:"<< endl;
            auto_encontrado.mostrarInformacion();
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontro un auto con el codigo " << codigo_busqueda << "." << endl;
    }

    archivo.close(); // Cerrar el archivo despues de usarlo

    if (validacion_continuar("Desea volver al menu principal? (S/N): ")) {
        menu();
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

// Funcion para generar un codigo aleatorio en formato A/C00000000
string generar_codigo(string prefijo) {
    string codigo = prefijo; // El codigo siempre empieza con "A"
    for (int i = 0; i < 8; i++) {
        codigo += to_string(rand() % 10); // Agrega un d�gito aleatorio (0-9)
    }
    return codigo;
}

// Funcion para verificar si un codigo ya existe en el archivo AUTOS.TXT
bool codigo_existe(const string& codigo, string nombre_archivo) {
    ifstream archivo(nombre_archivo);
    string linea;
    while (getline(archivo, linea)) {
        size_t pos = linea.find(','); // Busca la primera coma (el c�digo est� antes de la primera coma)
        if (pos != string::npos && linea.substr(0, pos) == codigo) {
            return true; // El c�digo ya existe
        }
    }
    return false; // El c�digo no existe
}

// Funcion para generar un codigo unico
string generar_codigo_unico(string prefijo, string nombre_archivo) {
    string codigo;
    do {
        codigo = generar_codigo(prefijo); // Genera un codigo aleatorio
    } while (codigo_existe(codigo, nombre_archivo));   // Verifica que no exista en el archivo
    return codigo;
}

// Funcion que verifica si una cadena representa un n�mero entero v�lido
bool es_numerico(const string& numero) {
    if (numero.empty()) return false; // Cadena vac�a no es num�rica

    size_t inicio = 0;

    // Permitir un signo '+' o '-' al inicio
    if (numero[0] == '+' || numero[0] == '-') {
        if (numero.size() == 1) return false; // Solo un signo no es v�lido
        inicio = 1; // Saltamos el primer car�cter
    }

    // Verificar que el resto de caracteres sean d�gitos
    for (size_t i = inicio; i < numero.size(); i++) {
        if (!isdigit(numero[i])) return false;
    }
    return true;
}

// Funci�n que convierte una cadena a n�mero entero
int convertir_numero(const string& numero) {
    if (!es_numerico(numero)) return -1; // Si no es num�rico, retorna -1
    try {
        return stoi(numero); // Convierte el n�mero
    } catch (const out_of_range&) {
        return -1; // Si el n�mero es demasiado grande o peque�o para int, retorna -1
    }
}

int leer_int(const string& mensaje) {
    string valor;
    int convertido;

    while (true) {
        cout << mensaje;
        cin >> valor;

        // Limpiar el buffer después de usar cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (es_numerico(valor)) {
            convertido = convertir_numero(valor);
            return convertido;
        }

        cout << "Error: Entrada no valida. Debe ingresar un numero entero. Intente de nuevo.\n";
        cin.clear(); // Limpia el estado de error de cin
    }
}

bool validar_id_registro(const string& id) {
    if (id.length() != 9) return false; // Verifica la longitud
    for (char c : id) {
        if (!isdigit(c)) return false; // Verifica que todos los caracteres sean d�gitos
    }
    return true;
}

void ingresar_auto(){
    string codigo = generar_codigo_unico("A", "AUTOS.TXT");
    string nombre;
    int velocidad;
    int caballos_fuerza;
    string equipo;
    int costo;
    string id_registro;
    system("cls");
    mostrar_banner("INGRESAR AUTO A INVENTARIO");
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

    if (validacion_continuar ("Esta seguro de que desea registrar este auto? (S/N): ")){
        guardar_auto(nuevo_auto);
    } else {
        return;
    }
}

void modificar_auto() {
    mostrar_banner("MODIFICAR AUTO EN INVENTARIO");

    string codigo_busqueda = leer_string("Ingrese el codigo del auto a modificar: ");
    Auto auto_encontrado = buscar_auto(codigo_busqueda);

    if (auto_encontrado.getCodigoAuto().empty()) {
        cout << "No se encontro un auto con el codigo " << codigo_busqueda << "." << endl;
        if (validacion_continuar("Desea intentar de nuevo? (S/N): ")) {
            modificar_auto(); // Volver a intentar
        }
        return;
    }

    mostrar_banner("Datos del Auto Encontrado");
    auto_encontrado.mostrarInformacion();

    if (validacion_continuar("Desea modificar la velocidad maxima y los caballos de fuerza? (S/N): ")) {
        int nueva_velocidad = leer_int("Nueva velocidad maxima (km/h): ");
        int nuevos_caballos_fuerza = leer_int("Nuevos caballos de fuerza (HP): ");

        // Actualizar el auto
        auto_encontrado.setVelocidadMaxima(nueva_velocidad);
        auto_encontrado.setCaballosFuerza(nuevos_caballos_fuerza);

        // Actualizar el archivo
        ifstream archivo_lectura("AUTOS.TXT");
        vector<string> lineas_archivo;
        string linea;

        while (getline(archivo_lectura, linea)) {
            size_t pos = linea.find(',');
            if (pos != string::npos && linea.substr(0, pos) == codigo_busqueda) {
                // Reemplazar la línea con los nuevos valores
                string nueva_linea = auto_encontrado.getCodigoAuto() + "," +
                                     auto_encontrado.getNombreAuto() + "," +
                                     to_string(auto_encontrado.getVelocidadMaxima()) + "," +
                                     to_string(auto_encontrado.getCaballosFuerza()) + "," +
                                     auto_encontrado.getEquipoPropietario() + "," +
                                     to_string(auto_encontrado.getCostoAuto()) + "," +
                                     auto_encontrado.getIdRegistrador();
                lineas_archivo.push_back(nueva_linea);
            } else {
                lineas_archivo.push_back(linea); // Mantener las otras líneas sin cambios
            }
        }
        archivo_lectura.close();

        // Escribir todas las líneas en el archivo
        ofstream archivo_escritura("AUTOS.TXT");
        for (const string& l : lineas_archivo) {
            archivo_escritura << l << endl;
        }
        archivo_escritura.close();

        mostrar_banner("Los datos han sido actualizados exitosamente.");
        auto_encontrado.mostrarInformacion();
    }

    if (validacion_continuar("Desea volver al menu principal? (S/N): ")) {
        menu(); // Volver a modificar otro auto
    }else{
        modificar_auto();
    }
}

void eliminar_auto() {
    mostrar_banner("ELIMINAR AUTO DEL INVENTARIO");

    string codigo_busqueda = leer_string("Ingrese el codigo del auto a eliminar: ");
    Auto auto_encontrado = buscar_auto(codigo_busqueda);

    if (auto_encontrado.getCodigoAuto().empty()) {
        cout << "No se encontro un auto con el codigo " << codigo_busqueda << "." << endl;
        if (validacion_continuar("Desea intentar de nuevo? (S/N): ")) {
            eliminar_auto(); // Volver a intentar
        }
        return;
    }

    mostrar_banner("Datos del Auto Encontrado");
    auto_encontrado.mostrarInformacion();

    if (validacion_continuar("Esta seguro de que desea eliminar este auto? (S/N): ")) {
        ifstream archivo_lectura("AUTOS.TXT");
        vector<string> lineas_archivo;
        string linea;

        while (getline(archivo_lectura, linea)) {
            size_t pos = linea.find(',');
            if (pos == string::npos || linea.substr(0, pos) != codigo_busqueda) {
                lineas_archivo.push_back(linea); // Guardar todas las líneas excepto la del auto a eliminar
            }
        }
        archivo_lectura.close();

        // Escribir todas las líneas en el archivo
        ofstream archivo_escritura("AUTOS.TXT");
        for (const string& l : lineas_archivo) {
            archivo_escritura << l << endl;
        }
        archivo_escritura.close();

        cout << "Auto eliminado exitosamente." << endl;
    } else {
        cout << "Eliminacion cancelada." << endl;
    }

    if (validacion_continuar("Desea volver al menu principal? (S/N): ")) {
        menu();
    } else {
        eliminar_auto();
    }
}

int seleccionar_opcion(const vector<string>& opciones, int min, int max) {
    bool continuar = true;
    string entrada;
    int opcion = -1;

    while (continuar) {
        // Mostrar las opciones
        cout << "Seleccione una opcion (" << min << "-" << max << "): " << endl;
        for (size_t i = 0; i < opciones.size(); i++) {
            cout << (i + 1) << ". " << opciones[i] << endl;
        }
        cout << "Seleccione una opcion: ";
        cin >> entrada;

        // Verificar si la entrada es numérica
        if (es_numerico(entrada)) {
            opcion = convertir_numero(entrada);

            // Verificar si la opcion está dentro del rango válido
            if (verifica_rango(opcion, min, max)) {
                continuar = false; // Salir del bucle
            } else {
                cout << "Opcion fuera de rango. Intente de nuevo." << endl;
            }
        } else {
            cout << "Entrada inválida. Debe ser un número." << endl;
        }
    }
    return opcion; // Retorna la opcion seleccionada
}

void menu_autos(){
    bool continuar = true;
    int opcion_ingresada_num = 0;
    string opcion_ingresada = "";
    while(continuar){
        system("cls");
        cout << "=============================" << endl;
        vector<string> opciones = {
            "Ingresar auto al inventario.",
            "Consultar auto del inventario",
            "Modificar auto del inventario",
            "Eliminar auto del inventario",
            "Salir del menu"
        };
        opcion_ingresada_num = seleccionar_opcion(opciones, 1, 5);
        cout << "=============================" << endl;
            
        switch (opcion_ingresada_num){
            case 1:{
                ingresar_auto();
                break;
            }
            case 2:{
                consultar_autos();
                break;
            }
            case 3:{
                modificar_auto();
                break;
            }
            case 4:{
                eliminar_auto();
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
}

bool esFechaValida(const string& fecha) {
    // Expresion regular para verificar el formato DD/MM/YYYY
    regex formato(R"(\d{2}/\d{2}/\d{4})");
    if (!regex_match(fecha, formato)) {
        return false; // El formato no coincide
    }

    // Extraer día, mes y año
    int dia, mes, anio;
    char separador;
    istringstream ss(fecha);
    ss >> dia >> separador >> mes >> separador >> anio;

    // Verificar si la fecha es válida
    if (mes < 1 || mes > 12) return false; // Mes inválido
    if (dia < 1 || dia > 31) return false; // Día inválido

    // Verificar meses con 30 días
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        return false;
    }

    // Verificar febrero y años bisiestos
    if (mes == 2) {
        bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        if (dia > 29 || (dia == 29 && !esBisiesto)) {
            return false;
        }
    }

    return true; // La fecha es válida
}


void guardar_competencia(const Competencia& nueva_competencia) {
    ofstream archivo("COMPETENCIAS.txt", ios::app); // Abre el archivo en modo append
    if (archivo.is_open()) {
        archivo << nueva_competencia.getCodigoCompetencia()
        << "," << nueva_competencia.getCodigoAuto1()
        << "," << nueva_competencia.getCodigoAuto2()
        << "," << nueva_competencia.getCategoriaCarrera()
        << "," << nueva_competencia.getFechaCompetencia()
        << "," << nueva_competencia.getEstadoCompetencia()
        << ","<< nueva_competencia.getGanador() << endl;
        archivo.close();
    } else {
        cout << "Error: No se pudo abrir el archivo COMPETENCIAS.TXT." << endl;
        if (validacion_continuar ("Desea volver a intentarlo? (S/N): ")){
            guardar_competencia(nueva_competencia);
        } else {
            return;
        }
    }
}

void incribir_competencia() {
    string codigo = generar_codigo_unico("C", "COMPETENCIAS.txt");
    string auto1;
    string auto2;
    bool existe = true;
    int categoria;
    string fecha;
    int estado;
    string ganador;

    mostrar_banner("REGISTRO DE AUTO A COMPETENCIA");

    cout << endl;
    cout << "Generando codigo de Competencia unico... " << codigo << endl;

    do {
        string codigo_auto1 = leer_string("Ingrese el codigo de auto 1: ");
        Auto auto_busqueda = buscar_auto(codigo_auto1);
        if (auto_busqueda.getCodigoAuto() != "") {
            auto1 = auto_busqueda.getCodigoAuto();
            existe = true;
        } else {
            cout << "No existe auto registrado con este codigo." << endl;
            cout << "Intente de nuevo." << endl;
            existe = false;
        }
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while(!existe);

    existe = true;

    do {
        string codigo_auto2 = leer_string("Ingrese el codigo de auto 2: ");
        Auto auto_busqueda = buscar_auto(codigo_auto2);
        if (auto_busqueda.getCodigoAuto() != "") {
            auto2 = auto_busqueda.getCodigoAuto();
            existe = true;
        } else {
            cout << "No existe auto registrado con este codigo." << endl;
            cout << "Intente de nuevo." << endl;
            existe = false;
        }
    } while(!existe);

    vector<string> categorias = {"Sprint", "Endurance", "Drift"};
    categoria = seleccionar_opcion(categorias, 1, 3);

    while (true) {
        cout << "Ingrese la fecha de la competencia (DD/MM/YYYY): ";
        cin >> fecha;

        // Limpiar el buffer después de usar cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (esFechaValida(fecha)) {
            break;
        } else {
            cout << "Formato de fecha incorrecto o fecha invalida. Por favor, use el formato DD/MM/YYYY." << endl;
        }
    }

    vector<string> estados = {"En proceso", "Cancelada", "Finalizada"};
    estado = seleccionar_opcion(estados, 1, 3);

    if (estado == 3) {
        do {
            cout << "Codigo de Auto 1: " << auto1 << endl;
            cout << "Codigo de Auto 2: " << auto2 << endl;

            ganador = leer_string("Seleccione un ganador: ");
            if (ganador != auto1 && ganador != auto2) {
                cout << "El auto seleccionado no compitio. " << endl;
                cout << "Seleccione una opcion valida. " << endl;
            } else {
                break;
            }
        } while(true);
    }else{
        ganador = "-";
    }

    Competencia nueva_competencia (codigo, auto1, auto2, categorias[categoria-1], fecha, estados[estado-1], ganador);

    mostrar_banner("La inscripcion ha sido exitosa.");
    cout << "" << endl;
    cout << "La competencia ha sido registada en COMPENTENCIAS.TXT" << endl;
    cout << "" << endl;
    nueva_competencia.mostrarInformacion();
    guardar_competencia(nueva_competencia);
    cout << "================================================"<< endl;

    if(validacion_continuar("Desea volver al menu principal? (S/N)")){
        menu();
    }else{
        menu_competencias();
    }
}

void consultar_competencia(){

}

void menu_competencias(){
    bool continuar = true;
    int opcion_ingresada_num = 0;
    while(continuar){
        system("cls");
        vector<string> opciones = {
            "Inscribir auto en competencia",
            "Consultar competencia",
            "Salir del programa"
        };
        opcion_ingresada_num = seleccionar_opcion(opciones, 1, 3);
        switch (opcion_ingresada_num){
            case 1:{
                incribir_competencia();
                break;
            }
            case 2:{
                consultar_competencia();
                break;
            }
            default:{
                cout << "Ingrese una opcion correcta. (1-2)" << endl;
            }
        }
    }
}

void menu(){
    bool continuar = true;
    int opcion_ingresada_num = 0;
    string opcion_ingresada = "";
    while(continuar){
        system("cls");
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
                    menu_competencias();
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
    menu();
    return 0;
}
