#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>

/**
 * @brief TODO
 */
class Application {
public:
	/**
	 * @brief TODO
	 */
	Application();

	/**
	 * @brief TODO
	 */
	void start();

	/**
	 * @brief TODO
	 */
	void menuWindow();

	/**
	 * @brief TODO
	 */
	void logWindow();

private:
	GLFWwindow* m_window = nullptr;
	ImGuiIO* m_ImGuiContext = nullptr;
	bool m_autoScroll = true;
};
