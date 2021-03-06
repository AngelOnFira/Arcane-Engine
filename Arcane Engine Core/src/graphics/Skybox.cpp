#include "Skybox.h"

namespace arcane { namespace graphics {

	Skybox::Skybox(const std::vector<std::string> &filePaths, Camera *camera) : m_SkyboxShader("src/shaders/skybox.vert", "src/shaders/skybox.frag"), m_Camera(camera)
	{
		m_SkyboxCubemap = utils::TextureLoader::loadCubemapTexture(filePaths[0], filePaths[1], filePaths[2], filePaths[3], filePaths[4], filePaths[5], true);
		
		float skyboxVertices[] = {
			// Front
			-1.0, -1.0,  1.0,
			1.0, -1.0,  1.0,
			1.0,  1.0,  1.0,
			-1.0,  1.0,  1.0,
			// Back
			-1.0, -1.0, -1.0,
			1.0, -1.0, -1.0,
			1.0,  1.0, -1.0,
			-1.0,  1.0, -1.0,
		};
		unsigned int skyboxIndices[] = {
			// front
			2, 1, 0,
			0, 3, 2,
			// top
			6, 5, 1,
			1, 2, 6,
			// back
			5, 6, 7,
			7, 4, 5,
			// bottom
			3, 0, 4,
			4, 7, 3,
			// left
			1, 5, 4,
			4, 0, 1,
			// right
			6, 2, 3,
			3, 7, 6,
		};

		m_SkyboxVBO.load(skyboxVertices, 8 * 3, 3); 
		m_SkyboxIBO.load(skyboxIndices, 36);
		m_SkyboxVAO.addBuffer(&m_SkyboxVBO, 0);
	}

	void Skybox::Draw() {
		m_SkyboxShader.enable();

		// Pass the texture to the shader
		m_SkyboxCubemap->bind(0);
		m_SkyboxShader.setUniform1i("skyboxCubemap", 0);

		m_SkyboxShader.setUniformMat4("view", m_Camera->getViewMatrix());
		m_SkyboxShader.setUniformMat4("projection", m_Camera->getProjectionMatrix());

		// Since the vertex shader is gonna make the depth value 1.0, and the default value in the depth buffer is 1.0 so this is needed to draw the sky  box
		glDepthFunc(GL_LEQUAL);
		m_SkyboxVAO.bind();
		m_SkyboxIBO.bind();
		glDrawElements(GL_TRIANGLES, m_SkyboxIBO.getCount(), GL_UNSIGNED_INT, 0);
		m_SkyboxVAO.unbind();
		m_SkyboxIBO.unbind();
		glDepthFunc(GL_LESS);

		m_SkyboxShader.disable();
	}

} }