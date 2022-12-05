#define STB_IMAGE_IMPLEMENTATION
#include "game.h"
#include "stb/stb_image.h"
#include <iostream>

#define TEX1_FILE_NAME  

void Field::PrepareTextures() {
	// generate names
	glGenTextures(COUNT_TEX_NAMES, textureNames);

	// load for each
	for (int i = 0; i < TEXTURE_LAST; i++) {
		LoadTexture(i, textFileNames[i]);
	}

	// clean up
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool Field::LoadTexture(int idxTx, char const* filename) {

	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load(filename, &widthImg, &heightImg, &numColCh, 0);
	if (!bytes) {
		std::cout << "Not found texture file: " << filename << std::endl;
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, textureNames[idxTx]);

	// modulation
	glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// filtration
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	stbi_image_free(bytes);

	return true;
}

void Field::EnableTransparancy() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
}

void Field::PrepareShaders() {

}
