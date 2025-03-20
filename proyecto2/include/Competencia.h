#ifndef COMPETENCIA_H
#define COMPETENCIA_H

#include <string>

class Competencia {
private:
    std::string codigoCompetencia;  // Formato: C00000000
    std::string codigoAuto1;
    std::string codigoAuto2;
    std::string categoriaCarrera;  // Sprint, Endurance, Drift
    std::string fechaCompetencia;  // Formato: DD/MM/YYYY
    std::string estadoCompetencia; // En proceso, Cancelada, Finalizada
    std::string ganador;           // Solo si el estado es "Finalizada"

public:
    // Constructor
    Competencia(std::string codigoCompetencia, std::string codigoAuto1, std::string codigoAuto2,
                std::string categoriaCarrera, std::string fechaCompetencia, std::string estadoCompetencia,
                std::string ganador = "");

    // Getters
    std::string getCodigoCompetencia() const;
    std::string getCodigoAuto1() const;
    std::string getCodigoAuto2() const;
    std::string getCategoriaCarrera() const;
    std::string getFechaCompetencia() const;
    std::string getEstadoCompetencia() const;
    std::string getGanador() const;

    // Setters
    void setCodigoCompetencia(const std::string& codigo);
    void setCodigoAuto1(const std::string& codigo);
    void setCodigoAuto2(const std::string& codigo);
    void setCategoriaCarrera(const std::string& categoria);
    void setFechaCompetencia(const std::string& fecha);
    void setEstadoCompetencia(const std::string& estado);
    void setGanador(const std::string& ganador);

    // Método para mostrar información
    void mostrarInformacion() const;
};

#endif // COMPETENCIA_H
