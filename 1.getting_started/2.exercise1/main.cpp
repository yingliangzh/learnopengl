//
//  main.cpp
//  HelloTriangle
//
//  Created by yingliang on 2/17/16.
//  Copyright © 2016 yingliang. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLfloat firstTriangle[] = {
    -0.9f, -0.5f, 0.0f,  // Left
    -0.0f, -0.5f, 0.0f,  // Right
    -0.45f, 0.5f, 0.0f,  // Top
};
GLfloat secondTriangle[] = {
     0.0f, -0.5f, 0.0f,  // Left
     0.9f, -0.5f, 0.0f,  // Right
     0.45f, 0.5f, 0.0f   // Top
};


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true,
    // closing the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800 / 2, 600 / 2, "LearnOpenGL", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);

    static const GLchar *vertex_src[] = {
        "#version 410 core                               \n"
        "layout (location = 0) in vec3 position; \n"
        "void main() \n"
        "{\n"
        "gl_Position = vec4(position.x, position.y, position.z, 1.0);"
        "}\n"
    };

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, vertex_src, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    static const GLchar *fragment_src[] = {
        "#version 410 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n"
    };

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, fragment_src, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    const GLchar* fragment_src2[] = {"#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 1.0f, 0.0f, 1.0f); // The color yellow \n"
    "}\n\0"};

    GLuint fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, fragment_src2, NULL);
    glCompileShader(fragmentShader2);

    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT2::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLuint shaderProgram2;
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }

    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);

    GLuint VAO[2];
    glGenVertexArrays(2, VAO);
    GLuint VBO[2];
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);

    return 0;
}
