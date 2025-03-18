#ifndef AUTO_H
#define AUTO_H

#include <string>

class Auto {
private:
    std::string codigoAuto;
    std::string nombreAuto;
    int velocidadMaxima;
    int caballosFuerza;
    std::string equipoPropietario;
    int costoAuto;
    std::string idRegistrador;

public:
    // Declaración del constructor
    Auto(std::string codigo, std::string nombre, int velocidad, int hp, std::string equipo, int costo, std::string idRegistrador);

    // Getters
    std::string getCodigoAuto() const;
    std::string getNombreAuto() const;
    int getVelocidadMaxima() const;
    int getCaballosFuerza() const;
    std::string getEquipoPropietario() const;
    int getCostoAuto() const;
    std::string getIdRegistrador() const;

    // Setters
    void setCodigoAuto(const std::string& codigo);
    void setNombreAuto(const std::string& nombre);
    void setVelocidadMaxima(int velocidad);
    void setCaballosFuerza(int hp);
    void setEquipoPropietario(const std::string& equipo);
    void setCostoAuto(int costo);
    void setIdRegistrador(const std::string& id);

    // Método para mostrar la información del auto
    void mostrarInformacion() const;
};

#endif // AUTO_H
