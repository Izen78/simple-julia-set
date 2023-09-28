#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <complex>
#include <iostream>
// Fractal Tree or Julia Set or Game of Life (color)
// Julia Set (color, animated)
bool Input();
void Update(SDL_Renderer* renderer);
void Render(SDL_Renderer* renderer, int x, int y);
int inJuliaSet(std::complex<double> x);

std::complex<double> c(0,0);

int main() {
  //input, update, and render graphics loop

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;

  SDL_CreateWindowAndRenderer(500, 500, 0, &window, &renderer);
  //SDL_RenderSetScale(renderer, 5, 5);

  bool Running {true};

  while (Running) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    Running = Input();
    Update(renderer);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

bool Input() {

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
          return false;
        break;
      case SDL_QUIT:
        return false;
        break;
      case SDL_MOUSEMOTION:
        double x = event.motion.x;
        double y = event.motion.y;
        x = x / 500;
        y = y / 500;
        c.real(x);
        c.imag(y);
        std::cout << "x: " << x << " y: " << y << '\n';
    }
  }
  return true;
}

void Update(SDL_Renderer* renderer) {
  for (int x = 0; x < 500; x++) { // loop through window pixels
    for (int y = 0; y < 500; y++) {
      //double zx = std::lerp(-2.0, 2.0, static_cast<double>(x) / 500); // maps x to be between ranges -2.0 and 2.0
      //double zy = std::lerp(-2.0, 2.0, static_cast<double>(y) / 500); // maps y to be between ranges -2.0 and 2.0
      
      //int point_set = inJuliaSet(std::complex<double>(zx, zy));
      //int point_set = inJuliaSet(std::complex<double>(x, y));

      double zx = x / 500.0 * (2.0 + 2.0) - 2.0;
      double zy = y / 500.0 * (2.0 + 2.0) - 2.0;

      int iter = 0;
      int max_iter = 100;
      std::complex<double> z(zx, zy);
      while (std::abs(z) < 2.0 && iter < max_iter) {
        z = z * z + c;
        iter++;
      }

      Uint8 color = (iter % 256);
      SDL_SetRenderDrawColor(renderer, color, color, color, 255);
      SDL_RenderDrawPoint(renderer, x, y);
    }
  }
}

void Render(SDL_Renderer* renderer, int x, int y) {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderDrawPoint(renderer, x, y);
}

int inJuliaSet(std::complex<double> z) {
  const std::complex<double> c(-0.7, 0.27015);
  int iter = 0;
  int max_iter = 100;
  
  //while (iter < max_iter) {
  //  std::complex<double> z = std::pow(z, 2) + c;

  //  if (std::norm(z) > 2.0) 
  //    return iter;

  //  iter++;
  //}

  while (std::abs(z) < 2.0 && iter < max_iter) {
    z = z * z + c;
    iter++;
  }

  return 0;
}
