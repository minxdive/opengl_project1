#ifndef SHADER_H
#define SHADER_H

#include <iostream>

class shader {
public:
    shader(const std::string& vertex_path, const std::string& fragment_path);

    void set_vec4(const std::string& value_name, float x, float y, float z, float w);
    
    void use_program();
    std::uint32_t program_id;  // shader program
private:
    std::string read_shader_file(const std::string& path);
    void check_compile_error(std::uint32_t shader_id, std::string_view type_name);
};

#endif
