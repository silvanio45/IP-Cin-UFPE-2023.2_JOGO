# PARA RODAR NO NOTEPAD++
1 - Abra o notepad do raylib (Notepad++ for Raylib)
2 - Abra o arquivo main dentro da janela do Notepad que aparecer
3 - Aperte F6 para rodar o código 
4 - Quando a janela com uns comandos aparecer, apague todos e cole os comendos abaixo:

echo > Setup required Environment
echo -------------------------------------
SET RAYLIB_PATH=C:\raylib\raylib
SET COMPILER_PATH=C:\raylib\w64devkit\bin
ENV_SET PATH=$(COMPILER_PATH)
SET CC=gcc
SET CFLAGS=$(RAYLIB_PATH)\src\raylib.rc.data -s -static -Os -std=c99 -Wall -I$(RAYLIB_PATH)\src -Iexternal -Iinclude -DPLATFORM_DESKTOP

SET LDFLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm
cd $(CURRENT_DIRECTORY)
echo
echo > Clean latest build
echo ------------------------
cmd /c IF EXIST $(NAME_PART).exe del /F $(NAME_PART).exe
echo
echo > Saving Current File
echo -------------------------
npp_save
echo
echo > Compile program
echo -----------------------
$(CC) --version
$(CC) -o $(NAME_PART).exe $(FILE_NAME) include/*.c $(CFLAGS) $(LDFLAGS)

echo
echo > Reset Environment
echo --------------------------
ENV_UNSET PATH
echo
echo > Execute program
echo -----------------------
cmd /c IF EXIST $(NAME_PART).exe $(NAME_PART).exe


5 - Aperte Ok.
