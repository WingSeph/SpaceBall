#pragma once
#include "Dependencies/glm/vec2.hpp"
#include "Dependencies/glm/vec3.hpp"
#include <map>
#include "Dependencies/glew/glew.h"
#include "ShaderLoader.h"
struct Character
{
	GLuint
		TextureID;	// Texture ID
	glm::ivec2
		Size;	// Size of glyph
	glm::ivec2
		Bearing;	// Positon of glyph
	GLuint
		Advance;	// How far to move for the next character
};

class TextLabel {
public:
	TextLabel(std::string _sText, std::string _sFont, glm::vec2 _pos, glm::vec3 _color);
	~TextLabel() {};
	void Update(std::string _sText);
	void Render();
	void SetText(std::string newText) { m_sText = newText; };
	void SetColor(glm::vec3 newColor) { m_color = newColor; };
	void SetScale(GLfloat newScale) { m_scale = newScale; };
	void SetPosition(glm::vec2 newPosition) { m_position = newPosition; };
	glm::vec2 GetPosition() { return m_position; }

private:
	std::string m_sText;
	GLfloat m_scale;
	glm::vec3 m_color;
	glm::vec2 m_position;
	GLuint m_VAO, m_VBO, m_program;
	std::map<GLchar, Character> m_characters;
	static ShaderLoader m_shaderLoader;
};
