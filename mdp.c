#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// função que diz se um número n é primo ou não //
int primo (long long int n)
{
	int i;
	for (i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0) return 0;
	}
	return 1;
}

// função que acha o mdc de dois números a e b // 
int mdc (int a, int b) 
{
	int r = a%b;
	while ( r > 0 )
	{
		a = b;
		b = r;
		r = a%b;
	}
	return b;
}

// função que resolve uma congruência ( pow(m,e) % (mod n) = c ) //
int mod (int m, int e, int n) {  //CALCULA O VALOR DE M^E MOD N
	int resultado = 1; 
	m %= n; 
	while (e > 0) {
		resultado = (resultado * m) % n;
		e--;
	}
	return resultado; 
}

// função que acha a chave privada tendo o expoente e o phi(n) //
long long int maior(long long int a, long long int b)
{
	if (a > b) return a;
	else return b;
}

int chave_privada(int p, int q, int e)
{
	int inv, i, resto, qnt = 0, phi = (p-1)*(q-1); 
	int divisores[100], aux[100], comb[100] = {0,1};
	resto = e % phi;
	while (resto != 0) {
		divisores[qnt] = e / phi;
		e = phi;
		phi = resto;
		resto = e % phi;
		qnt++;
	}
	for (i = 0; i < qnt; i++)
		aux[i+2] = divisores[qnt-i-1];
	for (i = 2; i < qnt + 2; i++)
		comb[i] = (aux[i] * comb[i-1]) + comb[i-2];
	inv = maior(comb[qnt+1], comb[qnt]);
	if(qnt % 2 != 0)
		return inv;
	else {
		inv *= -1;
		while(inv < 0) 
			inv += (p-1)*(q-1);
		return inv;
	}
}

// função para criar a chave pública e salvá-la em um arquivo txt //
void chave_publica()
{
	FILE *ponteiro;
	ponteiro = fopen("chave_publica.txt", "w");
	long int p, q; // dois números primos que formam o primeiro número a chave pública //
	printf("digite um numero primo p:\n");
	scanf("%ld", &p);	
	while (!primo(p))
	{
		printf("opcao invalida\n digite um numero primo p:\n");
		scanf("%ld", &p);
	}
	printf("digite um numero primo q:\n");
	scanf("%ld", &q);
	while (!primo(q))
	{
		printf("opcao invalida\n digite um numero primo q:\n");
		scanf("%ld", &q);
	}
	long long int n; // primeiro número da chave publica //
	n = p * q;
	long int e; // segundo número da chave pública //
	printf("digite um valor para o expoente:\n");
	scanf("%ld", &e);
	while (mdc((p-1)*(q-1), e) != 1)
	{
		printf("esse expoente nao eh coprimo a phi(n), escolha outro numero.\n%d\n", mdc((p-1)*(q-1), e));
		scanf("%ld", &e);
	}
	while (e <= 1 || e >= (p-1)*(q-1))
	{
		printf("esse expoente nao esta entre 1 e phi(n), escolha outro numero.\n");
	}
	fprintf(ponteiro,"%lld %ld\n", n, e);
	printf("o arquivo chave_publica.txt foi gerado\n");
	return; 
}

// função para criptografar uma mensagem e salvá-la em um arquivo txt //
void criptografar()
{
	FILE *ponteiro;
	ponteiro = fopen("mensagem_criptografada.txt", "w");
	char m[1000]; // mensagem a ser criptografada //
	printf("digite a mensagem a ser criptografada:\n");
	getchar();
	fgets(m, 1000, stdin);
	long long int n, e; // números que formam a chave pública //
	printf("digite os dois numeros que formam a chave publica:\n");
	scanf("%lld %lld", &n, &e);
	int array[strlen(m)-1];
	long long int c; // mensagem criptografada //
	for (int i = 0; i < strlen(m) - 1; i++) m[i] = toupper(m[i]);
	for (int i=0; i < strlen(m)-1; i++) 
	{
		if (m[i] == ' ') array[i] = 26;
		else array[i] = m[i] - 'A';
	}
	for (int i = 0; i < strlen(m)-1; ++i)
	{
		c = mod(array[i], e, n);
		fprintf(ponteiro,"%lld ", c);
	}
	printf("o arquivo mensagem_criptografada.txt foi gerado\n");
	return;
}

void descriptografar()
{
	FILE *ponteiro;
	ponteiro = fopen("mensagem_descriptografada.txt", "w");
	long long int i = 0, array[1000]; //mensagem a ser descriptografada//
	printf("digite a mensagem a ser descriptografada:\n");
	char aux;
	scanf("%lld%c", &array[i], &aux);
	while (aux != '\n')
	{
		i++;
		scanf("%lld%c", &array[i], &aux);
	}
	long long int p, q;
	printf("digite os dois primos ultilizados para formar a chava publica\n");
	scanf("%lld %lld", &p, &q);
	long long int e;
	printf("digite o expoente ultilizado para formar a chava publica\n");
	scanf("%lld", &e);
	long long int d;
	d = chave_privada(p, q, e);
	int j;
	for (j=0; j<i; j++)
	{
		array[j] = mod(array[j],d,p*q);
	}
	for (j=0; j<i; j++) 
	{
		if (array[j] == 26) fprintf(ponteiro, " ");
		else fprintf(ponteiro, "%lld", array[j] + 'A');
	}
	printf("o arquivo mensagem_descriptografada.txt foi gerado\n");
	return;
}

int main()
{
	int opcao;
	printf("Digite 1 para gerar chave publica\n");
	printf("Digite 2 para criptografar\n");
	printf("Digite 3 para descriptografar\n");
	scanf("%d", &opcao);
	while (opcao > 3 || opcao < 1)
	{
		printf("opcao invalida, selecione outra opcao.\n");
		scanf("%d", &opcao);
	}
	if (opcao == 1)
	{
		chave_publica();
	}
	else if (opcao == 2)
	{
		criptografar();
	}
	else if (opcao == 3)
	{
		descriptografar();
	}
	return 0;
}