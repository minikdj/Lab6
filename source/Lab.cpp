#include "Lab.h"

FrameBuffer colorBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

std::vector<dvec3> triangleVertices;
std::vector<dvec3> verticalLineVertices;
std::vector<dvec3> horizontalLineVertices;

// Index of the problem currently being rendered.
int displayedProblem = 2;

/**
* LAB INSTRUCTIONS:
* Below are descriptions of two dimensional transformation problems. With the
* exception of problem one, each problem requires you to transform the vertices
* of a triangle and render it.
*
* When you have completed all the problems, complete the following turning
* instructions:
*
*	1.	Copy the folder containing your solution to the desktop.
*	2.	Change the name of the folder to CSE287LabFive followed by your unique
*		identifier. For instance “CSE287LabFiveBachmaer.”
*	3.	Open the solution. Make sure it still runs.
*	4.	Clean the solution by selecting Build->Clean Solution. (The will delete
*		all the intermediate temporary files that are part of your project and
*		reduce the size of your submission.)
*	5.	Zip up the solution folder using the standard windows compression tool.
*		(No 7zips, rars, etc.)
*	6.	Submit your zip archive of the solution through canvas.

*/


// Use the linear algebra functionality of GLM to solve the following system of 
// linear equations. Print the solution vector to the console. 
//
// 3x + 7y + 2z = 4
// 2x - 4y - 3z = -1
// 5x + 2y + z = 1
void problem1()
{
    glm::mat3 a;
    a[0][0] = 3; a[0][1] = 7;  a[0][2] = 2;
    a[1][0] = 2; a[1][1] = -4; a[1][2] = -3;
    a[2][0] = 5; a[2][1] = 2;  a[2][2] = 1;

    glm::vec3 b(4,-1,1);

    glm::mat3 ainv = glm::inverse(a);

    glm::dvec3 x = ainv * b;

    std::cout << "x = " << x << std::endl;
} // end Problem1


std::vector<dvec3> transformVertices(const dmat3 & transMatrix, std::vector<dvec3>  vertices)
{
	std::vector<dvec3> transformedVertices;

	for (unsigned int i = 0; i < vertices.size(); i++) {

		dvec3 vt(transMatrix * vertices[i]);

		transformedVertices.push_back(vt);

	}

	return transformedVertices;

} // end transformVertices




// Translate the triangle by 300 in the horizontal direction and
// 250 in the vertical direction by calling transformVertices.
void problem2()
{
	// Create an identity matrix
	dmat3 trans(1.0f);
	
	std::vector<dvec3> transformedVert;

	trans[2][0] = 300;
	trans[2][1] = 250;

	transformedVert = transformVertices(trans, triangleVertices);

	drawFilledTriangle(transformedVert, color(1.0f, 0.0f, 0.0f, 1.0f));

} // end Problem2

// Use a scale transformation to shrink the triangle to three quarters the 
// original size by calling transformVertices.
void problem3()
{
    dmat3 scale(1.0f);
    
    std::vector<dvec3> scaleVert;

    scale[0][0] = 0.75;
    scale[1][1] = 0.75;

    scaleVert = transformVertices(scale, triangleVertices);

    drawFilledTriangle(scaleVert, color(0.0f, 1.0f, 0.0f, 1.0f));
    
} // end Problem3

// Use a scale transformation to reflect the triangle accross the x axis
// by calling transformVertices.
void problem4()
{
    dmat3 reflect(1.0f);

    std::vector<dvec3> reflectVert;

    reflect[0][0] = 1;
    reflect[1][1] = -1;

    reflectVert = transformVertices(reflect, triangleVertices);

    drawFilledTriangle(reflectVert, color(0.0f, 0.0f, 1.0f, 1.0f));

} // end Problem4



// Shear the triangle by a factor of 3 in the horizontal direction by 
// calling transformVertices
void problem5()
{
    dmat3 shear(1.0f);

    std::vector<dvec3> shearVert;

    shear[1][0] = 3;

    shearVert = transformVertices(shear, triangleVertices);

    drawFilledTriangle(shearVert, color(1.0f, 0.0f, 0.0f, 1.0f));

} // end Problem5

// Rotate the triangle by negative 90 degrees by calling transformVertices.
void problem6()
{
    dmat3 rotate(1.0f);

    std::vector<dvec3> rotateVert;

    rotate[0][0] = cos(MM_PI / -2.0);
    rotate[0][1] = -sin(MM_PI / -2.0);
    rotate[1][0] = sin(MM_PI / -2.0);
    rotate[1][1] = cos(MM_PI / -2.0);

    rotateVert = transformVertices(rotate, triangleVertices);

    drawFilledTriangle(rotateVert, color(0.0f, 1.0f, 0.0f, 1.0f));

} // end Problem6


// Create a composite transformation that translates the triangle 200 in the
// horizontal direction 300 in the vertical direction and rotates it in that
// position by 180 degrees. Use the transformVertices function.
void problem7()
{
    dmat3 translate(1.0f);
    dmat3 rotate(1.0f);

    std::vector<dvec3> composite;
    dmat3 combined;

    translate[2][0] = 200;
    translate[2][1] = 300;

    rotate[0][0] = cos(MM_PI);
    rotate[0][1] = -sin(MM_PI);
    rotate[1][0] = sin(MM_PI);
    rotate[1][1] = cos(MM_PI);

    combined = translate * rotate; 
    
    composite = transformVertices(combined, triangleVertices);

    drawFilledTriangle(composite, color(0.0f, 0.0f, 1.0f, 1.0f));

} // end Problem7

// Translate to the same position as the previous question. Instead of a 
// fixed rotation. Have the triangle continously rotate in place in a
// counter clockwise direction. Use the transformVertices function.
void problem8()
{
	static float angle = 0.0f;
    
    dmat3 translate(1.0f);
    dmat3 rotate(1.0f);

    std::vector<dvec3> composite;
    dmat3 combined;

    translate[2][0] = 200;
    translate[2][1] = 300;

    rotate[0][0] = cos(angle);
    rotate[0][1] = -sin(angle);
    rotate[1][0] = sin(angle);
    rotate[1][1] = cos(angle);

    combined = translate * rotate;

    composite = transformVertices(combined, triangleVertices);

    drawFilledTriangle(composite, color(0.0f, 0.0f, 1.0f, 1.0f));

    angle -= 0.1;

} // end Problem8


// Implement and animation that makes the triangle continuously orbit in a clockwise
// direction around the origin at a distance of 400 pixels use the transformVertices function.
void problem9()
{
	static float angle = 0.0f;
    
    dmat3 translate(1.0f);
    dmat3 rotate(1.0f);

    std::vector<dvec3> composite;

    translate[2][0] = 400;

    rotate[0][0] = cos(angle);
    rotate[0][1] = -sin(angle);
    rotate[1][0] = sin(angle);
    rotate[1][1] = cos(angle);

    composite = transformVertices(translate, triangleVertices);
    composite = transformVertices(rotate, composite);

    drawFilledTriangle(composite, color(0.0f, 0.0f, 1.0f, 1.0f));

    angle += 0.05;
} // end Problem9



// Accomplish the same orbit as the previous question with the exception that
// the triangle always points at the top of the screen while it orbits. Use 
// the transformVertices function.
void problem10() 
{
	static float angle = 0.0f;
    
    dmat3 translate(1.0f);
    dmat3 rotate(1.0f);
    dmat3 negRotate(1.0f);

    std::vector<dvec3> composite;
    dmat3 combined;

    translate[2][0] = 400;

    rotate[0][0] = cos(angle);
    rotate[0][1] = -sin(angle);
    rotate[1][0] = sin(angle);
    rotate[1][1] = cos(angle);
    
    negRotate[0][0] = cos(-angle);
    negRotate[0][1] = -sin(-angle);
    negRotate[1][0] = sin(-angle);
    negRotate[1][1] = cos(-angle);

    combined = translate * negRotate;

    composite = transformVertices(combined, triangleVertices);
    composite = transformVertices(rotate, composite);

    drawFilledTriangle(composite, color(0.0f, 0.0f, 1.0f, 1.0f));

    angle += 0.05;

} // end Problem10


// Create ankanimation that causes the triangle to continously bounce from one 
// side of the screen to the other. You can get the width and/or height of the
// screen in pixels by using glutGet( GLUT_WINDOW_WIDTH ) and 
// glutGet( GLUT_WINDOW_HEIGHT ). If you want to get fancy, you can move the
// triangle with a "velocity" vector and reflect the velocity vector each
// time the triangle hits the edge of the screen.
void problem11()
{
	static float angleH = 0;
    static float angleV = 0;
    static bool directionH = true;
    static bool directionV = true;

    dmat3 translate(1.0f);

    std::vector<dvec3> composite;

    translate[2][0] = angleH;
    translate[2][1] = angleV;

    composite = transformVertices(translate, triangleVertices);

    drawFilledTriangle(composite, color(0.0f, 0.0f, 1.0f, 1.0f));

    if ((int)angleV > glutGet(GLUT_WINDOW_HEIGHT) / 2 || (int)angleV < -1.0 * glutGet(GLUT_WINDOW_HEIGHT) / 2) {
        directionV = !directionV;
    }
    if ((int)angleH > glutGet(GLUT_WINDOW_WIDTH) / 2 || (int)angleH < -1.0 * glutGet(GLUT_WINDOW_WIDTH) / 2) {
        directionH = !directionH;
    }
    if(directionV) {
        angleV += 4.0;
    } else {
        angleV -= 4.0;
    }
    if (directionH){
        angleH += 4.0;
    } else {
        angleH -= 4.0;
    }
    
} // end Problem11

// Responds to 'f' and escape keys. 'f' key allows 
// toggling full screen viewing. Escape key ends the
// program. Allows lights to be individually turned on and off.

static void KeyboardCB(unsigned char key, int x, int y)
{
    switch (key) {

    case('1'):
        displayedProblem = 1;
        break;
    case('2'):
        displayedProblem = 2;
        break;
    case('3'):
        displayedProblem = 3;
        break;
    case('4'):
        displayedProblem = 4;
        break;
    case('5'):
        displayedProblem = 5;
        break;
    case('6'):
        displayedProblem = 6;
        break;
    case('7'):
        displayedProblem = 7;
        break;
    case('8'):
        displayedProblem = 8;
        break;
    case('9'):
        displayedProblem = 9;
        break;
    case('t'):
        displayedProblem = 10;
        break;
    case('e'):
        displayedProblem = 11;
        break;
    case('f') : case('F') : // 'f' key to toggle full screen
#warning uncomment
        //glutFullScreenToggle();
        break;
    case(27) : // Escape key
#warning uncomment
        // glutLeaveMainLoop();
        break;
    default:
        std::cout << key << " key pressed." << std::endl;
    }

    glutPostRedisplay();

} // end KeyboardCB

/**
* Acts as the display function for the window.
*/

///
//
//revert back to not use KeyboardCB
//
//
static void RenderSceneCB()
{
	// Clear the color buffer
	colorBuffer.clearColorAndDepthBuffers();

	// Drawn the reference lines
	drawLine(horizontalLineVertices, color(1.0f, 0.0f, 0.0f, 1.0f));
	drawLine(verticalLineVertices, color(0.0f, 1.0f, 0.0f, 1.0f));

	switch (displayedProblem) {

	case 1:
        KeyboardCB('1', 1, 1);
        problem1();
		break;
	case 2:
		KeyboardCB('2', 1, 1);
        problem2();
		break;
	case 3:
        KeyboardCB('3', 1, 1);
        problem3();
		break;
	case 4:
		KeyboardCB('4', 1, 1);
        problem4();
		break;
	case 5:
		KeyboardCB('5', 1, 1);
        problem5();
		break;
	case 6:
		KeyboardCB('6', 1, 1);
        problem6();
		break;
	case 7:
		KeyboardCB('7', 1, 1);
        problem7();
		break;
	case 8:
		KeyboardCB('8', 1, 1);
        problem8();
		break;
	case 9:
		KeyboardCB('9', 1, 1);
        problem9();
		break;
	case 10:
		KeyboardCB('t', 1, 1);
        problem10();
		break;
	case 11:
		KeyboardCB('e', 1, 1);
        problem11();
		break;
	default:
		std::cout << "Invalid displayProblem" << std::endl;
	}

	drawWireTriangle(triangleVertices, color(0.0f, 0.0f, 0.0f, 1.0f));

	// Display the color buffer
	colorBuffer.showColorBuffer();


} // end RenderSceneCB


// Reset viewport limits for full window rendering each time the window is resized.
// This function is called when the program starts up and each time the window is 
// resized.
static void ResizeCB(int width, int height)
{
	// Size the color buffer to match the window size.
	colorBuffer.setFrameBufferSize(width, height);

	verticalLineVertices.clear();

	verticalLineVertices.push_back(dvec3(width / 2, 0.0f, 1.0f));
	verticalLineVertices.push_back(dvec3(width / 2, height, 1.0f));

	horizontalLineVertices.clear();
	horizontalLineVertices.push_back(dvec3(0.0f, height / 2, 1.0f));
	horizontalLineVertices.push_back(dvec3(width, height / 2, 1.0f));

	// Signal the operating system to re-render the window
	glutPostRedisplay();

} // end ResizeCB


// Responds to 'f' and escape keys. 'f' key allows 
// toggling full screen viewing. Escape key ends the
// program. Allows lights to be individually turned on and off.
/*
static void KeyboardCB(unsigned char key, int x, int y)
{
	switch (key) {

	case('f') : case('F') : // 'f' key to toggle full screen
#warning uncomment
		//glutFullScreenToggle();
		break;
	case(27) : // Escape key
#warning uncomment
		//glutLeaveMainLoop();
		break;
	default:
		std::cout << key << " key pressed." << std::endl;
	}
	glutPostRedisplay();

} // end KeyboardCB
*/

// Responds to presses of the arrow keys
static void SpecialKeysCB(int key, int x, int y)
{
	switch (key) {

	case(GLUT_KEY_RIGHT) :

		break;
	case(GLUT_KEY_LEFT) :

		break;
	default:
		std::cout << key << " key pressed." << std::endl;
	}
	glutPostRedisplay();

} // end SpecialKeysCB

// Register as the "idle" function to have the screen continously
// repainted. Due to software rendering, the frame rate will not
// be fast enough to support motion simulation
static void animate()
{
	glutPostRedisplay();

} // end animate

void problemMenu(int value)
{

	if (value != 0) {

		displayedProblem = value;
	}
    else {
#warning uncomment
		//glutLeaveMainLoop();
	}


	// Signal GLUT to call display callback
	glutPostRedisplay();
} // end subMenu1


int main(int argc, char** argv)
{
	// freeGlut and Window initialization ***********************

	// Pass any applicable command line arguments to GLUT. These arguments
	// are platform dependent.
	glutInit(&argc, argv);

	// Set the initial display mode.
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

	// Set the initial window size
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Create a window using a string and make it the current window.
	GLuint world_Window = glutCreateWindow("2D Transformations");

	// Indicate to GLUT that the flow of control should return to the program after
	// the window is closed and the GLUTmain loop is exited.
#warning uncomment
	//glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Callback for window redisplay
	glutDisplayFunc(RenderSceneCB);
	glutReshapeFunc(ResizeCB);
	glutKeyboardFunc(KeyboardCB);
	glutSpecialFunc(SpecialKeysCB);
	glutIdleFunc(animate);

	// Create polygon submenu
	int menu1id = glutCreateMenu(problemMenu);
	// Specify menu items and integer identifiers
	glutAddMenuEntry("Problem 1", 1);
	glutAddMenuEntry("Problem 2", 2);
	glutAddMenuEntry("Problem 3", 3);
	glutAddMenuEntry("Problem 4", 4);
	glutAddMenuEntry("Problem 5", 5);
	glutAddMenuEntry("Problem 6", 6);
	glutAddMenuEntry("Problem 7", 7);
	glutAddMenuEntry("Problem 8", 8);
	glutAddMenuEntry("Problem 9", 9);
	glutAddMenuEntry("Problem 10", 10);
	glutAddMenuEntry("Problem 11", 11);
	glutAddMenuEntry("Quit", 0);

	// Attach menu to right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Request that the window be made full screen
	//glutFullScreenToggle();

	color blue(0.784, 0.784, 1.0, 1.0);

	// Set red, green, blue, and alpha to which the color buffer is cleared.
	colorBuffer.setClearColor(blue);

	// Set vertex locations for one triangle (Must be here do to full screen rendering. Erro)
	triangleVertices.push_back( dvec3( -glm::cos( glm::radians( 45.0f ) ) * 100.0f, -glm::cos( glm::radians( 45.0f ) ) * 100.0f, 1.0f ) );
	triangleVertices.push_back( dvec3( glm::cos( glm::radians( 45.0f ) ) * 100.0f, -glm::cos( glm::radians( 45.0f ) ) * 100.0f, 1.0f ) );
	triangleVertices.push_back( dvec3( 0.0f, 100.0f, 1.0f ) );

	glutFullScreen( );

	// Enter the GLUT main loop. Control will not return until the window is closed.
	glutMainLoop();

	// To keep the console open on shutdown, start the project with Ctrl+F5 instead of just F5.

	return 0;

} // end main
