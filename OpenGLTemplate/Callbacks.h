#pragma once
#include<glad/glad.h>
#include<SDL.h>
void Main_Init();
void Main_Render();
void Main_Update();
void Main_EventWatch(void* ud,SDL_Event* e);