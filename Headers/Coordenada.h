#ifndef __COORDENADA_H__
#define __COORDENADA_H__

class Coordenada{
    private:
    int x;
    int y;

    public:
    Coordenada(int x, int y);

    int getX();
    int getY();
    Coordenada getCoordenada();

    void setX(int x);
    void setY(int y);
    void setCoordenada(int x, int y);

    bool operator==(const Coordenada& c) const;
    bool operator!=(const Coordenada& c) const;
    
    void operator>>(Coordenada& c);
    void operator<<(Coordenada& c);
};

#endif