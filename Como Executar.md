Instalar a biblioteca Raylib para demostração Grafica, Raylib e uma interface para criação de janelas e elementos graficos em c.

Instalação em Ubuntu, Mint, zorin ou SOs que possuam apt como gerenciador de pacotes padrao

  sudo apt update
  sudo apt install libraylib-dev

Instalação em Arch, Cachy Os ou SOs que possuam o pacman como gerenciador de pacotes padrao

  sudo pacman -S raylib

Por ser uma biblioteca que precisa ser instalada, idle como o vscode quando instalados por meio de sandbox como flatpak, snap etc... não conseguem encotrar os arquivos de cabeçalhos novos 
nesse caso ao tentar compilar pela idle ocorreram erros e não irar gerar um executavel.

Se esse for o caso recomendo, navegar ate a pasta do projeto e compilar manualmente pelo terminal.

Compilar codigo C 

  gcc arvore_rubro_negra.c -I/usr/include -L/usr/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o arvore_visual

Rodar a Aplicação compilada

  ./arvore_visual
