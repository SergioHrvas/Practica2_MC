#include <iostream>
#include <fstream>
#include <string>
#include "conjunto.h"

using namespace std;

int main(int argc, char **argv)
{
    int nro, numPag = 0;

    do
    {
        cout << "Numeros de paginas a mostrar: ";
        cin >> nro;

        if (nro < 0)
            cout << "El numero debe ser positivo" << endl;
    } while (nro < 0);

    if (nro == 1)
    {

        do
        {

            cout << "Numero de pagina a visualizar: ";
            cin >> numPag;

            if (numPag < 0)
                cout << "El numero debe ser positivo" << endl;
        } while (numPag < 0);
    }

    for (int i = 0; i < 40 * nro; i += 40)
    {
        //curl de la pagina principal
        string comando;

        if (nro == 1)
        {
            comando = "curl -s https://playmax.mx/explorar.php?start=" + to_string((numPag - 1) * 40) + " | ./bin/extractorurls > tmp";
            system(comando.c_str());
        }
        else
        {
            comando = "curl -s https://playmax.mx/explorar.php?start=" + to_string(i) + " | ./bin/extractorurls > tmp";
            system(comando.c_str());
        }
        ifstream file("tmp");

        while (file)
        {
            string aux;
            file >> aux;

            if (aux[0] == 'h')
            {
                comando = "curl -s " + aux + " > tmp2";

                system(comando.c_str());
                //comando = "./bin/series < tmp2 | tee -a tmp3";
                comando = "./bin/series < tmp2 >> tmp3";

                system(comando.c_str());

                //********************
            }
        }

        //llamar al programa lex con esa salida de antes para que detecte urls de pelis y series -> las vuelca en un archivo
        //for de cada linea de ese archivo (enlace1, enlace2...) ejecutando el programa principal
        //una
        file.close();
    }
    system("echo FIN >> tmp3");

    ConjuntoPeliculaSeries p("tmp3");
    cout << "****************************************\n\nSalida primero las series y luego las pelis: " << endl
         << endl;

    cout << p;

    cout << "****************************************\n\nAhora se muestra por nota: " << endl
         << endl;

    vector<PeliculaSerie> aux = p.ordenarPor(ConjuntoPeliculaSeries::NOTA);

    for (auto it = aux.cbegin(); it != aux.cend(); ++it)
    {
        cout << *it << endl;
    }

    aux.clear();

    cout << "****************************************\n\nAhora se muestra por duracion: " << endl
         << endl;

    aux = p.ordenarPor(ConjuntoPeliculaSeries::DURACION);

    for (auto it = aux.cbegin(); it != aux.cend(); ++it)
    {
        cout << *it << endl;
    }

    aux.clear();

    cout << "****************************************\n\nAhora se muestra por pais: " << endl
         << endl;

    aux = p.ordenarPor(ConjuntoPeliculaSeries::PAIS);

    for (auto it = aux.cbegin(); it != aux.cend(); ++it)
    {
        cout << *it << endl;
    }

    aux.clear();

    cout << "****************************************\n\nAhora se muestra por titulo: " << endl
         << endl;

    aux = p.ordenarPor(ConjuntoPeliculaSeries::TITULO);

    for (auto it = aux.cbegin(); it != aux.cend(); ++it)
    {
        cout << *it << endl;
    }

    aux.clear();

    cout << "****************************************\n\nAhora se muestra por temporadas: " << endl
         << endl;

    aux = p.ordenarPor(ConjuntoPeliculaSeries::TEMPORADAS);

    for (auto it = aux.cbegin(); it != aux.cend(); ++it)
    {
        cout << *it << endl;
    }

    aux.clear();

    system("rm tmp tmp2 tmp3");

    return 0;
}