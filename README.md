# comppar-lab03-pthreads

## A função de Fibonacci pode ser facilmente calculada da seguinte forma:

fib(n) = fib(n-1) + fib(n-2)

sendo que fib(0)=0 e fib(1)=1.

O que acontece se, de alguma forma, fossem calculados os termos dessa soma de forma paralela?

Para isso, construa a função fib() que receba o parâmetro n e utilize PThreads para realizar a soma dos termos em threads diferentes. Ao final, mostre o resultado dessa soma.

Como parte do experimento, faça a validação dos resultados calculando o valor de n de forma tradicional e comparando com o valor do n calculado com threads, medindo o tempo gasto com cada um desses cálculos. Use apenas o programa `fibonacci.c` para este experimento. 

### Entrega:

Submeta seu código aqui no GitHub e também um PDF com os prints da execução do seu código.

## Experimentação de conta corrente

Neste experimento, construa alguns programas usando PThreads que reproduzam um problema clássico de condição de corrida no contexto de uma conta corrente e uma respectiva solução.

Garanta que os resultados entre uma solução com condição de corrida seja diferente de uma solução sem condição de corrida.

### Preparação - Fase 0

Construa um programa que seja seu baseline para as próximas fases do experimento. Use o programa `contacorrente.c` para este baseline.

### Fase 1

Construa uma outra versão da solução anterior usando a biblioteca PThreads e que tenha condição de corrida no saque/deposito da conta corrente. Nesta solução, o resultado do saldo final não será igual a versão baseline. Use o programa `contacorrentef1.c` para esta fase.

### Fase 2

Construa uma nova solução da versão anterior resolvendo o problema da condição de corrida com seção crítica (mutex). Garanta que o saldo final apresentado nesta fase do experimento seja igual ao baseline e, consequentemente, diferente da fase 1. Use o programa `contacorrentef2.c` para esta fase.

### Entregas

Submeta seu código aqui no GitHub e também crie um PDF com as evidências de execuções (eg. print de tela da execução).

## Números primos

Faça um programa usando PThreads que encontre todos os números primos até N; defina uma função no seu programa que receba 2 parâmetros J e K (individualmente ou por vetor), indicando o número de início e de fim dessa pequisa. O número de threads deve ser definido por argumento de linha de comando na chamada do programa ou por variável de ambiente (NTHREADS).

### Entregas

Submeta seu código aqui no GitHub (vc vai criar um novo arquivo fonte) e também os prints (PDF) das evidências de execuções.
