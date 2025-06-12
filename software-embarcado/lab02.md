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

Baixe o código fonte [`alarme.c`](/software-embarcado/alarme.c) 

### Usando GCC (Linux, Windows com MinGW ou WSL)
Certifique-se de ter o GCC instalado. No Linux, instale com:

```
sudo apt update && sudo apt install build-essential
```
No Windows, recomenda-se instalar o [MinGW](https://www.mingw-w64.org/) ou usar o WSL (Subsistema Linux para Windows).

Para compilar:
```
gcc alarme.c -o alarme
```

### Usando Code::Blocks (Windows)
O Code::Blocks já vem com um compilador embutido. Basta:
1. Abrir o Code::Blocks
2. Criar um novo projeto do tipo "Console Application" em C
3. Substituir o conteúdo do arquivo principal pelo código de `alarme.c`
4. Clicar em "Build and Run" (ou pressione F9)

## Como executar
Após compilar, execute no terminal:

```
./alarme
```
No Windows, pode ser:
```
alarme.exe
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

## Telas do Projeto

Tela 01 -  Compilando e rodando Menu
![`alarme.c`](/software-embarcado/assets/Screenshot_20250611_215600.png) 

Tela 02 -  Ativando o alarme
![`alarme.c`](/software-embarcado/assets/Screenshot_20250611_215702.png) 

Tela 03 -  Simulação de cômodo inválido
![`alarme.c`](/software-embarcado/assets/Screenshot_20250611_215747.png) 

Tela 04 -  Histórico de comando e testes
![`alarme.c`](/software-embarcado/assets/Screenshot_20250611_215824.png) 

## Autor
- Atividade desenvolvida para fins didáticos.
