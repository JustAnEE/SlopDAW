#ifndef GLFWAPI_HPP
#define GLFWAPI_HPP

#include <stdlib.h>
#include <iostream>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

class GlfwApi
{
   public:
      GlfwApi() = default;
      ~GlfwApi() = default;

   public:
      static int LoadTexture(const char* filepath);
};

#endif //!GLFWAPI_HPP
