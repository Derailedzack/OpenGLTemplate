#include"SDL2_GLWindow.h"
bool RenderingDisabled = false;
SDL_bool SDL_RenderLoop = SDL_FALSE;
void SDL2_GL_CreateWindow(int w, int h) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL 2", SDL_GetError(), NULL);
    }
    int window_renderer_combo = SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE, &SDL_window, &SDL_renderer);
    if (window_renderer_combo == -1) {

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Project", "Failed to create SDL 2 Window and Renderer", NULL);
#ifdef __CLIENT_BUILD
        GetCommandInput();
#endif
        //SDL_Quit();
    }
    else {

        SDL_context = SDL_GL_CreateContext(SDL_window);

        if (SDL_context == NULL) {

            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Project", "Failed to create a SDL 2 OpenGL Context!", NULL);

        }
        if (SDL_GL_MakeCurrent(SDL_window, SDL_context) != 0) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Project", "Failed to make OpenGL Current!", NULL);
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

#ifdef __CLIENT_BUILD
            RenderALLEntities();
#endif
            render_func();
            // }

            //

            glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#ifdef __CLIENT_BUILD
            UpdateALLEntities();
#endif
            update_func();
            //SDL_GL_SetSwapInterval(1);



            SDL_GL_SwapWindow(SDL_window);


            if (SDL_event.type == SDL_QUIT) {

                SDL_RenderLoop = SDL_FALSE;
                SDL_Quit();
            }
            //if(SDL_ONLY_DEBUG_DRAW == SDL_TRUE ){

            //}else{
#ifdef __CLIENT_BUILD
            if (SDL_event.type == SDL_KEYDOWN) {
                if (SDL_event.key.keysym.sym == SDLK_RIGHT) {
                    SDL2_OnPlayerMove(1);
                    Player_data->posX += 0.222225f;
                }
                if (SDL_event.key.keysym.sym == SDLK_LEFT) {
                    SDL2_OnPlayerMove(1);
                    Player_data->posX -= 0.222225f;
                }
                if (SDL_event.key.keysym.sym == SDLK_UP) {
                    SDL2_OnPlayerMove(0);
                    prev_ypos = Player_data->posY;
                    Player_data->posY += 0.222225f;
                }
                if (SDL_event.key.keysym.sym == SDLK_DOWN) {
                    SDL2_OnPlayerMove(0);
                    prev_ypos = Player_data->posY;
                    Player_data->posY -= 0.222225f;
                }
                if (SDL_event.key.keysym.sym == SDLK_SPACE) {
                    RenderingDisabled = true;
                    SDL_HideWindow(SDL_window);

                    GetCommandInput();

                    /*Player_data->posY -= 0.06f;
                    delay++;
                    if(delay >= 60){
                       Player_data->posY = prev_ypos;
                    }*/

                }
#endif
                input_func(SDL_event);

                if (SDL_event.type == SDL_WINDOWEVENT) {
                    if (SDL_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {

                        glViewport(0, 0, SDL_event.window.data1, SDL_event.window.data2);

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

void SDL2_GL_CreateWindowWithCallback(int w, int h, Init_Func* main_init_func, Main_Render_Func* main_render_func, Main_Input_Func* main_input_func, Main_Update_Func* main_update_func) {
        if (main_init_func != NULL) {
            SetInitCallback(main_init_func);
        }
        SetMainRenderCallback(main_render_func);
        SetMainUpdateCallback(main_update_func);
        SetMainInputCallback(main_input_func);
        SDL2_GL_CreateWindow(w, h);
        SDL2_GL_RenderLoop();
}

void SDL2_GL_DrawPixel(float w, float h, float x, float y, float x2, float y2) {
        glScalef(w, h, 0);
        glRectf(x, y, x2, y2);
}
