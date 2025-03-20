#include "Competencia.h"
#include <iostream>

// Constructor
Competencia::Competencia(std::string codigoCompetencia, std::string codigoAuto1, std::string codigoAuto2,
                         std::string categoriaCarrera, std::string fechaCompetencia, std::string estadoCompetencia,
                         std::string ganador)
    : codigoCompetencia(codigoCompetencia), codigoAuto1(codigoAuto1), codigoAuto2(codigoAuto2),
      categoriaCarrera(categoriaCarrera), fechaCompetencia(fechaCompetencia), estadoCompetencia(estadoCompetencia),
      ganador(ganador) {}

// Getters
std::string Competencia::getCodigoCompetencia() const { return codigoCompetencia; }
std::string Competencia::getCodigoAuto1() const { return codigoAuto1; }
std::string Competencia::getCodigoAuto2() const { return codigoAuto2; }
std::string Competencia::getCategoriaCarrera() const { return categoriaCarrera; }
std::string Competencia::getFechaCompetencia() const { return fechaCompetencia; }
std::string Competencia::getEstadoCompetencia() const { return estadoCompetencia; }
std::string Competencia::getGanador() const { return ganador; }

// Setters
void Competencia::setCodigoCompetencia(const std::string& codigo) { codigoCompetencia = codigo; }
void Competencia::setCodigoAuto1(const std::string& codigo) { codigoAuto1 = codigo; }
void Competencia::setCodigoAuto2(const std::string& codigo) { codigoAuto2 = codigo; }
void Competencia::setCategoriaCarrera(const std::string& categoria) { categoriaCarrera = categoria; }
void Competencia::setFechaCompetencia(const std::string& fecha) { fechaCompetencia = fecha; }
void Competencia::setEstadoCompetencia(const std::string& estado) { estadoCompetencia = estado; }
void Competencia::setGanador(const std::string& ganador) {
    if (estadoCompetencia == "Finalizada") {
        this->ganador = ganador;
    } else {
        this->ganador = "";
    }
}

// Método para mostrar información
void Competencia::mostrarInformacion() const {
    std::cout << "Codigo de Competencia: " << codigoCompetencia << std::endl;
    std::cout << "Codigo de Auto 1: " << codigoAuto1 << std::endl;
    std::cout << "Codigo de Auto 2: " << codigoAuto2 << std::endl;
    std::cout << "Categoria de la Carrera: " << categoriaCarrera << std::endl;
    std::cout << "Fecha de la Competencia: " << fechaCompetencia << std::endl;
    std::cout << "Estado de la Competencia: " << estadoCompetencia << std::endl;
    if (estadoCompetencia == "Finalizada") {
        std::cout << "Ganador: " << ganador << std::endl;
    }
}
