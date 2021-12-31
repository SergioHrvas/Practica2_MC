#include "conjunto.h"


/*************************************************
------------------SeriePelicula-------------------
*************************************************/
//seters
void PeliculaSerie::setTitulo(string title)
{
    titulo = title;
}

void PeliculaSerie::setPais(string p)
{
    pais = p;
}

void PeliculaSerie::setTemporadas(int temp)
{
    temporadas = temp;
}

void PeliculaSerie::setHoras(int h)
{
    horas = h;
}

void PeliculaSerie::setMinutos(int min)
{
    minutos = min;
}

void PeliculaSerie::setNota(double n)
{
    nota = n;
}
void PeliculaSerie::setesPelicula(bool esPeli)
{
    esPelicula = esPeli;
}

//geters
string PeliculaSerie::getTitulo() const
{
    return titulo;
}

string PeliculaSerie::getPais() const
{
    return pais;
}

int PeliculaSerie::getTemporadas() const
{
    return temporadas;
}

int PeliculaSerie::getHoras() const
{
    return horas;
}

int PeliculaSerie::getMinutos() const
{
    return minutos;
}

double PeliculaSerie::getNota() const
{
    return nota;
}

bool PeliculaSerie::getesPelicula() const
{
    return esPelicula;
}

istream &operator>>(istream &in, PeliculaSerie &p)
{
    string texto = "Titulo de la serie: ";
    int tam = texto.size();
    string aux;

    //extraemos titulo
    getline(in, aux);
    aux.erase(0, tam);

    p.setTitulo(aux);

    getline(in, aux);

    if (aux[0] == 'D')
    { //extraemos duracion
        texto = "Duracion: ";

        aux.erase(0, texto.size());
        p.setesPelicula(true);

        char aux2[3];
        aux2[0] = aux[0];

        int horas = atoi(aux2);

        p.setHoras(horas);

        aux.erase(0, 1);

        auto it = aux.begin();

        while (*it < '0' or *it > '9')
        {
            ++it;
        }

        aux2[0] = *it;
        if (*(it + 1) >= '0' and *(it + 1) <= '9')
            aux2[1] = *(it + 1);

        int minutos = atoi(aux2);

        p.setMinutos(minutos);
    }
    else if (aux[0] == 'T')
    { //extraemos temporadas
        texto = "Temporadas: ";

        aux.erase(0, texto.size());
        p.setesPelicula(false);

        char aux2[2];
        aux2[0] = aux[0];

        if (aux.size() == 2)
            aux2[1] = aux[1];

        int temporadas = atoi(aux2);

        p.setTemporadas(temporadas);
    }

    texto = "Nota: ";
    tam = texto.size();

    //extraemos nota
    getline(in, aux);
    aux.erase(0, tam);
    p.setNota(atof(aux.c_str()));

    //extraemos pais
    texto = "Pais: ";
    tam = texto.size();

    //extraemos pais
    getline(in, aux);
    aux.erase(0, tam);
    p.setPais(aux);

    return in;
}

ostream &operator<<(ostream &out, const PeliculaSerie &p)
{
    out << "Titulo de la serie: " << p.titulo << endl;

    if (p.getesPelicula())
    {
        string hora = " hora";
        string minuto = " minutos";

        if (p.getHoras() > 1)
            hora += "s";

        if (p.getMinutos() > 1)
            minuto += "s";

        out << "Duracion: " << p.getHoras() << hora << " y " << p.getMinutos() << minuto << endl;
    }

    else
        out << "Temporadas: " << p.getTemporadas() << endl;

    out << "Nota: " << p.getNota() << endl;
    out << "Pais: " << p.getPais() << endl;

    return out;
}

/*************************************************
-------------ConjuntoSeriesPeliculas--------------
*************************************************/


istream &operator>>(istream &in, ConjuntoPeliculaSeries &p){
    string aux;
    PeliculaSerie aux2;

    //getline(in, aux);

    do{
        in>>aux2;

        p.add(aux2);
        
        getline(in, aux);
    }while(aux=="********************" and (char)in.peek()!='F');

    return in;
}

ostream &operator<<(ostream &out, const ConjuntoPeliculaSeries &p){
    for(auto it=p.series.cbegin(); it!=p.series.cend(); ++it){
        out<<*it;
        out<<"********************" <<endl;
    }

    for(auto it=p.peliculas.cbegin(); it!=p.peliculas.cend(); ++it){
        out<<*it;
        out<<"********************"<< endl;
    }
    out<<"FIN" <<endl;
    //cout << "Nota Media Series: " << p.getNotaMediaSeries() <<endl << "Nota Media Peliculas: "<< p.getNotaMediaPeliculas() << endl << "Nota media: " << p.getNotaMedia();

    //cout <<"size: " <<p.series.size()+p.peliculas.size()<<endl;
    return out;
}

void ConjuntoPeliculaSeries::add(const PeliculaSerie & p){
    if(p.getesPelicula())
        peliculas.push_back(p);

    else
        series.push_back(p);
}

double ConjuntoPeliculaSeries::getNotaMediaSeries() const{
    double suma = 0;
    int contador = 0;
    for(auto it = series.cbegin(); it != series.cend(); ++it){
        suma += (*it).getNota();
        contador++;
    }
    suma = suma / contador;

    return suma;

}

double ConjuntoPeliculaSeries::getNotaMediaPeliculas() const{
    double suma = 0;
    int contador = 0;
    for(auto it = peliculas.cbegin(); it != peliculas.cend(); ++it){
        suma += (*it).getNota();
        contador++;
    }
    suma = suma / contador;

    return suma;

}

double ConjuntoPeliculaSeries::getNotaMedia() const{
    double media = (getNotaMediaPeliculas() + getNotaMediaSeries())/2;
    return media;

}