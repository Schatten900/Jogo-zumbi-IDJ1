# Jogo do Zumbi 🧟
Projeto de desenvolvimento de um jogo 2D utilizando a biblioteca **SDL2** em **C++** para a disciplina de Introdução ao Desenvolvimento de Jogos (IDJ).

---

## 📋 Entregas do Projeto
Acompanhamento do progresso das entregas modularizadas:

- [x] **Trabalho 1**: Concluído
- [x] **Trabalho 2**: Concluído
- [x] **Trabalho 3**: Concluido
- [x] **Trabalho 4**: Concluido
- [x] **Trabalho 5**: Concluido
- [ ] **Trabalho 6**: Pendente
- [ ] **Trabalho 7**: Pendente

---

## 🚀 Como rodar o projeto

Certifique-se de ter as dependências da **SDL2**, **SDL2_image** e **SDL2_mixer** instaladas em seu sistema. No terminal, execute os comandos abaixo:

```bash
# Criar o diretório de build
mkdir -p build 

# Compilar o projeto
g++ -std=c++17 $(find ./src -name "*.cpp") -I./include -Wall -Wextra -o ./build/game $(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_mixer 

# Executar o jogo
./build/game