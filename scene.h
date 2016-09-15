#ifndef _SCENE_H_
#define _SCENE_H_

#include "render.h"
#include "input.h"
#include "utils.h"

enum SCENE_STATE {
	SCENE_STATE_INIT,
	SCENE_STATE_RUN,
	SCENE_STATE_SLEEP,
	SCENE_STATE_END
};

class scene {
public:
	scene();
   ~scene();

   	void setState(const SCENE_STATE& sceneState);
    void setContext(render *m_Render, utils *m_Utils, input *m_Input);
    virtual void stateMachine();

    unsigned int getNextScene() const;
    SCENE_STATE getState() const;

protected:
	SCENE_STATE sceneState;

	unsigned int nextScene;

	render *m_Render;
	utils  *m_Utils;
	input  *m_Input;
};

#endif