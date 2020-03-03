
Conversa aberta. Uma mensagem não lida.

Pular para o conteúdo
Como usar o Gmail com leitores de tela
1 de 944
Meu código em python
Jean Bernardo da Silva Vieira
    
Anexos17:13 (há 13 minutos)
    
para eu
   
Traduzir mensagem
Desativar para: inglês
Segue anexo.


Área de anexos
    
    
    

# coding=cp1252
from math import sqrt # Função para cálculo da raiz quadrada
from math import gcd #função para cálculo do MDC
from random import choice # Função para escolher um item aleatório de uma lista
from random import randint # Função para escolher um número inteiro aleatório em dado intervalo
from os.path import exists # Função para saber se dado arquivo existe no diretório atual
from os import getcwd # Função para ler o caminho completo do diretório atual
from msvcrt import getch # função para receber apenas uma letra como variáve, sem ter que usar-se 'enter'
from os import system # usarei uma função incorporada neste módulo para limpar a tela
def func_primo(n=int):
    #Função para descobrir se dado número é primo
    if int(n) < 2: return False
    for i in range(2, int(sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True
#----------------------------------

def func_modulo(a, b, p):
    # (ab) mod p = ( (a mod p) (b mod p) ) mod p
    return ((a%p)**(b%p))%p
#------------------------------

def func_testaExpoente(e, phi_n):
    # Esta função testa se um expoente maior que 1 e menor que f(n) é co-primo de f(n), devolvendo True ou False
    if e > 1 and e < phi_n and gcd(e, phi_n) == 1:
        return True
    else:
        return False
#------------------------------

def func_coPrimoAleatorio(n):
    # Esta função devolve um co-primo aleatório de f(n)
    lista_coPrimos=[]
    i=0
    for i in list(range(i, n)):
        if gcd(i, n) == 1 and i > 1 and i < n:
            lista_coPrimos.append(i)
    return choice(lista_coPrimos)
#------------------------------

def func_leArquivo():
    '''
    Esta função le as linhas de um arquivo e armazena cada linha como  um item de uma lista.
    Assim é possível percorrer a lista e usar as informações contidas no arquivo sem ter-se que ficar reabrindo diversas
    vezes um arquivo a procura das informações
    '''

    chavePub=[] # variável local que armasenará a chave pública
    arquivo=open('chavePub.txt', 'r')

    # o for abaixo percorre todas as linhas do arquivo e acrescenta-as à lista chavePub
    for i in arquivo.readlines():
        chavePub.append(int(i))
    arquivo.close()
    return chavePub # a lista é retornada para que seus itens sejam usados posteriormente
#------------------------------

def func_escreveArquivo(arq, texto='', delimitador=' '):
    '''
    Esta função recebe três parâmetros:
    1. Caminho do arquivo onde o texto será armazenado;
    2. variável contendo o texto;
    3. Delimitador que separará cada palavra, etc. do texto.

    O delimitador padrão é um espaço, mas para armazenar a chave pública, optou-se por usar uma quebra de linha. Assim,
    fica fácil resgatar os elementos da chave pública para uma variável do tipo lista/array, para uso posterior.
    '''

    arquivo=open(str(arq), 'w') # arquivo será aberto no modo de escrita 'w' para armazenar algo dentro.
    if len(texto)!=0:
        for i in texto:
            arquivo.write(str(i))
            arquivo.write(delimitador) # Cada linha do arquivo será seguida ou pelo espaço ou pela quebra de linha.
    arquivo.close()
#------------------------------

def func_totient(p, q):
    '''
    Esta função retorna o totiente de Euller para phi(n).
    '''
    return (p-1)*(q-1)
#------------------------------

def func_alfabeto():
    '''
    É apenas uma lista com as letras do alfabeto. Apenas para não ter que digitá-la integralmente a cada vez que for
    necessária.
    '''
    return ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ']

#------------------------------


def func_gerarChave():
    chavePub=[]
    existe = exists('chavePub.txt') # Variável para verificar se um arquivo existe na pasta atual
    while existe == True:
        print('Já existe uma chave pública no arquivo ''chavePub.txt''. Quer utilizá-la?')
        quest1=input('Tecle ''s'' para sim, ''n'' para não ou ''c'' para cancelar: ')
        if quest1 == 's':
            chavePub = func_leArquivo() #  Chama a função que recupera a chave pública do arquivo
            print('Ok. Mantendo chave pública atual. \n')
            return chavePub
        elif quest1 == 'n':
            print('Iniciando procedimentos para criação da chave pública')
            break
        elif quest1 == 'c':
            print('Voltando ao menu')
        else:
            print('Opção inválida!\n\n')



    if existe==False or quest1=='n':
        # início do bloco 2
        while True:
            print('-- Escolha uma opção --\n'.center(15))
            quest2 = input('1: criar chave pública, 2: usar chave fornecida por terceiros, 3: cancelar: \n')
            if quest2 == '1' or quest2 == '2' or quest2 == '3':
                break
            else:
                print('Opção inválida! \n')

        # iniciando criação da chave pública
        if quest2 == '1':
            print('Criando chave pública: \n\n')
            while True:
                try:
                    p = int(input('Digite o 1º primo: \n'))
                    if func_primo(p) == True:
                        break
                    else:
                        print(p,'não é um número primo!')
                except:
                    print('Digite só números inteiros. \n')

            while True:
                try:
                    q = int(input('Digite o 2º primo: \n'))
                    if func_primo(q) == True and p != q:
                        break
                    elif p == q:
                        print('Os números primos não podem ser iguais! \n\n')
                    else:
                        print(q, 'não é um número primo!')
                except:
                    print('Digite só números inteiros. \n')



            n=p*q # produto dos dois primos fornecidos
            phi_n=int(func_totient(p, q)) # quantidade de coprimos menores que f(n), fornecidos pela função Totient de Euller
            chavePub.append(n) # Incluindo n à lista chavePub

            while True:
                try:
                    e=int(input('Digite o expoente:\n'))
                    if e > 1 and e < phi_n and func_testaExpoente(e, phi_n) == True:
                        chavePub.append(e)
                        break
                    else:
                        print('O expoente não é válido. ')
                        print('Sugiro',func_coPrimoAleatorio(int(phi_n)),'\n\n')
                except:
                    print('Opção inválida! O expoente tem que ser um número inteiro maior que 1 e menor que ' % phi_n)
                    print('Sugiro',func_coPrimoAleatorio(phi_n),'\n\n')

            print('Chave pública gerada! \n')

        # Inclusão de uma chave fornecida por terceiros
        elif quest2 == '2':
            while True:
                try:
                    n = int(input('Digite o valor de n, produto dos primos ''p'' e ''q'': '))
                    if func_primo(n) == False:
                        chavePub.append(n)
                        break
                    else:
                        print('n não pode ser um  número primo! \n\n')
                except:
                    print('Opção inválida! Digite um número inteiro composto!\n')

            while True:
                try:
                    e=int(input('Digite o expoente: \n\n'))
                    if e == int(e):
                        chavePub.append(e)
                        break
                    else:
                        print('O expoente deve ser um número inteiro. \n\n')
                except:
                    print('Opção inválida! Digite um número inteiro! \n\n')
            print('Chave pública armazenada!\n')



        elif quest2 == '3':
            print('Voltando ao menu. \n')
            func_menu()

    # Armazenando chave pública em arquivo para uso posterior
    func_escreveArquivo('chavePub.txt', chavePub, '\n')
    print('Consulte ''chavePub.txt'' em: \n%s' % getcwd())
    print('\n------------------------------\n\n')
    system('cls') or None # o none é para não sobrar um 0 no prompt de comandos depois da limpeza da tela
    func_menu()
#-----------------------------------------


def func_criptografar():
    # Esta função recebe uma mensagem e criptografa com uma chave pública anteriormente gerada
    # A variável abaixo recebe um par com letra e respectivo número de posição
    alfabeto = func_alfabeto()

    chavePub = [] # variável local que receberá a chave pública ou da digitação do usuário ou de um arquivo local
    msgCifrada = [] # Lista que receberá os números da mensagem, depois de encriptada

    print('Passo I: escolha da chave pública\n\n')
    chavePub = func_gerarChave()

    print('Passo II: escrita da mensagem a ser criptografada\n')
    print('Este programa aceita apenas mensagens com as 25 letras do alfabeto, (sem acentos) e espaços em branco. ')
    print('A tecla ''ENTER'' é usada para finalizar\n------------------------------\n\n')
    msgOriginal = input('Digite a mensagem a ser criptografada: ')
    msgOriginal = msgOriginal.upper() # método do módulo string para tornar todas as letras de uma string maiúsculas
    msgNumerada=[]
    print('Ok. \n------------------------------\n\n')


    print('Passo III: Criptografar a mensagem\n\n')
    # Aqui pegamos o valor de n e e da lista com a chave pública
    n = chavePub[0]
    e=chavePub[1]
    print('A chave pública é: %d, %d' % (n, e))
    # Para criptografar, primeiro multiplicamos cada caractere da mensagem pelo expoente 'e',
    # depois tiramos o módulo n dessa exponenciação
    for i in msgOriginal:
        if i in alfabeto:
            #letCifrada=(alfabeto.index(i)**e)%n # A letra cifrada resulta da operação à esquerda, como já explicado
            letCifrada=func_modulo(alfabeto.index(i), e, n) # A letra cifrada resulta da operação à esquerda, como já explicado
            msgCifrada.append(letCifrada)
        else:
            pass # Se uma letra digitada não estiver na tabela de caracteres, não faça nada.

    print('Salvando mensagem.\n------------------------------\n\n')
    func_escreveArquivo('mensagemCifrada.txt', msgCifrada, ' ')
    print('Mensagem criptografada e armazenada. \n\n')
    print('Consulte o arquivo ''mensagemCifrada.txt'' em: \n%s' % getcwd())
    print('------------------------------\n\n')
    system('cls') or None # o none é para não sobrar um 0 no prompt de comandos depois da limpeza da tela
    func_menu()
#------------------------------

def func_MDCE(num1, num2):
    '''
    MDC extendido de Euclides, também usado para fazer a combinação linear entre dois números, possibilitando
    encontrar-se o inverso modular.
    '''

    if num2==0:
        return [1,0,num1]
    else:
        x,y,d=func_MDCE(num2, num1%num2)
        return [y,x-(num1//num2)*y,d]
#------------------------------

def func_descriptografar():
    chavePv=[]
    msgDecifrada =[]
    msgOriginalNumerada=[] # Mensagem decifrada, mas ainda em números
    alfabeto = func_alfabeto()
    while True:
        try:
            p = int(input('Digite p: '))
            if func_primo(p) == False:
                print('%d não é primo!' % p)
            else:
                print('Ok. \n\n')
                break
        except:
            print('Digite um número inteiro! \n\n')


    while True:
        try:
            q = int(input('Digite q: '))
            if func_primo(q) == False:
                print('%d não é primo! ' % q)
            else:
                print('ok. \n')
                break
        except:
            print('Digite um número inteiro! \n\n')

    n = p*q # Tamanho do nosso conjunto e primeiro elemento da chave privada.

    while True:
        try:
            e=int(input('Digite o expoente: \n\n'))
            if e == int(e) and e < n:
                print('Ok. \n\n')
                break
            else:
                print('O expoente deve ser um número inteiro menor que n. \n\n')
        except:
            print('Opção inválida! Digite um inteiro menor que n! \n\n')

    # Geração da chave privada
    print('Gerando chave privada: \n\n')
    phi_n=func_totient(p, q)
    MDCE = func_MDCE(e, phi_n) # o inverso multiplicativo do expoente e
    d = MDCE[0] # O inverso multiplicativo do expoente e
    if d < 0:
        while d<0:
            d=d+phi_n
    chavePv.append(n) # o tamanho do conjunto (n), é o primeiro elemento da chave privada.
    chavePv.append(d) # o inverso multiplicativo de e é o segundo elemento da chave privada.
    func_escreveArquivo('chavePv.txt', chavePv, '\n')
    print('Chave privada gerada\n------------------------------\n\n')
    system('cls') or None # o none é para não sobrar um 0 no prompt de comandos depois da limpeza da tela

    # Obtensão da mensagem que será descriptografada
    while True:
        try:
            print('Como deseja inserir a mensagem a ser descriptografada? \n Escolha uma opção')
            quest3 = int(input('"1": digitando, "2": de um arquivo armazenado neste computador: '))
            if quest3 == 1 or quest3 == 2:
                break
            else:
                print('Opção inválida! \n')
        except:
            print('Opção inválida! Insira apenas números.\n\n')
        system('cls') or None # o none é para não sobrar um 0 no prompt de comandos depois da limpeza da tela

    if quest3==1:
        msg= input('Digite a mensagem criptografada separando os números por espaços. "ENTER" termina: ')

    msg=msg.split() # Transformamos a string numa lista.

    # descriptografando e salvando num arquivo na pasta atual.
    # m = c ^ d mod n
    for i in msg:
        c=func_modulo(int(i), d, n)
        if c < len(alfabeto):

            msgDecifrada.append(alfabeto[c])

    print("Salvando a mensagem decifrada num arquivo".center(15))
    print('\n\n')
    func_escreveArquivo('mensagem decifrada.txt', msgDecifrada, '')
    print("Mensagem decifrada com sucesso!")



#------------------------------


def func_menu():
    print('ESCOLHA UMA OPÇÃO'.center(15)) # o texto deve ficar centralizado
    print() # imprime uma linha em branco na tela
    try:
        opcao = int(input('1: gerar chave pública, 2: criptografar, 3: descriptografar, 4: sair: '))
        if opcao == 1:
            func_gerarChave()
        elif opcao == 2:
            func_criptografar()
        elif opcao == 3:
            func_descriptografar()
        elif opcao == 4:
            print('Até a próxima.\nMantenha suas informações seguras!')
            return
    except:
        print('Opção inválida!')
        func_menu()
    system('cls') or None # o none é para não sobrar um 0 no prompt de comandos depois da limpeza da tela
#------------------------------

def func_main():
    print('CRIPTO -- gerador e interpretador de mensagens criptografadas\n'.center(15))
    func_menu()
func_main()

cripto.py
Exibindo cripto.py.