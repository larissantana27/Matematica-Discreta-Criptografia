#include <stdio.h>
#include <math.h>
#include <string.h>

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
long long int mdc (long long int a, long long int b) 
{
	long long int r = a%b;
	while ( r > 0 )
	{
		a = b;
		b = r;
		r = a%b;
	}
	return b;
}

// função que sugere o menor expoente possível, coprimo de phi(n) //
long long int menor_expoente (long long int p, long long int q)
{
	long long int e, phi;
	phi = (p-1) * (q-1);
	for (e=4; e < phi; e++)
	{
		if ( mdc(phi, e) == 1)
		{
			return e;
		}
	}
}

// função que resolve uma congruência ( pow(m,e) % (mod n) = c ) //
long long int mod (long long int m, long long int e, long long int n) 
{
	long long int resultado = 1; 
	m %= n; 
	while (e > 0) 
	{
		resultado = (resultado * m) % n;
		e--;
	}
	return resultado; 
}

// função que retorna o maior valor de dois números // 
long long int maior(long long int a, long long int b)
{
	if (a > b) return a;
	else return b;
}

// função que acha a chave privada tendo o expoente e o phi(n) //
long long int inverso (long long int n, long long int d)
{
	long long int q, r, i=-1, j;
	long long int a = n;
	long long int quocientes[100], resultados[102];
	resultados[0] = 0;
	resultados[1] = 1;
	while (d != 1)
	{
		i++;
		q = n/d;
		r = n%d;
		n = d;
		d = r;
		quocientes[i] = q;
	}
	for (j = 2; j <= i+2; j++) 
	{
		resultados[j] = (quocientes[j-2]*resultados[j-1]) + resultados[j-2];
	}
	long long int x = maior(resultados[j-1], resultados[j]);
	if (x = resultados[j-1])
	{
		if ((i)%2 == 0)
		{
			x *= -1;
			while (x < 0)
			{
				x += a;
			}
		}
		return x;
	}
	if (x = resultados[j])
	{
		if ((i)%2 != 0)
		{
			x *= -1;
			while (x < 0)
			{
				x += a;
			}
		}
		return x;
	}
}

// função para criar a chave pública e salvá-la em um arquivo txt //
void chave_publica()
{
	FILE *ponteiro;
	ponteiro = fopen("chave_publica.txt", "w");
	long long int p, q; // dois números primos que formam o primeiro número a chave pública //
	printf("digite um numero primo p:\n");
	scanf("%lld", &p);	
	while (!primo(p))
	{
		printf("opcao invalida\n digite um numero primo p:\n");
		scanf("%lld", &p);
	}
	printf("digite um numero primo q:\n");
	scanf("%lld", &q);
	while (!primo(q))
	{
		printf("opcao invalida\n digite um numero primo q:\n");
		scanf("%lld", &q);
	}
	long long int n; // primeiro número da chave publica //
	n = p * q;
	long long int e; // segundo número da chave pública //
	long long int sugestao = menor_expoente(p, q);
	printf("digite um valor para o expoente, sugiro o valor: %lld\n", sugestao);
	scanf("%lld", &e);
	while (mdc((p-1)*(q-1), e) != 1)
	{
		printf("esse expoente nao eh coprimo a phi(n), escolha outro numero.\n");
		scanf("%lld", &e);
	}
	while (e <= 1 || e >= (p-1)*(q-1))
	{
		printf("esse expoente nao esta entre 1 e phi(n), escolha outro numero.\n");
		scanf("%lld", &e);
	}
	fprintf(ponteiro,"%lld %lld\n", n, e);
	printf("o arquivo chave_publica.txt foi gerado\n");
	printf("se desejar, compile novamente e selecione outra opcao\n");
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
	long long int i, c; // mensagem criptografada //
	for (i=0; i < strlen(m)-1; i++) 
	{
		if (m[i] == ' ') array[i] = 26;
		else array[i] = m[i] - 'a';
	}
	for (i=0; i < strlen(m)-1; i++)
	{
		c = mod(array[i], e, n);
		fprintf(ponteiro,"%lld ", c);
	}
	printf("o arquivo mensagem_criptografada.txt foi gerado\n");
	printf("se desejar, compile novamente e selecione outra opcao\n");
	return;
}

void descriptografar()
{
	FILE *ponteiro;
	ponteiro = fopen("mensagem_descriptografada.txt", "w");
	long long int i=0, array[1000]; //mensagem a ser descriptografada//
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
	d = inverso((p-1)*(q-1), e);
	long long int j;
	for (j=0; j < i+1; j++)
	{
		array[j] = mod(array[j],d,p*q);
	}
	for (j=0; j < i+1; j++) 
	{
		if (array[j] == 26) fprintf(ponteiro, " ");
		else fprintf(ponteiro, "%c", array[j] + 'a');
	}
	printf("o arquivo mensagem_descriptografada.txt foi gerado\n");
	printf("se desejar, compile novamente e selecione outra opcao\n");
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