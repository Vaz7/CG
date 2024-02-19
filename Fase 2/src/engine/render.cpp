#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <string>
#include <vector>
#include "../headers/engine/render.hpp"
#include "../headers/engine/group.hpp"
#include "../headers/engine/parser.hpp"

std::unique_ptr<Group> scene;
int startX, startY, tracking = 0;
int alpha_c = 0, beta_c = 45, r = 100;
struct window* win = (struct window*)malloc(sizeof(struct window));
struct camera* cam = (struct camera*)malloc(sizeof(struct camera));

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
	gluPerspective(cam->fov, ratio, cam->near, cam->far);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

	switch(c) {
		case '+': cam->c_radius -= 1; break;
		case '-': cam->c_radius += 1; break;
		case 'w': cam->look_x += 0.1; break;
		case 's': cam->look_y -= 0.1; break;
		case 'a': cam->look_z += 0.1; break;
		case 'd': cam->look_z -= 0.1; break;
		case 'j': cam->look_y += 0.1; break;
		case 'k': cam->look_y -= 0.1; break;
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

void processMouseButtons(int button, int state, int xx, int yy) {
	
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha_c += (xx - startX);
			beta_c += (yy - startY);
		}
		else if (tracking == 2) {
			
			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha_c + deltaX;
		betaAux = beta_c + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha_c;
		betaAux = beta_c;
		cam->c_radius = r - deltaY;
		if (cam->c_radius < 3)
			cam->c_radius = 3;
	}
	cam->pos_x = cam->c_radius * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	cam->pos_z = cam->c_radius * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	cam->pos_y = cam->c_radius * 							     sin(betaAux * 3.14 / 180.0);
}

void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //pos_x = cradius * cos(beta2 * dy) * sin(alfa * dxz);
    //pos_y = cradius * sin(beta2 * dy);                        // Tirar comentário para conseguir mover a câmera 
    //pos_z = cradius * cos(beta2 * dy) * cos(alfa * dxz);
	// set the camera
	glLoadIdentity();
	gluLookAt(cam->pos_x,cam->pos_y,cam->pos_z, 
		      cam->look_x,cam->look_y,cam->look_z,
			  cam->up_x,cam->up_y,cam->up_z);

	glPolygonMode(GL_FRONT_AND_BACK, mode);

	//desenhar os eixos
    // x axis
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    {
        glVertex3f(-10000, 0, 0);
        glVertex3f(10000, 0, 0);
    }
    glEnd();
    // y axis
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    {
        glVertex3f(0, -10000, 0);
        glVertex3f(0, 10000, 0);
    }
    glEnd();
    // z axis
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    {
        glVertex3f(0, 0, -10000);
        glVertex3f(0, 0, 10000);
    }
    glEnd();

    // Só desenhamos a cena quaso esta tenha sido encontrada no ficheiro xml
    if (scene.get() != nullptr) {
        scene->draw();
    }
    
	glutSwapBuffers();
}

void render(int argc, char** argv) {

		*win = (struct window){.w_width = 1600, .w_height = 1600};
		*cam = (struct camera){.pos_x = 5, .pos_y = 5, .pos_z = 5, .c_radius = 7, .look_x = 0, .look_y = 0, .look_z = 0,
							   .up_x = 0, .up_y = 1, .up_z = 0, .fov = 45, .near = 1, .far = 1000};

        std::string xml = "../xml/" + (std::string)argv[1];
        scene = xml_parser(xml.c_str(), &win, &cam);

        // init GLUT and the window
	    glutInit(&argc, argv);
	    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	    glutInitWindowPosition(100,100);
	    glutInitWindowSize(win->w_width,win->w_height);
	    glutCreateWindow("PROJETO-CG@UM-2023");
    
        // Required callback registry 
	    glutDisplayFunc(renderScene);
	    glutIdleFunc(renderScene);
	    glutReshapeFunc(changeSize);
    
        // Callback registration for keyboard processing
		glutMouseFunc(processMouseButtons);
		glutMotionFunc(processMouseMotion);
	    glutKeyboardFunc(processKeys);
	    glutSpecialFunc(processSpecialKeys);

        //  OpenGL settings
	    glEnable(GL_DEPTH_TEST);
	    glEnable(GL_CULL_FACE);
		
		glewInit();
		ilInit();
    
        // enter GLUT's main cycle
	    glutMainLoop();

        free(cam);
        free(win);
}