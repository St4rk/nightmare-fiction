#include "utils.h"


utils::utils() {
	m_Render = nullptr;

	fade.speed   = 0.0f;
	fade.r_Color = {0.0f, 0.0f, 0.0f, 0.0f};
	fade.type    = FADE_NONE;
	fade.inFade  = false;
}

utils::~utils() {
	m_Render = nullptr;


	fontSet.~modelObj();
	fadeTexture.~modelObj();

	fade.speed   = 0.0f;
	fade.r_Color = {0.0f, 0.0f, 0.0f, 0.0f};
	fade.type    = FADE_NONE;
	fade.inFade  = false;

	glDeleteBuffers(1, &utilsVBO);
	glDeleteBuffers(1, &utilsTexture);
}

/*
 * start
 * this function start utils stuff, set the m_Render pointer
 * and load texture stuff
 * no return
 */
void utils::start(render *m_Render) {
	this->m_Render = m_Render;

	/* 
	 * load font set
	 */

	fontSet.tex = m_Render->loadTexture("resource/font/1.BMP", true, {0.0f, 0.0f, 0.0f, 0.0f});
	fadeTexture.tex = m_Render->loadTexture("resource/ui/dummy.png");

	glGenBuffers(1, &fontSet.vbo);
	glGenBuffers(1, &utilsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, utilsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_rectangle_data), vertex_rectangle_data, GL_STATIC_DRAW);

	glGenBuffers(1, &utilsTexture);
	glBindBuffer(GL_ARRAY_BUFFER, utilsTexture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_rectangle_uv), vertex_rectangle_uv, GL_STATIC_DRAW);
}

/*
 * renderRectangle
 * this function render a rectangle
 * no return
 */
void utils::renderRectangle(const GLuint& texID, const GLuint& textureUnit, const color& r_Color) {
	GLuint m_Color = glGetUniformLocation(m_Render->getProgramId(), "m_Color");
	
	glUniform4f(m_Color, r_Color.r, r_Color.g, r_Color.b, r_Color.a);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glUniform1i(textureUnit, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, utilsVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, utilsTexture);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/*
 * renderText
 * This function is used to render bitmap fonts
 * no return
 */
void utils::renderText(const std::string& text, const float& Xo, const float& Yo, const float& Zo, const FONT_TYPE& font, const GLuint& textureUnit,
   			     	   const color& r_Color) {

	GLuint m_Color = glGetUniformLocation(m_Render->getProgramId(), "m_Color");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fontSet.tex->id);
	glUniform1i(textureUnit, 0);

	switch (font) {
		case FONT_TYPE_SMALL: {
			std::string::const_iterator it;
			std::vector<GLfloat> vbo_buffer;
			float x = Xo;
			float y = Yo;

			for (it = text.begin(); it != text.end(); it++) {

				if (*it == '\n') {
					x = Xo;
					y -= 0.1f;
				} else if (*it == ' ') {
					x += 0.060f;
				} else {
					float u = 0.03125f * (*it % 32);
					float v = 0.03125f * ((*it - 32)/32);

					GLfloat xyz_uv_coord[] = {
					   -0.03f    + x, -0.03f    + y, 0.0f,
					    0.0f     + u,  0.97f   - v,

					    0.03f    + x, -0.03f    + y, 0.0f,
						0.03125f   + u,  0.97f   - v,

					   -0.03f    + x,  0.03f    + y, 0.0f,
						0.0f     + u,  0.999f  - v,

					    0.03f    + x,  0.03f    + y, 0.0f,
						0.03125f   + u,  0.999f  - v,

					   -0.03f    + x,  0.03f    + y, 0.0f,
						0.0f     + u,  0.999f  - v,

					    0.03f    + x, -0.03f    + y, 0.0f,
						0.03125f   + u,  0.97f   - v
					};

					vbo_buffer.insert (vbo_buffer.end(), xyz_uv_coord, xyz_uv_coord+30);
					x += 0.060f;
				}
			}

			glUniform4f(m_Color, r_Color.r, r_Color.g, r_Color.b, r_Color.a);
			glBindBuffer(GL_ARRAY_BUFFER, fontSet.vbo);
			glBufferData(GL_ARRAY_BUFFER, vbo_buffer.size() * sizeof(GLfloat), &vbo_buffer[0], GL_STREAM_DRAW);
			
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)0x0);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)0xC);

				glDrawArrays(GL_TRIANGLES, 0, 6 * text.length());
		
			
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);


			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);

		}
		break;

		case FONT_TYPE_BIG: {
			std::string::const_iterator it;
			std::vector<GLfloat> vbo_buffer;
			float x = Xo;
			float y = Yo;

			for (it = text.begin(); it != text.end(); it++) {

				if (*it == '\n') {
					x = Xo;
					y -= 0.1f;
				} else if (*it == ' ') {
					x += 0.1f;
				} else {
					float u = 0.0545f  * (*it % 18);
					float v = 0.0543f  * ((*it - 36)/18) - 0.0545f;

					GLfloat xyz_uv_coord[] = {
					   -0.04f    + x, -0.05f    + y, 0.0f,
					    0.0f     + u,  0.78f   - v,

					    0.04f    + x, -0.05f    + y, 0.0f,
						0.054f   + u,  0.78f   - v,

					   -0.04f    + x,  0.05f    + y, 0.0f,
						0.0f     + u,  0.834f  - v,

					    0.04f    + x,  0.05f    + y, 0.0f,
						0.054f   + u,  0.834f  - v,

					   -0.04f    + x,  0.05f    + y, 0.0f,
						0.0f     + u,  0.834f  - v,

					    0.04f    + x, -0.05f    + y, 0.0f,
						0.054f   + u,  0.78f   - v
					};

					vbo_buffer.insert (vbo_buffer.end(), xyz_uv_coord, xyz_uv_coord+30);
					x += 0.1f;
				}
			}

			glUniform4f(m_Color, r_Color.r, r_Color.g, r_Color.b, r_Color.a);
			glBindBuffer(GL_ARRAY_BUFFER, fontSet.vbo);
			glBufferData(GL_ARRAY_BUFFER, vbo_buffer.size() * sizeof(GLfloat), &vbo_buffer[0], GL_STREAM_DRAW);
			
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)0x0);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)0xC);

				glDrawArrays(GL_TRIANGLES, 0, 6 * text.length());
		
			
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);


			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);

		}
		break;

		default:
			std::cout << "Invalid font type: " << font << std::endl;
		break;
	}
}

/*
 * setupFadeEffect
 * initialize fade effect
 * speed = speed of fade effect
 * r,g,b = color of fade effect
 * type  = FADE_IN, FADE_OUT, FADE_BLINK, FADE_IN_OUT
 * no return
 */
void utils::setupFadeEffect(const float& speed, const float& r, const float& g, const float& b, const FADE_EFFECT_TYPE& type) {
	this->fade.speed = speed;

	switch (type) {
		case FADE_IN: 		this->fade.r_Color = {r, g, b, 0.0f}; break;
		case FADE_OUT: 		this->fade.r_Color = {r, g, b, 1.0f}; break;
		case FADE_BLINK: 	this->fade.r_Color = {r, g, b, 0.0f}; break;
		case FADE_IN_OUT:  	this->fade.r_Color = {r, g, b, 1.0f}; this->fade.inOut = true; break;
		case FADE_NONE:     this->fade.r_Color = {0.0f, 0.0f, 0.0f, 0.0f}; break;
	}

	this->fade.type = type;
	this->fade.inFade = true;
}

/*
 * doFadeEffect
 * handle the fade effect to be rendered
 */
void utils::doFadeEffect() {
	// check if fade effect is enable
	if (fade.inFade) {
		switch (fade.type) {
			case FADE_IN:
				if (fade.r_Color.a < 1.0f) {
					fade.r_Color.a += fade.speed;
				} else {
					fade.inFade = false;
				}
			break;

			case FADE_OUT: {
				if (fade.r_Color.a > 0.0f) {
					fade.r_Color.a -= fade.speed;
				} else {
					if (fade.inOut) {
						fade.inOut = false;
						fade.type = FADE_IN;
						fade.r_Color = {0.0f, 0.0f, 0.0f, 0.0f};
					} else {
						fade.inFade = false;
					}
				}
			}
			break;

			case FADE_BLINK:
			
			break;

			case FADE_IN_OUT:
				fade.type = FADE_OUT;
			break;

			default:
				std::cout << "effect not implemented" << std::endl;
			break;
		}


		renderRectangle(fadeTexture.tex->id, m_Render->getTexUnit(), fade.r_Color);
	}

}

bool utils::isInFade() const { return fade.inFade; }