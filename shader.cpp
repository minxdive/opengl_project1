#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"

shader::shader(const std::string& vertex_path, const std::string& fragment_path)
{
    std::string vertex_shader_code     = read_shader_file(vertex_path);
    std::string fragment_shader_code   = read_shader_file(fragment_path);
    const char* vertex_shader_source   = vertex_shader_code.c_str();
    const char* fragment_shader_source = fragment_shader_code.c_str();

    // Shader compiling
    std::uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);

    check_compile_error(vertex_shader, "vertex");

    std::uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);

    check_compile_error(fragment_shader, "fragment");

    // shader program
    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader);
    glAttachShader(program_id, fragment_shader);
    glLinkProgram(program_id);

    check_compile_error(program_id, "program");

    // Delete shaders...
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

std::string shader::read_shader_file(const std::string& path)
{
    std::ifstream shader_file {path};
    if (!shader_file) {
        std::cerr << "Failed open to " << path << ".\n";
        return "";
    }

    std::stringstream code_stream;
    code_stream << shader_file.rdbuf();

    //std::string deliver_code = code_stream.str();
    return code_stream.str();
}

void shader::check_compile_error(std::uint32_t shader_id, std::string_view type_name)
{
    int success = 0;
    if (type_name != "program") {  // vertex, fragment
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            char info_log[1024];
            glGetShaderInfoLog(shader_id, 1024, nullptr, info_log);
            std::cerr << "Error::shader::" << type_name <<"::compilation_failed\n" << info_log << '\n';
        }    
    }
    else {  // program
        glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
        if (!success) {
            char info_log[1024];
            glGetProgramInfoLog(shader_id, 1024, nullptr, info_log);
            std::cerr << "Error::shader::" << type_name << "::linking_failed\n" << info_log << '\n';
        }
    }
}

void shader::use_program()
{
    glUseProgram(program_id);
}

void shader::set_vec4(const std::string& value_name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(program_id, "our_color"), x, y, z, w);
}
