%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void getURL(const char * texto, char * url);


%}
digitos [0-9]
letrasdigitos [a-zA-Zá-úÁ-Ú0-9]
caracteres [\-{}<>\,:\&]
espacio " "
url "3px;\">\n<a href=\"./"({letrasdigitos}|{caracteres})+"f"{digitos}+"\">"

    char i[1000];

%%

{url} {
    getURL(yytext, i);
    
    printf("%s", i);
}

%%
int yywrap()
{
    return 1;

}
int main(){
    yylex();
}





void getURL(const char * texto, char *url){
    url[0]='\0';
    int terminado=0;
    strcat(url, "https://playmax.mx/");
    
    int n=strlen(url);

    

    for(int i=0; texto[i]!='\0' && terminado==0; i++){
        if(texto[i]=='/'){
            int contador=i+1;
            int contador2=n;
            do{
                url[contador2++]=texto[contador++]; 
            }while(texto[contador]!='\"');
            terminado = 1;
            //url[contador2++]='\0';
            url[contador2++]='\n';
            url[contador2]='\0';
        }
    }
    
}
