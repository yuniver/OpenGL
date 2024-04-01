#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "src/cpp/OpenGlManager.h"


int main(void)
{
    OpenGlManager gameInstance;
    return gameInstance.InitOpenGl();
}
