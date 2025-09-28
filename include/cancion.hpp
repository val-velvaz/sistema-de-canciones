#ifndef _CANCION_HPP_
#define _CANCION_HPP_

#include <string>
#include <iostream>

class Cancion {
private:
    std::string nombre;
    std::string autor;
    std::string interprete;
    int ranking;
    std::string archivoMP3;

public:
    Cancion();
    Cancion(const std::string&, const std::string&, const std::string&, const int&, const std::string&);
    Cancion(const Cancion&);

    void setNombre(const std::string&);
    void setAutor(const std::string&);
    void setInterprete(const std::string&);
    void setRanking(const int&);
    void setArchivoMP3(const std::string&);

    std::string getNombre() const;
    std::string getAutor() const;
    std::string getInterprete() const;
    int getRanking() const;
    std::string getArchivoMP3() const;

    std::string toString() const;

    Cancion& operator=(const Cancion&);
    bool operator==(const Cancion&) const;

    friend std::ostream& operator<<(std::ostream& os, const Cancion& c);
    friend std::istream& operator>>(std::istream& is, Cancion& c);
};

// Funciones de comparación globales
int compararPorNombre(const Cancion& a, const Cancion& b);
int compararPorInterprete(const Cancion& a, const Cancion& b);
int compararPorAutor(const Cancion& a, const Cancion& b);
int compararPorRanking(const Cancion& a, const Cancion& b);

#endif