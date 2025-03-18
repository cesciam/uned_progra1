#include "Auto.h"
#include <iostream>

// Implementaci�n del constructor
Auto::Auto(std::string codigo, std::string nombre, int velocidad, int hp, std::string equipo, int costo, std::string idRegistrador)
    : codigoAuto(codigo), nombreAuto(nombre), velocidadMaxima(velocidad), caballosFuerza(hp), equipoPropietario(equipo), costoAuto(costo), idRegistrador(idRegistrador) {}

// Implementaci�n de los getters
std::string Auto::getCodigoAuto() const { return codigoAuto; }
std::string Auto::getNombreAuto() const { return nombreAuto; }
int Auto::getVelocidadMaxima() const { return velocidadMaxima; }
int Auto::getCaballosFuerza() const { return caballosFuerza; }
std::string Auto::getEquipoPropietario() const { return equipoPropietario; }
int Auto::getCostoAuto() const { return costoAuto; }
std::string Auto::getIdRegistrador() const { return idRegistrador; }

// Implementaci�n de los setters
void Auto::setCodigoAuto(const std::string& codigo) { codigoAuto = codigo; }
void Auto::setNombreAuto(const std::string& nombre) { nombreAuto = nombre; }
void Auto::setVelocidadMaxima(int velocidad) { velocidadMaxima = velocidad; }
void Auto::setCaballosFuerza(int hp) { caballosFuerza = hp; }
void Auto::setEquipoPropietario(const std::string& equipo) { equipoPropietario = equipo; }
void Auto::setCostoAuto(int costo) { costoAuto = costo; }
void Auto::setIdRegistrador(const std::string& id) { idRegistrador = id; }

// Implementaci�n del m�todo para mostrar la informaci�n del auto
void Auto::mostrarInformacion() const {
    std::cout << "C�digo de Auto: " << codigoAuto << std::endl;
    std::cout << "Nombre del Auto: " << nombreAuto << std::endl;
    std::cout << "Velocidad M�xima: " << velocidadMaxima << " km/h" << std::endl;
    std::cout << "Caballos de Fuerza: " << caballosFuerza << " HP" << std::endl;
    std::cout << "Equipo/Propietario: " << equipoPropietario << std::endl;
    std::cout << "Costo del Auto: $" << costoAuto << std::endl;
    std::cout << "ID del Registrador: " << idRegistrador << std::endl;
}
