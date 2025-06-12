# Sistema de Alarme Residencial em C

## Descrição
Este projeto simula um sistema de alarme residencial para uma casa com três cômodos: Sala, Quarto e Cozinha. O sistema permite ativar/desativar o alarme com senha, simular detecção de movimento em cada cômodo e visualizar o status do sistema e dos sensores.

## Funcionalidades
- **Ativar alarme:** Protege a casa, requer senha ("1234").
- **Desativar alarme:** Desativa a proteção, requer senha.
- **Simular movimento:** Permite simular a detecção de movimento em qualquer cômodo.
- **Ver status:** Mostra o estado do alarme e dos sensores de cada cômodo.
- **Menu interativo:** Interface via terminal para fácil navegação.

## Como compilar
Execute o comando abaixo no terminal:

```
gcc alarme.c -o alarme
```

## Como executar
Após compilar, execute:

```
./alarme
```

## Exemplo de uso
```
--- Sistema de Alarme Residencial ---
1. Ativar alarme
2. Desativar alarme
3. Simular movimento
4. Ver status
5. Sair
Escolha: 1
Digite a senha: 1234
Alarme ativado com sucesso.
Escolha: 3
Escolha o cômodo (0: Sala, 1: Quarto, 2: Cozinha): 1
[ALERTA] Movimento detectado no Quarto! Alarme disparado!
Escolha: 4
Status: Alarme ATIVADO
Sala: Sem movimento
Quarto: Movimento detectado
Cozinha: Sem movimento
```

## Estrutura do código
- Uso de arrays para armazenar nomes dos cômodos e estados dos sensores.
- Funções para ativar/desativar alarme, simular movimento e exibir status.
- Controle de acesso por senha.
- Menu com `switch-case` para navegação.

## Autor
- Atividade desenvolvida para fins didáticos.
