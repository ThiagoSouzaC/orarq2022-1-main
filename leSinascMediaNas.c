// http://10.101.1.135:1234/sinasc.csv.gz
// http://10.101.1.135:1234/leSinasc.c
// Teresina = 221100
// Curitiba = 410690

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 2048

// index,CODMUNRES,data_nasc,PESO,SEMAGESTAC,adeq_peso_id_gestac,SEXO,IDANOMAL,RACACOR,ESCMAEAGR1,ESTCIVMAE,IDADEMAE,CONSULTAS,PARTO,STTRABPART,KOTELCHUCK,APGAR5,TPROBSON

struct DadosNascimento {
    int index;
    int CODMUNRES;
    char data_nasc[11];
    int PESO;
    int SEMAGESTAC;
    float adeq_peso_id_gestac;
    int SEXO;
    int IDANOMAL;
    int RACACOR;
    int ESCMAEAGR1;
    int ESTCIVMAE;
    int IDADEMAE;
    int CONSULTAS;
    int PARTO;
    int STTRABPART;
    int KOTELCHUCK;
    int APGAR5;
    int TPROBSON;
};

void separaData(char* data, int *dia, int *mes, int *ano)
{
    *ano = atoi(strtok(data,"-"));
    *mes = atoi(strtok(NULL,"-"));
    *dia = atoi(strtok(NULL,"-"));
}

float totalPesoTeresina = 0;
float totalPesoCuritiba = 0;
int contadorTeresina = 0;
int contadorCuritiba = 0;
int ano = 2014;

void processa(struct DadosNascimento* dn) {
    int dia, mes, ano;
    separaData(dn->data_nasc, &dia, &mes, &ano);

    printf("%d %d %d %d\n",dn->CODMUNRES, dia, mes, ano);
}


int main() {

    struct DadosNascimento dadosNas;
    static char buffer[MAX];
    char *prox = NULL;
    char* linha[18];
    int condicaoParada = 0;

    FILE *f = fopen("sinasc.csv","r");
    fgets(buffer,MAX,f);
    fgets(buffer,MAX,f);
    
    float totalPesoTeresina2014 = 0;
    float totalPesoCuritiba2014 = 0;
    int contadorTeresina2014 = 0;
    int contadorCuritiba2014 = 0;

    while(!feof(f)) {
        
        //strtok é uma função que divide uma string em substrings
        linha[0] = strtok_r(buffer, ",\n", &prox);

        for(int i = 1; i < 18; i ++) {

            linha[i] = strtok_r(NULL, ",\n", &prox);

            if(linha[i] == NULL) {
                linha[i] = "";
            }
        }
        
        int ano, mes, dia;
        separaData(linha[2], &dia, &mes, &ano);

        dadosNas.CODMUNRES = atoi(linha[1]);
        dadosNas.PESO = atoi(linha[3]);

        if (ano == 2014) {
            if (dadosNas.CODMUNRES == 221100) {  
                totalPesoTeresina2014 += dadosNas.PESO;
                contadorTeresina2014++;
            } else if (dadosNas.CODMUNRES == 410690) {  
                totalPesoCuritiba2014 += dadosNas.PESO;
                contadorCuritiba2014++;
            }
        }

        condicaoParada++;

        if(condicaoParada == 1000) {
            break;
        }
        fgets(buffer,MAX,f);
    }

    fclose(f);

    // cálculo dos pesos 
    float pesoMedioTeresina2014 = totalPesoTeresina2014 / contadorTeresina2014;
    float pesoMedioCuritiba2014 = totalPesoCuritiba2014 / contadorCuritiba2014;

    // Imprimir resultados
    printf("Peso médio em Teresina no ano de 2014: %.2f\n", pesoMedioTeresina2014);
    printf("Peso médio em Curitiba no ano de 2014: %.2f\n", pesoMedioCuritiba2014);

    return 0;
}
