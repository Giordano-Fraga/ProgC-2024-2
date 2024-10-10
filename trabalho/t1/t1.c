#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void menu(char* nomemimagem);
void pretoEbranco(char* nome);
void raioX(char* nome);
void inverter(char* nome);
void envelhecer(char* nome);
void rotacionar(char* nome);



int main () 
{
	char nomeimagem[100];
	printf("Digite o nome da imagem (formato .ppm): ");
	scanf("%s", nomeimagem);
	menu(nomeimagem);
	printf("Terminou!");
	return 0;
}



void menu(char *nomeimagem){
	printf("\n---- Editar a imagem ----");
	printf("\n[1] --- Preto e branco ");
	printf("\n[2] --- Raio-X ");
	printf("\n[3] --- Inverter as cores ");
	printf("\n[4] --- Envelhecer ");
	printf("\n[5] --- Rotacionar ");
	printf("\n\n{Qualquer outro numero para sair}\n");

	int escolha;
	scanf("%d", &escolha);

	switch(escolha){
		case 1: pretoEbranco(nomeimagem); break;
		case 2: raioX(nomeimagem); break;
		case 3: inverter(nomeimagem); break;
		case 4: envelhecer(nomeimagem); break;
		case 5: rotacionar(nomeimagem); break;
		default : printf("Finalizando..."); break;
	}
}



void pretoEbranco(char* nome){
	FILE *fp;
    fp = fopen(nome,"r");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char tipoImg[3];
    int i, j, linha, coluna, val, r, g, b;

    fscanf(fp, "%s", tipoImg); // lê o tipo de imagem 
    printf("%s\n", tipoImg);
    fscanf(fp, "%d %d", &coluna, &linha); // lê o tamanho da matriz
    printf("%d %d\n", coluna, linha);
    fscanf(fp, "%d", &val); // lê o valor máximo
    printf("%d\n", val);

	int matriz[700][700];

    for(j = 0; j < linha; j++)
    {
        for(i = 0; i < coluna; i++)
        {  	
            fscanf(fp, "%d %d %d", &r, &g, &b);
            matriz[j][i] = ((r*0.30)+(g*0.59)+(b*0.11)); // convertendo para p&b
        }
    }

    fclose(fp);

    // criando a imagem P&B no formato P3
    FILE* fp_novo = fopen("imagem_p&b.ppm", "w");
    if(fp_novo == NULL){
        printf("Erro ao criar o arquivo P&B!\n");
        return;
    }

    fprintf(fp_novo, "P3\n");
    fprintf(fp_novo, "%d %d\n", coluna, linha);
    fprintf(fp_novo, "%d\n", val);

    for(j = 0; j < linha; j++)
    {
        for(i = 0; i < coluna; i++)
        {  	
            int cinza = matriz[j][i];
            fprintf(fp_novo, "%d %d %d\n", cinza, cinza, cinza);
        }
    }

    fclose(fp_novo);
    printf("Imagem em preto e branco gerada com sucesso.\n");
}



void raioX(char* nome){
	FILE *fp;
	fp = fopen(nome,"r");
	if(fp == NULL){
		printf("Erro ao abrir o arquivo!\n");
		return;
	}
	
	char tipoImg[3];
	int i, j, linha, coluna, val, r, g, b;
	float fator = 1.3; // contraste
	
	fscanf(fp, "%s", tipoImg); 
	printf("%s\n", tipoImg);
	fscanf(fp, "%d %d", &coluna, &linha); 
	printf("%d %d\n", coluna, linha);
	fscanf(fp, "%d", &val); 
	printf("%d\n", val);

	int matriz[700][700];

	// 1 - convertendo a imagem para cinza
	for(j = 0; j < linha; j++)
	{
		for(i = 0; i < coluna; i++)
		{  	
			fscanf(fp, "%d %d %d", &r, &g, &b);
			matriz[j][i]=((r*0.299)+(g*0.587)+(b*0.114));
		}
	}
	
	// 2 - convertendo para efeito raio-x
	for(j = 0; j < linha; j++)
	{
		for(i = 0; i < coluna; i++)
		{
			// contraste
			matriz[j][i] = pow(matriz[j][i], fator);
			// teste pra ver se é válido
			if(matriz[j][i]>255) matriz[j][i]=255;
		}
	}

	fclose(fp);

	// criando nova imagem
	FILE* fp_novo = fopen("imagem_raioX.ppm", "w");
	if(fp_novo == NULL){
		printf("Erro ao criar o arquivo raio-X!\n");
		return;
	}
	
	fprintf(fp_novo, "P2\n");
	fprintf(fp_novo, "%d %d\n", coluna, linha);
	fprintf(fp_novo, "%d\n", val);

	for(j = 0; j < linha; j++)
	{
		for(i = 0; i < coluna; i++)
		{  	
			fprintf(fp_novo, "%d\n", matriz[j][i]);
		}
	}

	fclose(fp_novo);
	printf("Imagem com efeito raio-X gerada com sucesso.\n");
}



void inverter(char* nome){
	FILE *fp;
	fp = fopen(nome,"r");
	if(fp == NULL){
		printf("Erro ao abrir o arquivo!\n");
		return;
	}

	char tipoImg[3];
	int i, j, linha, coluna, val, r, g, b;

	fscanf(fp, "%s", tipoImg); 
	printf("%s\n", tipoImg);
	fscanf(fp, "%d %d", &coluna, &linha); 
	printf("%d %d\n", coluna, linha);
	fscanf(fp, "%d", &val); 
	printf("%d\n", val);

	// criando a imagem
	FILE* fp_novo = fopen("imagem_invertida.ppm", "w");
	if(fp_novo == NULL){
		printf("Erro ao criar o arquivo com cores invertidas!\n");
		fclose(fp);
		return;
	}

	fprintf(fp_novo, "P3\n");
	fprintf(fp_novo, "%d %d\n", coluna, linha);
	fprintf(fp_novo, "%d\n", val);

	// lendo a imagem original, invertendo, e salvando
	for(j = 0; j < linha; j++)
	{
		for(i = 0; i < coluna; i++)
		{  	
			fscanf(fp, "%d %d %d", &r, &g, &b);
			fprintf(fp_novo, "%d %d %d\n", 255-r, 255-g, 255-b);
		}
	}

	fclose(fp);
	fclose(fp_novo);
	printf("Imagem com cores invertidas gerada com sucesso.\n");
}



void envelhecer(char* nome){
	FILE *fp;
	fp = fopen(nome,"r");
	if(fp == NULL){
		printf("Erro ao abrir o arquivo!\n");
		return;
	}

	char tipoImg[3];
	int i, j, linha, coluna, val, r, g, b;
	float fator = 0.1; // usado para ajustar nas cores

	fscanf(fp, "%s", tipoImg); 
	printf("%s\n", tipoImg);
	fscanf(fp, "%d %d", &coluna, &linha); 
	printf("%d %d\n", coluna, linha);
	fscanf(fp, "%d", &val); 
	printf("%d\n", val);

	// criando nova imagem
	FILE* fp_novo = fopen("imagem_sepia.ppm", "w");
	if(fp_novo == NULL){
		printf("Erro ao criar o arquivo sépia!\n");
		fclose(fp);
		return;
	}

	fprintf(fp_novo, "P3\n");
	fprintf(fp_novo, "%d %d\n", coluna, linha);
	fprintf(fp_novo, "%d\n", val);

	// processando a imagem diretamente
	for(j=0; j<linha; j++)
	{
		for(i=0; i<coluna; i++)
		{
			fscanf(fp, "%d %d %d", &r, &g, &b);
			// reduzindo e aumentado cores
			b = b*(1-fator);
			r = r*(1+fator);
			g = g*(1+fator);
			// tintura
			r = r + 10;
			g = g + 10;
			b = b - 10;
			// teste para ver se cores são válidas
			if(r > 255) r = 255;
			if(g > 255) g = 255;
			if(b < 0) b = 0;
			// escrevendo no arquivo
			fprintf(fp_novo, "%d %d %d\n", r, g, b);
		}
	}

	fclose(fp);
	fclose(fp_novo);
	printf("Imagem com efeito sepia gerada com sucesso.\n");
}




typedef struct {
    int r, g, b;
} Pixel;



void rotacionar(char* nome) {
    FILE *fp = fopen(nome, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    char tipoImg[3];
    int linha, coluna, val;

	fscanf(fp, "%2s", tipoImg);
    printf("%s\n", tipoImg);
	fscanf(fp, "%d %d", &coluna, &linha);
    printf("%d %d\n", coluna, linha);
    fscanf(fp, "%d", &val);
    printf("%d\n", val);

    // alocando memória pra matriz de pixels
    Pixel **matriz = (Pixel **)malloc(linha * sizeof(Pixel *));
    for (int i=0; i<linha; i++) {
        matriz[i] = (Pixel *)malloc(coluna * sizeof(Pixel));
    }

    // ler e armazenar pixels
    for (int j = 0; j < linha; j++) {
        for (int i = 0; i < coluna; i++) {
            if (fscanf(fp, "%d %d %d", &matriz[j][i].r, &matriz[j][i].g, &matriz[j][i].b) != 3) {
                printf("Erro ao ler os valores RGB\n");
                fclose(fp);
                return;
            }
        }
    }

    fclose(fp);

    // rotacionando
    Pixel **rotacionada = (Pixel **)malloc(coluna * sizeof(Pixel *));
    for (int i=0; i<coluna; i++) {
        rotacionada[i] = (Pixel *)malloc(linha * sizeof(Pixel));
    }

    for (int j=0; j<linha; j++) {
        for (int i=0; i<coluna; i++) {
            rotacionada[i][linha-1-j]=matriz[j][i];
        }
    }

    // criando nova imagem
    FILE* fp_novo = fopen("imagem_rotacionada.ppm", "w");
    if (fp_novo == NULL) {
        printf("Erro ao criar o arquivo rotacionado");
        return;
    }

    fprintf(fp_novo, "P3\n");
    fprintf(fp_novo, "%d %d\n", linha, coluna); // inverte linha e coluna
    fprintf(fp_novo, "%d\n", val);

    for (int j=0; j<coluna; j++) {
        for (int i=0; i<linha; i++) {
            Pixel p = rotacionada[j][i];
            fprintf(fp_novo, "%d %d %d\n", p.r, p.g, p.b); // salvando as cores no arquivo
        }
    }

    fclose(fp_novo);
    printf("Imagem rotacionada gerada com sucesso.\n");
}