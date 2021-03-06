//Init_GLUT.h
#pragma once
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include <iostream>
#include "Init_GLEW.h"
#include "IListener.h"
#include "DebugOutput.h"
#include "IEventsListener.h"

namespace BasicEngine {
	namespace Core {
		namespace Init {

			class Init_GLUT {

			public:             //use the structures from Part II
				static void init(const Core::WindowInfo& window,
					const Core::ContextInfo& context,
					const Core::FramebufferInfo& framebufferInfo);

			public:
				static void run();//called from outside
				static void close();
				static void setKeyDownCallback(void(*KeyDownCallback)(unsigned char, int, int));
				static void setMouseMoveCallback(void(*MouseMoveCallback)(int, int));
				static void setPassiveMouseMoveCallback(void(*PassiveMouseMoveCallback)(int, int));


				void enterFullscreen();
				void exitFullscreen();

				//used to print info about GL
				static void printOpenGLInfo(const Core::WindowInfo& windowInfo,
					const Core::ContextInfo& context);
			private:
				static void idleCallback(void);
				static void displayCallback(void);
				static void reshapeCallback(int width, int height);
				static void closeCallback();

			private:
				static Core::IListener* listener;
				//static Core::IEventsListener* eventsListener;
				static Core::WindowInfo windowInformation;

			public:
				static void setListener(Core::IListener* iListener);
				//static void setEventsListener(Core::IEventsListener* iEventsListener);
			};
		}
	}
}