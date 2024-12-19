#include "guitask.hpp"
#include "datapool.hpp"
#include "shutdownmessage.hpp"
#include "taskspawner.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <stdio.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

static void ErrorCallbackCrash(int error, const char* description)
{
   fprintf(stderr, "GLFW Error %d: %s\n", error, description);
   exit(error); // Temp
}


BOOL 
GUITask::Init()
{
   // !TODO: This should be hidden from the user :)
   std::weak_ptr<GUITask> pclTaskHandle = TaskSpawner<TaskTable::N>::GetSharedTaskHandle<GUITask>(TaskIDEnum::GUI_TASK);
   if(pclTaskHandle.lock())
   {
      GetDataPoolInstance<ShutDownMessage>()->RegisterCallBack(&GUITask::RespondToShutDown, pclTaskHandle);
      return TRUE;
   }
   return FALSE;
}


void 
GUITask::Main()
{
   glfwSetErrorCallback(ErrorCallbackCrash);

   glfwInit();

   // GL 3.0 + GLSL 130
   const char* glsl_version = "#version 130";
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

   GLFWwindow* window = glfwCreateWindow(1920, 1080, "SlopDAW", nullptr, nullptr);

   glfwMakeContextCurrent(window);
   glfwSwapInterval(1); // Enable vsync

   // Setup Dear ImGui context
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO& io = ImGui::GetIO();
   (void)io;
   io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
   //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
   //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows.  May need when using other VST's

   // Setup Dear ImGui style
   ImGui::StyleColorsDark();

   // Setup Platform/Renderer backends
   ImGui_ImplGlfw_InitForOpenGL(window, true);
   ImGui_ImplOpenGL3_Init(glsl_version);

   // System Variables
   int display_w, display_h;

   // State Variables
   ImVec4 clear_color = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

   while (!glfwWindowShouldClose(window))
   {
      // Poll and handle events (inputs, window resize, etc.)
           // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
           // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
           // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
           // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
      glfwPollEvents();
      if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
      {
         ImGui_ImplGlfw_Sleep(10);
         continue;
      }

      // Start the Dear ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      // Content
      this->tracklist.SetupMainLayout();

      // Rendering
      ImGui::Render();

      glfwGetFramebufferSize(window, &display_w, &display_h);
      glViewport(0, 0, display_w, display_h);
      glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
      glClear(GL_COLOR_BUFFER_BIT);

      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(window);
   }

   // Cleanup
   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();

   glfwDestroyWindow(window);
   glfwTerminate();

   return;
}

void 
GUITask::RespondToShutDown(
   const std::shared_ptr<ShutDownMessage>& pstShutDown_)
{
   return;
}


