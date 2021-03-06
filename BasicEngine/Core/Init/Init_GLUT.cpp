//GlutInit.cpp
#include "Init_GLUT.h"

using namespace BasicEngine;
using namespace Core::Init;

Core::IListener* Init_GLUT::listener = NULL;
Core::WindowInfo Init_GLUT::windowInformation;

void Init_GLUT::init(const Core::WindowInfo& windowInfo,
	const Core::ContextInfo& contextInfo,
	const Core::FramebufferInfo& framebufferInfo)
{
	//we need to create these fake arguments
	int fakeargc = 1;
	char *fakeargv[] = { "fake", NULL };
	glutInit(&fakeargc, fakeargv);

	if (contextInfo.core)
	{
		glutInitContextVersion(contextInfo.major_version,
			contextInfo.minor_version);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		//As I said in part II, version doesn't matter
		// in Compatibility mode
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	//these functions were called in the old main.cpp
	//Now we use info from the structures
	glutInitDisplayMode(framebufferInfo.flags);
	glutInitWindowPosition(windowInfo.position_x,
		windowInfo.position_y);
	glutInitWindowSize(windowInfo.width, windowInfo.height);

	glutCreateWindow(windowInfo.name.c_str());

	std::cout << "GLUT:initialized" << std::endl;
	glEnable(GL_DEBUG_OUTPUT);

	//these methods require some glew functionality, so we have to
	//move Core::Init::Init_GLEW::Init(); just before calling thse methods
	Core::Init::Init_GLEW::Init();
	glDebugMessageCallback(DebugOutput::myCallback, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
		GL_DONT_CARE, 0, NULL, GL_TRUE);

	//these callbacks are used for rendering
	glutIdleFunc(idleCallback);
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	
	//glutSetCursor(GLUT_CURSOR_NONE);

	//cleanup
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//our method to display some info. Needs contextInfo and windowinfo
	printOpenGLInfo(windowInfo, contextInfo);

	windowInformation = windowInfo;//add this line
}

//starts the rendering Loop
void Init_GLUT::run()
{
	std::cout << "GLUT:\t Start Running " << std::endl;
	glutMainLoop();
}

void Init_GLUT::close()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init_GLUT::setKeyDownCallback(void(*KeyDownCallback)(unsigned char, int, int)) {
	glutKeyboardFunc(KeyDownCallback);
}

void Init_GLUT::setMouseMoveCallback(void(*MouseMoveCallback)(int, int)) {
	glutMotionFunc(MouseMoveCallback);
}

void BasicEngine::Core::Init::Init_GLUT::setPassiveMouseMoveCallback(void(*PassiveMouseMoveCallback)(int, int))
{
	glutPassiveMotionFunc(PassiveMouseMoveCallback);
}

void Init_GLUT::idleCallback(void)
{
	//do nothing, just redisplay
	glutPostRedisplay();
}

void Init_GLUT::displayCallback()
{
	//check for NULL
	if (listener)
	{
		listener->NotifyBeginFrame();
		listener->NotifyDisplayFrame();

		glutSwapBuffers();

		listener->NotifyEndFrame();
	}
}

void Init_GLUT::reshapeCallback(int width, int height)
{
	if (windowInformation.isReshapable == true)
	{
		if (listener)
		{
			listener->NotifyReshape(width,
				height,
				windowInformation.width,
				windowInformation.height);
		}
		windowInformation.width = width;
		windowInformation.height = height;
	}
}

void Init_GLUT::closeCallback()
{
	close();
}

//set the listener
void Init_GLUT::setListener(Core::IListener* iListener)
{
	listener = iListener;
}

//void Init_GLUT::setEventsListener(Core::IEventsListener* iEventsListener) {
//	eventsListener = iEventsListener;
//}

void Init_GLUT::enterFullscreen()
{
	glutFullScreen();
}

void Init_GLUT::exitFullscreen()
{
	glutLeaveFullScreen();
}

void Init_GLUT::printOpenGLInfo(const Core::WindowInfo& windowInfo,
	const Core::ContextInfo& contextInfo) {

	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "******************************************************************************" << std::endl;
	std::cout << "GLUT:Initialise" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
}