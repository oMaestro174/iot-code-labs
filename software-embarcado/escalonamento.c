#include <stdio.h>
#include <time.h>
#include <stdbool.h>

//Definições periodos
#define TASK_NAVIGATION_PERIOD_MS 100
#define TASK_COLLECTION_PERIOD_MS 500
#define TASK_MONITORING_PERIOD_MS 1000
//Duração
#define TASK_NAVIGATION_DURATION_MS 20
#define TASK_COLLECTION_DURATION_MS 50
#define TASK_MONITORING_DURATION_MS 100

//pegar tempo em ms
unsigned long millis(){
  return (unsigned long)(clock() * 1000/CLOCKS_PER_SEC);
}

typedef struct {
  const char* name;
  void (*function)(void);
  unsigned long period_ms;
  unsigned long duration_ms;
  unsigned long last_execution;
  unsigned long next_deadline;
  bool is_running;
}Task;

//Task navegação
void task_navigation(){
  unsigned long start_time = millis();
  printf("[%lu ms] [NAV] Iniciando: Atualizando posição do robo ... \n", start_time);
  
  //Execução
  while((millis() - start_time) < TASK_NAVIGATION_DURATION_MS){
    // somente simulando
  }
  printf("[%lu ms] [NAV] Concluido: Posição atualizada \n", millis());
}

//[TODO] Criar outras tarefas ....

//Tarefa deve ser executada
bool should_execute_task(Task* task, unsigned long current_time){
  return (current_time - task->last_execution) >= task->period_ms && !task->is_running;
}

void execute_task(Task* task, unsigned long current_time){
  if(task->is_running){
    printf("[ERROR] tentativa de executar a tarefa %s \n", task->name);
    return;
  }
  //ok vamos executar
  task->is_running = true;
  task->last_execution = current_time;
  task->next_deadline = current_time + task->period_ms;
  task->function();
  task->is_running = false;
}

void check_missed_deadlines(Task* task, int num_tasks, unsigned long current_time){
  for(int i =0; i < num_tasks; i++){
    if(task[i].next_deadline > 0 &&
       current_time > task[i].next_deadline &&
       !task[i].is_running){
       printf("[ALERTA] deadline perdido %s \n", task->name);
    }
  }
}

int main(){
  printf("=== INICIANDO ESCALONADOR DE TAREFAS DO ROBO ===\n\n");
  //definição das tarefas
  Task tasks[] = {
    {
      "Navegacao", task_navigation, TASK_NAVIGATION_PERIOD_MS,
      TASK_NAVIGATION_DURATION_MS, 0, 0, false      
    }
    /**,
    {
      "Coleta", task_collection, TASK_COLLECTION_PERIOD_MS,
      TASK_COLLECTION_DURATION_MS, 0, 0, false      
    },
    {
      "Monitoramento", task_monitoring, TASK_MONITORING_PERIOD_MS,
      TASK_MONITORING_DURATION_MS, 0, 0, false      
    }**/
  };
  
  int num_tasks = sizeof(tasks)/sizeof(Task);
  
  unsigned long start_time = millis();
  unsigned long last_stats_time = start_time;
  int cycle_count = 0;
  
  printf("Iniciando a execução das tarefas \n\n");
  while((millis() - start_time) < 5000){
    unsigned long current_time = millis();
    check_missed_deadlines(tasks, num_tasks, current_time);
    //Escalonar por prioridades
    for(int i; i< num_tasks; i++){
      if(should_execute_task(&tasks[i], current_time)){
        execute_task(&tasks[i], current_time);
        cycle_count++;
        break;
      }
      //delay
      for(int i = 0; i < 1000; i++);     
    }
    
    printf("\n === SIMULAÇÃO FINALIZADA === \n");
    printf("Tempo total de execução: %lu ms\n", millis()-start_time);
    
  }
  
  
  return 0;
}
