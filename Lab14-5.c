
#include <stdlib.h>
#include <stdio.h>

/* EXERCÍCIO TEÓRICO #1
*  
*  Assuma uma Cache com endereços de 32 Bits, linhas de 16B e tamanho TOTAL da cache de 512B.
*  --> A memória é word-addressable! 
*  --> A cache tem 2 vias (2-way associativity)!!;
*  Políticas de Write-Back, Write-Allocate e LRU
*  Sabendo que &M1[0] = 0x0008 0000, indique o mapeamento na Cache
*  (index e offset) os seguintes valores, assumindo um formato M[][]
*  M1[1][1]
*  M2[0][5]
*/

/* EXERCÍCIO TEÓRICO-PRÁTICO #1
* 
*  Coloque o codigo em baixo no simulador Ripes, utilizando a cache
*  descrita no exercício teórico #1. Verifique qual é o hit rate.
* 
*  Justifique o porquê deste valor!
*/

/* EXERCÍCIO TEÓRICO-PRÁTICO #2
*
*  Altere o código para ter uma melhor performance com a cache anterior.
*
*  Justifique!
* 
*/


/* EXERCÍCIO TEÓRICO-PRÁTICO #3
*
*  Altere a configuração da cache para ter uma performance melhor com o código original.
*  
*  Façam a solução mais "engenheira", ou seja a com melhor custo benefício
*
*  Justifique!
* 
*/


/*******************************************************************************
 * Definicao de constantes e macros
*******************************************************************************/
// Constantes
#define N 32

/*******************************************************************************
 * Declaracao de variaveis globais
*******************************************************************************/

typedef struct {
	int x;
	int y;
	int z;
} target;

target vect[N];
target vect2[N];
target vect3[N];
int x_mean, y_mean, z_mean;

/*******************************************************************************
 * Declaracao de funcoes
*******************************************************************************/
void init();
void CacheKernel();
void VerifyResult();

/*******************************************************************************
 * CacheKernel
*******************************************************************************/

void CacheKernel()
{
    // a keyword register pede ao compilador para alocar as variaveis em registos
    register int i;

    register int x_sum = 0;
    register int y_sum=0;
    register int z_sum=0;

    for (i = 0; i < N; i++)
		x_sum += vect[i].x + vect2[i].x + vect3[i].x ;
    for (i = 0; i < N; i++)
        y_sum += vect[i].y + vect2[i].y + vect3[i].y ;
    for (i = 0; i < N; i++)
        z_sum += vect[i].z + vect2[i].z + vect3[i].z ; 

	x_mean = x_sum / N; 
	y_mean = y_sum / N;
   	z_mean = z_sum / N;
}


/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
	Init();
    CacheKernel();
    VerifyResult();

    return EXIT_SUCCESS;
}

/*******************************************************************************
 * Definicao de funcoes
*******************************************************************************/

void Init()
{
	int i;
	for(i = 0; i < N; i++) {
		vect[i].x = i;
		vect[i].y = N-i-1;
		vect[i].z = i*i;
        vect2[i].x = i;
		vect2[i].y = N-1;
		vect2[i].z = i-2;
        vect3[i].x = i*4;
		vect3[i].y = N-i-i;
		vect3[i].z = i*2;

	}
}

void VerifyResult(void)
{
	printf("x mean: %d, y mean: %d, z mean: %d\n", x_mean, y_mean, z_mean);
}
