#include <iostream>
#include <string>
#include <dlfcn.h>
#include <csignal>
#include "SDL.h"

#ifdef OS_WINDOWS
#define SDL_LIB_PATH "SDL2.dll"
#elif defined(OS_MACOS)
#define SDL_LIB_PATH "libSDL2-2.0.0.dylib"
#elif defined(OS_LINUX)
#define SDL_LIB_PATH "libSDL2-2.0.so.0"
#endif

namespace life_frontend {
    class LifeFrontend {
    public:
        explicit LifeFrontend(const std::string &sdlLibPath) : sdl_lib_path_(sdlLibPath) {
            sdl_lib_handle_ = dlopen(sdl_lib_path_.c_str(), RTLD_LAZY);
            if (sdl_lib_handle_ != nullptr) {
                throw std::runtime_error("kto-to lozhanulsya");
            }
            SDL_Init_Func = (int (*)(Uint32)) dlsym(sdl_lib_handle_, "SDL_Init");
            SDL_CreateWindow_Func = (SDL_Window *(*)(const char *, int, int, int, int, Uint32)) dlsym(sdl_lib_handle_,
                                                                                                      "SDL_CreateWindow");
            SDL_CreateRenderer_Func = (SDL_Renderer *(*)(SDL_Window *, int, Uint32)) dlsym(sdl_lib_handle_,
                                                                                           "SDL_CreateRenderer");
            SDL_SetRenderDrawColor_Func = (int (*)(SDL_Renderer *, Uint8, Uint8, Uint8, Uint8)) dlsym(sdl_lib_handle_,
                                                                                                      "SDL_SetRenderDrawColor");
            SDL_Quit_Func = (void (*)()) dlsym(sdl_lib_handle_, "SDL_Quit");
        };

        ~LifeFrontend() {
            if (sdl_lib_handle_ != nullptr) {
                dlclose(sdl_lib_handle_);
            }
        }

    private:
        typedef int (*SDL_Init_Wrapper)(Uint32 flags);

        typedef SDL_Window *(*SDL_CreateWindow_Wrapper)(const char *title, int x, int y, int w, int h, Uint32 flags);

        typedef SDL_Renderer *(*SDL_CreateRenderer_Wrapper)(SDL_Window *window, int index, Uint32 flags);

        typedef void (*SDL_Quit_Wrapper)(void);

        std::string sdl_lib_path_;
        void *sdl_lib_handle_;

        int (*SDL_Init_Func)(Uint32 flags);

        void (*SDL_Quit_Func)(void);

        SDL_Renderer *(*SDL_CreateRenderer_Func)(SDL_Window *window, int index, Uint32 flags);

        SDL_Window *(*SDL_CreateWindow_Func)(const char *title, int x, int y, int w, int h, Uint32 flags);

        int (*SDL_SetRenderDrawColor_Func)(SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    public:
        SDL_CreateWindow_Wrapper getSdlCreateWindowFunc() const {
            return SDL_CreateWindow_Func;
        }

        SDL_Init_Wrapper getSdlInitWrapper() const {
            return SDL_Init_Func;
        }

        SDL_Quit_Wrapper getSdlQuitWrapper() const {
            return SDL_Quit_Func;
        }

        SDL_CreateRenderer_Wrapper getSdlCreateRendererFunc() const {
            return SDL_CreateRenderer_Func;
        }
    };
}

int main(int argc, char *argv[]) {
    life_frontend::LifeFrontend frontend("libSDL2.dylib");
    frontend.getSdlInitWrapper(SDL_INIT_VIDEO);
    auto screen = frontend.getSdlCreateWindowFunc()("My SDL empty window", SDL_WINDOWPOS_UNDEFINED,
                                                    SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    auto render = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED: SDL_RENDERER_TERGETTEXTURE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);

//    SDL_Event 0;
//    bool quit = false;
//

    sleep(5);
    frontend.getSdlQuitWrapper()();
}