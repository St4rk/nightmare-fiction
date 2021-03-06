#include "core.h"


#ifdef DEBUG
unsigned int fpsCount = 0;
unsigned int tFps = 0;

float tmr60 = 0.0f;
float tmr1000 = 0.0f;;

#endif

core::core()  {
	coreLoop = false;
}

core::~core() {
	coreLoop = false;
}


/*
 * start
 * this function initialize all engine stuff
 * no return
 */
void core::start() {
	m_Render.initGL();
	m_Input.setInputInfo(m_Render.getContext());
	m_Input.setInputType(INPUT_KEYBOARD);
	m_Utils.start(&m_Render);

	m_Schedule.start(&m_Render, &m_Utils, &m_Input, &m_Sound);

	coreLoop = true;

	mainLoop();
}

/*
 * mainLoop
 * this function deal with the main loop
 * no return
 */
void core::mainLoop() {

	while (coreLoop) {
		m_Render.clearScene();

			m_Input.update();
			m_Schedule.dispatch();
			m_Utils.doFadeEffect();

			#ifdef DEBUG
				/*
				 * TODO: Check if it's right
				 *
				 */
				if (tmr1000 < glfwGetTime()) {
					tmr1000 = glfwGetTime() + 1.0f;
					tFps = fpsCount;
					fpsCount = 0;
				} else {
					fpsCount++;
				}

				std::stringstream fps;
				std::stringstream sceneNum;

				fps << "fps:" << tFps;

				m_Utils.renderText(fps.str(), -0.9f, 0.8f, 0.0f, FONT_TYPE_SMALL, {1.0f, 0.0f, 0.0f, 1.0f});

				sceneNum << "Scene:" << m_Schedule.getSceneNum();
				m_Utils.renderText(sceneNum.str(), -0.9f, 0.9f, 0.0f, FONT_TYPE_SMALL, {1.0f, 1.0f, 1.0f, 1.0f});

			#endif

		m_Render.swapBuffers();
	}

}