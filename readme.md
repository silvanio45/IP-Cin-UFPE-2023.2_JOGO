"Makefile" tá funcionando para o linux, para windons é só tirar o "." do ".Makefile" e apagar ou colocar o "." no "Makefile".
Não testei então não posso garantir que funcione no windowns.

# OBS
Para rodar o makefile é só digitar "make game" no terminal e depois rodar o arquivo digitando "game" ou abrindo o game.exe

# OBS 2
Sempre tentar fazer o código de forma modularizada (separando as funções em um arquivo [auxiliar.c] com seu header [arquivo.h])

Arquivos header não devem ter implementações de funções contidas neles, apenas a declaração (ver arquivos já implementados).

# Descrição das pastas:
1. include/
    Contém os arquivos header (.h) com as declarações de funções e variáveis.
    
2. obj/
    Vai ficar uns arquivos .o, não precisar mexer. Apenas para o funcionamento do Makefile
    
3. src/
    Todos os arquivos com as implementações das diversas funções do código devem ficar aqui. Tanto a main quanto outros arquivos das demais funções do jogo devem ficar aqui e importar seus arquivos .h na forma "../include/arquivo.h"
