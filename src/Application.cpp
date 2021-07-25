#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

#include "Shader.h"




//struct ShaderProgramSource {
//    std::string VertexSource;
//    std::string FragmentSource;
//};
//
//static ShaderProgramSource ParseShader(const std::string& filepath) {
//    std::ifstream stream(filepath);
//
//    enum class ShaderType {
//        NONE = -1, VERTEX = 0, FRAGMENT = 1
//    };
//
//    std::string line;
//    std::stringstream ss[2];
//    ShaderType type = ShaderType::NONE;
//    while (std::getline(stream, line)) {
//        if (line.find("#shader") != std::string::npos) {
//            if (line.find("vertex") != std::string::npos) {
//                type = ShaderType::VERTEX;
//            } else if (line.find("fragment") != std::string::npos) {
//                type = ShaderType::FRAGMENT;
//            }
//        } else {
//            ss[(int)type] << line << std::endl;
//        }
//    }
//    
//    return { ss[0].str(), ss[1].str() };
//}
//
//static unsigned int CompileShader(unsigned int type, const std::string& source) {
//    GLCall(unsigned int id = glCreateShader(type));
//    const char* src = source.c_str(); // could also do src = &source[0];
//    GLCall(glShaderSource(id, 1, &src, nullptr));
//    GLCall(glCompileShader(id));
//
//    // error handling - we can query OpenGL to get info
//    int result;
//    // i - integer, v - vector / array / pointer
//    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
//    if (result == GL_FALSE) {
//        int length;
//        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
//        char* message = (char*)alloca(length * sizeof(char));
//        GLCall(glGetShaderInfoLog(id, length, &length, message));
//        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
//        std::cout << message << std::endl;
//        GLCall(glDeleteShader(id));
//        return 0;
//    }
//    return id;
//}
//
//// the strings are supposed to be the actual source code
//static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
//    GLCall(unsigned int program = glCreateProgram());
//    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//    // now we have to attach our shaders to our program
//
//    GLCall(glAttachShader(program, vs));
//    GLCall(glAttachShader(program, fs));
//    GLCall(glLinkProgram(program));
//    GLCall(glValidateProgram(program));
//
//    // now we can delete the intermediates since they're stored inside our program
//    GLCall(glDeleteShader(vs));
//    GLCall(glDeleteShader(fs));
//
//    return program;
//}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    { // creating new scope so that the buffer destructors are called when we leave this scope.
        float positions[] = {
            -0.5f, -0.5f, // 0
             0.5f, -0.5f, // 1
             0.5f,  0.5f, // 2
            -0.5f,  0.5f  // 3
        };

        unsigned int indices[] = {
            0, 1, 2, // first trianGLCall(gle uses these positions
            2, 3, 0  // second trianGLCall(gle usees these positions
        };

        // initialize vertex array object, vertex buffer object, and index buffer object
        VertexArray vao;
        VertexBuffer vb(&positions, 4 * 2 * sizeof(float));
        IndexBuffer  ib(indices, 6);
        /*unsigned int vao;
        unsigned int vb;
        unsigned int ib;

        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glGenBuffers(1, &vb));
        GLCall(glGenBuffers(1, &ib));*/

        // bind and send data to the vertex buffer and index buffer objects
        /*GLCall(glBindBuffer(GL_ARRAY_BUFFER, vb));
        GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), &positions, GL_STATIC_DRAW));

        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(unsigned int), &indices, GL_STATIC_DRAW));*/

        // bind the vertex array object
        //GLCall(glBindVertexArray(vao));

        // enable the attribute index to be used for the position attribute
        //GLCall(glEnableVertexAttribArray(0));

        // give the layout of the position attribute to the vertex array at the same index
        //GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        vao.AddBuffer(vb, layout);


        //unsigned int vao; // vertex array object
        /*GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));*/

        /*VertexArray va;
        VertexBuffer vb(&positions, 4 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);*/

        //GLCall(glEnableVertexAttribArray(0));
        //GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

        std::string filepath = "res/shaders/Basic.shader";
        Shader shader(filepath);
        

        //ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
        ////std::cout << "VertexSource" << std::endl;
        ////std::cout << source.VertexSource << std::endl;
        ////std::cout << "FragmentSource:" << std::endl;
        ////std::cout << source.FragmentSource << std::endl;


        //unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        //GLCall(glUseProgram(shader));

        //GLCall(int loc = glGetUniformLocation(shader, "u_Color"));
        //ASSERT(loc != -1);

        /*
        When you have more than one of each thing (shader, vertex buffer, index buffer, etc...),
        you'll need to unbind them and rebind them before each draw call.
        */

        GLCall(glBindVertexArray(0));
        GLCall(glUseProgram(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        std::string u_Color("u_Color");

        float r = 0.8f;
        float inc = 0.025f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            shader.Bind();
            shader.SetUniform4f(u_Color, r, 0.3f, 0.8f, 1.0f);

            /*GLCall(glUseProgram(shader));
            GLCall(glUniform4f(loc, r, 0.3f, 0.8f, 1.0f));*/

            //GLCall(glBindVertexArray(vao));

            vao.Bind();
            ib.Bind();

            // bind the vertex array object
            //GLCall(glBindVertexArray(vao));

            // bind the index buffer object
            //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib));

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            if (r > 1.0f || r < 0.0f)
                inc = -inc;

            r += inc;

            //GLCall(glDrawArrays(GL_TRIANGLES, 0, 6);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }


        //GLCall(glDeleteProgram(shader);
    }

    glfwTerminate();
    return 0;
}