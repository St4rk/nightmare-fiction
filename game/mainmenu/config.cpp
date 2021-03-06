#include "config.h"

menuConfig::menuConfig() {
	pressed = false;
	arrow = 0;
}


menuConfig::~menuConfig() {

}

void menuConfig::checkInput() {
	if (m_Input->getPad() & CORE_PAD_UP) {
		if (!pressed) {
			if (arrow > 0) arrow--; 
			pressed = true;
		}
	} else if (m_Input->getPad() & CORE_PAD_DOWN) {
		if (!pressed) {
			if (arrow < 2) arrow++;
			pressed = true;
		}
	} else if (m_Input->getPad() & CORE_PAD_2) {
		if (!pressed) {
			switch (arrow) {
				case 0:

				break;

				case 1: 

				break;

				case 2:
					m_Utils->setupFadeEffect(0.007f, 0.0f, 0.0f, 0.0f, FADE_IN);
					layers = CONFIG_LAYER_END;
				break;
			}
		}
	} else {
		pressed = false;
	}
}


void menuConfig::start() {
	layers = CONFIG_LAYER_INIT;
	bg.reset(m_Render->loadTexture("resource/ui/conf.png"));
}

void menuConfig::stateMachine() {


	static _menu configMenu[] = {
		{"PLACEHOLDER1", -0.5f, -0.5f, 0.0f},
		{"PLACEHOLDER2", -0.5f, -0.6f, 0.0f},
		{"EXIT", -0.1f, -0.7f, 0.0f}
	};

	switch (layers) {
		case CONFIG_LAYER_INIT:

			m_Utils->renderRectangle(bg->id, {1.0f, 1.0f, 1.0f, 1.0f});			
			if (!m_Utils->isInFade()) {
				layers = CONFIG_LAYER_RUN;
			}
		break;

		case CONFIG_LAYER_RUN:
			checkInput();
			m_Utils->renderRectangle(bg->id, {1.0f, 1.0f, 1.0f, 1.0f});			

			for (int i = 0; i < TOTAL_ENTRY; i++) {
				color r_Color;
				i == arrow ? r_Color = {0.0f, 1.0f, 0.0f, 1.0f} : r_Color = {1.0f, 1.0f, 1.0f, 1.0f};
				m_Utils->renderText(configMenu[i].text,configMenu[i].x, configMenu[i].y, configMenu[i].z, FONT_TYPE_BIG, r_Color);
			}


		break;

		case CONFIG_LAYER_END: {
			m_Utils->renderRectangle(bg->id, {1.0f, 1.0f, 1.0f, 1.0f});			

			if (!m_Utils->isInFade()) {
				m_Utils->setupFadeEffect(0.007f, 0.0f, 0.0f, 0.0f, FADE_OUT);
				layers     = CONFIG_LAYER_INIT;
				sceneState = SCENE_STATE_END;
				nextScene  = 0;
			}			
		}
		break;

		default:

		break;
	}
}

