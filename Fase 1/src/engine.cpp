#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "./tinyxml/tinyxml.h"
#include "./headers/point.hpp"

using namespace std;

vector<Point> points;

int w_width = 800, w_height = 800;           // valores do tamanho da janela
float pos_x = 5.0, pos_y = 5.0, pos_z = 5.0; // valores da posição da câmera
float look_x = 0, look_y = 0, look_z = 0;    // valores da orientação da câmera
float up_x = 0, up_y = 1.0, up_z = 0;        // valores do eixo vertical da câmera
float fov = 45, near = 1, far = 1000;        // valores da perspetiva do glut 

int mode = GL_LINE, face = GL_FRONT_AND_BACK;
float alfa = M_PI / 9, beta2 = M_PI / 9, cradius = 7.0f;
int dxz = 1, dy = 1;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(fov, ratio, near, far);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

	switch(c) {
		case '+': cradius -= 1; break;
		case '-': cradius += 1; break;
		case 'w': look_x += 0.1; break;
		case 's': look_y -= 0.1; break;
		case 'a': look_z += 0.1; break;
		case 'd': look_z -= 0.1; break;
		case 'j': look_y += 0.1; break;
		case 'k': look_y -= 0.1; break;
		case 'f': mode = GL_FILL; break;
		case 'l': mode = GL_LINE; break;
		case 'p': mode = GL_POINT; break;
		case 'b': face = GL_BACK; break;
		case 'n': face = GL_FRONT; break;
		case 'm': face = GL_FRONT_AND_BACK; break;
		default: break;
	}
	glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here
	switch(key) {
		case GLUT_KEY_UP: 
			if (beta2 * (dy+1) < M_PI / 2 && beta2 * (dy+1) > -M_PI / 2 ) 
				dy += 1; 
			break;
		case GLUT_KEY_DOWN: 
			if (beta2 * (dy-1) < M_PI / 2 && beta2 * (dy-1) > -M_PI / 2 ) 
				dy -= 1;
			break;
		case GLUT_KEY_LEFT: dxz += 1; break;
		case GLUT_KEY_RIGHT: dxz -= 1; break;
		default: break;
	}
	glutPostRedisplay();
}

void draw_triangles(){
        
    for (vector<Point>::iterator i = points.begin(); i != points.end(); i += 3) {
        Point p1 = *i;
        Point p2 = *(i + 1);
        Point p3 = *(i + 2);

        glColor3f(1,1,1);
        glBegin(GL_TRIANGLES);
        glVertex3f(p1.getX(),p1.getY(),p1.getZ());
        glVertex3f(p2.getX(),p2.getY(),p2.getZ());
        glVertex3f(p3.getX(),p3.getY(),p3.getZ());
        glEnd();
    }
}

void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pos_x = cradius * cos(beta2 * dy) * sin(alfa * dxz);
	pos_y = cradius * sin(beta2 * dy); 
	pos_z = cradius * cos(beta2 * dy) * cos(alfa * dxz);

	// set the camera
	glLoadIdentity();
	gluLookAt(pos_x,pos_y,pos_z, 
		      look_x,look_y,look_z,
			  up_x,up_y,up_z);

	glPolygonMode(GL_FRONT_AND_BACK, mode);

	//desenhar os eixos
	glBegin(GL_LINES);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

	draw_triangles();
	glutSwapBuffers();
}

void read_3D_file(string filename) {
	ifstream ficheiro(filename);
	string line;

	while(getline(ficheiro,line)){
		stringstream p(line);
		float x,y,z;
	    p >> x >> y >> z;
		points.push_back(Point(x,y,z));
	}
}

void xml_parser(const char* filename) {
    TiXmlDocument doc(filename);

    if (doc.LoadFile()) {
        TiXmlElement *proot = doc.FirstChildElement("world");

        if (proot) {
            TiXmlElement *pwindow = proot->FirstChildElement("window");
            TiXmlElement *position = proot->FirstChildElement("camera")->FirstChildElement("position");
            TiXmlElement *lookAt = proot->FirstChildElement("camera")->FirstChildElement("lookAt");
            TiXmlElement *up = proot->FirstChildElement("camera")->FirstChildElement("up");
            TiXmlElement *projection = proot->FirstChildElement("camera")->FirstChildElement("projection");
            TiXmlElement *model = proot->FirstChildElement("group")->FirstChildElement("models")->FirstChildElement("model");
            string _3D_path = "../3DFiles/";

            if (pwindow) {
                w_width = stoi(pwindow->Attribute("width"));
                w_height = stoi(pwindow->Attribute("height"));
            }

            if (position) {
                pos_x = stof(position->Attribute("x"));
                pos_y = stof(position->Attribute("y"));
                pos_z = stof(position->Attribute("z"));
				cradius = sqrt(pos_x*pos_x + pos_y*pos_y + pos_z*pos_z);
            }

            if (lookAt) {
                look_x = stof(lookAt->Attribute("x"));
                look_y = stof(lookAt->Attribute("y"));
                look_z = stof(lookAt->Attribute("z"));
            }

            if (up) {
                up_x = stof(up->Attribute("x"));
                up_y = stof(up->Attribute("y"));
                up_z = stof(up->Attribute("z"));
            }

            if (projection) {
                fov = stof(projection->Attribute("fov"));
                near = stof(projection->Attribute("near"));
                far = stof(projection->Attribute("far"));
            }

            while (model) {
                string model_name = _3D_path + model->Attribute("file");
                read_3D_file(model_name);
				cout << model_name;
                model = model->NextSiblingElement("model");
            }            
        }
        else {
            cout << "Oops! Something went wrong! Please make sure that the configuration file follows the expected format." << endl;
        }
    }
    else {
        cout << "Failed to load file " + (string)filename << endl;
    }
} 

int main(int argc, char** argv) {

    if (argc == 2) {
        string xml = "../" + (string)argv[1];
        xml_parser(xml.c_str());

        // init GLUT and the window
	    glutInit(&argc, argv);
	    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	    glutInitWindowPosition(100,100);
	    glutInitWindowSize(w_width,w_height);
	    glutCreateWindow("PROJETO-CG@UM-2023");
    
        // Required callback registry 
	    glutDisplayFunc(renderScene);
	    glutReshapeFunc(changeSize);
    
        // Callback registration for keyboard processing
	    glutKeyboardFunc(processKeys);
	    glutSpecialFunc(processSpecialKeys);

        //  OpenGL settings
	    glEnable(GL_DEPTH_TEST);
	    glEnable(GL_CULL_FACE);
    
        // enter GLUT's main cycle
	    glutMainLoop();
    }
    else {
        cout << "Invalid number of arguments provided!" << endl;
    }

    return 1;
}