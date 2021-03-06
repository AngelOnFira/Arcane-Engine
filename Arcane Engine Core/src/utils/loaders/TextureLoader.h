#pragma once

#include <map>
#include <gl/glew.h>
#include <stb_image_aug.h>
#include <string>

#include "../../graphics/texture/Texture.h"
#include "../../graphics/texture/Cubemap.h"

namespace arcane { namespace utils {

	class TextureLoader {
	private:

		struct DefaultTextures {
			graphics::Texture *m_DefaultDiffuse;
			graphics::Texture *m_FullSpecular, *m_NoSpecular;
			graphics::Texture *m_DefaultNormal;
			graphics::Texture *m_DefaultEmission;
		};

	public:
		static void initializeDefaultTextures();

		// isSRGB will let the loader know that the texture needs to be "linearlized" before it is sampled in the shaders
		// Anything that will be used for colour in a renderer should be linearlized. However textures that contain data (Heightfields, normal maps, metallic maps etc.) should not be,
		// thus they are not in SRGB space
		static graphics::Texture* load2DTexture(std::string &path, bool isSRGB, graphics::TextureSettings *settings = nullptr);
		static graphics::Cubemap* loadCubemapTexture(const std::string &right, const std::string &left, const std::string &top, const std::string &bottom, const std::string &back, const std::string &front, bool isSRGB, graphics::CubemapSettings *settings = nullptr);

		inline static graphics::Texture* getDefaultDiffuse() { return m_DefaultTextures.m_DefaultDiffuse; }
		inline static graphics::Texture* getDefaultSpecular() { return m_DefaultTextures.m_NoSpecular; }
		inline static graphics::Texture* getDefaultNormal() { return m_DefaultTextures.m_DefaultNormal; }
		inline static graphics::Texture* getDefaultEmission() { return m_DefaultTextures.m_DefaultEmission; }
		inline static graphics::Texture* getFullSpec() { return m_DefaultTextures.m_FullSpecular; }
		inline static graphics::Texture* getNoSpec() { return m_DefaultTextures.m_NoSpecular; }
	private:
		static std::map<std::string, graphics::Texture> m_TextureCache;
		static DefaultTextures m_DefaultTextures;
	};

} }