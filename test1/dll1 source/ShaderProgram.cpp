#include "pch.h"
#include "ShaderProgram.h"


ShaderSourceString ShaderProgram::PraseShaderSource(const std::string& file)
{
    std::ifstream source(file);
    if (!source.is_open())
    {
        std::cout << "the given file path maybe wrong" << std::endl;
        return {};
    }

    std::string vertex_source;
    std::string fragment_source;
    int type = -1; //specifies the shader mode
    std::string line;
    while (getline(source, line))
    {
        if (line.find("#shader") != std::string::npos) //need to prase
        {
            if (line.find("vertex") != std::string::npos)
                type = 0;
            else if (line.find("fragment") != std::string::npos)
                type = 1;
        }
        else { //start prase
            if (type == 0) //vertex mode
            {
                vertex_source += line;
                vertex_source += "\n";
            }
            else if (type == 1) //fragment mode
            {
                fragment_source += line;
                fragment_source += "\n";
            }
        }
    }
    return { vertex_source, fragment_source };
}

unsigned int ShaderProgram::compileShader(unsigned int type, const std::string& shader_source)
{
    unsigned int shader;
    //before create shader, we need to check if the type given is right
    if (type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER)
    {
        std::cout << "give the wrong type of shader" << std::endl;
        return 0;
    }

    shader = glCreateShader(type);
    const char* c_src = shader_source.c_str();
    glShaderSource(shader, 1, &c_src, NULL);
    glCompileShader(shader);

    //check if compiling successfully
    int res;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE)
    {
        int len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        char* info = new char(len);
        glGetShaderInfoLog(shader, len, &len, info);
        std::cout << info << std::endl;
        delete info;
    }
    return shader;
}

unsigned int ShaderProgram::createShaderProgram(const std::string& file)
{
    ShaderSourceString ss = PraseShaderSource(file);

    program = glCreateProgram();
    unsigned int vertex_shader = compileShader(GL_VERTEX_SHADER, ss.vertex_source);
    unsigned int fragment_shader = compileShader(GL_FRAGMENT_SHADER, ss.fragment_source);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program); //link the two shader together
    glValidateProgram(program); //validate the program

    glDeleteShader(vertex_shader); //now we don't need the shader object
    glDeleteShader(fragment_shader);

    return program;
}

unsigned int ShaderProgram::createShaderProgram(const std::string& vertex_source, const std::string& fragment_source)
{
    program = glCreateProgram();
    unsigned int vertex_shader = compileShader(GL_VERTEX_SHADER, vertex_source);
    unsigned int fragment_shader = compileShader(GL_FRAGMENT_SHADER, fragment_source);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program); //link the two shader together
    glValidateProgram(program); //validate the program

    glDeleteShader(vertex_shader); //now we don't need the shader object
    glDeleteShader(fragment_shader);

    return program;
}

unsigned int ShaderProgram::useProgram()
{
    glUseProgram(this->program);
    return 0;
}

unsigned int ShaderProgram::deleteProgram()
{
    glDeleteProgram(this->program);
    return 0;
}
