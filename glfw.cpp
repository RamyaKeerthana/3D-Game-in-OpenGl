#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <unistd.h>

#include <FTGL/ftgl.h>
#include <SOIL/SOIL.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include <sstream> 

#define PI 3.14159265358979323846
#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0)))
int checktarget();
GLFWwindow* window;
int nofo=8;
float q=0,w=0,e=0,a=0,s=0,d=0,z=0,x=0,c=0,X=0,Y=0,Z=2;
float av=0,fcv=0,tv=0,Tv=0,hv=0;
int i=0,j=0,k=0,l=0,tileflag=0;
float jump=0;
int R,rx[50],ry[50],tt=0;
float array[]={-10,-8,-6,-4,-2,0,2,4,6,8};
float camera_rotation_angle = 90;
int rectangle_rotation=0;
int Lifes=0,Level=1,Score=0;
int click=0;
float ax=0,by=0;


using namespace std;

struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int NumVertices;
	GLuint TextureBuffer;
	GLuint TextureID;

};

typedef struct VAO VAO;

struct tile {
	VAO *t[10][10];
};

typedef struct tile Tile;

struct obstacle {
	VAO* obs[50];
};

typedef struct obstacle obstacle;


struct GLMatrices {
	glm::mat4 projection;
	glm::mat4 model;
	glm::mat4 view;
	GLuint MatrixID;
	GLuint TexMatrixID; // For use with texture shader
} Matrices;

struct FTGLFont {
	FTFont* font;
	GLuint fontMatrixID;
	GLuint fontColorID;
} GL3Font;




GLuint programID, fontProgramID, textureProgramID;

/* Function to load Shaders - Use it as it is */
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open())
	{
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	// Link the program
	fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void quit(GLFWwindow *window)
{
	
    if(Lifes>4)		
    {
    	glfwDestroyWindow(window);
    	glfwTerminate();
	exit(EXIT_SUCCESS);
    }
    else if(checktarget()!=1)
    {
	
 q=0,w=0,e=4,a=0,s=0,d=0,z=0,x=0,c=0,X=0,Y=0,Z=2;
 av=0,fcv=0,tv=0,Tv=0,hv=0;
 i=0,j=0,k=0,l=0,tileflag=0;
 jump=0;
tt=0;

 
 camera_rotation_angle = 90;
 rectangle_rotation=0;


	Lifes=Lifes+1;
	printf("%d Lifes left\n",6-Lifes);
	
}	
	else if(checktarget()==1)
	{
	Score=Score+5;
	Level++;
	nofo=nofo+2;
	printf("You Won!!! Reached Level %d\n Score:%d\n",Level,Score);
	 q=0,w=0,e=4,a=0,s=0,d=0,z=0,x=0,c=0,X=0,Y=0,Z=2;
 av=0,fcv=0,tv=0,Tv=0,hv=0;
 i=0,j=0,k=0,l=0,tileflag=0;
 jump=0;
tt=0;

 
 camera_rotation_angle = 90;
 rectangle_rotation=0;
	}
	
	
}

glm::vec3 getRGBfromHue (int hue)
{
	float intp;
	float fracp = modff(hue/60.0, &intp);
	float x = 1.0 - abs((float)((int)intp%2)+fracp-1.0);

	if (hue < 60)
		return glm::vec3(1,x,0);
	else if (hue < 120)
		return glm::vec3(x,1,0);
	else if (hue < 180)
		return glm::vec3(0,1,x);
	else if (hue < 240)
		return glm::vec3(0,x,1);
	else if (hue < 300)
		return glm::vec3(x,0,1);
	else
		return glm::vec3(1,0,x);
}



/* Generate VAO, VBOs and return VAO handle */
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat* color_buffer_data, GLenum fill_mode=GL_FILL)
{
    struct VAO* vao = new struct VAO;
    vao->PrimitiveMode = primitive_mode;
    vao->NumVertices = numVertices;
    vao->FillMode = fill_mode;

    // Create Vertex Array Object
    // Should be done after CreateWindow and before any other GL calls
    glGenVertexArrays(1, &(vao->VertexArrayID)); // VAO
    glGenBuffers (1, &(vao->VertexBuffer)); // VBO - vertices
    glGenBuffers (1, &(vao->ColorBuffer));  // VBO - colors

    glBindVertexArray (vao->VertexArrayID); // Bind the VAO 
    glBindBuffer (GL_ARRAY_BUFFER, vao->VertexBuffer); // Bind the VBO vertices 
    glBufferData (GL_ARRAY_BUFFER, 3*numVertices*sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW); // Copy the vertices into VBO
    glVertexAttribPointer(
                          0,                  // attribute 0. Vertices
                          3,                  // size (x,y,z)
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );

    glBindBuffer (GL_ARRAY_BUFFER, vao->ColorBuffer); // Bind the VBO colors 
    glBufferData (GL_ARRAY_BUFFER, 3*numVertices*sizeof(GLfloat), color_buffer_data, GL_STATIC_DRAW);  // Copy the vertex colors
    glVertexAttribPointer(
                          1,                  // attribute 1. Color
                          3,                  // size (r,g,b)
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );

    return vao;
}

/* Generate VAO, VBOs and return VAO handle - Common Color for all vertices */
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode=GL_FILL)
{
    GLfloat* color_buffer_data = new GLfloat [3*numVertices];
    for (int i=0; i<numVertices; i++) {
        color_buffer_data [3*i] = red;
        color_buffer_data [3*i + 1] = green;
        color_buffer_data [3*i + 2] = blue;
    }

    return create3DObject(primitive_mode, numVertices, vertex_buffer_data, color_buffer_data, fill_mode);
}
struct VAO* create3DTexturedObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat* texture_buffer_data, GLuint textureID, GLenum fill_mode=GL_FILL)
{
	struct VAO* vao = new struct VAO;
	vao->PrimitiveMode = primitive_mode;
	vao->NumVertices = numVertices;
	vao->FillMode = fill_mode;
	vao->TextureID = textureID;

	// Create Vertex Array Object
	// Should be done after CreateWindow and before any other GL calls
	glGenVertexArrays(1, &(vao->VertexArrayID)); // VAO
	glGenBuffers (1, &(vao->VertexBuffer)); // VBO - vertices
	glGenBuffers (1, &(vao->TextureBuffer));  // VBO - textures

	glBindVertexArray (vao->VertexArrayID); // Bind the VAO
	glBindBuffer (GL_ARRAY_BUFFER, vao->VertexBuffer); // Bind the VBO vertices
	glBufferData (GL_ARRAY_BUFFER, 3*numVertices*sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW); // Copy the vertices into VBO
	glVertexAttribPointer(
						  0,                  // attribute 0. Vertices
						  3,                  // size (x,y,z)
						  GL_FLOAT,           // type
						  GL_FALSE,           // normalized?
						  0,                  // stride
						  (void*)0            // array buffer offset
						  );

	glBindBuffer (GL_ARRAY_BUFFER, vao->TextureBuffer); // Bind the VBO textures
	glBufferData (GL_ARRAY_BUFFER, 2*numVertices*sizeof(GLfloat), texture_buffer_data, GL_STATIC_DRAW);  // Copy the vertex colors
	glVertexAttribPointer(
						  2,                  // attribute 2. Textures
						  2,                  // size (s,t)
						  GL_FLOAT,           // type
						  GL_FALSE,           // normalized?
						  0,                  // stride
						  (void*)0            // array buffer offset
						  );

	return vao;
}


/* Render the VBOs handled by VAO */
void draw3DObject (struct VAO* vao)
{
    // Change the Fill Mode for this object
    glPolygonMode (GL_FRONT_AND_BACK, vao->FillMode);

    // Bind the VAO to use
    glBindVertexArray (vao->VertexArrayID);

    // Enable Vertex Attribute 0 - 3d Vertices
    glEnableVertexAttribArray(0);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->VertexBuffer);

    // Enable Vertex Attribute 1 - Color
    glEnableVertexAttribArray(1);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->ColorBuffer);

    // Draw the geometry !
    glDrawArrays(vao->PrimitiveMode, 0, vao->NumVertices); // Starting from vertex 0; 3 vertices total -> 1 triangle
}
void draw3DTexturedObject (struct VAO* vao)
{
	// Change the Fill Mode for this object
	glPolygonMode (GL_FRONT_AND_BACK, vao->FillMode);

	// Bind the VAO to use
	glBindVertexArray (vao->VertexArrayID);

	// Enable Vertex Attribute 0 - 3d Vertices
	glEnableVertexAttribArray(0); 
	// Bind the VBO to use
	glBindBuffer(GL_ARRAY_BUFFER, vao->VertexBuffer);

	// Bind Textures using texture units
	glBindTexture(GL_TEXTURE_2D, vao->TextureID);

	// Enable Vertex Attribute 2 - Texture
	glEnableVertexAttribArray(2); 
	// Bind the VBO to use
	glBindBuffer(GL_ARRAY_BUFFER, vao->TextureBuffer);

	// Draw the geometry !
	glDrawArrays(vao->PrimitiveMode, 0, vao->NumVertices); // Starting from vertex 0; 3 vertices total -> 1 triangle

	// Unbind Textures to be safe
	glBindTexture(GL_TEXTURE_2D, 0);
}

/* Create an OpenGL Texture from an image */
GLuint createTexture (const char* filename)
{
	GLuint TextureID;
	// Generate Texture Buffer
	glGenTextures(1, &TextureID);
	// All upcoming GL_TEXTURE_2D operations now have effect on our texture buffer
	glBindTexture(GL_TEXTURE_2D, TextureID);
	// Set our texture parameters
	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering (interpolation)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load image and create OpenGL texture
	int twidth, theight;
	unsigned char* image = SOIL_load_image(filename, &twidth, &theight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D); // Generate MipMaps to use
	SOIL_free_image_data(image); // Free the data read from file after creating opengl texture
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess it up

	return TextureID;
}


/**************************
 * Customizable functions *
 **************************/


int collisioncheck()
{
int i,j;
for(j=0;j<10;j++)
{	
	for(i=0;i<10;i++)
	{
		if(!((i==3 and j==7) or (i==0 and j==1) or (i==8 and j==9) or (i==5 and j==6) or (i==8 and j==7) or (i==6 and j==1) or (i==2 and j==3) ))
		{
		if((i%R==0 and j%(R+3)==0 and (i!=0 and j!=0)))
		{
			if(X+8==(2*(-5+i)) and Y+8==(2*(-5+j)))
			{
				if(!((0.7)*sin(rectangle_rotation*M_PI/180.0f)<0 and (0.7)*sin(rectangle_rotation*M_PI/180.0f)>-0.5) and tileflag==0)
				{
					printf("collided with block\n");
					return 1;
				}	
				else
				{
					tileflag=1;
					
				}
			
			}
			else
				tileflag=0;
			
		}
		
		}	
	}
}
for(i=0;i<8;i++)
{
	if(X+8==array[rx[i]] and Y+8==array[ry[i]])
	{
		printf("Collided with object\n");
		return 1;
	}

}
if(checktarget()==1)
{
return 1;
}

return 0;	
}

int checktarget()
{
	if(X+8==-10 and Y+8==-10)
	{
	
	return 1;
	}
	else
	return 0;
}














/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */

void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
     // Function is called first on GLFW_PRESS.

    if ( action == GLFW_PRESS or action==GLFW_REPEAT) {
        switch (key) {
            
	case GLFW_KEY_UP:
		
		if(Y+8+2!=10 and tileflag==0)
		{
			if(!((X+8==-4 and Y+8+2==4 ) or (X+8==-10 and Y+8+2==-8) or (X+8==6 and Y+8+2==8) or (X+8==0 and Y+8+2==2) or (X+8==6 and Y+8+2==4)or (X+8==2 and Y+8+2==-8) or (X+8==-6 and Y+8+2==-4)  ))
			{
				
				Y=Y+2;
				if(collisioncheck()==1 )
				{
					quit(window);
				}
			}
			else
			{
			printf("You Lost\n");
			quit(window);
			}
		}
		else
		{
			printf("You Lost\n");
			quit(window);
		}

			break;	
	case GLFW_KEY_DOWN:
		if(Y+8-2!=-12 and tileflag==0 )
		{
			if(!((X+8==-4 and Y+8-2==4 ) or (X+8==-10 and Y+8-2==-8) or (X+8==6 and Y+8-2==8) or (X+8==0 and Y+8-2==2)or (X+8==6 and Y+8-2==4) or (X+8==2 and Y+8-2==-8) or  (X+8==-6 and Y+8-2==-4)))
			{
				
				Y=Y-2;
				if(collisioncheck()==1)
				{
					quit(window);
				}
			}
			else
			{
			printf("You Lost\n");
			quit(window);
			}
		}
		else
		{
			printf("You Lost\n");
			quit(window);
		}

	
			break;
		
	case GLFW_KEY_RIGHT:
		if(X+8+2!=10 and tileflag==0)
		{
			if(!((X+8+2==-4 and Y+8==4 ) or (X+8+2==-10 and Y+8==-8) or (X+8+2==6 and Y+8==8) or (X+8+2==0 and Y+8==2) or (X+8+2==6 and Y+8==4)or (X+8+2==2 and Y+8==-8)or (X+8+2==-6 and Y+8==-4)))
			{
				
				X=X+2;
				if(collisioncheck()==1 )
				{
					quit(window);
				}
			}
			else
			{
			printf("You Lost\n");
			quit(window);
			}
		}
		else
		{
			printf("You Lost\n");
			quit(window);
		}

			
			break;
	case GLFW_KEY_LEFT:
		if(X+8-2!=-12 and tileflag==0)
		{
			if(!((X+8-2==-4 and Y+8==4 ) or (X+8-2==-10 and Y+8==-8) or (X+8-2==6 and Y+8==8) or (X+8-2==0 and Y+8==2)or (X+8-2==6 and Y+8==4)or (X+8-2==2 and Y+8==-8)or (X+8-2==-6 and Y+8==-4)))
			{
				
				X=X-2;
				if(collisioncheck()==1 )
				{
					quit(window);
				}
			}
			else
			{
			printf("You Lost\n");
			quit(window);
			}
		}
		else
		{
			printf("You Lost\n");
			quit(window);
		}

		
			break;
	case '7':
		printf("q=%f\n",q);
	        q=q-1;
		break;


  	case '8':
		w=w-1;
		printf("w=%f\nwr",w);
	        break;

	case '9':
		e=e-1;
		printf("e=%f\n",e);
	        break;

	case '4':
		a=a-1;
		printf("a=%f\n",a);
 	        break;

	case '5':
		s=s-1;
		printf("s=%f\n",s);
	        break;

   	case '6':
		d=d-1;
		printf("d=%f\n",d);
                break;

	case '1':
		z=z-1;
		printf("z=%f\n",z);
	      break;

 	case '2':
		x=x-1;
		printf("x=%f\n",x);
	        break;

	case '3':
		c=c-1;
		printf("c=%f\n",c);
		break;

	case 'P':
		X=0,Y=0;
		break;

	case ' ':
		q=0,w=0,e=0,a=0,s=0,d=0,z=0,x=0,c=0;
		av=0,fcv=0,tv=0,Tv=0,hv=0;
		break;

 	case 'Q':
		q=q+1;
		printf("q=%f\n",q);
		break;
       

	case 'W':
			w=w+1;	
		printf("w=%f\n",w);
		break;
      
	case 'E':
		e=e+1;
		printf("e=%f\n",e);
		break;
      
	case 'A':
		a=a+1;
		printf("a=%f\n",a);
		break;
        
	case 'S':
		s=s+1;
		printf("s=%f\n",s);
		break;
       
	case 'D':
		d=d+1;
		printf("d=%f\n",d);
		break;
     
	case 'Z':
		z=z+1;
		printf("z=%f\n",z);
		break;
       
	case 'X':
		x=x+1;
		printf("x=%f\n",x);
		break;
       
	case 'C':
		c=c+1;
		printf("c=%f\n",c);
		break;
	
//cameraviews

	case GLFW_KEY_F1://adventurer view
		av=1,fcv=0,tv=0,Tv=0,hv=0;
		printf("adventurer view\n");
		break;

		

	case GLFW_KEY_F2://Follow Cam view
		av=0,fcv=1,tv=0,Tv=0,hv=0;
		printf("Follow Cam view\n");
		break;

	case GLFW_KEY_F3://Tower View
		av=0,fcv=0,tv=1,Tv=0,hv=0;
		printf("Tower View\n");
		break;

	case GLFW_KEY_F4://Top View
		av=0,fcv=0,tv=0,Tv=1,hv=0;
		printf("Top View\n");
		break;

	case GLFW_KEY_F5://Helicopter View
		av=0,fcv=0,tv=0,Tv=0,hv=1;
		printf("Helicopter View\n");
		break;


	case 'I'://front jump
		if(Y+8+2+2<10)
		{
			if(!((X+8==-4 and Y+8+2+2==4 ) or (X+8==-10 and Y+8+2+2==-8) or (X+8==6 and Y+8+2+2==8) or (X+8==0 and Y+8+2+2==2) or (X+8==6 and Y+8+2+2==4)or (X+8==2 and Y+8+2+2==-8) or (X+8==-6 and Y+8+2+2==-4)  ))
			{			
				i=1;	
				printf("jump i\n");			
			}
			else 
			{
				printf("you lost\n");
				quit(window);
			}
		}
		else 
		{
			printf("you lost\n");
			quit(window);
		}
		
		break;


	case 'K'://back jump
		if(Y+8-2-2>-12)
		{
			if(!((X+8==-4 and Y+8-2-2==4 ) or (X+8==-10 and Y+8-2-2==-8) or (X+8==6 and Y+8-2-2==8) or (X+8==0 and Y+8-2-2==2)or (X+8==6 and Y+8-2-2==4) or (X+8==2 and Y+8-2-2==-8) or  (X+8==-6 and Y+8-2-2==-4)))
			{
				k=1;	
				printf("jump k\n");			
			}
			else 
			{
				printf("you lost\n");
				quit(window);
			}
		}
		else 
		{
			printf("you lost\n");
			quit(window);
		}
		break;

	case 'J'://left jump
		
		if(X+8-2-2>-12)
		{
			if(!((X+8-2-2==-4 and Y+8==4 ) or (X+8-2-2==-10 and Y+8==-8) or (X+8-2-2==6 and Y+8==8) or (X+8-2-2==0 and Y+8==2)or (X+8-2-2==6 and Y+8==4)or (X+8-2-2==2 and Y+8==-8)or (X+8-2-2==-6 and Y+8==-4)))
			{
				j=1;
				printf("jump j\n");
			}
			else 
			{
				printf("you lost\n");
				quit(window);
			}
			
		}
		else 
		{
			printf("you lost\n");
			quit(window);
		}
		break;

	case 'L'://right jump
		if(X+8+2+2<10)
		{
			if(!((X+8+2+2==-4 and Y+8==4 ) or (X+8+2+2==-10 and Y+8==-8) or (X+8+2+2==6 and Y+8==8) or (X+8+2+2==0 and Y+8==2) or (X+8+2+2==6 and Y+8==4)or (X+8+2+2==2 and Y+8==-8)or (X+8+2+2==-6 and Y+8==-4)))
			{
				l=1;
				printf("jump l\n");
			}
			else 
			{
				printf("you lost\n");
				quit(window);
			}
			
		}
		else 
		{
			printf("you lost\n");
			quit(window);
		}
		break;


	
	default:
            break;
        }
    }
    else if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                quit(window);
                break;
            default:
                break;
        }
    }
   
}



void scrollcallback(GLFWwindow* window,double xoffset,double yoffset)
{
	
	if(yoffset>0)
	{
		d=d+2;
		e=e+2;
	}
	else
	{
		d=d-2;
		e=e-2;
	}
}


/* Executed when a mouse button is pressed/released */
void mouseButton (GLFWwindow* window, int button, int action, int mods)
{
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (action == GLFW_PRESS or action == GLFW_REPEAT)
	    {
		click=1;
	    }
	    else if(action == GLFW_RELEASE)
		click=0;
            break;
        
        default:
            break;
    }
}







void cursorcallback(GLFWwindow* window,double xoffset,double yoffset)
{
	
	if (click==1 and hv==1)
	{
		if(xoffset>ax and yoffset>by)//q1
		{
			z=z+4;
		}
		else if(xoffset<ax and yoffset<by)//q3
		{
			z=z-4;
		}
		else if(xoffset<ax and yoffset>by)//q2
		{
			x=x+4;
		}
		else if(xoffset>ax and yoffset<by)//q4
		{
			x=x-4;
		}
		ax=xoffset;
		by=yoffset;
	}
	else
	{
		ax=0,by=0;
	}
	
}


/* Executed for character input (like in text boxes) */
void keyboardChar (GLFWwindow* window, unsigned int key)
{
	
}



/* Executed when window is resized to 'width' and 'height' */
/* Modify the bounds of the screen here in glm::ortho or Field of View in glm::Perspective */
void reshapeWindow (GLFWwindow* window, int width, int height)
{
    int fbwidth=width, fbheight=height;
    /* With Retina display on Mac OS X, GLFW's FramebufferSize
     is different from WindowSize */
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);

	GLfloat fov = 90.0f;

	// sets the viewport of openGL renderer
	glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);

	// set the projection matrix as perspective
	/* glMatrixMode (GL_PROJECTION);
	   glLoadIdentity ();
	   gluPerspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1, 500.0); */
	// Store the projection matrix in a variable for future use
    // Perspective projection for 3D views
     Matrices.projection = glm::perspective (fov, (GLfloat) (fbwidth) / (GLfloat) fbwidth, 0.1f, 500.0f);

    // Ortho projection for 2D views
    //Matrices.projection = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, 0.1f, 500.0f);
}

VAO  *base,*player,*tar ,*rectangle;
Tile tile;
obstacle o;

// Creates the rectangle object used in this sample code
void createRectangle (GLuint textureID)
{
	// GL3 accepts only Triangles. Quads are not supported
	static const GLfloat vertex_buffer_data [] = {
-100,-100,-3.5,
100,-100,-3.5,
100,100,-3.5,

100,100,-3.5,
-100,100,-3.5,
-100,-100,-3.5,

	-100,90,-3.5,
90,90,-3.5,
90,-100,-3.5,
90,-100,-3.5,
-100,90,-3.5,
-100,-100,-3.5,
90,-100,-3.5,

	
		-1.2,-1,0, // vertex 1
		1.2,-1,0, // vertex 2
		1.2, 1,0, // vertex 3

		1.2, 1,0, // vertex 3
		-1.2, 1,0, // vertex 4
		-1.2,-1,0  // vertex 1
	};

	static const GLfloat color_buffer_data [] = {
		1,0,0, // color 1
		0,0,1, // color 2
		0,1,0, // color 3

		0,1,0, // color 3
		0.3,0.3,0.3, // color 4
		1,0,0  // color 1
	};

	// Texture coordinates start with (0,0) at top left of the image to (1,1) at bot right
	static const GLfloat texture_buffer_data [] = {
		0,1, // TexCoord 1 - bot left
		1,1, // TexCoord 2 - bot right
		1,0, // TexCoord 3 - top right

		1,0, // TexCoord 3 - top right
		0,0, // TexCoord 4 - top left
		0,1  // TexCoord 1 - bot left
	};

	// create3DTexturedObject creates and returns a handle to a VAO that can be used later
	rectangle = create3DTexturedObject(GL_TRIANGLES, 6, vertex_buffer_data, texture_buffer_data, textureID, GL_FILL);
}


void createcone()
{

GLfloat* vertex_buffer_data=new GLfloat[6*720];
int i;
for(i=0;i<720;i++)
{
vertex_buffer_data[6*i]=(1 *cos(DEG2RAD(i)));
vertex_buffer_data[6*i+1]=(1 *sin(DEG2RAD(i)));
vertex_buffer_data[6*i+2]=0;
vertex_buffer_data[6*i+3]=0;
vertex_buffer_data[6*i+4]=0;
vertex_buffer_data[6*i+5]=1.5;
}
GLfloat color_buffer_data[6*720];

for(i=0;i<360;i++)
{

color_buffer_data[12*i]=1;
color_buffer_data[12*i+1]=1;
color_buffer_data[12*i+2]=1;

color_buffer_data[12*i+3]=0;
color_buffer_data[12*i+4]=0;
color_buffer_data[12*i+5]=0;

color_buffer_data[12*i+6]=1;
color_buffer_data[12*i+7]=1;
color_buffer_data[12*i+8]=1;

color_buffer_data[12*i+9]=1;
color_buffer_data[12*i+10]=0;
color_buffer_data[12*i+11]=0;
}


for(i=0;i<50;i++)
{
 o.obs[i]=create3DObject(GL_LINES,2*720,vertex_buffer_data,color_buffer_data,GL_FILL);
}
}












void createtile ()
{
  // GL3 accepts only Triangles. Quads are not supported
  static const GLfloat vertex_buffer_data [] = {
//front
-1,1,0,
1,1,0,
1,-1,0,

-1,1,0,
-1,-1,0,
1,-1,0,

//back

-1,1,-3,
1,1,-3,
1,-1,-3,

-1,1,-3,
-1,-1,-3,
1,-1,-3,

//right
1,1,0,
1,1,-3,
1,-1,-3,


1,1,0,
1,-1,0,
1,-1,-3,

//left
-1,1,0,
-1,1,-3,
-1,-1,-3,

-1,1,0,
-1,-1,0,
-1,-1,-3,

//top
-1,1,0,
-1,1,-3,
1,1,-3,

-1,1,0,
1,1,-3,
1,1,0,

//bottom
-1,-1,0,
-1,-1,-3,
1,-1,-3,

-1,-1,0,
1,-1,-3,
1,-1,0,





  };




static const GLfloat vertex_buffer_data1 [] = {
//front
-1*0.5,1*0.5,0,
1*0.5,1*0.5,0,
1*0.5,-1*0.5,0,

-1*0.5,1*0.5,0,
-1*0.5,-1*0.5,0,
1*0.5,-1*0.5,0,

//back

-1*0.5,1*0.5,-2,
1*0.5,1*0.5,-2,
1*0.5,-1*0.5,-2,

-1*0.5,1*0.5,-2,
-1*0.5,-1*0.5,-2,
1*0.5,-1*0.5,-2,

//right
1*0.5,1*0.5,0,
1*0.5,1*0.5,-2,
1*0.5,-1*0.5,-2,


1*0.5,1*0.5,0,
1*0.5,-1*0.5,0,
1*0.5,-1*0.5,-2,

//left
-1*0.5,1*0.5,0,
-1*0.5,1*0.5,-2,
-1*0.5,-1*0.5,-2,

-1*0.5,1*0.5,0,
-1*0.5,-1*0.5,0,
-1*0.5,-1*0.5,-2,

//top
-1*0.5,1*0.5,0,
-1*0.5,1*0.5,-2,
1*0.5,1*0.5,-2,

-1*0.5,1*0.5,0,
1*0.5,1*0.5,-2,
1*0.5,1*0.5,0,

//bottom
-1*0.5,-1*0.5,0,
-1*0.5,-1*0.5,-2,
1*0.5,-1*0.5,-2,

-1*0.5,-1*0.5,0,
1*0.5,-1*0.5,-2,
1*0.5,-1*0.5,0,





  };

  static const GLfloat color_buffer_data [] = {



0,0,1,1,1,2,1,1,0,
0,0,1,1,1,2,1,1,0,

0,1,0,1,1,2,1,1,0,
0,1,0,1,1,2,1,1,0,

0,1,1,1,0,2,1,1,0,
0,1,1,1,0,2,1,1,0,

0,1,1,1,0,2,1,1,0,
0,1,1,1,0,2,1,1,0,

0,1,1,2,0,1,1,1,0,
0,1,1,2,0,1,1,1,0,

0,1,1,2,0,1,1,1,0,
0,1,1,2,0,1,1,1,0,


  };

static const GLfloat color_buffer_data1 [] = {

0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4
0,1,0, // color 3
    0.3,0.3,0.3, // color 4

  };

static const GLfloat color_buffer_data2 [3*36]={};



  // create3DObject creates and returns a handle to a VAO that can be used later
int i,j;
for(i=0;i<10;i++)
{
	for(j=0;j<10;j++)
	{
		tile.t[i][j] = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color_buffer_data, GL_FILL);
	}
}
player = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data1, color_buffer_data1, GL_FILL);
tar = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data1, color_buffer_data2, GL_FILL);

}

void createrectangle ()
{
  // GL3 accepts only Triangles. Quads are not supported
  static const GLfloat vertex_buffer_data [] = {
-11,9,-3.5,
9,9,-3.5,
9,-11,-3.5,
9,-11,-3.5,
-11,9,-3.5,
-11,-11,-3.5,
9,-11,-3.5,




    -1.2,-1,0, // vertex 1
    1.2,-1,0, // vertex 2
    1.2, 1,0, // vertex 3

    1.2, 1,0, // vertex 3
    -1.2, 1,0, // vertex 4
    -1.2,-1,0  // vertex 1
  };

  static const GLfloat color_buffer_data [] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  base = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
}



/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw ()
{



  // clear the color and depth in the frame buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // use the loaded shader program
  // Don't change unless you know what you are doing
  glUseProgram (programID);

// Eye - Location of camera. Don't change unless you are sure!!
	glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f)+q, 0+w, 5*sin(camera_rotation_angle*M_PI/180.0f)+e );
// Target - Where is the camera looking at.  Don't change unless you are sure!!
	glm::vec3 target (0+a, 0+s, 0+d);
// Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
	glm::vec3 up (0+z, 1+x, 0+c);

if(av==0 and fcv==0 and tv==0 and Tv==0 and hv==0)
{
	glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f)+q, 0+w, 5*sin(camera_rotation_angle*M_PI/180.0f)+e );
	glm::vec3 target (0+a, 0+s, 0+d);
	glm::vec3 up (0+z, 1+x, 0+c);

}
else if(av==1)//adventure view
{
	if(i==0 and j==0 and k==0 and l==0)
	{
	glm::vec3 eye1 ( X+10,Y+10 ,3 );
	glm::vec3 target1 (X+8, Y+8, Z);
	glm::vec3 up1 (1, 1+x, 0+13);
	eye=eye1,target=target1,up=up1;
	}
}
else if(fcv==1)//follow cam view
{
	if(i==0 and j==0 and k==0 and l==0)
	{
	glm::vec3 eye2 ( X+8,Y+8 ,4 );
	glm::vec3 target2 (X-10, Y-10, Z);
	glm::vec3 up2 (z, 1+x, 0+13);
	eye=eye2,target=target2,up=up2;
	}

}

else if(tv==1)//tower view
{
	
	//q=0,w=0,e=0,a=0,s=0,d=0,z=0,x=0,c=0;
	//a=580,z=222,c=187,d=-120,w=-7,q=-16,s=57;
	//z=2,q=6,d=3,s=3,a=5,c=5,x=4;
	glm::vec3 eye3 (10,10,4.5);
	glm::vec3 target3 (8,8,2);
	glm::vec3 up3 (0+z, 1+x, 0+6);
	eye=eye3,target=target3,up=up3;

}

else if(Tv==1)//top view
{
	q=0,w=0,e=4,a=0,s=0,d=0,z=0,x=0,c=0;
	glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f)+q, 0+w, 5*sin(camera_rotation_angle*M_PI/180.0f)+e );
	glm::vec3 target (0+a, 0+s, 0+d);
	glm::vec3 up (0+z, 1+x, 0+c);

}

else if(hv==1)//helicopter view
{
	
	//glm::vec3 eye5 (4,4,10);
//	glm::vec3 target5 (8, 8, 8);
//	glm::vec3 up5 (0+z, 1+x, 0+c);
	//q=0,w=0,e=4,d=0,z=0,x=0,c=0;
	//a=0,s=0;
	
	glm::vec3 eye5 ( 5*cos(camera_rotation_angle*M_PI/180.0f)+q, 0+w, (5*sin(camera_rotation_angle*M_PI/180.0f))+4+e );
	glm::vec3 target5 (0+a, 0+s, 0+d);
	glm::vec3 up5 (0+z, 1+x, 0+c);

	eye=eye5,target=target5,up=up5;


}





  // Compute Camera matrix (view)
   Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
  //  Don't change unless you are sure!!
  //Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

  // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
  //  Don't change unless you are sure!!
  glm::mat4 VP = Matrices.projection * Matrices.view;

  // Send our transformation to the currently bound shader, in the "MVP" uniform
  // For each model you render, since the MVP will be different (at least the M part)
  //  Don't change unless you are sure!!
  glm::mat4 MVP;	// MVP = Projection * View * Model

int p,q;

if(rectangle_rotation%360==0)
{
R=abs(rand()%7)+2;

for(p=0;p<nofo;p++)
{
	rx[p]=rand()%9;
	ry[p]=rand()%9;
}
tileflag=0;
}

glm::mat4 translatetile,translateplayer,translatecone;
glm::mat4 rotatetile;
for(q=0;q<10;q++)
{

	for(p=0;p<10;p++)
	{
		if(!((p==3 and q==7) or (p==0 and q==1) or (p==8 and q==9) or (p==5 and q==6) or (p==8 and q==7) or (p==6 and q==1) or (p==2 and q==3) ))
		{
			Matrices.model = glm::mat4(1.0f);
		        translatetile = glm::translate (glm::vec3(2*(-5+p),2*(-5+q), 0));
			if((p%R==0 and q%(R+3)==0 and (p!=0 and q!=0)))
			{
				translatetile = glm::translate (glm::vec3(2*(-5+p),2*(-5+q), (0.7)*sin(rectangle_rotation*M_PI/180.0f)));
				rotatetile =  glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1)); 
				Matrices.model *= (translatetile*rotatetile);
			}
			else
				 Matrices.model *= (translatetile);
			MVP = VP * Matrices.model;
			glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
			draw3DObject(tile.t[q][p]);
		}
	}
}



q=0;

for(p=0;p<nofo;p++)
{
	Matrices.model = glm::mat4(1.0f);
	translatecone = glm::translate (glm::vec3(array[rx[p]],array[ry[p]], 0));
 //       translatecone = glm::translate (glm::vec3(-8,-8, 0));
	glm :: mat4 rotatecone =  glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,1,7)); 
	Matrices.model *= (translatecone * rotatecone);
	MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(o.obs[p]);
}




/*Matrices.model = glm::mat4(1.0f);
MVP = VP * Matrices.model;
glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
draw3DObject(base);*/


Matrices.model = glm::mat4(1.0f);

if(i==1)
{
	if(jump<4)
	{
		Y=Y+0.5;
		Z=Z+1;
		jump++;
	}
	else if(jump<8)
	{
		Y=Y+0.5;
		Z=Z-1;
		jump++;
	}
	else 
	{
		jump=0;
		i=0;
		if(collisioncheck()==1)
		{
			quit(window);
		}
	}
		
}
else if(k==1)
{
	if(jump<4)
	{
		Y=Y-0.5;
		Z=Z+1;
		jump++;
	}
	else if(jump<8)
	{
		Y=Y-0.5;
		Z=Z-1;
		jump++;
	}
	else 
	{
		jump=0;
		k=0;
		if(collisioncheck()==1)
		{
			quit(window);
		}
	}
		
}
else if(l==1)
{
	if(jump<4)
	{
		X=X+0.5;
		Z=Z+1;
		jump++;
	}
	else if(jump<8)
	{
		X=X+0.5;
		Z=Z-1;
		jump++;
	}
	else 
	{
		jump=0;
		l=0;
		if(collisioncheck()==1)
		{
			quit(window);
		}
	}
		
}
else if(j==1)
{
	if(jump<4)
	{
		X=X-0.5;
		Z=Z+1;
		jump++;
	}
	else if(jump<8)
	{
		X=X-0.5;
		Z=Z-1;
		jump++;
	}
	else 
	{
		jump=0;
		j=0;
		if(collisioncheck()==1)
		{
			quit(window);
		}
	}
		
}
collisioncheck();
translateplayer = glm::translate (glm::vec3(X+8,Y+8, Z+(tileflag*(0.7)*sin(rectangle_rotation*M_PI/180.0f))));
collisioncheck();
//printf("%d",tileflag);
glm::mat4 Scale1 = glm::scale(glm::mat4(1.0f), glm::vec3(1));
Matrices.model *= (  translateplayer * Scale1 );
MVP = VP * Matrices.model;
glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
draw3DObject(player);
		
Matrices.model = glm::mat4(1.0f);

translateplayer= glm::translate (glm::vec3(-10,-10, 2));
glm::mat4 Scale2 = glm::scale(glm::mat4(1.0f), glm::vec3(1));
Matrices.model *= (  translateplayer * Scale2 );
MVP = VP * Matrices.model;
glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
draw3DObject(tar);
		




rectangle_rotation=rectangle_rotation+1;  




// Render with texture shaders now
	glUseProgram(textureProgramID);

	// Pop matrix to undo transformations till last push matrix instead of recomputing model matrix
	// glPopMatrix ();
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 rotatetex =  glm::rotate((float)(5*M_PI/180.0f), glm::vec3(1,0,0)); 
	Matrices.model *= (rotatetex );
	MVP = VP * Matrices.model;

	// Copy MVP to texture shaders
	glUniformMatrix4fv(Matrices.TexMatrixID, 1, GL_FALSE, &MVP[0][0]);

	// Set the texture sampler to access Texture0 memory
	glUniform1i(glGetUniformLocation(textureProgramID, "texSampler"), 0);

	// draw3DObject draws the VAO given to it using current MVP matrix
	draw3DTexturedObject(rectangle);

	// Increment angles
	float increments = 1;

	// Render font on screen
	static int fontScale = 0;
	
	glm::vec3 fontColor = getRGBfromHue (fontScale);



	// Use font Shaders for next part of code
	glUseProgram(fontProgramID);
	Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

	// Transform the text
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translateText = glm::translate(glm::vec3(-2.5,4,0));
	
	Matrices.model *= (translateText );
	MVP = Matrices.projection * Matrices.view * Matrices.model;
	// send font's MVP and font color to fond shaders
	glUniformMatrix4fv(GL3Font.fontMatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniform3fv(GL3Font.fontColorID, 1, &fontColor[0]);

	// Render font
	char sc[10];
	sprintf(sc, "%d", Score);
	GL3Font.font->Render(sc);
	
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translateText1 = glm::translate(glm::vec3(-4.5,4,0));
	
	Matrices.model *= (translateText1 );
	MVP = Matrices.projection * Matrices.view * Matrices.model;
	// send font's MVP and font color to fond shaders
	glUniformMatrix4fv(GL3Font.fontMatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniform3fv(GL3Font.fontColorID, 1, &fontColor[0]);
	GL3Font.font->Render("Score: ");
	

	

	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translateText2 = glm::translate(glm::vec3(1,4,0));
	
	Matrices.model *= (translateText2 );
	MVP = Matrices.projection * Matrices.view * Matrices.model;
	// send font's MVP and font color to fond shaders
	glUniformMatrix4fv(GL3Font.fontMatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniform3fv(GL3Font.fontColorID, 1, &fontColor[0]);

	char le[10];
	sprintf(le, "%d", Level);
	GL3Font.font->Render(le);


	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translateText21 = glm::translate(glm::vec3(-1,4,0));
	
	Matrices.model *= (translateText21 );
	MVP = Matrices.projection * Matrices.view * Matrices.model;
	// send font's MVP and font color to fond shaders
	glUniformMatrix4fv(GL3Font.fontMatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniform3fv(GL3Font.fontColorID, 1, &fontColor[0]);	
	GL3Font.font->Render("Level: ");



//	GL3Font.font->Render("Level: ");

	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translateText3 = glm::translate(glm::vec3(4,4,0));
	
	Matrices.model *= (translateText3 );
	MVP = Matrices.projection * Matrices.view * Matrices.model;
	// send font's MVP and font color to fond shaders
	glUniformMatrix4fv(GL3Font.fontMatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniform3fv(GL3Font.fontColorID, 1, &fontColor[0]);


	int Life=6-Lifes;
	char li[10];
	sprintf(li, "%d", Life);
	GL3Font.font->Render(li);

	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translateText31 = glm::translate(glm::vec3(2,4,0));
	
	Matrices.model *= (translateText31);
	MVP = Matrices.projection * Matrices.view * Matrices.model;
	// send font's MVP and font color to fond shaders
	glUniformMatrix4fv(GL3Font.fontMatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniform3fv(GL3Font.fontColorID, 1, &fontColor[0]);
	

	GL3Font.font->Render("Lifes: ");



	// font size and color changes
	//fontScale = (fontScale + 1) % 360;





}

/* Initialise glfw window, I/O callbacks and the renderer to use */
/* Nothing to Edit here */
GLFWwindow* initGLFW (int width, int height)
{
    GLFWwindow* window; // window desciptor/handle

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Sample OpenGL 3.3 Application", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval( 1 );

    /* --- register callbacks with GLFW --- */

    /* Register function to handle window resizes */
    /* With Retina display on Mac OS X GLFW's FramebufferSize
     is different from WindowSize */
    glfwSetFramebufferSizeCallback(window, reshapeWindow);
    glfwSetWindowSizeCallback(window, reshapeWindow);

    /* Register function to handle window close */
    glfwSetWindowCloseCallback(window, quit);

    /* Register function to handle keyboard input */
    glfwSetKeyCallback(window, keyboard);      // general keyboard input
    glfwSetCharCallback(window, keyboardChar);  // simpler specific character handling

    /* Register function to handle mouse click */
    glfwSetMouseButtonCallback(window, mouseButton);  // mouse button clicks


	glfwSetScrollCallback(window,scrollcallback);
	glfwSetCursorPosCallback(window,cursorcallback);	

			

    return window;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL (GLFWwindow* window, int width, int height)
{
	glActiveTexture(GL_TEXTURE0);
	GLuint textureID = createTexture("images (4).jpg");
	if(textureID == 0 )
	cout << "SOIL loading error: '" << SOIL_last_result() << "'" << endl;
	textureProgramID = LoadShaders( "TextureRender.vert", "TextureRender.frag" );
Matrices.TexMatrixID = glGetUniformLocation(textureProgramID, "MVP");


    /* Objects should be created before any other gl function and shaders */
	// Create the models
	createtile (); 
	createrectangle (); 
	createcone();
	createRectangle (textureID);
	
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

	
	reshapeWindow (window, width, height);

    // Background color of the scene
	glClearColor (0.3f, 0.3f, 0.3f, 0.0f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

   // Initialise FTGL stuff
	const char* fontfile = "arial.ttf";
	GL3Font.font = new FTExtrudeFont(fontfile); // 3D extrude style rendering

	if(GL3Font.font->Error())
	{
		cout << "Error: Could not load font `" << fontfile << "'" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Create and compile our GLSL program from the font shaders
	fontProgramID = LoadShaders( "fontrender.vert", "fontrender.frag" );
	GLint fontVertexCoordAttrib, fontVertexNormalAttrib, fontVertexOffsetUniform;
	fontVertexCoordAttrib = glGetAttribLocation(fontProgramID, "vertexPosition");
	fontVertexNormalAttrib = glGetAttribLocation(fontProgramID, "vertexNormal");
	fontVertexOffsetUniform = glGetUniformLocation(fontProgramID, "pen");
	GL3Font.fontMatrixID = glGetUniformLocation(fontProgramID, "MVP");
	GL3Font.fontColorID = glGetUniformLocation(fontProgramID, "fontColor");

	GL3Font.font->ShaderLocations(fontVertexCoordAttrib, fontVertexNormalAttrib, fontVertexOffsetUniform);
	GL3Font.font->FaceSize(1);
	GL3Font.font->Depth(0);
	GL3Font.font->Outset(0, 0);
	GL3Font.font->CharMap(ft_encoding_unicode);

	cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
	cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
	cout << "VERSION: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

}

int main (int argc, char** argv)
{
	
     int width = 600;
	int height = 600;

    GLFWwindow* window = initGLFW(width, height);
	initGL (window, width, height);

    double last_update_time = glfwGetTime(), current_time;

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {

        // OpenGL Draw commands
        draw();

        // Swap Frame Buffer in double buffering
        glfwSwapBuffers(window);

        // Poll for Keyboard and mouse events
        glfwPollEvents();

        // Control based on time (Time based transformation like 5 degrees rotation every 0.5s)
        current_time = glfwGetTime(); // Time in seconds
        if ((current_time - last_update_time) >= 0.5) { // atleast 0.5s elapsed since last frame
            // do something every 0.5 seconds ..
            last_update_time = current_time;
        }
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
