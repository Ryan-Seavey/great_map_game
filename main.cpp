#include <thread>
#include <SDL3/SDL.h>

#include "RyUtil.h++"
#include "Country.h++"
#include "Pixel.h++"


constexpr unsigned MAP_HEIGHT{75};
constexpr unsigned MAP_WIDTH{100};
constexpr unsigned MAP_AREA{MAP_WIDTH*MAP_HEIGHT};

constexpr unsigned operator""_rgba(unsigned long long rgba) {
    if constexpr (std::endian::native == std::endian::big) return rgba;
    else return
           ((rgba & 0x000000FFu) << 24) | // R → shift to byte 3 (MSB)
           ((rgba & 0x0000FF00u) << 8)  | // G → byte 2
           ((rgba & 0x00FF0000u) >> 8)  | // B → byte 1
           ((rgba & 0xFF000000u) >> 24); // A → byte 0 (LSB)
}


template<typename T = unsigned>
T randint(T min, T max) requires std::is_integral_v<T>
{
    static std::random_device rd;
    static std::mt19937 twister_engine{rd()};
    static std::uniform_int_distribution<T> dist{min, max};
    return dist(twister_engine);
}

template<typename T = double>
T randfloat(T min, T max) requires std::is_floating_point_v<T>
{
    static std::random_device rd;
    static std::mt19937 twister_engine{rd()};
    static std::uniform_real_distribution<T> dist{min, max};
    return dist(twister_engine);
}


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

    if (not SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Pixel Map",
        500, 500, SDL_WINDOW_RESIZABLE | SDL_WINDOW_TRANSPARENT);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                                             SDL_TEXTUREACCESS_STREAMING, MAP_WIDTH, MAP_HEIGHT);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    bool running{true};
    bool mouseDown{false};
    size_t currentColorIndex{};

    unsigned coolColor = randint(0, 0x00FFFFFF);
    for (auto& recolor : pixelsOnScreen) recolor.rgba_ = coolColor  |= 0x80000000;
    std::array<uint32_t, MAP_AREA> pixelBuffer{};

    colors.emplace_back(coolColor);

    std::vector<Country> countries{};

    for (int i = 0; i < MAP_AREA; ++i)
    {
        countries.emplace_back("", randint(0, 0x00FFFFFF) | 0x80000000);
    }


    if (countries.size() != MAP_AREA)
    //random
    for (auto& country : countries) country.setOwnership(&pixelsOnScreen[RyUtil::randint(0u, MAP_AREA - 1)]);
    else
    //every tile a country
    for (int i = 0; i < MAP_AREA; ++i) countries[i].setOwnership(&pixelsOnScreen[i]);



    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            Pixel& p = pixelsOnScreen[y * MAP_WIDTH + x];
            if (y > 0) p.bordering[0] = &pixelsOnScreen[(y - 1) * MAP_WIDTH + x]; // up
            if (x < MAP_WIDTH - 1) p.bordering[1] = &pixelsOnScreen[y * MAP_WIDTH + (x + 1)]; // right
            if (y < MAP_HEIGHT - 1) p.bordering[2] = &pixelsOnScreen[(y + 1) * MAP_WIDTH + x]; // down
            if (x > 0) p.bordering[3] = &pixelsOnScreen[y * MAP_WIDTH + (x - 1)]; // left
        }
    }
    unsigned timescale = 100;
    while (running) {
        for(auto iter = countries.begin() ; iter != countries.end(); iter++)
        {
            if (iter->size() == 0) countries.erase(iter);
            else iter->tryExpand();
        }
        for (size_t i = 0; i < pixelsOnScreen.size(); ++i)
            pixelBuffer[i] = pixelsOnScreen[i].rgba_;

        std::this_thread::sleep_for(std::chrono::milliseconds(timescale));
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    // Cycle colors on right click
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



        // Update texture with pixel data
        //for (auto & z : pixelBuffer) z = randint(0u, 0xFFFFFFFF);




        float mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        int windowWidth, windowHeight;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        float scaleX = static_cast<float>(windowWidth) / MAP_WIDTH;
        float scaleY = static_cast<float>(windowHeight) / MAP_HEIGHT;

        // Convert to grid coordinates
        int pixelX = static_cast<int>(mouseX / scaleX);
        int pixelY = static_cast<int>(mouseY / scaleY);



        // Draw if left mouse is held down
        if (mouseDown && pixelX >= 0 && pixelX < MAP_WIDTH && pixelY >= 0 && pixelY < MAP_HEIGHT) {
            pixelsOnScreen[pixelY * MAP_WIDTH + pixelX].rgba_ = colors[currentColorIndex];
        }




        SDL_UpdateTexture(texture, nullptr, pixelBuffer.data(), MAP_WIDTH * sizeof(uint32_t)); //todo: use the streaming version

        // Render to screen
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

