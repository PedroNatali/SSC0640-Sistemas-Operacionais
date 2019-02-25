import math

#calcula a distancia entre 2 pontos(euclidiana)
def distancia_local(a,b):
	return math.sqrt(pow(a-b, 2))

#funcao que calcula o dtw
def dtw(s,t):
	distancia = 0
#criando a matriz c/ valores vazios
	vetor_anterior = []
	for i in range(len(s)):
		linha = []
		vetor_anterior.append(linha)

#estrutura destinada a guardar a distancia ao setar valor inicial -1
	distancia = []
	valor_defaut = -1
	for i in range(len(s)):
		linha = []
		for j in range(len(t)):
			linha.append(valor_defaut)
		distancia.append(linha)

#visita todas as posicoes
	for i in range(len(s)):
		for j in range(len(t)):
#analisando o caso base 
			if (i==0) and (j==0):
				distancia[i][j] = distancia_local(s[i], t[j])
#analisando o caso onde soh i eh zero
			elif (i==0):
				assert distancia[i][j-1] >= 0
				distancia[i][j] = distancia[i][j-1] + distancia_local(s[i],t[i])
#analisando  caso onde soh j eh zero			
			elif(j==0):
				assert distancia[i-1][j] >= 0
				distancia[i][j] = distancia[i-1][j] + distancia_local(s[i], t[j])
#caso mais comum, vetor vindo de um lugar qlqr			
			else :
#checa se as posicoes anteriores ja foram visitadas
				assert distancia[i][j-1]>=0
				assert distancia[i-1][j]>=0
				assert distancia[i-1][j-1]>=0
#Parte 'principal' do programa que analisa a menor distancia comparando com as outras e pegando a menor
				menor_distancia = distancia[i-1][j]
 
				if distancia[i][j-1] < menor_distancia:
 					menor_distancia = distancia[i][j-1]
 
				if distancia[i-1][j-1] < menor_distancia:
					menor_distancia = distancia[i-1][j-1]
 
				distancia[i][j] = menor_distancia + distancia_local( s[i], t[j] )

	melhor_distancia = distancia[len(s)-1][len(t)-1]

	return melhor_distancia 

#funcao que executa a ordenacao da matriz
def quick_Sort(matriz_nao_ordenada):
	if len(matriz_nao_ordenada) <= 1:
		return matriz_nao_ordenada
	meio = matriz_nao_ordenada[(len(matriz_nao_ordenada)-1)/2]
	matriz_nao_ordenada.remove(meio)
	parte_menor = []
	parte_maior = []
	for i in range(len(matriz_nao_ordenada)):
		if matriz_nao_ordenada[i][1] <= meio[1]:
			parte_menor.append(matriz_nao_ordenada[i])
		else:
			parte_maior.append(matriz_nao_ordenada[i])
	return quick_Sort(parte_menor) + [meio] + quick_Sort(parte_maior)

# As funcoes leitura e separador criam a 'matriz' 
# e alocam o arquivo a ela, separando por linha do arquivo
#nota-se que o arquivo eh entao transformado em float
#a fim de que possamos realizar as operacoes matematicas
def leitura(arquivo):
	arquivo_aberto = open(arquivo, 'r')
	conjunto_de_linhas = []
	linha_do_arquivo = arquivo_aberto.readline()
	conjunto_de_linhas.append(linha_do_arquivo)
	for linha_do_arquivo in arquivo_aberto:
		conjunto_de_linhas.append(linha_do_arquivo)
	arquivo_aberto.close
	return conjunto_de_linhas

def separador(vet):
	tamanho_vet = len(vet)
	linha_separada_1 = [-1] * tamanho_vet
	linha_separada_2 = [-1] * tamanho_vet
	for j in range(tamanho_vet):
		linha_separada_2[j] = vet[j].split()
		linha_separada_1[j] = [float(x) for x in linha_separada_2[j]]
	return linha_separada_1

#essa funcao eh responsavel por criar a matriz de 
#distancias do dtw
def distancias_usando_dtw(serie111,serie2222):
	tamanho = len(serie2222)
	valores_pos_dtw = [-1] * tamanho
	for k in range(tamanho):
		valores_pos_dtw[k] = [-1] * 2
	for i in range(tamanho):	
		valores_pos_dtw[i][0] = serie2222[i][0]
		primeiro_vetor = serie111[1:len(serie111)]
		segundo_vetor = serie2222[i][1:len(serie2222[i])]
		valores_pos_dtw[i][1] = dtw(primeiro_vetor,segundo_vetor)
	return valores_pos_dtw

#O vetor eh cortado, sao criadas matrizes onde o primeiro
#elemento corresponde ao tipo e o resto ao dtw
#e por fim o tipo mais comum eh alocado ao ultimo elemento
#eu usei esses float-int pq nao tava dando pra jogar direto no int, entao primeiro
#passei pra float e dps pra int, que curiosamente funcionou (nao entendi o porque)
def k_vizinhos_mais_proximos(tipos_de_movimento_ordenados, numero_de_k_vizinhos):	
	
	auxiliar = tipos_de_movimento_ordenados[0:numero_de_k_vizinhos]

	conjunto_de_tipos = [0] * 12

	for j in range(12):
		conjunto_de_tipos[j] = [0] * 2
		conjunto_de_tipos[j][0] = j+1

	for i in range(0,numero_de_k_vizinhos,1):
		tipo = (auxiliar[i][0])
		tipo = float(tipo)
		tipo_usaremos = int(tipo) - 1
		conjunto_de_tipos[tipo_usaremos][1] = conjunto_de_tipos[tipo_usaremos][1] + 1

	conjunto_ordenado = quick_Sort(conjunto_de_tipos)
	tamanho = len(conjunto_ordenado) - 1

	tipo_mais_comum = conjunto_ordenado[tamanho][0]

	return tipo_mais_comum

def tenta_adivinhar_tipo(serie11, serie22, k):
	#eh feita uma matriz com os dtws
	valores_pos_dtw = distancias_usando_dtw(serie11, serie22)
	#essa matriz eh ordenada
	valores_ordenados = quick_Sort(valores_pos_dtw)
	#o tipo eh excluido pq aqui nao eh necessario
	tamanho = len(valores_ordenados)
	for i in range(tamanho):
		valores_ordenados[i].pop(1)
	#o vetor que usaremos para analisar o tipo eh alocado
	tipos_de_movimento_ordenados = valores_ordenados	
	tipo_real_do_movimento = k_vizinhos_mais_proximos(tipos_de_movimento_ordenados, k)
	#apos executar a analise eh retornado o tipo 
	return tipo_real_do_movimento

#funcao ja explicada na main
def verifica_tipo(serie1, serie2, k):
	nao_adivinhou = 0
	adivinhou = 0
	for j in range(0,960,10):
		movimento = float(serie1[j][0])
		tipo_real_do_movimento = int(movimento)
		tipo_adivinhado = int(tenta_adivinhar_tipo(serie1[j], serie2, k))
		if (tipo_real_do_movimento == tipo_adivinhado):
			adivinhou  = adivinhou + 1
		else:
			nao_adivinhou = nao_adivinhou + 1
	
	balanco_total = adivinhou + nao_adivinhou
	percentual_de_acertos = float(100*adivinhou/balanco_total)
	print "Os acertos correspondem a", percentual_de_acertos, "%"

if __name__ == "__main__":
 
	#abre o arquivo e o transforma em matriz de acordo com a linha ( para ambos teste e treino )
	x1 = leitura("teste.txt")
	y1 = separador(x1)
	#fiz essa separacao em string so pra garantir que tudo daria certo e o fato do primeiro
	#elemento ser float nao prejudicar
	for i in range(len(y1)):
		y1[i][0] = str(y1[i][0])


	x2 = leitura("treino.txt")
	y2 = separador(x2)
	for i in range(len(y2)):
		y2[i][0] = str(y2[i][0])
	#eh dado como entrada as duas series e o valor de k (terceiro elemento)
	#a partir das series, havera a verificacao para analise de tipo
	#sempre que o tipo for igual ao esperado, eh dado 
	#que o algoritmo adivinhou
	verifica_tipo(y1,y2,1)
