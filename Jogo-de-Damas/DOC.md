# 🎲 Jogo de Damas

Projeto de um jogo de damas desenvolvido em **C++**, utilizando a biblioteca **Raylib** para a interface gráfica.

O projeto também possui um sistema de cadastro e login de usuários, armazenamento de dados em arquivo binário e comunicação em rede para permitir partidas entre computadores.

---

## 📌 Tecnologias utilizadas

- C++
- C++17
- Raylib
- Code::Blocks
- GNU GCC
- TCP/IP
- Sockets
- Arquivos binários

# 🌐 Comunicação em rede

A comunicação entre jogadores é feita utilizando o modelo **cliente-servidor**.

Um computador executa o programa como **servidor** e fica aguardando a conexão de outro computador, que executa o programa como **cliente**.

```text
              REDE LOCAL / WI-FI

        ┌──────────────────────┐
        │      SERVIDOR        │
        │                      │
        │ IP: 192.168.0.9      │
        │ Porta: 5000          │
        └──────────┬───────────┘
                   │
                   │ TCP
                   │
        ┌──────────▼───────────┐
        │       CLIENTE        │
        │                      │
        │ Outro computador     │
        └──────────────────────┘
```

Inicialmente, a comunicação foi testada utilizando dois computadores conectados à mesma rede Wi-Fi.

---

# 📡 O que é uma rede?

Uma rede permite que dois ou mais dispositivos troquem informações.

No projeto, a rede será utilizada para que dois jogadores possam jogar uma partida de damas em computadores diferentes.

Por exemplo:

```text
Computador A
IP: 192.168.0.9

        ↓

      REDE WI-FI

        ↓

Computador B
IP: 192.168.0.15
```

Os computadores conseguem trocar mensagens através da rede.

---

# 🔢 O que é um endereço IP?

O **IP (Internet Protocol)** identifica um dispositivo dentro de uma rede.

Por exemplo:

```text
192.168.0.9
```

Esse endereço pode identificar o computador que está executando o servidor.

Para descobrir o IP no Linux, podemos utilizar:

```bash
hostname -I
```

Exemplo:

```text
192.168.0.9
```

No Windows, podemos utilizar:

```cmd
ipconfig
```

e procurar pelo campo:

```text
Endereço IPv4
```

---

# 🚪 O que é uma porta?

A porta identifica qual serviço ou aplicação deve receber a comunicação dentro de um computador.

Neste projeto foi utilizada a porta:

```text
5000
```

Portanto, o servidor pode ser acessado utilizando:

```text
192.168.0.9:5000
```

Podemos pensar da seguinte forma:

```text
IP       → identifica o computador
Porta    → identifica o serviço
```

Exemplo:

```text
192.168.0.9:5000
```

---

# 🖥️ Servidor e cliente

## Servidor

O servidor é responsável por:

- Criar o socket;
- Definir IP e porta;
- Aguardar conexões;
- Aceitar jogadores;
- Receber mensagens;
- Validar informações;
- Enviar informações para os clientes;
- Controlar o estado da partida.

O servidor funciona como o ponto central da partida.

---

## Cliente

O cliente é responsável por:

- Criar o socket;
- Informar o IP do servidor;
- Informar a porta;
- Solicitar a conexão;
- Enviar informações;
- Receber informações do servidor;
- Exibir o estado atualizado da partida.

---

# 🔌 O que é um Socket?

Um **socket** é uma interface utilizada para permitir a comunicação entre programas através da rede.

No projeto, o socket é utilizado para criar o canal de comunicação entre cliente e servidor.

A criação do socket é feita com:

```cpp
int servidor = socket(AF_INET, SOCK_STREAM, 0);
```

Nesse código:

```text
AF_INET
```

indica que será utilizado o protocolo de endereçamento IPv4.

```text
SOCK_STREAM
```

indica uma comunicação baseada em fluxo, utilizada com TCP.

---

# 📦 TCP

O projeto utiliza **TCP (Transmission Control Protocol)**.

O TCP estabelece uma conexão entre cliente e servidor e garante que os dados sejam entregues de forma confiável e ordenada.

Isso é importante para o jogo porque uma jogada não pode simplesmente desaparecer durante a transmissão.

Por exemplo:

```text
Jogador faz uma jogada
        ↓
Cliente envia a jogada
        ↓
Servidor recebe
        ↓
Servidor valida
        ↓
Servidor atualiza o tabuleiro
        ↓
Servidor envia atualização
        ↓
Outro jogador recebe
```

---

# 🏠 Localhost

Durante os primeiros testes foi utilizado:

```text
127.0.0.1
```

Esse endereço representa o próprio computador.

Também podemos chamá-lo de:

```text
localhost
```

Quando utilizamos:

```text
127.0.0.1:5000
```

o cliente está tentando conectar ao servidor que está executando no mesmo computador.

---

# 🌎 Comunicação entre dois computadores

Depois do teste utilizando `localhost`, foi possível utilizar dois computadores na mesma rede.

Por exemplo:

```text
Servidor:

IP: 192.168.0.9
Porta: 5000
```

No cliente:

```cpp
inet_pton(AF_INET, "192.168.0.9", &endereco.sin_addr);
```

Nesse caso, o cliente tenta se conectar ao computador que possui o IP:

```text
192.168.0.9
```

utilizando a porta:

```text
5000
```

O endereço completo pode ser representado como:

```text
192.168.0.9:5000
```

---

# ⚙️ Funcionamento do servidor

O servidor segue algumas etapas para estabelecer a comunicação.

## 1. Criar o socket

```cpp
int servidor = socket(AF_INET, SOCK_STREAM, 0);
```

Cria o socket que será utilizado pelo servidor.

---

## 2. Definir o endereço

```cpp
sockaddr_in endereco;

endereco.sin_family = AF_INET;
endereco.sin_addr.s_addr = INADDR_ANY;
endereco.sin_port = htons(5000);
```

A estrutura `sockaddr_in` armazena informações relacionadas ao endereço IPv4.

### `sin_family`

```cpp
endereco.sin_family = AF_INET;
```

Indica que será utilizado IPv4.

### `sin_addr`

```cpp
endereco.sin_addr.s_addr = INADDR_ANY;
```

Indica que o servidor poderá aceitar conexões através das interfaces de rede disponíveis.

### `sin_port`

```cpp
endereco.sin_port = htons(5000);
```

Define a porta utilizada pelo servidor.

A função `htons()` converte o número da porta para o formato utilizado pela rede.

---

# 🔗 Bind

Depois de criar o socket, é necessário associá-lo a um endereço e uma porta.

Isso é feito utilizando:

```cpp
bind(servidor, (sockaddr*)&endereco, sizeof(endereco));
```

O `bind()` associa o socket às informações definidas anteriormente.

Neste projeto:

```text
IP   → interfaces disponíveis
Porta → 5000
```

---

# 👂 Listen

Depois do `bind()`, o servidor precisa começar a aguardar conexões.

Para isso utilizamos:

```cpp
listen(servidor, 1);
```

O `listen()` coloca o socket em modo de espera por conexões.

---

# 🤝 Accept

Para aceitar um jogador utilizamos:

```cpp
int cliente = accept(servidor, nullptr, nullptr);
```

O `accept()` fica aguardando até que algum cliente tente se conectar.

Quando a conexão acontece, ele retorna um novo socket.

É importante entender que existem dois sockets:

```text
servidor
   ↓
socket utilizado para aguardar novas conexões

cliente
   ↓
socket utilizado para conversar com o jogador conectado
```

Isso permite que futuramente o servidor aceite mais jogadores sem perder o socket responsável por receber novas conexões.

---

# 📥 Recebendo mensagens

Para receber dados utilizamos:

```cpp
recv(cliente, mensagem, sizeof(mensagem), 0);
```

Nesse caso:

```text
cliente
```

é o socket da conexão.

```text
mensagem
```

é o espaço onde os dados recebidos serão armazenados.

```text
sizeof(mensagem)
```

define o tamanho máximo que poderá ser recebido.

---

# 📤 Enviando mensagens

Para enviar uma mensagem utilizamos:

```cpp
send(cliente, resposta.c_str(), resposta.size() + 1, 0);
```

O método:

```cpp
c_str()
```

permite acessar o conteúdo de uma `std::string` como uma sequência de caracteres.

O:

```cpp
size() + 1
```

é utilizado neste primeiro protocolo simples para enviar também o caractere `\0`, que representa o final da string.

---

# ❌ Fechando a conexão

Quando a comunicação termina, utilizamos:

```cpp
close(cliente);
close(servidor);
```

O `close()` encerra o socket.

---

# 🧪 Primeiro teste de comunicação

O primeiro teste realizado foi uma comunicação simples.

O cliente envia:

```text
Ola servidor!
```

O servidor recebe a mensagem e responde:

```text
Ola, jogador!
```

Fluxo:

```text
CLIENTE
   │
   │ "Ola servidor!"
   ▼
SERVIDOR
   │
   │ "Ola, jogador!"
   ▼
CLIENTE
```

Esse teste serviu para verificar se a comunicação TCP estava funcionando corretamente.

---

# 🎮 Comunicação durante a partida

Depois de validar a conexão, a mesma estrutura poderá ser utilizada para transmitir as jogadas.

Por exemplo:

```text
MOVE|2|3|3|4
```

Essa mensagem poderia representar:

```text
MOVE
2  → linha inicial
3  → coluna inicial
3  → linha final
4  → coluna final
```

O servidor receberia a jogada, verificaria se ela é válida e então atualizaria o estado do jogo.

---

# 🔐 Servidor como autoridade da partida

O servidor será responsável por controlar o estado oficial da partida.

O cliente não deve simplesmente alterar o próprio tabuleiro e informar que a jogada aconteceu.

O fluxo será:

```text
CLIENTE
   │
   │ Solicita jogada
   ▼
SERVIDOR
   │
   ├── Verifica jogador
   ├── Verifica turno
   ├── Verifica movimento
   ├── Atualiza tabuleiro
   │
   ▼
OUTROS CLIENTES
```

Isso evita que cada computador tenha um estado diferente da partida.

---

# 🏠 Conceito de sala

Para permitir que dois jogadores iniciem uma partida, poderá ser criado o conceito de **sala**.

Uma sala representa uma partida.

Por exemplo:

```text
Sala: ABC123

Jogador 1 → Larissa
Jogador 2 → João

Status → Em andamento
```

O servidor poderá manter as informações da sala.

Exemplo:

```text
                SERVIDOR
                   │
             ┌─────▼─────┐
             │  SALA     │
             │  ABC123   │
             └─────┬─────┘
                   │
          ┌────────┴────────┐
          │                 │
       Jogador 1         Jogador 2
       Cliente A         Cliente B
```

---

# 🔑 Código da sala

Uma possibilidade é gerar um código para cada partida.

Exemplo:

```text
ABC123
```

O primeiro jogador cria a sala:

```text
Criar partida
      ↓
Servidor cria ABC123
      ↓
Jogador 1 entra
```

O segundo jogador informa:

```text
ABC123
```

e entra na mesma partida.

---

# 📡 Protocolo de comunicação

Para que cliente e servidor consigam entender as mensagens, será necessário definir um protocolo.

O protocolo é um conjunto de regras que define como as informações serão enviadas.

Alguns exemplos:

```text
CREATE_ROOM
```

Cria uma nova sala.

```text
JOIN_ROOM|ABC123
```

Solicita entrada na sala `ABC123`.

```text
PLAYER_JOINED
```

Informa que um jogador entrou.

```text
MOVE|2|3|3|4
```

Envia uma jogada.

```text
PLAYER_WON
```

Informa que um jogador venceu.

```text
PLAYER_LEFT
```

Informa que um jogador saiu.

Dessa forma, cliente e servidor possuem um padrão para interpretar as mensagens.

---

# 💾 Arquivos x Rede

O projeto utiliza dois conceitos diferentes que não devem ser confundidos.

## Arquivos

Os arquivos são utilizados para **persistência**.

Por exemplo:

```text
dados/usuarios.dat
```

pode armazenar os usuários cadastrados.

No futuro também poderá existir um arquivo para armazenar o histórico das partidas.

```text
dados/partidas.dat
```

---

## Rede

A rede será utilizada para a comunicação **em tempo real**.

Por exemplo:

```text
Jogador 1 realiza uma jogada
        ↓
Cliente envia pela rede
        ↓
Servidor recebe
        ↓
Servidor valida
        ↓
Servidor envia para Jogador 2
```

Portanto:

```text
ARQUIVO
→ guardar informações

REDE
→ transmitir informações
```

Não será utilizado o arquivo `usuarios.dat` como mecanismo de comunicação entre os jogadores.

---

# 🧱 Arquitetura planejada

A estrutura geral do projeto pode ser representada da seguinte forma:

```text
                    JOGO DE DAMAS
                         │
        ┌────────────────┼────────────────┐
        │                │                │
        ▼                ▼                ▼
      TELAS           USUÁRIOS          REDE
        │                │                │
        │                │                ├── Servidor
        │                │                └── Cliente
        │                │
        ▼                ▼
     Raylib          usuarios.dat
        │
        ▼
    Tabuleiro
        │
        ▼
     Partida
```

---

# 🚀 Próximos passos

A implementação da rede será feita de forma gradual.

### 1. Comunicação básica

Primeiro foi testada a comunicação entre cliente e servidor utilizando uma mensagem simples.

### 2. Dois jogadores

O servidor deverá aceitar dois clientes simultaneamente.

```text
Servidor
   ├── Cliente 1
   └── Cliente 2
```

### 3. Comunicação contínua

Em vez de conectar, enviar uma mensagem e encerrar, os clientes deverão permanecer conectados durante toda a partida.

### 4. Sala

Será implementado o conceito de sala para associar dois jogadores à mesma partida.

### 5. Comunicação das jogadas

Os clientes enviarão as jogadas para o servidor.

### 6. Validação

O servidor verificará se a jogada pode ser realizada.

### 7. Atualização do tabuleiro

Após uma jogada válida, o servidor enviará a atualização para os jogadores.

### 8. Integração com Raylib

A comunicação em rede será integrada à interface gráfica e ao tabuleiro do jogo.

### 9. Histórico

Ao finalizar uma partida, as informações poderão ser armazenadas em arquivo para consulta posterior.

---

# ⚠️ Observação sobre a rede

A primeira versão da comunicação foi desenvolvida pensando em computadores conectados à **mesma rede local**, como uma mesma rede Wi-Fi.

Para conectar jogadores que estejam em redes diferentes, pela Internet, será necessário lidar com questões adicionais, como:

- IP público;
- NAT;
- Port forwarding;
- Firewall;
- Servidor externo;
- Ou algum mecanismo intermediário de comunicação.

Por isso, a implementação inicial utiliza uma rede local, tornando o desenvolvimento e os testes mais simples.

---

# 📝 Resumo

O sistema de rede do jogo utiliza o modelo:

```text
              CLIENTE
                 │
                 │ TCP
                 ▼
              SERVIDOR
                 │
                 │ TCP
                 ▼
              CLIENTE
```

Os principais conceitos utilizados são:

| Conceito | Função |
|---|---|
| IP | Identifica o computador na rede |
| Porta | Identifica o serviço |
| Socket | Permite a comunicação |
| TCP | Realiza comunicação confiável |
| Servidor | Aguarda e gerencia conexões |
| Cliente | Solicita conexão e troca dados |
| `socket()` | Cria o socket |
| `bind()` | Associa endereço e porta |
| `listen()` | Aguarda conexões |
| `accept()` | Aceita uma conexão |
| `send()` | Envia dados |
| `recv()` | Recebe dados |
| `close()` | Encerra a conexão |
| Protocolo | Define o formato das mensagens |
| Sala | Representa uma partida |
| Arquivo | Persiste informações |

A ideia final é utilizar a rede para permitir que dois jogadores joguem uma partida de damas em computadores diferentes, enquanto os arquivos continuam sendo utilizados para armazenar informações que precisam permanecer salvas.