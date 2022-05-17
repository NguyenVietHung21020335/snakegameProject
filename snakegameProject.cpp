
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
//Kich thuoc cua so
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Hằng số bề mặt nhấn phím ( Giống kiểu đặt cho các hẳng số các phim lần lượt là 0,1,2,3,4,5)
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_TOTAL
};

//Khởi động SDL và tạo cửa sổ
bool init();
//Tải ảnh
bool loadmedia();
//Giải phóng phương tiện và tắt SDL 
void close();

// Tải hình ảnh riêng lẻ làm kết cấu
SDL_Texture* loadTexture(std::string path);
/*Loads individual image
SDL_Surface* loadSurface(std::string path); */
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;
//Surface được chứa trong cửa sổ
SDL_Surface* gScreenSurface = NULL;
/*Hình ảnh được tải và hiển thị lên màn hình
SDL_Surface* gHelloWorld = NULL;*/
// Các hình ảnh tương ứng với một lần nhấn phím ( mảng con trỏ chứa các ảnh mà ta sẽ dùng)
SDL_Texture* gKeyPressSurface[KEY_PRESS_SURFACE_TOTAL];
//Hình ảnh hiển thị hiện tại(tùy theo phím nhận đc)
SDL_Texture* gCurrentSurface = NULL;
// Hình ảnh hiển thị hiện tại
SDL_Texture* gTexture = NULL;




bool init()
{
	//Cờ(đánh dấu) khởi tạo (Cờ này là cờ đánh dấu xem khởi tạo có oke không)
	bool success = true;
	//Khởi tạo SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Đặt tính năng lọc kết cấu thành tuyến tính
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		//Mở cửa sổ
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		//Kiểm tra xem cửa sổ có lỗi không
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Tạo trình kết xuất cho cửa sổ
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Khởi tạo màu của trình kết xuất
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				// Khởi tạo PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

/*
Chức năng tải kết cấu của chúng tôi trông gần giống như trước đây chỉ bây giờ thay vì chuyển đổi bề mặt được tải sang định dạng hiển thị,
chúng tôi tạo kết cấu từ bề mặt được tải bằng cách sử dụng SDL_CreateTextureFromSurface .
Giống như trước đây, chức năng này tạo ra một kết cấu mới từ một bề mặt hiện có, có nghĩa là trước khi chúng ta phải giải phóng bề mặt đã tải và sau đó trả lại kết cấu đã tải.
*/

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Tải ảnh "default"
	gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] = loadTexture("04_key_presses/press.bmp");
	//Check lỗi
	if (gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load image! \n");
		success = false;
	}

	//Tải ảnh "default"
	gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] = loadTexture("04_key_presses/left.bmp");
	//Check lỗi
	if (gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load image! \n");
		success = false;
	}

	//Tải ảnh "default"
	gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] = loadTexture("04_key_presses/right.bmp");
	//Check lỗi
	if (gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Failed to load image! \n");
		success = false;
	}

	//Tải ảnh "default"
	gKeyPressSurface[KEY_PRESS_SURFACE_UP] = loadTexture("04_key_presses/up.bmp");
	//Check lỗi
	if (gKeyPressSurface[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load image! \n");
		success = false;
	}

	//Tải ảnh "default"
	gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] = loadTexture("04_key_presses/down.bmp");
	//Check lỗi
	if (gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load image! \n");
		success = false;
	}
	return success;
}

void close()
{
	//Giai phong surface
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++)
	{
		SDL_DestroyTexture(gKeyPressSurface[i]);
		gKeyPressSurface[i] = NULL;
	}

	//Giải phóng cửa sổ
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Tắt SDL
	SDL_Quit();
	//Tắt IMG
	IMG_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	//khai báo một con trỏ đến hình ảnh được tối ưu hóa cuối cùng.
	SDL_Surface* optimizedSurface = NULL;
	// Tải hình ảnh tại đường dẫn được chỉ định
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	//Nếu hình ảnh được tải thành công trong các dòng mã trước đó, chúng tôi sẽ tối ưu hóa bề mặt mà chúng tôi đã tải.
	else {
		// Chuyển đổi bề mặt sang định dạng màn hình
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		// Giải phóng bề mặt đã tải cũ (trước khi convert)
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
};

int main(int argc, char* args[])
{
	//Khoi dong SDL và mo cua so
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Tải ảnh
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Cờ lặp chính
			bool quit = false;
			//Trình xử lý sự kiện
			SDL_Event e;
			//Cài surface mặt định để hiện thị
			gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
			while (!quit) {
				// Xử lý các sự kiện trên hàng đợi
				while (SDL_PollEvent(&e) != 0) {
					// Yêu cầu của người dùng thoát
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					// Người dùng nhấn một phím
					else if (e.type = SDL_KEYDOWN) //Bên trong Sự kiện SDL là sự kiện Bàn phím SDL chứa thông tin cho sự kiện quan trọng.Bên trong đó là một SDL Keysym chứa thông tin về phím được nhấn.Kí khóa đó chứa Mã khóa SDL xác định phím đã được nhấn.
					{
						// Chọn bề mặt dựa trên phím bấm
						switch (e.key.keysym.sym)
						{
						case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_LEFT];
							break;

						case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT];
							break;

						case SDLK_UP:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_UP];
							break;

						case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DOWN];
							break;

						default:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}

				//Clear screen
				SDL_RenderClear(gRenderer);

				//Render texture to screen
				for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
					SDL_RenderCopy(gRenderer, gKeyPressSurface[i], NULL, NULL);
				}


				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	//Giải phóng tài nguyên và đóng SDL
	close();
	return 0;
}