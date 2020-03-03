#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int primo(int a) { //VERIFICA SE UM NÚMERO É PRIMO
	int i;
	for (i = 2; i <= sqrt(a); i++) {
		if (a % i == 0) return 0;
	}
	return 1;
}

int mdc(int a, int b) { //CALCULA O MDC ENTRE DOIS NÚMEROS
 	if (b == 0) return a;
 	else return mdc(b, a % b);
}

int maior(int a, int b) { //ENCONTRA O MAIOR VALOR ENTRE DOIS NÚMEROS
	if (a > b) return a;
	else return b;
}

int exponential(int m, int e, int n) {  //CALCULA O VALOR DE M^E MOD N
	int resultado = 1; 
	m %= n; 
	while (e > 0) {
		resultado = (resultado * m) % n;
		e--;
	}
	return resultado; 
}

int generate_exponent(int p, int q) { //GERA O EXPOENTE 'E' DA CHAVE PÚBLICA
  	int i, phi = (p-1)*(q-1);
  	for (i = 4; i < phi; i++) {
  		if ((mdc(phi, i) == 1)){
  			return i;
  		}
  	}
}

int private_key(int p, int q, int e) { //ENCONTRA O INVERSO DE 'E' NO ANEL PHI(N)
	int inv, i, resto, qnt = 0, phi = (p-1)*(q-1); 
	int divisores[100], aux[100], comb[100] = {0,1};
	printf("%d\n", e);
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

void generate_key() { //GERA O ARQUIVO DE TEXTO KEY.TXT, QUE ARMAZENA A CHAVE PÚBLICA
	FILE *key;
	key = fopen("key.txt","w");
	int p, q, n;
	printf("Digite um numero primo P\n");
	scanf("%d", &p);
	while (!primo(p)) {
		printf("Por favor, digite um numero primo para P\n");
		scanf("%d", &p);
	}
	printf("Digite um numero primo Q\n");
	scanf("%d", &q);
	while (!primo(q)) {
		printf("Por favor, digite um numero primo para Q\n");
		scanf("%d", &q);
	}
	n = p * q;
	fprintf(key,"%d %d", n, generate_exponent(p, q));
	printf("Chave Publica criada!\n");
	return;
}

void encrypt() { //GERA O ARQUIVO ENCRYPTED.TXT, QUE ARMAZENA A MENSAGEM CRIPTOGRAFADA
	FILE *encrypted;
	encrypted = fopen("encrypted.txt", "w");
	char str[10000];
	printf("Digite o texto a ser criptografado:\n");
	getchar();
	gets(str);
	int i, n, e;
	int v[strlen(str)];
	for (i = 0; i < strlen(str); i++) str[i] = toupper(str[i]);
	for (i = 0; i < strlen(str); i++) {
		if(str[i] == ' ') v[i] = 26;
		else v[i] = str[i] - 'A';
	}
	printf("Digite o par de numeros que forma a chave publica\n");
	scanf("%d %d", &n, &e);
	for (i = 0; i < strlen(str); i++) {
		v[i] = exponential(v[i], e, n);
		fprintf(encrypted,"%d ", v[i]);
	}
	printf("Mensagem criptografada!\n");
	return;
}

void decrypt() { //GERA O ARQUIVO DECRYPTED.TXT, QUE ARMAZENA A MENSAGEM DESCRIPTOGRAFADA
	FILE *decrypted;
	decrypted = fopen("decrypted.txt", "w");
	int v[10000];
	char aux;
	int n, p, q, e, d, i, j = 0;
	printf("Digite o par de numeros primos P e Q usado pra gerar a chave publica\n");
	scanf("%d %d", &p, &q);
	d = private_key(p, q, generate_exponent(p, q));
	printf("%d\n", d);
	n = p * q;
	printf("Digite a mensagem a ser descriptografada:\n");
	scanf("%d%c", &v[j], &aux);
	while (aux != '\n') {
		j++;
		scanf("%d%c", &v[j], &aux);
	}
	for (i = 0; i < j+1; i++) {
		v[i] = exponential(v[i], d, n);
		if (v[i] == 26) fprintf(decrypted, " ");
		else fprintf(decrypted,"%c", v[i] + 'A');
	}
	printf("Mensagem descriptografada!\n");
	return;
}

int main() {
	int n;
	printf("Escolha uma opcao abaixo para iniciar:\n");
	printf("1 - Gerar chave publica\n");
	printf("2 - Criptografar\n");
	printf("3 - Descriptografar\n");
	scanf("%d", &n);
	while (n > 3 || n < 1) {
		printf("Opcao Invalida, selecione outra opcao\n");
		scanf("%d", &n);
	}
	if (n == 1) {
		generate_key();
	}
	else if (n == 2) {
		encrypt();
	}
	else {
		decrypt();
	}
	//system("pause");
	return 0;
}