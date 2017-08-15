#ifndef SKYBOX_RESOURCE_MANAGER_H
#define SKYBOX_RESOURCE_MANAGER_H

#include <GL/glew.h>

/**
 * Vertex manager for Skybox instances.
 */
class SkyboxResourceManager {
 public:
  SkyboxResourceManager() {
    // Set up data for OpenGL: vertex data, buffers, and attribute pointers
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

    // First, set the container's VAO (and VBO)
    glGenVertexArrays(1, &containerVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
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
  }

  ~SkyboxResourceManager() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &containerVAO);
  }

  GLuint getContainerVAO() { return containerVAO; }

 private:
  GLuint VBO;
  GLuint containerVAO;
};

#endif
