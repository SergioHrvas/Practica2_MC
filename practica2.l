%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void getTitulo(const char * texto, char * texto2);
int getTemporada(const char * texto);
void getPais(const char * texto, char * pais);


float getNota(const char *v){
    float valor;
    char aux[10];

    int terminado=0;
    
    for(int i=0; v[i]!='\0' && terminado==0; i++){
        if(v[i]>='0' && v[i]<='9'){
            int cont=0;
            int iAux=i;
            do{
                aux[cont++]=v[iAux++];
            }while((v[iAux]>='0' && v[iAux]<='9') || v[iAux]=='.');

            aux[cont++]='\0';

            terminado=1;
        }
    }
    
    valor=atof(aux);

    return valor;
}


%}
digitos [0-9]
letrasdigitos [a-zA-Zá-úÁ-Ú0-9]
caracteres [{}<>\,:]
espacio " "
title "var ficha_titulo = '"({letrasdigitos}|{espacio})+"';"
season "<span itemprop=\"numberOfSeasons\">"{digitos}+"</span>"
pais "<a href=\"./explorar.php?pais="{digitos}+"\" class=\"e_new\">"({letrasdigitos}|{espacio})+"</a>"

nota "<meta name=\"description\" content=\"Información, Trailers y Críticas | Valoración: "{digitos}{1,2}(\.{digitos})*" |"
      

    char i[1000],a[1000], pais[1000];
    float puntuacion=0.0;
    int temporadas = 0;
    char aux[1000];

%%

{title} {
    char vector[1000];
    //strcpy(a, yytext);

    getTitulo(yytext, i);
}
{season} {
    temporadas = getTemporada(yytext);
}

{nota} {
    puntuacion=getNota(yytext);
    strcpy(aux, yytext);
}

{pais} {
    getPais(yytext, pais);
}


%%
int yywrap()
{
    printf("Titulo de la serie: %s\n", i);
    printf("Temporadas: %d\n", temporadas);
    printf("Nota: %.1f\n", puntuacion);
    printf("Pais: %s\n", pais);

    return 1;

}
int main(){
    yylex();
}

void getTitulo(const char * texto, char *titulo){
    int terminado=0;
    for(int i=0; texto[i]!='\0' && terminado==0; i++){
        if(texto[i]=='\''){
            int contador=i+1;
            int contador2=0;
            do{
                titulo[contador2++]=texto[contador++];
            }while(texto[contador]!='\'');
            terminado = 1;
            titulo[contador2]='\0';
        }
    }
}


int getTemporada(const char * texto){
    char temporada[1000];
    int terminado=0;
    char inicio='>';
    char final='<';
    
    for(int i=0; texto[i]!='\0' && terminado==0; i++){
        if(texto[i]==inicio){
            int contador=i+1;
            int contador2=0;
            do{
                temporada[contador2++]=texto[contador++];
            }while(texto[contador]!=final);
            terminado = 1;
            temporada[contador2]='\0';
        }
    }

    int temp = atoi(temporada);
    return temp;
}

void getPais(const char * texto, char * pais){
    int terminado=0;
    char inicio='>';
    char final='<';
    int num_inicio = 0;
    
    for(int i=0; texto[i]!='\0' && terminado==0; i++){
        if(texto[i]==inicio){
            int contador=i+1;
            int contador2=0;
            do{
                pais[contador2++]=texto[contador++];
            }while(texto[contador]!=final);
            terminado = 1;
            pais[contador2]='\0';
        }
    }

}
     //<span><a href="./explorar.php?pais=1" class="e_new">Estados Unidos</a></span>
