
%{
#include <stdio.h>
%}

car [a-zA-Z]
digito [0-9]
signo (\-|\+)
suc ({digito}+)
enter ({signo}?{suc})
real1 ({enter}\.{digito}*)
real2 ({signo}?\.{suc})
    int ent=0, real=0, ident=0, sumaent=0;
%%
    int i;
{enter}     {ent++; sscanf(yytext,"%d",&i); sumaent += i; printf("Numero entero%s\n",yytext);}
({real1}|{real2})   {real++; printf("Num. real%s\n",yytext);}
{car}({car}|{digito})* {ident++; printf("Var. ident.%s\n",yytext);}
.|\n {;}
%%
int yywrap()
{printf("Numero de Enteros%d, reales%d, ident%d,Suma de Enteros%d",ent,real,ident,sumaent); return 1;}

int main(){
    archivo = fopen("salida.txt");
    if(archivo.is_open()){
        archivo << "traduccion" << endl;

    }
    else cerr << "Error de apertura" << endl;


}