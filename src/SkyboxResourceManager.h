#ifndef SKYBOX_RESOURCE_MANAGER_H
#define SKYBOX_RESOURCE_MANAGER_H

#include <GL/glew.h>
#include <iostream>
#include <vector>

#include "stb_image.h"

/**
 * Vertex manager for Skybox instances.
 */
class SkyboxResourceManager {
 public:
  SkyboxResourceManager() {
    std::vector<std::string> faces = {
/*
        "res/ame_siege/siege_rt.tga",
        "res/ame_siege/siege_lf.tga",
        "res/ame_siege/siege_up.tga",
        "res/ame_siege/siege_dn.tga",
        "res/ame_siege/siege_bk.tga",
        "res/ame_siege/siege_ft.tga"
*/
        "res/ely_hills/hills_rt.tga",
        "res/ely_hills/hills_lf.tga",
        "res/ely_hills/hills_up.tga",
        "res/ely_hills/hills_dn.tga",
        "res/ely_hills/hills_bk.tga",
        "res/ely_hills/hills_ft.tga"
/*

        "res/skybox_lake/right.jpg",
        "res/skybox_lake/left.jpg",
        "res/skybox_lake/top.jpg",
        "res/skybox_lake/bottom.jpg",
        "res/skybox_lake/back.jpg",
        "res/skybox_lake/front.jpg",
*/
     };

    /*
        GLfloat vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  1.0f,
            0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  1.0f,
            -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  1.0f,

            -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  -1.0f,
             0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  -1.0f,
             0.5f,  0.5f, 0.5f,  0.0f,  0.0f,  -1.0f,
             0.5f,  0.5f, 0.5f,  0.0f,  0.0f,  -1.0f,
            -0.5f,  0.5f, 0.5f,  0.0f,  0.0f,  -1.0f,
            -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  -1.0f,

            -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,  0.0f,
            -0.5f, 0.5f,  -0.5f, 1.0f, 0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f,
            -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  -0.5f, -1.0f,  0.0f,  0.0f,
            0.5f,  -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            0.5f,  -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            0.5f,  -0.5f, 0.5f,  -1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
            0.5f,  -0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
            0.5f,  -0.5f, 0.5f,  0.0f,  1.0f, 0.0f,
            0.5f,  -0.5f, 0.5f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f,  1.0f, 0.0f,

            -0.5f, 0.5f,  -0.5f, 0.0f,  -1.0f,  0.0f,
            0.5f,  0.5f,  -0.5f, 0.0f,  -1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  -1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  -1.0f,  0.0f,
            -0.5f, 0.5f,  0.5f,  0.0f,  -1.0f,  0.0f,
            -0.5f, 0.5f,  -0.5f, 0.0f,  -1.0f,  0.0f};
    */
    float vertices[] = {
        // positions
        -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f,
        1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,

        -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f,
        -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,

        1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,

        -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,

        -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f,
        1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f};

    
/*
    for (int i = 0; i < 12*9; i++) {
        vertices[i] *= 1000.0f;
    }
*/
/*
    // First, set the container's VAO (and VBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(VAO);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
*/


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    texture = loadSkybox(faces);
  }

  ~SkyboxResourceManager() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
  }

  GLuint getContainerVAO() { return VAO; }
  unsigned int getTexture() { return texture; }

 private:
  GLuint VBO;
  GLuint VAO;
  unsigned int texture;

  // Method copied and modified from
  // https://learnopengl.com/#!Advanced-OpenGL/Cubemaps
  unsigned int loadSkybox(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
      unsigned char* data =
          stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
      if (data) {
        std::cout << "Loaded image" << std::endl;
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width,
                     height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
      } else {
        std::cout << "Cubemap texture failed to load at path: " << faces[i]
                  << std::endl;
        stbi_image_free(data);
      }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
  }
};

#endif
