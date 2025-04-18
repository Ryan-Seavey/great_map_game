#include <span>
#include <thread>
#include <SDL3/SDL.h>

#include "RyUtil.h++"
#include "Country.h++"
#include "Pixel.h++"

using RyUtil::operator ""_rgba;


constexpr unsigned MAP_HEIGHT{75};
constexpr unsigned MAP_WIDTH{100};
constexpr unsigned MAP_AREA{MAP_WIDTH*MAP_HEIGHT};



enum Colors : unsigned{
    White = 0xFFFFFFFF,
    Red = 0xFF0000FF,
    Green = 0xFF00FF00,
    Blue = 0xFFFF0000,
    Pink = 0xFFFF00FF,
    Yellow = 0xFF00FFFF
};

inline std::vector<unsigned> colors{
    White,
    Red,
    Green,
    Blue,
    Pink,
    Yellow
};

int main()
{
    std::array<Pixel, MAP_AREA> pixelsOnScreen{};

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            Pixel& p = pixelsOnScreen[y * MAP_WIDTH + x];
            if (y > 0)                          p.bordering_[RyUtil::UP] = &pixelsOnScreen[(y - 1) * MAP_WIDTH + x];
            if (y < MAP_HEIGHT - 1) p.bordering_[RyUtil::DOWN] = &pixelsOnScreen[(y + 1) * MAP_WIDTH + x];
            if (x > 0)                          p.bordering_[RyUtil::LEFT] = &pixelsOnScreen[y * MAP_WIDTH + (x - 1)];
            if (x < MAP_WIDTH - 1)  p.bordering_[RyUtil::RIGHT] = &pixelsOnScreen[y * MAP_WIDTH + (x + 1)];
        }
    }

    if (not SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Pixel Map",
        500, 500, SDL_WINDOW_RESIZABLE | SDL_WINDOW_TRANSPARENT);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    SDL_Texture* country_layer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                                             SDL_TEXTUREACCESS_STREAMING, MAP_WIDTH, MAP_HEIGHT);
    SDL_SetTextureScaleMode(country_layer, SDL_SCALEMODE_NEAREST);
    SDL_Texture * terrain_layer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, MAP_WIDTH, MAP_HEIGHT);
    SDL_SetTextureScaleMode(terrain_layer, SDL_SCALEMODE_NEAREST);
    bool running{true};
    bool mouseDown{false};
    size_t currentColorIndex{};



    /////////////////////
    //LOGIC FOR TERRAIN
    /////////////////////
    std::array<uint32_t, MAP_AREA> pixelBuffer{};
    if constexpr (false) {
        Country terrain_data[] = {
            {"plains", 0x00D123FF_rgba, new AI_peaceful}, {"mountains",0x8c8c8cFF_rgba, new AI_peaceful},
            {"water", 0x0000FFFF_rgba, new AI_peaceful}, {"desert", 0xFFFF00FF_rgba, new AI_peaceful},
            {"snow", 0xFFFFFFFF, new AI_peaceful}, {"mesa", 0xFF8000FF_rgba, new AI_peaceful},
            {"flower_field", 0xFF00FFFF_rgba, new AI_peaceful}, {"Volcano", 0xFF0000FF, new AI_peaceful}};
        std::span terrain{terrain_data};
        for (auto & i : terrain) i.setOwnership(&pixelsOnScreen[RyUtil::randint(0u, MAP_AREA - 1)]);

        bool goAgain = false;
        do {
            goAgain = false;
            for (size_t i = 0; i < pixelsOnScreen.size(); ++i){
                pixelBuffer[i] = pixelsOnScreen[i].rgba_;
                if (pixelsOnScreen[i].owner_ == nullptr) goAgain = true;
            }
            for (auto & i : terrain) i.update();
            SDL_UpdateTexture(terrain_layer, nullptr, pixelBuffer.data(), MAP_WIDTH * sizeof(uint32_t)); //todo: use the streaming version
            SDL_RenderClear(renderer);
            SDL_RenderTexture(renderer, terrain_layer, nullptr, nullptr);
            SDL_RenderPresent(renderer);
        } while (goAgain);
    }

    //reset the pixels for use in the normal game loop
    unsigned coolColor = RyUtil::randint(0, 0x00FFFFFF);
    for (auto& recolor : pixelsOnScreen)
    {
        recolor.rgba_ = coolColor  |= 0x80000000;
        recolor.owner_ = nullptr;
    }
    pixelBuffer.fill(coolColor);
    colors.emplace_back(coolColor);

    /////////////////////
    //LOGIC FOR CREATING COUNTRIES
    /////////////////////
    std::vector<Country> countries{};

    for (int i = 0; i < 200; ++i)
    {
        countries.emplace_back("", RyUtil::randint(0, 0x00FFFFFF) | 0x80000000);
    }


    if (countries.size() != MAP_AREA)
    //random
    for (auto& country : countries) country.setOwnership(&pixelsOnScreen[RyUtil::randint(0u, MAP_AREA - 1)]);
    else
    //every tile a country
    for (int i = 0; i < MAP_AREA; ++i) countries[i].setOwnership(&pixelsOnScreen[i]);




    unsigned timescale = 100;
    while (running) {
        unsigned stillInPlay = 0;
        for(auto & countrie : countries)
        {
            //if (iter->size() == 0) countries.erase(iter); else
                countrie.update();
            if (countrie.size() > 0) ++stillInPlay;
        }
        if (stillInPlay <= 1) goto breakma;

        for (size_t i = 0; i < pixelsOnScreen.size(); ++i)
            pixelBuffer[i] = pixelsOnScreen[i].rgba_;

        std::this_thread::sleep_for(std::chrono::milliseconds(timescale));

        //I handle SDL input; I handle SDL input.
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    // I cycle the colors!
                    ++currentColorIndex %= colors.size();
                }
                else if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseDown = true;
                }
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseDown = false;
                }
            }
            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                if (event.key.key == SDLK_SPACE) timescale = 0                ;
            } else
            {
                timescale = 100;
            }
        }



        float mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        int windowWidth, windowHeight;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        float scaleX = static_cast<float>(windowWidth) / MAP_WIDTH;
        float scaleY = static_cast<float>(windowHeight) / MAP_HEIGHT;

        int pixelX = static_cast<int>(mouseX / scaleX);
        int pixelY = static_cast<int>(mouseY / scaleY);



        // DRAWING "LOGIC" (P.S. this form of bounds checking is faster than try/catch)
        if (mouseDown && pixelX >= 0 && pixelX < MAP_WIDTH && pixelY >= 0 && pixelY < MAP_HEIGHT) {
            pixelsOnScreen[pixelY * MAP_WIDTH + pixelX].rgba_ = colors[currentColorIndex];
        }




        SDL_UpdateTexture(country_layer, nullptr, pixelBuffer.data(), MAP_WIDTH * sizeof(uint32_t)); //todo: use the streaming version

        // Run this garbage last
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, terrain_layer, nullptr, nullptr);
        SDL_RenderTexture(renderer, country_layer, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }
breakma:
    // I do my due diligence.
    SDL_DestroyTexture(country_layer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

