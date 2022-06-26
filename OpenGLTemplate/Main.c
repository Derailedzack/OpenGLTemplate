#include"SDL2_GLWindow.h"
#include"Callbacks.h"
#undef main

int main(){
	SDL2_GL_CreateWindowWithCallback(640, 480, Main_Init, Main_Render, Main_Input, Main_Update);
}
