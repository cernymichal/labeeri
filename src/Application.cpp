#include "Application.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>

#include "log.h"

static void glfw_error_callback(int error, const char* description) {
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

Application::Application() {
}

void Application::start() {
	LAB_LOGH1("Application::start()");

	glfwSetErrorCallback(glfw_error_callback);

	// Initialize the library
	if (!glfwInit())
		throw std::runtime_error("glfwInit failed");

	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

	// Create window with graphics context
	m_window = glfwCreateWindow(1600, 1200, "Hello World", NULL, NULL);
	if (!m_window) {
		glfwTerminate();
		throw std::runtime_error("glfwCreateWindow failed");
	}

	// Make the window's context current
	glfwMakeContextCurrent(m_window);

	glfwSwapInterval(1);  // Enable vsync

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	m_ImGuiContext = &ImGui::GetIO();
	(void)*m_ImGuiContext;
	m_ImGuiContext->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	m_ImGuiContext->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
	m_ImGuiContext->ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Docking
	m_ImGuiContext->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable Multi-Viewport / Platform Windows
	// io.ConfigViewportsNoAutoMerge = true;
	// io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (m_ImGuiContext->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImVec4 clear_color = ImVec4(1.0f, 0.0f, 1.0f, 1.00f);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(m_window)) {
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		menuWindow();
		logWindow();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(m_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (m_ImGuiContext->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(m_window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Application::menuWindow() {
	ImGui::Begin("Menu");

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / m_ImGuiContext->Framerate, m_ImGuiContext->Framerate);

	ImGui::End();
}

void Application::logWindow() {
	ImGui::Begin("Log");

	bool autoScrollChanged = ImGui::Checkbox("Auto-scroll", &m_autoScroll);
	ImGui::SameLine(ImGui::GetWindowWidth() - 100);
	if (ImGui::SmallButton("Clear"))
		LAB_LOGSTREAM.str("");
	ImGui::SameLine();
	if (ImGui::SmallButton("Copy"))
		glfwSetClipboardString(m_window, LAB_LOGSTREAM.str().c_str());

	ImGui::Separator();

	ImGui::BeginChild("Log content");

	ImGui::TextUnformatted(LAB_LOGSTREAM.str().c_str());

	if (ImGui::GetScrollY() != ImGui::GetScrollMaxY() && !autoScrollChanged)
		m_autoScroll = false;

	if (m_autoScroll)
		ImGui::SetScrollHereY(1.0f);

	ImGui::EndChild();

	ImGui::End();
}
