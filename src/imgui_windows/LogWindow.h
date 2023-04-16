#pragma once

#include "../Renderable.h"

/**
 * @brief TODO
 */
class LogWindow : public Renderable
{
public:
	/**
	 * @brief TODO
	 */
	LogWindow(Application& application);

	/**
	 * @brief TODO
	 */
	void render() override;

private:
	bool m_autoScroll = true;
};
