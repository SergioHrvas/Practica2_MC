#ifndef CONJUNTO_H
#define CONJUNTO_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class PeliculaSerie
{
    /**
     * titulo, pais, temporadas, duracion, nota
     * 
     */

private:
    string titulo;
    string pais;
    int temporadas = -1;
    int horas = -1, minutos = -1;
    double nota = -1;

    bool esPelicula = false;

public:
    PeliculaSerie() = default;
    PeliculaSerie(string nombre)
    {
        ifstream file(nombre);

        if (!file)
            exit(-1);

        file >> *this;

        file.close();
    }

    //seters
    void setTitulo(string title);
    void setPais(string p);
    void setTemporadas(int temp);
    void setHoras(int h);
    void setMinutos(int min);
    void setNota(double n);
    void setesPelicula(bool esPeli);

    //geters
    string getTitulo() const;
    string getPais() const;
    int getTemporadas() const;
    int getHoras() const;
    int getMinutos() const;
    double getNota() const;
    bool getesPelicula() const;

    friend istream &operator>>(istream &in, PeliculaSerie &p);
    friend ostream &operator<<(ostream &out, const PeliculaSerie &p);
};

istream &operator>>(istream &in, PeliculaSerie &p);
ostream &operator<<(ostream &out, const PeliculaSerie &p);

class ConjuntoPeliculaSeries
{
private:
    vector<PeliculaSerie> series;
    vector<PeliculaSerie> peliculas;

public:
    ConjuntoPeliculaSeries() = default;
    ConjuntoPeliculaSeries(string nombre = "tmp3")
    {
        ifstream file(nombre);

        if (!file)
            exit(-1);

        file >> *this;
    }
    enum Ordena
    {
        NOTA,
        DURACION,
        PAIS,
        TITULO,
        TEMPORADAS
    };
    
    const PeliculaSerie &operator[](int i) const;
    PeliculaSerie &operator[](int i);

    vector<PeliculaSerie> ordenarPor(Ordena valor);
    void add(const PeliculaSerie &p);
    double getNotaMediaSeries() const;
    double getNotaMediaPeliculas() const;
    double getNotaMedia() const;

    friend istream &operator>>(istream &in, ConjuntoPeliculaSeries &p);
    friend ostream &operator<<(ostream &out, const ConjuntoPeliculaSeries &p);
};

istream &operator>>(istream &in, ConjuntoPeliculaSeries &p);
ostream &operator<<(ostream &out, const ConjuntoPeliculaSeries &p);

#endif