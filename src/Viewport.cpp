#include "Viewport.h"
#include "Application.h"

Viewport::Viewport(Application& application) : Renderable(application) {
}

void Viewport::render() {
	auto [display_w, display_h] = m_application.frameBufferSize();

	ImVec4 clear_color = ImVec4(1.0f, 0.0f, 1.0f, 1.00f);

	glViewport(0, 0, display_w, display_h);
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}