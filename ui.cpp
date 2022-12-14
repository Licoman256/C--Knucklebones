#define STB_IMAGE_IMPLEMENTATION
#include "game.h"
#include "stb/stb_image.h"
#include <iostream>


Game* Game::_this = nullptr;
void Game::resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	_this->Render();
}

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		_this->pressedKey = key;
	}
	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window, 1);
	}
}

static char const* textFileNames[TEXTURE_LAST] = {
	"data/background.png",
	"data/field.png",
	"data/slot.png",
	"data/numbers.png",
	"data/lightning.png",
	"data/D-lightning.png",
	"data/dice1.png",
	"data/dice2.png",
	"data/dice3.png",
	"data/dice4.png",
	"data/dice5.png",
	"data/dice6.png",
};

GLFWwindow* Field::CreateWindow() {
	// Create a windowed mode window and its OpenGL context
	auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Knucklebones", NULL, NULL);
	if (window) {
		// Make the window's context current
		glfwMakeContextCurrent(window);

		// tell OpenGL where to render
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		// have minimal textures for the first render
		StartupTextures();
	}

	return window;
}


void TexDic::StartupTextures() {
	// generate names
	glGenTextures(COUNT_TEX_NAMES, textureNames);

	// load what's needed on start
	LoadTexture(E_BACKGROUND, textFileNames[E_BACKGROUND]);
	LoadTexture(E_FIELD,      textFileNames[E_FIELD]);
}

void TexDic::LoadMainBlockTex() {

	// load for each
	for (int i = E_SLOT; i < TEXTURE_LAST; i++) {
		LoadTexture(i, textFileNames[i]);
	}

	// clean up
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool TexDic::LoadTexture(int idxTx, char const* filename) {

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

void TexDic::EnableTransparancy() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
}

void TexDic::PrepareShaders() {

}
