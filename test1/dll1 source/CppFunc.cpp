#include "pch.h"
#include "CppFunc.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <math.h>
#include "Item.h"
#include "ItemBuffer.h"
#include "ShaderProgram.h"


#define VERTEX_SHADER_SOURCE   "#version 330 core\n\
								layout(location = 0) in vec4 position;\n\
								layout(location = 1) in vec4 color;\n\
								out vec4 o_color;\n\
								void main()\n\
								{\n\
									gl_Position = position;\n\
									o_color = color;\n\
								};"

#define FRAGMENT_SHADER_SOURCE "#version 330 core\n\
								layout(location = 0) out vec4 fragment_color;\n\
								in vec4 o_color; \n\
								void main()\n\
								{\n\
									fragment_color = o_color;\n\
								};"


static GLFWwindow* window;
static int win_width;
static int win_height;
static std::vector<ItemBuffer> ibuffers;
static ShaderProgram program;

static void convertToCenter(float &x, float &y)
{
	x = x - (float)win_width / 2;
	y = (float)win_height / 2 - y;
}


JNIEXPORT jint JNICALL Java_cpp_CppFunc_initWindow(JNIEnv* env, jobject obj, jint width, jint height, jstring name)
{
	char* rtn = NULL;
	jclass   clsstring = env->FindClass("java/lang/String");
	jstring   strencode = env->NewStringUTF("GB2312");
	jmethodID   mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray   barr = (jbyteArray)env->CallObjectMethod(name, mid, strencode);
	jsize   alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0)
	{
		rtn = (char*)malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	std::string win_name(rtn);
	free(rtn);

	win_width = width;
	win_height = height;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(width, height, win_name.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() == GLEW_OK)
		std::cout << "glew init ok" << std::endl;

	program.createShaderProgram(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
	program.useProgram();

	return 0;
}

JNIEXPORT jint JNICALL Java_cpp_CppFunc_drawRectangle
    (JNIEnv* env, jobject obj, jint posx, jint posy, jint width, jint height, jint r, jint g, jint b, jfloat alpha)
{
	float ver_pos[4 * 6];
	float pos[4][2];
	pos[0][0] = posx;
	pos[0][1] = posy;
	pos[1][0] = posx + width;
	pos[1][1] = posy;
	pos[2][0] = posx + width;
	pos[2][1] = posy + height;
	pos[3][0] = posx;
	pos[3][1] = posy + height;

	for (int i = 0; i < 4; i++)
	{
		convertToCenter(pos[i][0], pos[i][1]);

		ver_pos[i * 6 + 0] = pos[i][0] * 2 / win_width;
		ver_pos[i * 6 + 1] = pos[i][1] * 2 / win_height;
		ver_pos[i * 6 + 2] = (float)r / 255;
		ver_pos[i * 6 + 3] = (float)g / 255;
		ver_pos[i * 6 + 4] = (float)b / 255;
		ver_pos[i * 6 + 5] = alpha;
	}

	unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };

	VertexBufferLayout vblayout;
	vblayout.push<float>(2);
	vblayout.push<float>(4);

	ItemBuffer ibuffer;
	ibuffer.SetBuffer(Item(24, ver_pos, 6, indices, vblayout));
	ibuffers.push_back(ibuffer);
	return 0;
}

#define PI 3.141592654
#define accuracy 360
JNIEXPORT jint JNICALL Java_cpp_CppFunc_drawCircular(JNIEnv*, jobject, jint posx, jint posy, jint radius,
	jint r, jint g, jint b, jfloat alpha)
{
	float ver_pos[(accuracy + 1) * 6];
	
	for (int i = 1; i <= accuracy; i++)
	{
		ver_pos[i * 6 + 0] = (float)radius * (float)cos(2 * PI * (i - 1) / accuracy) + (float)posx;
		ver_pos[i * 6 + 1] = (float)radius * (float)sin(2 * PI * (i - 1) / accuracy) + (float)posy;
		convertToCenter(ver_pos[i * 6 + 0], ver_pos[i * 6 + 1]);

		ver_pos[i * 6 + 0] = ver_pos[i * 6 + 0] * 2 / win_width; 
		ver_pos[i * 6 + 1] = ver_pos[i * 6 + 1] * 2 / win_height;

		//std::cout << i << ": " << ver_pos[i * 6 + 0] << " " << ver_pos[i * 6 + 1] << std::endl;

		ver_pos[i * 6 + 2] = (float)r / 255;
		ver_pos[i * 6 + 3] = (float)g / 255;
		ver_pos[i * 6 + 4] = (float)b / 255;
		ver_pos[i * 6 + 5] = alpha;
	}
	ver_pos[0] = posx;
	ver_pos[1] = posy;
	convertToCenter(ver_pos[0], ver_pos[1]);
	ver_pos[0] = ver_pos[0] * 2 / win_width;
	ver_pos[1] = ver_pos[1] * 2 / win_height;
	//std::cout << "0: " << ver_pos[0] << " " << ver_pos[1] << std::endl;
	ver_pos[2] = (float)r / 255;
	ver_pos[3] = (float)g / 255;
	ver_pos[4] = (float)b / 255;
	ver_pos[5] = alpha;


	unsigned int indices[accuracy * 3];
	for (int i = 0; i < accuracy; i++)
	{
		indices[i * 3 + 0] = 0;
		indices[i * 3 + 1] = i + 1;
		indices[i * 3 + 2] = (i + 2) == (accuracy + 1) ? 1 : (i + 2);
		//std::cout << indices[i * 3 + 0] << " " << indices[i * 3 + 1] << " " << indices[i * 3 + 2] << std::endl;
	}

	VertexBufferLayout vblayout;
	vblayout.push<float>(2);
	vblayout.push<float>(4);

	ItemBuffer ibuffer;
	ibuffer.SetBuffer(Item((accuracy + 1) * 6, ver_pos, accuracy * 3, indices, vblayout));
	ibuffers.push_back(ibuffer);
	return 0;
}

JNIEXPORT jint JNICALL Java_cpp_CppFunc_drawTriangle(JNIEnv*, jobject, jint posx, jint posy, jint v1x, jint v1y, 
	jint v2x, jint v2y, jint v3x, jint v3y, jint r, jint g, jint b, jfloat alpha) 
{
	float ver_pos[3 * 6];
	float pos[3][2];
	pos[0][0] = v1x;
	pos[0][1] = v1y;
	pos[1][0] = v2x;
	pos[1][1] = v2y;
	pos[2][0] = v3x;
	pos[2][1] = v3y;

	for (int i = 0; i < 3; i++)
	{
		convertToCenter(pos[i][0], pos[i][1]);
		ver_pos[i * 6 + 0] = pos[i][0] * 2 / win_width;
		ver_pos[i * 6 + 1] = pos[i][1] * 2 / win_height;
		ver_pos[i * 6 + 2] = (float)r / 255.0f;
		ver_pos[i * 6 + 3] = (float)g / 255.0f;
		ver_pos[i * 6 + 4] = (float)b / 255.0f;
		ver_pos[i * 6 + 5] = alpha;

		//std::cout << ver_pos[i * 6 + 2] << " " << ver_pos[i * 6 + 3] << " " << ver_pos[i * 6 + 4] << std::endl;
	}
	unsigned int indices[6] = { 0, 1, 2 };

	VertexBufferLayout vblayout;
	vblayout.push<float>(2);
	vblayout.push<float>(4);

	ItemBuffer ibuffer;
	ibuffer.SetBuffer(Item(18, ver_pos, 3, indices, vblayout));
	ibuffers.push_back(ibuffer);
	return 0;
}

JNIEXPORT jint JNICALL Java_cpp_CppFunc_drawBegin(JNIEnv*, jobject)
{
	std::cout << "item number: " << ibuffers.size() << std::endl;
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(1, 1, 1, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		for (int i = 0; i < ibuffers.size(); i++)
		{
			ibuffers[i].drawBuffer();
		}
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	program.deleteProgram();
	glfwTerminate();
	return 0;
}
