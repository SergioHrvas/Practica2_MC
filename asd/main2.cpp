#include <iostream>
#include <fstream>
#include <string>

using namespace std;



int main(){
    //curl de la pagina principal
    system("curl -s https://playmax.mx/explorar.php?start=40 | ../bin/extractorurls > tmp");

    ifstream file("tmp");

    while(file){
        string aux;
        file>>aux;
        
    
        string comando="curl -s "+aux+" > tmp2";

        system(comando.c_str());
        comando="../bin/series < tmp2";
        
        system(comando.c_str());
        
        cout <<endl;
    }
    //llamar al programa lex con esa salida de antes para que detecte urls de pelis y series -> las vuelca en un archivo 
    //for de cada linea de ese archivo (enlace1, enlace2...) ejecutando el programa principal 
    //una


    system("rm tmp tmp2");

    return 0;
}