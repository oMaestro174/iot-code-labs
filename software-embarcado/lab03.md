# Simulação de Escalonamento de Tarefas Periódicas em C 

Este projeto simula o escalonamento cooperativo de tarefas periódicas em um sistema embarcado de tempo real, sem uso de RTOS, para fins didáticos.

## Aluno

- **Nome:** Janei Vieira Pereira  
- **Turma:** ECAI_IOT  
- **Atividade:** 02

## Objetivos

- Modelar tarefas periódicas com deadlines.
- Simular execução e medir utilização da CPU.
- Detectar deadlines perdidos.
- Facilitar análise temporal sem hardware embarcado.

## Como funciona

O código principal está em [`escalonamento.c`](escalonamento.c). Ele define três tarefas:
- **Navegação** (100ms, duração 20ms)
- **Coleta** (500ms, duração 50ms)
- **Monitoramento** (1000ms, duração 100ms)

A função `millis()` simula o tempo decorrido usando `clock()` da biblioteca padrão C.

O loop principal executa as tarefas conforme seus períodos, detectando deadlines perdidos e calculando a utilização do processador.

## Execução

Compile com:

```sh
gcc escalonamento.c -o escalonamento
./escalonamento
```

## Exemplo de Saída

```
=== INICIANDO ESCALONADOR DE TAREFAS DO ROBÔ ===

[0 ms] [NAV] Iniciando: Atualizando posição do robô...
[20 ms] [NAV] Concluído: Posição atualizada.
...
=== SIMULAÇÃO FINALIZADA ===
Tempo total de execução: 5000 ms
Total de ciclos executados: 50
Utilização aproximada do processador: 37.00%
```

## Telas do Projeto

Tela 01 -  Execução da simulação no terminal
![`escalonamento.c`](/software-embarcado/assets/Screenshot_20250613_152111.png) 

Tela 02 -  Exemplo de saída com deadlines perdidos
![`escalonamento.c`](/software-embarcado/assets/Screenshot_20250613_154007.png)

## Links

- [Documentação do clock() - C Library](https://en.cppreference.com/w/c/chrono/clock)

Projeto desenvolvido para fins acadêmicos na disciplina de IoT.
