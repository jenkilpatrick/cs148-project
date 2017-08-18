#ifndef SEGMENT_RESOURCE_MANAGER_H
#define SEGMENT_RESOURCE_MANAGER_H

#include <GL/glew.h>

#include "stb_image.h"

/**
 * Vertex manager for Segment instances.
 */
class SegmentResourceManager {
 public:
  std::string leaf_texture = "res/coloredmapleleaffont2048.png";

  SegmentResourceManager() {
    // Set up data for OpenGL: vertex data, buffers, and attribute pointers
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, 0.5f,  -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f, 0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f,  0.0f,

         0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f,  -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f,  -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f,  -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,
    };

    // First, set the container's VAO (and VBO)
    glGenVertexArrays(1, &containerVAO);
    glGenBuffers(1, &containerVBO);

    glBindBuffer(GL_ARRAY_BUFFER, containerVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(containerVAO);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    setTextureFields();
  }

  ~SegmentResourceManager() {
    glDeleteBuffers(1, &containerVBO);
    glDeleteVertexArrays(1, &containerVAO);
    glDeleteBuffers(1, &textureVBO);
    glDeleteVertexArrays(1, &textureVAO);
  }

  GLuint getContainerVAO() { return containerVAO; }
  GLuint getTextureVAO() { return textureVAO; }
  unsigned int getTexture() { return texture; }

 private:
  GLuint containerVBO;
  GLuint containerVAO;
  GLuint textureVBO;
  GLuint textureVAO;

  unsigned int texture;

  unsigned int loadTexture(std::string file_path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(file_path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return textureID;
  }

  void setTextureFields() {
    texture = loadTexture(leaf_texture);

    float scale = 1.0f;
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, scale, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, scale, scale,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, scale, scale,
        -0.5f, 0.5f,  -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, scale,
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, scale, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, scale, scale,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, scale, scale,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, scale,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f,  0.0f, scale, scale,
        -0.5f,  0.5f, -0.5f, -1.0f, 0.0f,  0.0f, scale, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f, 0.0f,  0.0f, 0.0f, scale,
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f,  0.0f, scale, scale,

         0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, scale, scale,
         0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, scale, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 0.0f, scale,
         0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, scale, scale,

        -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f, scale, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f,  -1.0f, 0.0f, scale, scale,
         0.5f, -0.5f,  0.5f, 0.0f,  -1.0f, 0.0f, scale, scale,
        -0.5f, -0.5f,  0.5f, 0.0f,  -1.0f, 0.0f, 0.0f, scale,
        -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f, 0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, scale, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, scale, scale,
         0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, scale, scale,
        -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 0.0f, scale,
        -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
    };

    glGenVertexArrays(1, &textureVAO);
    glGenBuffers(1, &textureVBO);

    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(textureVAO);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);  

    glBindVertexArray(0);
  }
};

#endif
