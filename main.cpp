#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <string.h>
using namespace std;

#define Win_width 800
#define Win_height 600
#define frame_terget_time (100 / FPS)
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool game_running = false;
int last_frame_time = 0;
int clicks = 0;
TTF_Font* font = NULL;
int x, y;
int text_width = 0;
int text_height = 0;
void display_text();

int initialize_window();

void process_input();

void update();

void render();

void destroy_window();

void setup() {
    font = TTF_OpenFont("comic.ttf", 40);
    SDL_Surface* iconsurface = SDL_LoadBMP("icon.bmp");
    SDL_SetWindowIcon(window, iconsurface);
    
}

int main (int argc, char *argv[]) {
    game_running = initialize_window();
    
    setup();

    while (game_running) {
        process_input();
        update();
        render();
    }

    

    destroy_window();

    return 0;
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            game_running = false;
            break;
        default:
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x, &y);
            if (x > ((Win_width/2)-(100/2)) && x < (Win_width/2)+(100/2) && y > 150 && y < 150+20){
                clicks++;
            }
            break;
    }   
}

void update() {
    last_frame_time = SDL_GetTicks();

}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Rect button = {(Win_width/2)-(100/2), 150, 100, 20};

    display_text();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &button);

    SDL_RenderPresent(renderer);
}

void display_text() {
    SDL_Color text_color = {255,255,255};
    char clicks_text[40];
    SDL_Texture* clicks_texture = NULL;
    if (font == NULL) {
        printf("font file eror\n");
        game_running = false;
    }
    else {
        sprintf(clicks_text, "%d", clicks);
        SDL_Surface* click_surface = TTF_RenderText_Solid(font, clicks_text, text_color);
        if (click_surface == NULL){
            printf("font surface error\n");
            game_running = false;
        } else {
            clicks_texture = SDL_CreateTextureFromSurface(renderer, click_surface);
            if (clicks_texture == NULL) {
                printf("font texture error\n");
                game_running = false;
            }
            else {
                text_width = click_surface->w;
                text_height = click_surface->h;
                SDL_FreeSurface(click_surface);
                SDL_Rect clickrect = {(Win_width/2)-(text_width/2), 40, text_width, text_height};

                SDL_RenderCopy(renderer, clicks_texture, NULL, &clickrect);
                SDL_DestroyTexture(clicks_texture);
            }
        }
    }
}


void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int initialize_window(void) {
    TTF_Init();
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {
        printf("init sdl failed\n");
        return 0;
    }


    window = SDL_CreateWindow("clicker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Win_width, Win_height, 0);
    

    if (!window) {
        printf ("failed to create window\n");
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        printf ("failed to create renderer\n");
        return 0;
    }

    return 1;
}