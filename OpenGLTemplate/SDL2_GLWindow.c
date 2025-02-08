#include"SDL2_GLWindow.h"
bool RenderingDisabled = false;
SDL_bool SDL_RenderLoop = SDL_FALSE;
void SDL2_CreateWindow(int w, int h, SDL_bool use_gl) {
    if (use_gl == SDL_TRUE) {
        SDL2_GL_CreateWindow(w, h);
    }
    else {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Project", SDL_GetError(), NULL);
        }
        int window_renderer_combo = SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_RESIZABLE, &SDL_window, &SDL_renderer);
        if (window_renderer_combo == -1) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Project(Window Creation)", SDL_GetError(), NULL);
        }
        else {

          
            Current_window = SDL;
            if (init_func != NULL) {
                init_func();
            }



            SDL_RenderLoop = SDL_TRUE;
            render_func();
            //}

        }
    }
}
void SDL2_GL_CreateWindow(int w, int h) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Project", SDL_GetError(), NULL);
    }
    int window_renderer_combo = SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE, &SDL_window, &SDL_renderer);
    if (window_renderer_combo == -1) {

        //SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Project", "Failed to create SDL 2 Window and Renderer", NULL);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Project(Window Creation)",SDL_GetError(), NULL);
#ifdef __CLIENT_BUILD
        GetCommandInput();
#endif
        //SDL_Quit();
    }
    else {

        SDL_context = SDL_GL_CreateContext(SDL_window);

        if (SDL_context == NULL) {

            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Project(GL Context Creation)", SDL_GetError(), NULL);

        }
        if (SDL_GL_MakeCurrent(SDL_window, SDL_context) != 0) {
            //SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Project", "Failed to make OpenGL Current!", NULL);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Project", SDL_GetError(), NULL);
#ifdef __CLIENT_BUILD
            GetCommandInput();
#endif
        }
#ifdef HAVE_GLAD_H
        gladLoadGLLoader(SDL_GL_GetProcAddress);
#else

#endif
        Current_window = GL;
        if (init_func != NULL) {
            init_func();
        }



        SDL_RenderLoop = SDL_TRUE;

        //SDL_GL_GetProcAddress(gladloadgl)

   // if(SDL_ONLY_DEBUG_DRAW == SDL_TRUE ){
     //   RenderALLDebugObjects();
    //}else{
#ifdef __CLIENT_BUILD
        RenderALLEntities();
#endif
        render_func();
        //}

    }
}
void SDL2_GL_RenderLoop() {
    float prev_ypos;
    int delay;
    while (SDL_RenderLoop == SDL_TRUE) {
        SDL_PollEvent(&SDL_event);

        //SDL_RenderClear(SDL_renderer);
  //  if(SDL_ONLY_DEBUG_DRAW == SDL_TRUE ){
        //RenderALLDebugObjects();
        //UpdateALLDebugObjects();
  //  }else{
        if (RenderingDisabled == true) {
            SDL_RenderLoop = false;
            //SDL_RenderPresent(SDL_renderer);
        }
        else {

            render_func();
            // }

            //


            update_func();
            //SDL_GL_SetSwapInterval(1);



            SDL_GL_SwapWindow(SDL_window);


            if (SDL_event.type == SDL_QUIT) {

                SDL_RenderLoop = SDL_FALSE;
                SDL_Quit();
            }
            //if(SDL_ONLY_DEBUG_DRAW == SDL_TRUE ){

            //}else{
  //input_func(SDL_event);
                SDL_AddEventWatch(event_watch_func,NULL);
                if (SDL_event.type == SDL_WINDOWEVENT) {
                    if (SDL_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {

                        glViewport(0, 0, SDL_event.window.data1, SDL_event.window.data2);

                    }
                }
            }
        }
}
void SDL2_RenderLoop() {
    float prev_ypos;
    int delay;
    while (SDL_RenderLoop == SDL_TRUE) {
        SDL_PollEvent(&SDL_event);

        
  //  if(SDL_ONLY_DEBUG_DRAW == SDL_TRUE ){
        //RenderALLDebugObjects();
        //UpdateALLDebugObjects();
  //  }else{
        if (RenderingDisabled == true) {
            SDL_RenderLoop = false;
            //
        }
        else {
            SDL_RenderClear(SDL_renderer);
            render_func();
            // }
            SDL_RenderPresent(SDL_renderer);
            //


            update_func();
            //SDL_GL_SetSwapInterval(1);





            if (SDL_event.type == SDL_QUIT) {

                SDL_RenderLoop = SDL_FALSE;
                SDL_Quit();
            }
            //if(SDL_ONLY_DEBUG_DRAW == SDL_TRUE ){

            //}else{
  //input_func(SDL_event);
            SDL_AddEventWatch(event_watch_func, NULL);
            if (SDL_event.type == SDL_WINDOWEVENT) {
                if (SDL_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {

                 

                }
            }
        }
    }
}

void SDL2_GL_Restart() {
        RenderingDisabled = false; //Clear rendering disabled
        SDL_ShowWindow(SDL_window);

        // SDL2_GL_CreateWindow(640,480);
        SDL2_GL_RenderLoop();
}

void SDL2_CreateWindowWithCallback(int w, int h, SDL_bool use_gl, Init_Func* main_init_func, Main_Render_Func* main_render_func, SDL_EventFilter* main_event_watch_func, Main_Update_Func* main_update_func) {
        if (main_init_func != NULL) {
            SetInitCallback(main_init_func);
        }
        SetMainRenderCallback(main_render_func);
        SetMainUpdateCallback(main_update_func);
        SetMainEventWatchCallback(main_event_watch_func);
        SDL2_CreateWindow(w, h,use_gl);
        if (use_gl == SDL_TRUE) {
          
            SDL2_GL_RenderLoop();
        }
        else {
            SDL2_RenderLoop();
        }
      
}

void SDL2_GL_DrawPixel(float w, float h, float x, float y, float x2, float y2) {
        glScalef(w, h, 0);
        glRectf(x, y, x2, y2);
}
