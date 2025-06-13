// Aluno: JANEI VIEIRA PEREIRA
// Turma: ECAI_IOT
// Atividade: 02
// Link para o repositório:

// Esta simulação foi desenvolvida para cumprir os objetivos da atividade: modelar tarefas periódicas em um sistema embarcado de tempo real sem uso de RTOS e permitir análise temporal com deadlines.
// As tarefas foram implementadas com base nos requisitos fornecidos (período e duração).
// O uso de millis() simulado com clock() foi adotado para medir tempo sem precisar de hardware embarcado.
// A análise final inclui detecção de deadlines perdidos e cálculo da utilização da CPU.
// A abordagem é cooperativa (executa uma tarefa por vez), respeitando o modelo simplificado solicitado na atividade.
// Se necessário, o código pode ser facilmente adaptado para plataformas como Arduino ou ESP32 com pequenas modificações nos temporizadores.


#include <stdio.h>
#include <time.h>
#include <stdbool.h>

// ----------------------
// DEFINIÇÕES GERAIS
// ----------------------

// Definimos os períodos das três tarefas do sistema, em milissegundos
#define TASK_NAVIGATION_PERIOD_MS    100
#define TASK_COLLECTION_PERIOD_MS    500
#define TASK_MONITORING_PERIOD_MS   1000

// Duração simulada de execução para cada tarefa (em milissegundos)
#define TASK_NAVIGATION_DURATION_MS   20
#define TASK_COLLECTION_DURATION_MS   50
#define TASK_MONITORING_DURATION_MS  100

// Tempo total de simulação (por exemplo, 5 segundos)
#define SIMULACAO_TEMPO_TOTAL_MS    5000

// Função que retorna o tempo decorrido desde o início da simulação em milissegundos
// Usamos clock() da biblioteca <time.h> para simular o comportamento de 'millis()' de sistemas embarcados
unsigned long millis() {
    return (unsigned long)(clock() * 1000 / CLOCKS_PER_SEC);
}

// ----------------------
// ESTRUTURA DE TAREFA
// ----------------------

// Criamos uma struct para encapsular todas as informações de uma tarefa periódica
typedef struct {
    const char* name;              // Nome da tarefa
    void (*function)(void);        // Ponteiro para a função que implementa a tarefa
    unsigned long period_ms;       // Período da tarefa
    unsigned long duration_ms;     // Duração estimada de execução
    unsigned long last_execution;  // Última vez que a tarefa foi executada
    unsigned long next_deadline;   // Prazo (deadline) da próxima execução
    bool is_running;               // Flag para evitar reentradas
} Task;

// ----------------------
// IMPLEMENTAÇÃO DAS TAREFAS
// ----------------------

// Cada função abaixo simula o comportamento de uma tarefa do robô,
// executando "busy wait" pelo tempo estimado, para simular consumo de CPU

void task_navigation() {
    unsigned long start_time = millis();
    printf("[%lu ms] [NAV] Iniciando: Atualizando posição do robô...\n", start_time);

    while ((millis() - start_time) < TASK_NAVIGATION_DURATION_MS);  // Simula execução
    printf("[%lu ms] [NAV] Concluído: Posição atualizada.\n", millis());
}

void task_collection() {
    unsigned long start_time = millis();
    printf("[%lu ms] [COLETA] Iniciando: Ativando braço mecânico...\n", start_time);

    while ((millis() - start_time) < TASK_COLLECTION_DURATION_MS);
    printf("[%lu ms] [COLETA] Concluído: Caixa coletada.\n", millis());
}

void task_monitoring() {
    unsigned long start_time = millis();
    printf("[%lu ms] [MONITORAMENTO] Iniciando: Atualizando inventário...\n", start_time);

    while ((millis() - start_time) < TASK_MONITORING_DURATION_MS);
    printf("[%lu ms] [MONITORAMENTO] Concluído: Inventário atualizado.\n", millis());
}

// ----------------------
// ESCALONAMENTO DAS TAREFAS
// ----------------------

// Função que decide se uma tarefa está pronta para ser executada com base no tempo atual
bool should_execute_task(Task* task, unsigned long current_time) {
    return (current_time - task->last_execution) >= task->period_ms && !task->is_running;
}

// Função que executa a tarefa e atualiza suas variáveis de controle
void execute_task(Task* task, unsigned long current_time) {
    if (task->is_running) {
        printf("[ERRO] Tarefa %s já está em execução!\n", task->name);
        return;
    }

    task->is_running = true;
    task->last_execution = current_time;
    task->next_deadline = current_time + task->period_ms;

    task->function();  // Chama a função da tarefa
    task->is_running = false;
}

// Verifica se alguma tarefa perdeu seu deadline (prazo), apenas para fins de simulação
void check_missed_deadlines(Task* tasks, int num_tasks, unsigned long current_time) {
    for (int i = 0; i < num_tasks; i++) {
        if (tasks[i].next_deadline > 0 &&
            current_time > tasks[i].next_deadline &&
            !tasks[i].is_running) {
            printf("[ALERTA] Deadline perdido para a tarefa: %s\n", tasks[i].name);
        }
    }
}

// ----------------------
// FUNÇÃO PRINCIPAL
// ----------------------

int main() {
    printf("=== INICIANDO ESCALONADOR DE TAREFAS DO ROBÔ ===\n\n");

    // Inicializamos as 3 tarefas com seus respectivos dados
    Task tasks[] = {
        { "Navegacao", task_navigation, TASK_NAVIGATION_PERIOD_MS, TASK_NAVIGATION_DURATION_MS, 0, 0, false },
        { "Coleta", task_collection, TASK_COLLECTION_PERIOD_MS, TASK_COLLECTION_DURATION_MS, 0, 0, false },
        { "Monitoramento", task_monitoring, TASK_MONITORING_PERIOD_MS, TASK_MONITORING_DURATION_MS, 0, 0, false }
    };

    int num_tasks = sizeof(tasks) / sizeof(Task);
    unsigned long start_time = millis();  // Tempo inicial da simulação
    int cycle_count = 0;                  // Contador de execuções feitas

    // Loop principal: simula o comportamento do sistema por 5 segundos
    while ((millis() - start_time) < SIMULACAO_TEMPO_TOTAL_MS) {
        unsigned long current_time = millis();

        // Checa se alguma tarefa perdeu o deadline
        check_missed_deadlines(tasks, num_tasks, current_time);

        // Executa uma tarefa por vez (modelo cooperativo simples)
        for (int i = 0; i < num_tasks; i++) {
            if (should_execute_task(&tasks[i], current_time)) {
                execute_task(&tasks[i], current_time);
                cycle_count++;
                break;  // Executamos apenas uma tarefa por ciclo (cooperativo)
            }
        }

        // Pequeno atraso para simular um sistema embarcado real
        for (volatile int d = 0; d < 10000; d++);
    }

    // ----------------------
    // RELATÓRIO FINAL
    // ----------------------

    printf("\n=== SIMULAÇÃO FINALIZADA ===\n");
    printf("Tempo total de execução: %lu ms\n", millis() - start_time);
    printf("Total de ciclos executados: %d\n", cycle_count);

    // Cálculo da utilização da CPU com base nas fórmulas de tempo real
    // U = C1/T1 + C2/T2 + C3/T3
    float utilizacao =
        ((float)TASK_NAVIGATION_DURATION_MS / TASK_NAVIGATION_PERIOD_MS) +
        ((float)TASK_COLLECTION_DURATION_MS / TASK_COLLECTION_PERIOD_MS) +
        ((float)TASK_MONITORING_DURATION_MS / TASK_MONITORING_PERIOD_MS);

    printf("Utilização aproximada do processador: %.2f%%\n", utilizacao * 100);

    return 0;
}
