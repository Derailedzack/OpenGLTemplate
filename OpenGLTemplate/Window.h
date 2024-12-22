#pragma once
#include<SDL.h>
#include <stdbool.h>
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
typedef void(Create_Window_Func)(int w, int h);
typedef void (Main_Render_Func)();
typedef void (Main_Update_Func)();
//typedef void (Main_Input_Func)(SDL_Event e);
typedef void (Init_Func)(); //This is so that things can be initialized when the window is created
typedef void (RenderLoop_func)();
typedef void (Destroy_Window_func)();
typedef void (OnRenderingFinished_func)();
typedef void (OnRenderingFailure_func)();
typedef enum WINDOW_TYPE
{
	NONE,
	GL,
	SDL,
	GDI,
	DIRECTX,
	LUA
}WINDOW_TYPE;
WINDOW_TYPE Current_window;
Main_Render_Func* render_func;
Main_Update_Func* update_func;
SDL_EventFilter* event_watch_func;
Main_Render_Func* debug_render_func;
Main_Update_Func* debug_update_func;

Init_Func* init_func;

//void  RenderLoop(RenderLoop_func* renderloop);
//void  OnRenderingFinished(OnRenderingFinished_func* onrenderingfinished);
//void  OnRenderingFailure(OnRenderingFailure_func* onrenderingfailure);
void SetMainRenderCallback(Main_Render_Func* main_render_func);
void SetMainUpdateCallback(Main_Update_Func* main_update_func);
void SetDebugRenderCallback(Main_Render_Func* main_debug_render_func);
void SetDebugUpdateCallback(Main_Update_Func* main_debug_update_func);
void SetMainEventWatchCallback(SDL_EventFilter* main_event_watch_func);
void SetInitCallback(Init_Func* init_func_custom);

void Tick();
