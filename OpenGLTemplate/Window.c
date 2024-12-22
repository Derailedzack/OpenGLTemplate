#include "Window.h"
/*SetCurrentWindowType and GetCurrentWindowType no longer have a function prototype in the header*/
//void SetCurrentWindowType()
//{
//}
//WINDOW_TYPE GetCurrentWindowType(WINDOW_TYPE win_type)
//{

	//return false;
//}
//void CreateWindow(Create_Window_Func* create_window)
//{
//	(create_window)(WINDOW_WIDTH,WINDOW_HEIGHT);
//}

/*
void RenderLoop(RenderLoop_func* renderloop)
{
	(renderloop)();
}
*/
//void DestroyWindow(Destroy_Window_func* destroywindow)
//{
//	(destroywindow)();
//}

void OnRenderingFinished(OnRenderingFinished_func* onrenderingfinished)
{
	(onrenderingfinished)();
}

void OnRenderingFailure(OnRenderingFailure_func* onrenderingfailure)
{
	(onrenderingfailure)();
}

void Tick()
{
}
void SetMainRenderCallback(Main_Render_Func* main_render_func) {
	render_func = main_render_func;
}
void SetMainUpdateCallback(Main_Update_Func* main_update_func) {
	update_func = main_update_func;
}
void SetInitCallback(Init_Func* init_func_custom) {
	init_func = init_func_custom;
}
void SetDebugRenderCallback(Main_Render_Func* main_debug_render_func) {
	debug_render_func = main_debug_render_func;
}
void SetDebugUpdateCallback(Main_Update_Func* main_debug_update_func) {
	debug_update_func = main_debug_update_func;
}
void SetMainInputCallback(SDL_EventFilter* main_event_watch_func) {
	event_watch_func = main_event_watch_func;
}