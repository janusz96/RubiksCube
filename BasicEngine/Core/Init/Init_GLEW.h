//Init_GLEW.h
#pragma once
#include <iostream>
//#include "../../Dependencies/include/glew/glew.h"
//#include "../../Dependencies/include/freeglut/freeglut.h"
#include <glew/glew.h>
#include <freeglut/freeglut.h>

namespace BasicEngine {
	namespace Core {
		//notice that I added another namespace here(optional)
		namespace Init {

			class Init_GLEW
			{
			public:
				static void Init();
			};
		}
	}
}