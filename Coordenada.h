#ifndef __COORDENADA_H__
#define __COORDENADA_H__
#include <iostream>

class Coordenada{
    private:
    int x;
    int y;
    int z;

    public:
    Coordenada(int x, int y, int z);
    Coordenada(const Coordenada& c);

    int getX();
    int getY();
    int getZ();
    Coordenada* getCoordenada();

    void setX(int x);
    void setY(int y);
    void setZ(int Z);
    void setCoordenada(int x, int y, int z);

    friend std::ostream& operator<<(std::ostream& os, const Coordenada& c);
    friend std::istream& operator>>(std::istream& is, Coordenada& c);
    friend bool operator==(const Coordenada& c1, const Coordenada& c2);
    friend bool operator!=(const Coordenada& c1, const Coordenada& c2);

};

#endif