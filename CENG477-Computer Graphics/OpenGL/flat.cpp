#include "helper.h"
#include <vector>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include <cmath>
#include <iostream>

static GLFWwindow * win = NULL;
#define PI 3.14159265

GLuint idProgramShader;
GLuint idFragmentShader;
GLuint idVertexShader;
GLuint idJpegTexture;
GLuint idJpegHeightMapTexture;
GLuint idMVPMatrix;

GLint rgbTexture;
GLint heightMapTexture;

glm::vec3 u;
glm::vec3 v;
glm::vec3 w;
glm::vec3 position;
glm::vec3 gaze;
glm::mat4 view;
glm::mat4 projection;
glm::mat4 projectionView;

double angle;
double aspectRatio;
double nearPlane;
double farPlane;
double heightFactor;
double speed;

float* vertex;
float moveFactor;

int widthTexture;
int heightTexture;
int lightSourceMoveModifierX;
int lightSourceMoveModifierY;
int lightSourceMoveModifierZ;
int width, height;
int displayWidth;
int displayHeight;
int i;
int k;
int j;
	
bool fullScreen = false;


static void errorCallback(int error,
	const char * description) {
	fprintf(stderr, "Error: %s\n", description);
}

void clear() {
	glClearColor(0, 0, 0, 1);
	glClearDepth(1.0f);
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

glm::vec3 crossProduct(glm::vec3 a, glm::vec3 b) {
    glm::vec3 result(a.y * b.z - b.y * a.z, b.x * a.z - a.x * b.z, a.x * b.y - b.x * a.y);
    return result;
}

struct vertex {
	float x, y, z;

	static vertex normalizeVertex(vertex v) {
	double d;

	d = v.x*v.x + v.y*v.y + v.z*v.z;
	return{	v.x / d,
			v.y / d,
			v.z / d,
		};
	}
};

void initialize(int widthTexture, int heightTexture, GLuint &idProgramShader){
	v = glm::vec3 (0,1.0,0);
	gaze = glm::vec3 (0,0,1.0);
	u = crossProduct(v, gaze);
	w = glm::vec3 (-(gaze.x), -(gaze.y), -(gaze.z));
	position = glm::vec3 (static_cast<float>(widthTexture/2.0), static_cast<float>(widthTexture/10.0), static_cast<float>(-widthTexture/4.0));
	nearPlane = 0.1;
	farPlane = 1000;
	aspectRatio = 1;
	angle = 45.0;
	speed = 0;
	heightTexture = heightTexture;
	rgbTexture = 1;
	heightMapTexture = 0;
	idProgramShader = idProgramShader;
	idProgramShader = idProgramShader;
	vertex = new float[18*widthTexture*heightTexture];
	heightFactor = 10;
	projection = glm::perspective(angle, aspectRatio, nearPlane, farPlane);
	moveFactor = 0.0;
	lightSourceMoveModifierX=0;
	lightSourceMoveModifierY=0;
	lightSourceMoveModifierZ=0;
}


static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  
    switch(key) {
      
		case GLFW_KEY_R:
		{
			heightFactor += 0.5;
			GLuint hfLocation = glGetUniformLocation(idProgramShader, "heightFactor");
			glUniform1f(hfLocation, heightFactor);
			break;
		}


		case GLFW_KEY_F:
		{
			heightFactor -= 0.5;
			GLuint hfLocation = glGetUniformLocation(idProgramShader, "heightFactor");
			glUniform1f(hfLocation, heightFactor);
			break;
		}


		case GLFW_KEY_W:
		{
			gaze = glm::rotate(gaze, -0.05f, u);
		  	v = glm::rotate(v, -0.05f, u);
			break;
		}


		case GLFW_KEY_S:
		{
		 
			gaze = glm::rotate(gaze, 0.05f, u);
		  	v = glm::rotate(v, 0.05f, u);
			break;
		}


		case GLFW_KEY_D:
		{
			gaze = glm::rotate(gaze, -0.05f, v);
			u = glm::rotate(u, -0.05f, v);
			break;
		}


		case GLFW_KEY_A:
		{
			gaze = glm::rotate(gaze, 0.05f, v);
		  	u = glm::rotate(u, 0.05f, v);
			break;
		}


		case GLFW_KEY_Y:
		{
			speed += 0.01;
			break;
		}

		case GLFW_KEY_H:
		{
			speed -= 0.01;
			break;
		}

		case GLFW_KEY_P:
		{
			if(action == GLFW_PRESS) {
		   		if(fullScreen){

		    		fullScreen = false;
		    		glfwSetWindowMonitor( win, nullptr, 0, 0, displayWidth, displayHeight, 0 );

		  		}
		  		else{
		    		displayWidth = width;
		    		displayHeight = height;

				    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
				    fullScreen = true;
				    
				    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
				    glfwSetWindowMonitor( win, monitor, 0, 0, mode->width, mode->height, 0 );
		  		}	
			}
		
		break;
		}

		case GLFW_KEY_Q:
		{
			moveFactor += 1;
			break;
		}

		case GLFW_KEY_E:
		{
			moveFactor -= 1;
			break;
		}

		case GLFW_KEY_LEFT:
		{
			lightSourceMoveModifierX -= 5 ;
			break;
		}

		case GLFW_KEY_RIGHT:
		{
			lightSourceMoveModifierX += 5 ;
			break;
		}

		case GLFW_KEY_G:
		{
			lightSourceMoveModifierY -= 5 ;
			break;
		}

		case GLFW_KEY_T:
		{
			lightSourceMoveModifierY += 5 ;
			break;
		}

		case GLFW_KEY_DOWN:
		{
			lightSourceMoveModifierZ -= 5 ;
			break;
		}

		case GLFW_KEY_UP:
		{
			lightSourceMoveModifierZ += 5 ;
			break;
		}

		case GLFW_KEY_X:
		{
			speed = 0 ;
			break;
		}

		case GLFW_KEY_I:
		{
			initialize(widthTexture, heightTexture, idProgramShader);
			break;
		}
	}
}

int main(int argc, char * argv[]) {

  	if (argc != 3) {
    	printf("Only two texture image expected!\n");
    	exit(-1);
  	}

  	glfwSetErrorCallback(errorCallback);

  	if (!glfwInit()) {
    	exit(-1);
  	}

  	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

  	win = glfwCreateWindow(1000, 1000, "CENG477 - HW3", NULL, NULL);

  	if (!win) {
		glfwTerminate();
    	exit(-1);
  	}
  
  	glfwMakeContextCurrent(win);
  
  	GLenum err = glewInit();
  	if (err != GLEW_OK) {
    	fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    	glfwTerminate();
    	exit(-1);
  	}

	initShaders();
	glUseProgram(idProgramShader);

	auto heightMapTextureLocation = glGetUniformLocation(idProgramShader, "heightMapTexture");
	auto rgbTextureLocation = glGetUniformLocation(idProgramShader, "rgbTexture");

	initHeightMapTexture(argv[1], & widthTexture, & heightTexture);////////
	initTexture(argv[2], & widthTexture, & heightTexture);

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,idJpegHeightMapTexture);
	glUniform1i(heightMapTextureLocation, 0); // set it manually

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,idJpegTexture);
	glUniform1i(rgbTextureLocation, 1); // set it manually

	initialize(widthTexture, heightTexture, idProgramShader);

	glEnable(GL_DEPTH_TEST);

	glfwSetKeyCallback(win, keyCallback);

	unsigned int vertexBufferObject;

  	k=0;
  	for(i=0; i<heightTexture ; i++){
      	for(j=0; j<widthTexture; j++ ){
        
			vertex[k++] = j;vertex[k++] = 0;vertex[k++] = i;

			vertex[k++] = j;vertex[k++] = 0;vertex[k++] = (i+1);
			
			vertex[k++] = (j+1);vertex[k++] = 0;vertex[k++] = i;

			vertex[k++] = (j+1);vertex[k++] = 0;vertex[k++] = (i+1);

			vertex[k++] = (j+1);vertex[k++] = 0;vertex[k++] = i;

			vertex[k++] = j;vertex[k++] = 0;vertex[k++] = (i+1);
      	}
  	}

	glGenBuffers(1, &vertexBufferObject); 

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*heightTexture*widthTexture*18, vertex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); 
   
	int vertexSize = 18*widthTexture*heightTexture;

	glUniform1i(glGetUniformLocation(idProgramShader, "heightTexture"), heightTexture);
	glUniform1i(glGetUniformLocation(idProgramShader, "widthTexture"), widthTexture);
	glUniform1i(glGetUniformLocation(idProgramShader, "rgbTexture"), rgbTexture);
	glUniform1i(glGetUniformLocation(idProgramShader, "heightMapTexture"), heightMapTexture);

  

  	while (!glfwWindowShouldClose(win)) {
   
	    clear();

	    glfwGetWindowSize(win, &width, &height);
	    glViewport (0, 0, width, height);

	    position += speed * gaze;
	    
	    glm::vec3 viewCenter = glm::vec3(position + gaze * nearPlane);
	    view = glm::lookAt(position, viewCenter, v);
	    projectionView = projection * view;
	    glUniformMatrix4fv(glGetUniformLocation(idProgramShader, "MVP"), 1, GL_FALSE, &projectionView[0][0]);
	    glUniformMatrix4fv(glGetUniformLocation(idProgramShader, "MV"), 1, GL_FALSE, &view[0][0]);
	    glUniformMatrix3fv(glGetUniformLocation(idProgramShader, "cameraPosition"), 1, GL_FALSE, &position[0]);
	    glUniform1f(glGetUniformLocation(idProgramShader, "moveFactor"), moveFactor);
	    glUniform1f(glGetUniformLocation(idProgramShader, "heightFactor"), heightFactor);
	    glUniform1i(glGetUniformLocation(idProgramShader, "lightSourceMoveModifierX"), lightSourceMoveModifierX);
	    glUniform1i(glGetUniformLocation(idProgramShader, "lightSourceMoveModifierY"), lightSourceMoveModifierY);
	    glUniform1i(glGetUniformLocation(idProgramShader, "lightSourceMoveModifierZ"), lightSourceMoveModifierZ);
	    glDrawArrays(GL_TRIANGLES, 0, vertexSize);
	    glfwSwapBuffers(win);
	    glfwPollEvents();
	}

  	glfwDestroyWindow(win);
 	glfwTerminate();

  	return 0;
}