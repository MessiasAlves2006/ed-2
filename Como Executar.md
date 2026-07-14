Instalar a biblioteca Raylib para demostração Grafica

Instalação em Ubuntu, Mint, zorin ou SOs que possuam apt como gerenciador de pacotes padrao

  sudo apt update
  sudo apt install libraylib-dev

Instalação em Arch, Cachy Os ou SOs que possuam o pacman como gerenciador de pacotes padrao

  sudo pacman -S raylib

Compilar codigo C 

  gcc arvore_rubro_negra.c -I/usr/include -L/usr/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o arvore_visual

Rodar a Aplicação compilada

  ./arvore_visual