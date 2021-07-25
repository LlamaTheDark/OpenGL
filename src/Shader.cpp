#include "Shader.h"
#include "Renderer.h"
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(std::string& filepath)
	: m_Filepath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}
Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

bool Shader::CompileShader() {
    return 0;
}


/*
* ParseShader takes a file containing a vertex and fragment shader 
* and splits them into two strings for convenience.
* 
* @param filepath, the path to the file to be parsed
* @return a struct ShaderProgramSource
* 
*/
ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << std::endl;
        }
    }

    return { ss[0].str(), ss[1].str() };
}

/*
* CompileShader takes in some source code and creates an openGL shader with 
* that source code based on the type of shader to be compiled. It then 
* does some error checking and returns the id of the compiled shader. 
* 
* @param type, an unsigned int representing the type of shader to be compiled (e.g. GL_VERTEX_SHADER)
* @param source, a string containing the source code for the shader
* 
* @return the reference id of the compiled shader
*/
unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str(); // could also do src = &source[0];
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // error handling - we can query OpenGL to get info
    int result;
    // i - integer, v - vector / array / pointer
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }
    return id;
}

/*
* CreateShader uses CompileShader to compile botht the vertex and fragment shaders
* It then links the two to create an openGL program (i.e. just another shader
* that has both of the other shaders).
* 
* @param vertexShader
* @param fragmentShader
* 
* @return the id of the created openGL program.
*/
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    // now we have to attach our shaders to our program

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    // now we can delete the intermediates since they're stored inside our program
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}


void Shader::SetUniform4f(std::string& name, float v0, float v1, float v2, float v3) {
    int location = GetUniformLocation(name);
    GLCall(glUniform4f(location, v0, v1, v2, v3));
}
int Shader::GetUniformLocation(std::string& name) {
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) {
        std::cout << "Warning: uniform \'" << name << "\' doesn\'t exist." << std::endl;
    }
    return location;
}


void Shader::Bind() const {
    GLCall(glUseProgram(m_RendererID));
}
void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}