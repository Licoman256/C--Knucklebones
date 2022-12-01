#define STB_IMAGE_IMPLEMENTATION
#include "game.h"
#include "stb/stb_image.h"
#include <GLFW/glfw3.h>
#include <iostream>

#define TEX1_FILE_NAME  "data/cat.png"

void Game::PrepareTextures() {
	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load(TEX1_FILE_NAME, &widthImg, &heightImg, &numColCh, 0);
	if (!bytes) {
		std::cout << "Not found texture file: " << TEX1_FILE_NAME << std::endl;
		return;
	}

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_PROXY_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_PROXY_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_PROXY_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_PROXY_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

}

// Vertex Shader source code
const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

void Game::PrepareShaders() {
	//unsigned int VBO;
	//glGenBuffers(1, &VBO);
}
