# Controle de Servomotor por PWM no RP2040

Repositório criado para a atividade individual da disciplina **Unidade 4 | Capítulo 7**, ministrada pelo professor **Ricardo Menezes Prates**. O projeto utiliza o **microcontrolador RP2040** para simular o controle do ângulo de um servomotor por meio do módulo **PWM **.

## Objetivos do Projeto

O objetivo desta atividade é implementar um sistema capaz de controlar a posição de um servomotor padrão no **simulador Wokwi**, utilizando o **PWM do Raspberry Pi Pico W**. A implementação contempla:

- Definição da frequência do PWM.
- Configuração de ciclos ativos para posicionamento do servomotor em 0°, 90° e 180°.
- Movimentação contínua do servomotor entre os extremos com transição suave.
- Testes com o LED RGB (GPIO 12) na BitDogLab para observação do comportamento do LED sob o efeito do PWM.

---

## Funcionalidades

### 1. Configuração do PWM na GPIO 22
- O sinal PWM é configurado para uma frequência de **50 Hz** (período de **20 ms**).

### 2. Controle de Posição do Servomotor
- O ciclo ativo do PWM é ajustado para diferentes valores, conforme a tabela:
  
  | Posição (graus) | Ciclo Ativo (us) | Duty Cycle (%) | Tempo |
  |------------------|----------------|----------------|--------|
  | 180°           | 2400 µs       | 0,12%          | 5s     |
  | 90°            | 1470 µs       | 0,0735%        | 5s     |
  | 0°             | 500 µs        | 0,025%         | 5s     |

### 3. Movimentação Contínua
- O servo se movimenta suavemente entre 0° e 180°, ajustando o ciclo ativo em incrementos de **±5 µs** a cada **10 ms**.

### 4. Teste com o LED RGB (GPIO 12)
- A iluminação do LED RGB é observada para entender o impacto do PWM na BitDogLab.

---

## Dependências

Para compilar e executar este projeto, você precisará:

- **Placa Raspberry Pi Pico W** (ou simulação no Wokwi)
- **Ambiente de Desenvolvimento RP2040** (CMake, GCC, Pico SDK)
- **Simulador Wokwi**
- **VS Code** 

---

## Instruções de Instalação

1. **Clonar o repositório**
    ```bash
    git clone https://github.com/GfppLLa/picoPWM
    cd picoPWM
    ```

2. **Criar diretório para build**
    ```bash
    mkdir build
    cd build
    ```

3. **Gerar arquivos para compilação**
    ```bash
    cmake ..
    ```

4. **Compilar o projeto**
    ```bash
    make
    ```

5. **Executar a simulação** no Wokwi
    ```bash
    wokwi-server --project picoPWM
    ```

6. **Carregar o código na bitDogLab**
    ```bash
    picotool load build/picoPWM.uf2
    ```

---

## Estrutura do Projeto

1. `picoPWM.c` - Código-fonte do projeto.
2. `build/` - Saída dos binários.
3. `CMakeLists.txt` - Configuração do CMake.

---

## Vídeo de Demonstração

Veja uma demonstração em vídeo do funcionamento do projeto:

[**Assista à Demonstração**](https://youtube.com/live/nZ7zuGoTwJ0)

---

## Licença

Este projeto está licenciado sob a **Licença GNU**.

---

<div align="center">
    GNUs not Unix
<pre>
    _-`````-,           ,- '- .
  .'   .- - |          | - -.  `.
 /.'  /                     `.   \
:/   :      _...   ..._      ``   :
::   :     /._ .`:'_.._\.    ||   :
::    `._ ./  ,`  :    \ . _.''   .
`:.      /   |  -.  \-. \\_      /
  \:._ _/  .'   .@)  \@) ` `\ ,.'
     _/,--'       .- .\,-.`--`.
       ,'/''     (( \ `  )    
        /'/'  \    `-'  (      
         '/''  `._,-----'
          ''/'    .,---'
           ''/'      ;:
             ''/''  ''/
               ''/''/''
                 '/'/'
                  `;      
<pre>
</div>
