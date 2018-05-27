#include "init.hpp"
#include <cstdio>
/**
* Log an SDL error with some error message to the output stream of our choice
* @param msg The error message to write, format will be msg error: SDL_GetError()
**/
void logSDLError(const char* msg){
	fprintf(stderr, "%s, error: %s", msg, SDL_GetError());
};

/**
* Loads a BMP image into a texture on the rendering device
* @param file The BMP image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const char* file, SDL_Renderer *ren){
	//Initialize to nullptr to avoid dangling pointer issues
	SDL_Texture *texture = nullptr;
	//Load the image
	SDL_Surface *loadedImage = SDL_LoadBMP(file);
	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Make sure converting went ok too
		if (texture == nullptr){
			logSDLError("CreateTextureFromSurface failed");
		}
	}
	else {
		logSDLError("LoadBMP failed");
	}
	return texture;
}
