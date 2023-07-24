#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <filesystem>

#include "dataset.h"

void glfw_error_callback(int error, const char* description) {
	std::cout << error << std::endl;
	std::cout << description << std::endl;
}

int main() {
	
	std::cout << std::filesystem::current_path();
	
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
        return EXIT_FAILURE;
	
	const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
	#if defined(__APPLE__)
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	
	GLFWwindow* window = glfwCreateWindow(1080, 720, "Hello GLFW", NULL, NULL);
	if (!window)
		return EXIT_FAILURE;
	
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }
	
	IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;        
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	
	ImGui::StyleColorsDark();
	
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	Dataset* dataset = create_dataset("C:/dev/c++/convnet/src/dataset/test.bin", 32, 32, 3);
	
	uint32_t image_width, image_height, image_size = 0;
	get_dataset_image_size(dataset, &image_width, &image_height, &image_size);

	std::cout << "Width: " << image_width << ", Height: " << image_height << ", Size: " << image_size << std::endl;
	
	uint8_t* dataset_texture_array = get_dataset_texture_array(dataset, 0);
	
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		
		ImGui::NewFrame();
		ImGui::ShowDemoWindow();
		
		ImGui::Begin("OpenGL Texture Text");
		//ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
		ImGui::End();
		
		ImGui::Render();
		
		glViewport(0, 0, 1080, 720);
        glClearColor(0.3f, 0.9f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}
