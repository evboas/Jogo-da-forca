#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"forca.h"

char palavra[TAMANHO_PALAVRA];
char chutes[26];
int chutesDados = 0;

void cabecalho(){
	printf("*******************\n");
	printf("*  Jogo da forca  *\n");
	printf("*******************\n\n\n");
}

void adicionaPalavra(){
	char quer;
	printf("Você deseja adicionar uma nova palavra no jogo? (S/N) ");
	scanf(" %c", &quer);
	if(quer == 'S'){
		char novaPalavra[TAMANHO_PALAVRA];
		printf("Qual a nova palavra? ");
		scanf("%s", novaPalavra);

		FILE* f;
		f = fopen("palavras.txt", "r+");
		if(f == 0){
			printf("Desculpe, banco de dados não disponível\n\n");
			exit(1);
		}

		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;

		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtd);
		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", novaPalavra);

		fclose(f);
	}
}

void escolhePalavra(){
	FILE* f;
	f = fopen("palavras.txt", "r");
	if(f == 0){
		printf("Deculpe, banco de dados não disponível\n\n");
		exit(1);
	}

	int qtdPalavras;
	fscanf(f, "%d", &qtdPalavras);

	srand(time(0));
	int randomico = rand() % qtdPalavras;

	for(int i = 0; i <= randomico; i++){
		fscanf(f, "%s", palavra);
	}

	fclose(f);
}

void guardaChute(){
	char chute;
	scanf(" %c", &chute);
	printf("\n\n");
	
	chutes[chutesDados] = chute;
	chutesDados++;
}

int jaChutou(char letra){
	int achou = 0;
		for(int j=0; j< chutesDados; j++){
			if(chutes[j] == letra){
				achou = 1;
				break;
			}
		}
	return achou;
}

void desenhaPalavra(){

	int erros = chutesErrados();
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(':' '), (erros >= 1 ? '_':' '), (erros >= 1 ? ')':' '));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\':' '), (erros >= 2 ? '|':' '), (erros >= 3 ? '/':' '));
    printf(" |       %c     \n", (erros >= 2 ? '|':' '));
    printf(" |      %c %c   \n", (erros >= 4 ? '/':' '), (erros >= 4 ? '\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

	for(int i = 0; i < strlen(palavra); i++){
		int achou = jaChutou(palavra[i]);
		if(achou){
			printf("%c ", palavra[i]);
		}else{
			printf("_ ");
		}
	} //Este for desenha os tracejados
	printf("\n\n");
}

int chutesErrados(){
	int erros = 0;
	for(int i = 0; i < chutesDados;i++){
		int existe = 0;
		for(int j = 0; j < strlen(palavra); j++){
			if(chutes[i] == palavra[j]){
				existe = 1;
				break;
			}
		}
		if(!existe) erros++;
	}
	return erros;
}

int enforcou(){
	return chutesErrados() >= 5;
}

int ganhou(){
	for (int i = 0; i < strlen(palavra); i++){
		if(!jaChutou(palavra[i])){
			return 0;
		}
	}
	return 1;
}

int main(){
	escolhePalavra();
	cabecalho();

	do{	
		desenhaPalavra();
		guardaChute();

	}while(!ganhou() && !enforcou());

	if(ganhou()){
		printf("Parabéns você acertou!\n");
		printf("A palavra era %s \n\n", palavra);
	}else{
		printf("Que pena! Você perdeu!\n");
		printf("A palavra era %s \n\n", palavra);

	
	}
	adicionaPalavra();
}