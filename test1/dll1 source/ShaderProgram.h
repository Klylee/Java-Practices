#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>
#include <fstream>

struct ShaderSourceString
{
    std::string vertex_source;
    std::string fragment_source;
};

class ShaderProgram
{
    unsigned int program;

    ShaderSourceString PraseShaderSource(const std::string& file);
    unsigned int compileShader(unsigned int type, const std::string& shader_source);
public:
    unsigned int createShaderProgram(const std::string& file);
    unsigned int createShaderProgram(const std::string& vertex_source, const std::string& fragment_source);
    unsigned int useProgram();
    unsigned int deleteProgram();
};