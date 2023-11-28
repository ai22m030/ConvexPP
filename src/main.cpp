#include <SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>

#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

#include "program_options.h"
#include "MeasurementsLog.h"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool show_demo_window = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    auto windowFlags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("ForestFire", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH,
                              WINDOW_HEIGHT, windowFlags);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        SDL_Log("Error creating SDL_Renderer!");
        return EXIT_FAILURE;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    unsigned int totalFrameTicks = 0;
    unsigned int totalFrames = 0;
    bool running = true;
    while (running) {
        totalFrames++;
        Uint32 startTicks = SDL_GetTicks();
        Uint64 startPerf = SDL_GetPerformanceCounter();
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                running = false;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
                event.window.windowID == SDL_GetWindowID(window))
                running = false;


            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            // Show the ImGui menu bar
            if(show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // Rendering
            ImGui::Render();

            SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
            SDL_SetRenderDrawColor(renderer, static_cast<int>(clear_color.x * 255),
                                   static_cast<int>(clear_color.y * 255),
                                   static_cast<int>(clear_color.z * 255),
                                   static_cast<int>(clear_color.w * 255));

            SDL_RenderClear(renderer);

            // render your own stuff here

            // End frame timing
            auto endTicks = SDL_GetTicks();
            auto endPerf = SDL_GetPerformanceCounter();

            measurements.framePerf = endPerf - startPerf;
            measurements.fps = 1 / ((static_cast<float>(endTicks) - static_cast<float>(startTicks)) / 1000.0f);
            totalFrameTicks += endTicks - startTicks;
            measurements.avg = 1000.0f / (static_cast<float>(totalFrameTicks) / static_cast<float>(totalFrames));

            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
            SDL_RenderPresent(renderer);
        }
    }

    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
