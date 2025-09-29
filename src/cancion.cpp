#include "cancion.hpp"
#include <sstream>

Cancion::Cancion(): nombre(""), autor(""), interprete(""), ranking(0), archivoMP3("") {}

Cancion::Cancion(const std::string& n, const std::string& a, const std::string& i, const int& r, const std::string& archivo)
    : nombre(n), autor(a), interprete(i), ranking(r), archivoMP3(archivo) {}

Cancion::Cancion(const Cancion& other)
    : nombre(other.nombre), autor(other.autor), interprete(other.interprete), 
      ranking(other.ranking), archivoMP3(other.archivoMP3) {}

void Cancion::setNombre(const std::string& n) {
    nombre = n;
}

void Cancion::setAutor(const std::string& a) {
    autor = a;
}

void Cancion::setInterprete(const std::string& i) {
    interprete = i;
}

void Cancion::setRanking(const int& r) {
    ranking = r;
}

void Cancion::setArchivoMP3(const std::string& archivo) {
    archivoMP3 = archivo;
}

std::string Cancion::getNombre() const {
    return nombre;
}

std::string Cancion::getAutor() const {
    return autor;
}

std::string Cancion::getInterprete() const {
    return interprete;
}

int Cancion::getRanking() const {
    return ranking;
}

std::string Cancion::getArchivoMP3() const {
    return archivoMP3;
}

std::string Cancion::toString() const {
    std::ostringstream oss;
    oss << "Cancion: " << nombre 
        << ", Autor: " << autor 
        << ", Interprete: " << interprete 
        << ", Ranking: " << ranking
        << ", Archivo MP3: " << archivoMP3;
    return oss.str();
}

bool Cancion::operator==(const Cancion& other) const {
    return nombre == other.nombre && autor == other.autor && interprete == other.interprete;
}

Cancion& Cancion::operator=(const Cancion& other) {
    if (this != &other) {
        nombre = other.nombre;
        autor = other.autor;
        interprete = other.interprete;
        ranking = other.ranking;
        archivoMP3 = other.archivoMP3;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Cancion& c) {
    os << c.nombre << std::endl;
    os << c.autor << std::endl;
    os << c.interprete << std::endl;
    os << c.ranking << std::endl;
    os << c.archivoMP3 << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Cancion& c) {
    std::string temp_ranking;
    
    std::getline(is, c.nombre);
    std::getline(is, c.autor);
    std::getline(is, c.interprete);
    std::getline(is, temp_ranking);
    std::getline(is, c.archivoMP3);

    if (!c.nombre.empty()) {
        try {
            c.ranking = std::stoi(temp_ranking);
        } catch(const std::invalid_argument& e) {
            c.ranking = 0;
        }
    }
    return is;
}

int compararPorNombre(const Cancion& a, const Cancion& b) {
    if (a.getNombre() < b.getNombre()) return -1;
    if (a.getNombre() > b.getNombre()) return 1;
    return 0;
}

int compararPorInterprete(const Cancion& a, const Cancion& b) {
    if (a.getInterprete() < b.getInterprete()) return -1;
    if (a.getInterprete() > b.getInterprete()) return 1;
    return 0;
}

int compararPorAutor(const Cancion& a, const Cancion& b) {
    if (a.getAutor() < b.getAutor()) return -1;
    if (a.getAutor() > b.getAutor()) return 1;
    return 0;
}

int compararPorRanking(const Cancion& a, const Cancion& b) {
    if (a.getRanking() < b.getRanking()) return -1;
    if (a.getRanking() > b.getRanking()) return 1;
    return 0;
}