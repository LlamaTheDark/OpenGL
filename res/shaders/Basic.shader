#shader vertex
#version 330 core

layout (location = 0) in vec4 position; // 0 is the index of our attribute, position is what we're calling the input

void main() { // gets called when the vertex shader gets called
   gl_Position = position;
};


#shader fragment
#version 330 core

layout (location = 0) out vec4 color;
uniform vec4 u_Color;

void main() { // gets called when the vertex shader gets called
	color = u_Color;
};
