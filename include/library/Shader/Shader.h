#ifndef SHADER_H
#define SHADER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "library/Shader/ShaderScript.h"

class Shader{
	
	sf::Shader::Type m_type;
	std::vector<ShaderScript*> m_shaderScripts;
	std::string getScript();
	void applyShaderParameters();
public:
	Shader();
	void buildShader();
	sf::Shader m_shader;
	void addShaderScript(ShaderScript *shaderScirpt);
};

#endif