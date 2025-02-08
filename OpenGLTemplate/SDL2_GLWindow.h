#pragma once
#include<SDL.h>
#include "Window.h"
#ifdef HAVE_GLAD_H

#include<glad/glad.h>
#else
#undef __gl_h_
#include"gl/glew.h"
#endif
SDL_Window* SDL_window;
SDL_Renderer* SDL_renderer;
SDL_Event SDL_event;
SDL_GLContext SDL_context;
void SDL2_GL_CreateWindow(int w, int h);
void SDL2_GL_DrawPixel(float w, float h, float x, float y, float x2, float y2);
void SDL2_GL_RenderLoop();
void SDL2_GL_Restart();
void SDL2_CreateWindow(int w,int h,SDL_bool use_gl);
void SDL2_RenderLoop();
void SDL2_CreateWindowWithCallback(int w,int h,SDL_bool use_gl,Init_Func* main_init_func,Main_Render_Func* main_render_func, SDL_EventFilter* main_event_watch_func,Main_Update_Func* main_update_func);

