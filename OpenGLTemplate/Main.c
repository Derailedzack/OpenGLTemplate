#include"SDL2_GLWindow.h"
#include"Callbacks.h"
#undef main

int main(){
	SDL2_CreateWindowWithCallback(640, 480,SDL_FALSE, Main_Init, Main_Render, Main_EventWatch, Main_Update);
}
