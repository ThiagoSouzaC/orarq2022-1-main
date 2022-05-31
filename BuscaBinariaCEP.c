#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; 
};

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
	int c = 0;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	f = fopen("cep_ordenado.dat","rb");

	fseek(f, 0, SEEK_END);
	long tamByte = ftell(f);
	long tamReg = tamByte/sizeof(Endereco);

	int inicio = 0;
	int fim = tamReg - 1;

	while(inicio <= fim) {
		int meio = (inicio + fim)/2;

		fseek(f, meio*sizeof(Endereco), SEEK_SET);
		fread(&e, sizeof(Endereco), 1, f);

		int comparacao = strncmp(argv[1], e.cep, 8);

		if(comparacao == 0) {
			printf("%.8s", e.cep);= 
		}
		if(comparacao < 0) {
			fim = meio - 1;
		} else {
			inicio = meio + 1;
		}
		c++;
	}
	printf("\n%d", c);
	printf("\n");
	fclose(f);
}
