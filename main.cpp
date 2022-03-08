#include "SDL.h"
#include <SDL2/SDL.h>
// #include "SDL_ttf.h"
#include <iostream>
#include <vector>

using namespace std;
int main()
{

	int count =0;
	int grid_cell_size = 26;
	int grid_width = 36;
	int grid_height = 32;
	int window_width = (grid_width * grid_cell_size) + 1;
	int window_height = (grid_height * grid_cell_size) + 1;
	int x = 0;
	int y = 0;
	bool up = false, down = false, right = false, left = false, clicked = false;

	vector<vector<int> > food;
	vector<int> f;
	f.push_back(4 * grid_cell_size);
	f.push_back(4 * grid_cell_size);
	food.push_back(f);
	f.clear();

	vector<vector<int> > point;
	SDL_Rect grid_cursor_ghost = {0, 0, grid_cell_size, grid_cell_size};

	SDL_Color grid_background = {22, 22, 22, 255};
	SDL_Color grid_line_color = {44, 44, 44, 255};
	SDL_Color grid_cursor_ghost_color = {44, 44, 44, 255};
	SDL_Color grid_cursor_color = {33, 47, 60, 1};

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s", SDL_GetError());
		return EXIT_FAILURE;
	}
	// if (TTF_Init() < 0)
	// {
	// 	cout << "ttf";
	// 	return EXIT_FAILURE;
	// }
	// TTF_Font * font = TTF_OpenFont("arial.ttf", 25);
	// SDL_Color color = { 255, 255, 255 };
	// SDL_Surface * surface = TTF_RenderText_Solid(font,"Welcome to Gigi Labs", color);
	SDL_Window *window;
	SDL_Renderer *renderer;
	if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Create window and renderer: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_SetWindowTitle(window, "mid point line algorithm");

	SDL_bool quit = SDL_FALSE;
	SDL_bool mouse_active = SDL_FALSE;
	SDL_bool mouse_hover = SDL_FALSE;

	while (!quit)
	{
		vector<int> p;
		// linePoints.clear();
		bool is_exist = false;
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
				case SDLK_UP:
					if (point.size() > 0)
					{
						if (point.size() == 1)
						{
							up = true;
							down = false;
							right = false;
							left = false;
						}
						else if (!down)
						{
							up = true;
							down = false;
							right = false;
							left = false;
						}
					}
					break;
				case SDLK_s:
				case SDLK_DOWN:
					if (point.size() > 0)
					{
						if (point.size() == 1)
						{
							up = false;
							down = true;
							right = false;
							left = false;
						}
						else if (!up)
						{
							up = false;
							down = true;
							right = false;
							left = false;
						}

						// p.push_back(point[point.size() - 1][0]);
						// p.push_back(point[point.size() - 1][1] + grid_cell_size);
						// point.push_back(p);
						// point.erase(point.begin());
					}
					break;
				case SDLK_a:
				case SDLK_LEFT:
					if (point.size() > 0)
					{
						if (point.size() == 1)
						{
							up = false;
							down = false;
							right = false;
							left = true;
						}
						else if (!right)
						{
							up = false;
							down = false;
							right = false;
							left = true;
						}

						// p.push_back(point[point.size() - 1][0] - grid_cell_size);
						// p.push_back(point[point.size() - 1][1]);
						// point.push_back(p);
						// point.erase(point.begin());
					}
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					if (point.size() > 0)
					{
						if (point.size() == 1)
						{
							up = false;
							down = false;
							right = true;
							left = false;
						}
						else if (!left)
						{
							up = false;
							down = false;
							right = true;
							left = false;
						}

						// p.push_back(point[point.size() - 1][0] + grid_cell_size);
						// p.push_back(point[point.size() - 1][1]);
						// point.push_back(p);
						// point.erase(point.begin());
					}
					break;
				case SDLK_ESCAPE:
					up = false;
					down = false;
					right = false;
					left = false;
					point.clear();

					break;
				case SDLK_z:
					if (point.size() > 0)
					{
						point.pop_back();
					}
					break;
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					p.push_back((event.motion.x / grid_cell_size) * grid_cell_size);
					p.push_back((event.motion.y / grid_cell_size) * grid_cell_size);
					point.push_back(p);
					break;
				case SDL_BUTTON_RIGHT:
					int j = 0;
					for (auto it = point.begin(); it != point.end(); ++it, j++)
					{
						if (((event.motion.x / grid_cell_size) * grid_cell_size) == point[j][0] && ((event.motion.y / grid_cell_size) * grid_cell_size) == point[j][1])
						{
							point.erase(it);
							break;
						}
					}
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				grid_cursor_ghost.x = (event.motion.x / grid_cell_size) * grid_cell_size;
				grid_cursor_ghost.y = (event.motion.y / grid_cell_size) * grid_cell_size;

				if (!mouse_active)
					mouse_active = SDL_TRUE;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouse_hover)
					mouse_hover = SDL_TRUE;
				else if (event.window.event == SDL_WINDOWEVENT_LEAVE && mouse_hover)
					mouse_hover = SDL_FALSE;
				break;
			case SDL_QUIT:
				quit = SDL_TRUE;
				cout << "final point : "<< count << endl;
				break;
			}
		}

		// Draw grid background.
		SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g,
							   grid_background.b, grid_background.a);
		SDL_RenderClear(renderer);

		// Draw grid lines.
		SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g,
							   grid_line_color.b, grid_line_color.a);

		// vertical lines
		for (int x = 0; x < 1 + grid_width * grid_cell_size; x += grid_cell_size)
		{
			SDL_RenderDrawLine(renderer, x, 0, x, window_height);
		}

		// horizontal lines
		for (int y = 0; y < 1 + grid_height * grid_cell_size; y += grid_cell_size)
		{
			SDL_RenderDrawLine(renderer, 0, y, window_width, y);
		}

		if (mouse_active && mouse_hover)
		{
			SDL_SetRenderDrawColor(renderer, grid_cursor_ghost_color.r,
								   grid_cursor_ghost_color.g,
								   grid_cursor_ghost_color.b,
								   grid_cursor_ghost_color.a);
			SDL_RenderFillRect(renderer, &grid_cursor_ghost);
		}

		SDL_SetRenderDrawColor(renderer, grid_cursor_color.r, grid_cursor_color.g, grid_cursor_color.b, grid_cursor_color.a);

		for (int i = 0; i < point.size(); i++)
		{
			SDL_Rect temp = {
				.x = point[i][0],
				.y = point[i][1],
				.w = grid_cell_size,
				.h = grid_cell_size,
			};
			SDL_RenderFillRect(renderer, &temp);
		}
		if (food.size() == 0)
		{
			f.push_back((rand() % grid_width) * grid_cell_size);
			f.push_back((rand() % grid_height) * grid_cell_size);
			food.push_back(f);
			count++;
			f.clear();
		}
		for (int i = 0; i < food.size(); i++)
		{
			SDL_Rect temp = {
				.x = food[i][0],
				.y = food[i][1],
				.w = grid_cell_size,
				.h = grid_cell_size,
			};
			SDL_SetRenderDrawColor(renderer, 170, 54, 42, 1);
			SDL_RenderFillRect(renderer, &temp);
		}
		if (point.size() == 1)
		{
			if (up)
			{
				// SDL_RenderFillRect(renderer, &temp4);
				if ((point[0][1] - grid_cell_size) == food[0][1] && point[0][0] == food[0][0])
				{
					p.push_back((point[0][0]));
					p.push_back(((point[0][1] - grid_cell_size) % (window_height - 1) + (window_height - 1)) % (window_height - 1));
					point.push_back(p);
					p.clear();
					food.clear();
				}
				else
				{
					p.push_back((point[0][0]));
					p.push_back(((point[0][1] - grid_cell_size) % (window_height - 1) + (window_height - 1)) % (window_height - 1));
					point.push_back(p);
					point.erase(point.begin());
					p.clear();
				}
			}
			else if (down)
			{
				// SDL_RenderFillRect(renderer, &temp4);
				if ((point[0][1] + grid_cell_size) == food[0][1] && point[0][0] == food[0][0])
				{
					p.push_back((point[0][0]));
					p.push_back((point[0][1] + grid_cell_size) % (window_height - 1));
					point.push_back(p);
					p.clear();
					food.clear();
				}
				else
				{
					p.push_back((point[0][0]));
					p.push_back((point[0][1] + grid_cell_size) % (window_height - 1));
					point.push_back(p);
					point.erase(point.begin());
					p.clear();
				}
			}
			else if (left)
			{
				// SDL_RenderFillRect(renderer, &temp4);
				if ((point[0][0] - grid_cell_size) == food[0][0] && point[0][1] == food[0][1])
				{
					p.push_back((point[0][0] - grid_cell_size) % (window_width - 1));
					p.push_back((point[0][1]));
					point.push_back(p);
					food.clear();
					p.clear();
				}
				else
				{
					p.push_back(((point[0][0] - grid_cell_size) % (window_width - 1) + (window_width - 1)) % (window_width - 1));
					p.push_back((point[0][1]));
					point.push_back(p);
					point.erase(point.begin());
					p.clear();
				}
			}
			else if (right)
			{
				// SDL_RenderFillRect(renderer, &temp4);
				if ((point[0][0] + grid_cell_size) == food[0][0] && point[0][1] == food[0][1])
				{
					p.push_back((point[0][0] + grid_cell_size) % (window_width - 1));
					p.push_back((point[0][1]));
					point.push_back(p);
					food.clear();
					p.clear();
				}
				else
				{
					p.push_back((point[0][0] + grid_cell_size) % (window_width - 1));
					p.push_back((point[0][1]));
					point.push_back(p);
					point.erase(point.begin());
					p.clear();
				}
			}
			SDL_Delay(100);
		}
		else if (point.size() > 1)
		{
			if (up)
			{
				// SDL_RenderFillRect(renderer, &temp4);
				if ((point[point.size() - 1][1] - grid_cell_size) == food[0][1] && (point[point.size() - 1][0]) == food[0][0])
				{
					p.push_back((point[point.size() - 1][0]));
					p.push_back((point[point.size() - 1][1] - grid_cell_size) % (window_height - 1));
					point.push_back(p);
					p.clear();
					food.clear();
				}
				else
				{

					p.push_back((point[point.size() - 1][0]));
					p.push_back(((point[point.size() - 1][1] - grid_cell_size) % (window_height - 1) + (window_height - 1)) % (window_height - 1));
					for(int i=3;i<point.size();i++){
						if((point[point.size() - 1][1] - grid_cell_size) == point[i][1] && (point[point.size() - 1][0]) == point[i][0]){
							up = false;
							down = false;
							right = false;
							left = false;
							// point.clear();
						}
					}
					point.push_back(p);
					point.erase(point.begin());
					p.clear();
				}
			}
			else if (down)
			{
				// SDL_RenderFillRect(renderer, &temp4);
				if ((point[point.size() - 1][1] + grid_cell_size) == food[0][1] && (point[point.size() - 1][0]) == food[0][0])
				{
					p.push_back((point[point.size() - 1][0]));
					p.push_back((point[point.size() - 1][1] + grid_cell_size) % (window_height - 1));
					point.push_back(p);
					p.clear();
					food.clear();
				}
				else
				{
					p.push_back((point[point.size() - 1][0]));
					p.push_back((point[point.size() - 1][1] + grid_cell_size) % (window_height - 1));
					for(int i=3;i<point.size();i++){
						if((point[point.size() - 1][1] + grid_cell_size) == point[i][1] && (point[point.size() - 1][0]) == point[i][0]){
							up = false;
							down = false;
							right = false;
							left = false;
							// point.clear();
						}
					}
					point.push_back(p);
					point.erase(point.begin());
					p.clear();
				}
			}
			else if (left)
			{
				// SDL_RenderFillRect(renderer, &temp4);
				if ((point[point.size() - 1][0] - grid_cell_size) == food[0][0] && (point[point.size() - 1][1]) == food[0][1])
				{
					p.push_back((point[point.size() - 1][0] - grid_cell_size) % (window_width - 1));
					p.push_back((point[point.size() - 1][1]));
					point.push_back(p);
					p.clear();
					food.clear();
				}
				else
				{
					p.push_back(((point[point.size() - 1][0] - grid_cell_size) % (window_width - 1) + (window_width - 1)) % (window_width - 1));
					p.push_back((point[point.size() - 1][1]));
					for(int i=3;i<point.size();i++){
						if((point[point.size() - 1][0] - grid_cell_size) == point[i][0] && (point[point.size() - 1][1]) == point[i][1]){
							up = false;
							down = false;
							right = false;
							left = false;
							// point.clear();
						}
					}
					point.push_back(p);
					point.erase(point.begin());
					p.clear();
				}
			}
			else if (right)
			{
				// SDL_RenderFillRect(renderer, &temp4);
				if ((point[point.size() - 1][0] + grid_cell_size) == food[0][0] && (point[point.size() - 1][1]) == food[0][1])
				{
					p.push_back((point[point.size() - 1][0] + grid_cell_size) % (window_width - 1));
					p.push_back((point[point.size() - 1][1]));
					point.push_back(p);
					food.clear();
					p.clear();
				}
				else
				{
					p.push_back((point[point.size() - 1][0] + grid_cell_size) % (window_width - 1));
					p.push_back((point[point.size() - 1][1]));
					for(int i=3;i<point.size();i++){
						if((point[point.size() - 1][0] + grid_cell_size) == point[i][0] && (point[point.size() - 1][1]) == point[i][1]){
							up = false;
							down = false;
							right = false;
							left = false;
							// point.clear();
						}
					}
					point.push_back(p);
					point.erase(point.begin());
					p.clear();
				}
			}
			// }

			SDL_Delay(150);
		}

		cout << count << " "<< endl;
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	// TTF_Quit();

	return EXIT_SUCCESS;
}