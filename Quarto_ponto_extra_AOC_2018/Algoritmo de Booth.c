#include <stdio.h>
#include <stdlib.h>

typedef struct Produto{
	int *hi;
	int *lo;
	int carryOut;
}produto;


void converteToBinario(int x, int *v, int tam){
	int i;
	for (i = tam-1; i >= 0; i--){
		v[i] = x % 2;
		x = x / 2;
	}
}

void somaBinario(int *v1, int *v2,int *soma, int tam){
	int i,CarryIn = 0;
	for (i = tam-1; i>=0;i--){
		CarryIn += v1[i] + v2[i];
		if (CarryIn > 1){
			soma[i] = (CarryIn == 3) ? 1:0;
			CarryIn = 1;
		}
		else{
			soma[i] = CarryIn;
			CarryIn = 0;
		}
	}
}

void ComplementoA2(int *vetor,int *comp, int tam){
	int i;
	int *aux = calloc(tam, sizeof(int));
	aux[tam-1] = 1;
	for (i = tam-1; i >= 0; i--){
		if(vetor[i] == 1){
            comp[i] = 0;
		}

		else{
            comp[i] = 1;
		}
    }
	somaBinario(comp,aux,comp,tam);
}

void shiftaDireita(produto *p, int tam){
	int i,aux = 0, aux2 = 0;
	for (i = 0; i < tam; i++){
		aux2 = p->hi[i];
		p->hi[i] = aux;
		aux = aux2;
	}
	for (i = 0; i< tam; i++){
		aux2 = p->lo[i];
		p->lo[i] = aux;
		aux = aux2;
	}
	p->carryOut = aux;
}

int main(void){
	int valor1,valor2,i,tam,contador = 1;

	printf("Indique a quantidade de bits: ");
	scanf("%d", &tam);
	printf("Digite o 1 numero : ");
	scanf("%d", &valor1);
	printf("Digite o 2 numero : ");
	scanf("%d", &valor2);

	int *p = (int*) calloc (tam, sizeof(int));
	int *p2 = (int*) calloc (tam, sizeof(int));
	int *complemento = (int*) calloc(tam, sizeof(int));
	int *soma = (int*) calloc(tam, sizeof(int));
	produto *vet = (produto*)malloc(sizeof(produto));

	converteToBinario(valor1,p,tam);
	converteToBinario(valor2,p2,tam);
	//somaBinario(p,p2,soma,tam);
	ComplementoA2(p,complemento,tam);
	vet->carryOut = 0;
	vet->hi = soma;
	vet->lo = p2;

	while(contador <= tam){
        if (p2[tam-1] == 1 && vet->carryOut == 0 ){
            somaBinario(vet->hi,complemento,vet->hi,tam);
            shiftaDireita(vet, tam);
        }
        if (p2[tam-1] == 1 && vet->carryOut == 1){
            shiftaDireita(vet, tam);
        }
        if (p2[tam-1] == 0 && vet->carryOut == 1){
            somaBinario(vet->hi, p2, vet->hi, tam);
        }
        if (p2[tam-1] == 0 && vet->carryOut == 0){
            shiftaDireita(vet, tam);
        }
        contador+= 1;
	}
	printf("produto dos numeros em binario eh: ");
	for (i = 0; i < tam; i++){
		printf("%d ", vet->hi[i]);
	}
	for (i = 0; i < tam; i++){
		printf("%d ", vet->lo[i]);
	}
    return 0;
}
