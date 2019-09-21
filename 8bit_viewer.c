#include<SDL.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define SDL_MAIN_HANDLED

static inline void fill_texture_buffer_from_8bit(int* tex_buf,
						 unsigned char* buffer,
						 int width, int height) {

  int i;
  int * current_int;
  char* current_char;
  for(i=0;i<width*height;i++) {
    current_int = tex_buf+i;
    current_char = (char*)current_int;

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    
    current_char[0]=buffer[i];
    // G
    current_char[1]=buffer[i];
    // R
    current_char[2]=buffer[i];
    // A
    current_char[3]=255;

#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

    current_char[0] = 255;
    current_char[1] = buffer[i];
    current_char[2] = buffer[i];
    current_char[3] = buffer[i];
    
#endif

  }
  
}

unsigned char * load_image_from_file(char* filename,
				     unsigned int width,
				     unsigned int height) {

  unsigned char * image = malloc(sizeof(unsigned char)*width*height);
  int fd = open(filename, O_RDONLY);

  if (fd < 1) {
    printf("Error opening image file \n");
    _exit(1);
  }
  
  if (width*height != read(fd, image, width*height)) {
    printf("Error reading image file \n");
    _exit(1);
  }
  
  return(image);
}


int main(int argc, char** argv) {

  SDL_Window * my_window = NULL;
  SDL_Renderer * my_renderer = NULL;
  SDL_Texture * my_texture;
  SDL_Event my_event;

  int pitch;
  
  int width, height;
  char* image_8bit;
  int* image_32bit;

  if(argc != 2) {
  
    sscanf(argv[2],"%i", &width);
    sscanf(argv[3],"%i", &height);

  } else {

    width = 640;
    height = 400;

  }
    
  pitch = width*4;
  
  image_8bit = load_image_from_file(argv[1],width,height);

  SDL_SetMainReady();

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

  my_window = SDL_CreateWindow("The Fancy Overlord Image Viewer",
			       100,100,width,height,0);

  my_renderer = SDL_CreateRenderer(my_window,-1,SDL_RENDERER_SOFTWARE);
  my_texture = SDL_CreateTexture(my_renderer, SDL_PIXELFORMAT_ARGB8888,
				 SDL_TEXTUREACCESS_STREAMING,
				 width,height);
  

  SDL_LockTexture(my_texture,NULL,(void**)&image_32bit,&pitch);
  fill_texture_buffer_from_8bit(image_32bit,image_8bit,width,height);
  SDL_UnlockTexture(my_texture);
  SDL_RenderCopy(my_renderer,my_texture,NULL,NULL);
  SDL_RenderPresent(my_renderer);

  while(1) {

    SDL_RenderPresent(my_renderer);
    
    while(SDL_PollEvent(&my_event)){
      switch(my_event.type) {
      case SDL_QUIT:
	goto finish;
	break;
      case SDL_WINDOWEVENT:
	if(my_event.window.event == SDL_WINDOWEVENT_CLOSE) {
	  SDL_Quit();
	  goto finish;
	}
	break;
      }
    }
    SDL_Delay(50);
  }

 finish:
  return(0);
 }
