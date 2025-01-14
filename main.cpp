#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

int main()
{
    glfwInit();
    // OpenGL Version: major.minor => 3.3
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(800, 600, "HERO FLASH!", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "gladLoadGLLoader: Failed to initialize GLAD!\n";
        return -1;
    }

    shader gl_shader{"shader.vs", "shader.fs"};
    
    // H
    float h_vertices[] = {
        -0.95f, -0.5f,  0.0f,
        -0.85f, -0.5f,  0.0f,
        -0.95f,  0.5f,  0.0f,
        -0.85f,  0.5f,  0.0f,
        -0.85f,  0.05f, 0.0f,
        -0.65f,  0.05f, 0.0f,
        -0.65f, -0.05f, 0.0f,
        -0.85f, -0.05f, 0.0f,
        -0.65f, -0.5f,  0.0f,
        -0.55f, -0.5f,  0.0f,
        -0.65f,  0.5f,  0.0f,
        -0.55f,  0.5f,  0.0f
    };
    std::uint32_t h_indices[] = {
        0, 1,  2,
        1, 2,  3,
        4, 5,  6,
        4, 6,  7,
        8, 9,  10,
        9, 10, 11
    };
    // E
    float e_vertices[] = {
        -0.45f, -0.5f,  0.0f,
        -0.45f,  0.5f,  0.0f,
        -0.35f, -0.5f,  0.0f,
        -0.35f,  0.5f,  0.0f,
        -0.05f,  0.5f,  0.0f,
        -0.05f,  0.4f,  0.0f,
        -0.35f,  0.4f,  0.0f,
        -0.35f,  0.05f, 0.0f,
        -0.05f,  0.05f, 0.0f,
        -0.05f, -0.05f, 0.0f,
        -0.35f, -0.05f, 0.0f,
        -0.35f, -0.4f,  0.0f,
        -0.05f, -0.4f,  0.0f,
        -0.05f, -0.5f,  0.0f,
        -0.35f, -0.5f,  0.0f
    };
    std::uint32_t e_indices[] = {
        0,  1,  2,
        1,  2,  3,
        3,  4,  5,
        3,  5,  6,
        7,  8,  9,
        7,  9,  10,
        11, 12, 13,
        11, 13, 14
    };
    // R
    float r_vertices[] = {
        0.05f, -0.5f,  0.0f,
        0.05f,  0.5f,  0.0f,
        0.15f, -0.5f,  0.0f,
        0.15f,  0.5f,  0.0f,
        0.45f,  0.5f,  0.0f,
        0.45f,  0.4f,  0.0f,
        0.15f,  0.4f,  0.0f,
        0.45f,  0.05f, 0.0f,
        0.35f,  0.05f, 0.0f,
        0.35f,  0.4f,  0.0f,
        0.15f,  0.05f, 0.0f,
        0.15f,  0.15f, 0.0f,
        0.35f,  0.15f, 0.0f,
        0.15f, -0.05f, 0.0f,
        0.25f,  0.05f, 0.0f,
        0.35f, -0.5f,  0.0f,
        0.45f, -0.4f,  0.0f,
        0.45f, -0.5f,  0.0f
    };
    std::uint32_t r_indices[] = {
        0,  1,  2,
        1,  2,  3,
        3,  4,  5,
        3,  5,  6,
        5,  7,  8,
        5,  8,  9,
        8,  10, 11,
        8,  11, 12,
        10, 13, 14,
        13, 14, 15,
        14, 15, 16,
        15, 16, 17
    };
    float o_vertices[] = {
        0.55f, -0.5f, 0.0f,
        0.55f,  0.5f, 0.0f,
        0.65f, -0.5f, 0.0f,
        0.65f,  0.5f, 0.0f,
        0.65f,  0.4f, 0.0f,
        0.95f,  0.4f, 0.0f,
        0.95f,  0.5f, 0.0f,
        0.85f,  0.4f, 0.0f,
        0.85f, -0.4f, 0.0f,
        0.95f, -0.4f, 0.0f,
        0.65f, -0.4f, 0.0f,
        0.95f, -0.5f, 0.0f
    };
    std::uint32_t o_indices[] = {
        0, 1, 2,
        1, 2, 3,
        3, 4, 5,
        3, 5, 6,
        5, 7, 8,
        5, 8, 9,
        2, 9, 10,
        2, 9, 11
    };

    // Vertex input
    std::uint32_t vertex_buffer_object[4];
    std::uint32_t vertex_array_object[4];
    std::uint32_t element_buffer_object[4];
    
    // generate arrays and buffers
    glGenVertexArrays(4, vertex_array_object);
    glGenBuffers(4, vertex_buffer_object);
    glGenBuffers(4, element_buffer_object);
    
    // Binding arrays and buffers
    // H
    glBindVertexArray(vertex_array_object[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(h_vertices), h_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(h_indices), h_indices, GL_STATIC_DRAW);
    // Linking vertex attributes
    // shader.vs's location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);
    // E
    glBindVertexArray(vertex_array_object[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(e_vertices), e_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(e_indices), e_indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);
    // R
    glBindVertexArray(vertex_array_object[2]);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(r_vertices), r_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(r_indices), r_indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);
    // O
    glBindVertexArray(vertex_array_object[3]);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(o_vertices), o_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(o_indices), o_indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);
    

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Use shader program
        gl_shader.use_program();

        // Set uniform color
        float time_value = static_cast<float>(glfwGetTime());
        float color_value1 = std::abs(std::sinf(time_value));
        float color_value2 = std::abs(std::cosf(time_value));
        float color_value3 = std::abs(std::tanf(time_value));
        float color_value4 = std::abs(std::sinf(time_value)*0.5f);
        
        // Draw H
        gl_shader.set_vec4("our_color", color_value1, color_value2, color_value3, 1.0f);
        glBindVertexArray(vertex_array_object[0]);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        // Draw E
        gl_shader.set_vec4("our_color", color_value2, color_value3, color_value4, 1.0f);
        glBindVertexArray(vertex_array_object[1]);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
        // Draw R
        gl_shader.set_vec4("our_color", color_value3, color_value4, color_value1, 1.0f);
        glBindVertexArray(vertex_array_object[2]);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        // Draw O
        gl_shader.set_vec4("our_color", color_value4, color_value1, color_value2, 1.0f);
        glBindVertexArray(vertex_array_object[3]);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &vertex_array_object[0]);
    glDeleteBuffers(1, &vertex_buffer_object[0]);
    glDeleteProgram(gl_shader.program_id);
    
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
