#include <string>
#include <iostream>
#include "library/Shader/Shader.h"

Shader::Shader() {
	
}

std::string Shader::getScript() {
	std::string header = "uniform sampler2D texture; \
	";
	for(unsigned int ii=0;ii<m_shaderScripts.size();ii++) {
		m_shaderScripts.at(ii)->setShaderScript();
		header.append(m_shaderScripts.at(ii)->m_headerScript);
	}

	std::string main = "\
	void main() { \
		vec2 pos; \
		pos.x = gl_TexCoord[0].x; \
		pos.y = gl_TexCoord[0].y;\
		";

	for(unsigned int ii=0;ii<m_shaderScripts.size();ii++) {
		main.append(m_shaderScripts.at(ii)->m_mainScript);
	}
	
	main.append("\
		gl_FragColor = texture2D(texture, pos) * gl_Color;\
	}");
    
	return header.append(main);
}

void Shader::applyShaderParameters() {
	for(unsigned int ii=0;ii<m_shaderScripts.size();ii++) {
		m_shaderScripts.at(ii)->setShaderParams(m_shader);
	}
}

void Shader::buildShader() {
	m_shader.loadFromMemory(this->getScript(), sf::Shader::Fragment);
	applyShaderParameters();
	m_shader.setParameter("texture", sf::Shader::CurrentTexture);
}

void Shader::addShaderScript(ShaderScript *shaderScirpt) {
	m_shaderScripts.push_back(shaderScirpt);
}