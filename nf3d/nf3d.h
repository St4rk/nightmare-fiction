#ifndef _NF3D_H_
#define _NF3D_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "emd.h"
#include "plw.h"
#include "../render.h"
#include "../physics.h"


enum NF3D_TYPE {
	NF3D_TYPE_EMD,
	NF3D_TYPE_PLW
};

struct vertexCnt {
	unsigned int begin;
	unsigned int total;
};

class nf3d {
public:
	nf3d(const std::string& dir, nTexture* tex, const NF3D_TYPE& type);
	~nf3d();

	const GLuint& getVBO();
	const GLuint& getTexId();
	const EMD_SEC2_DATA_T& getanimFrame();
	const EMD_SECTION_LIST& getAnimSection();
	const STANDARD_SEC2_ANIMATION& getSec2Animation();
	const STANDARD_SEC4_ANIMATION& getSec4Animation();
	const unsigned int& getAnimCnt();
	unsigned int getMaxAnimCnt();

	void run();

	void setAnimSection(const EMD_SECTION_LIST& emdSection);
	void setSec2Animation(const STANDARD_SEC2_ANIMATION& emdSec2Animation);
	void setSec4Animation(const STANDARD_SEC4_ANIMATION& emdSec4Animation);
	void setAnimCnt(const unsigned int& animCnt);
	void setAnimSet(std::vector<EMD_SEC2_DATA_T> animSet, std::vector<EMD_ANIM_INFO> animSetInfo);
	void removeAnimSet();

	std::unique_ptr<EMD> model;
	PLW weapon;
	std::vector<vertexCnt> vCnt;
	EMD_SEC2_DATA_T animFrame;
	EMD_SEC2_DATA_T oldFrame;
	bool isWeapon;
	bool isAnimSet;
	bool isInterpolation;

	float interStep;

	float interTotal;
private:
	nTexture* tex;
	GLuint vbo;
	



	EMD_SECTION_LIST emdSection;
	STANDARD_SEC2_ANIMATION emdSec2Animation;
	STANDARD_SEC4_ANIMATION emdSec4Animation;

	/* extra anim set */
	std::vector<EMD_SEC2_DATA_T> animSet;
	std::vector<EMD_ANIM_INFO> animSetInfo;


	unsigned int animCnt;

	NF3D_TYPE type;
};

#endif