/**\file Renderer2D.h*/

#pragma once

#include <glm/glm.hpp>
#include "RendererCommon.h"

namespace Engine
{
	class Quad
	{
	public:
		Quad() = default;
		static Quad createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents);
	private:
		glm::vec3 m_translate = glm::vec3(0.f); //!< Translation vector
		glm::vec3 m_scale = glm::vec3(1.f); //!< Scale vector 
		friend class Renderer2D;

	};
	/**\class Renderer
	**\brief Class which allows simple 2D
	*/
	class Renderer2D
	{
	public:
		static void init(); //!< Init the internal data of the renderer 
		static void begin(const SceneWideUniforms& swu); //!< Begin a 2D Scene
		static void submit(Quad& quad, const glm::vec4& tint); //!< Render a tinted quad
		static void submit(Quad& quad, const std::shared_ptr<Texture>& texture); //!< Render a textured
		static void submit(Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture); //!< Render a tinted and textured quad
		static void submit(Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture, float angle, bool degrees = false); //!< Render a tinted, textured and rotated quad
		static void submit(Quad& quad, const glm::vec4& tint, float angle, bool degrees = false); //!< Render a tinted rotated quad
		static void submit(Quad& quad, const std::shared_ptr<Texture>& texture, float angle, bool degrees = false); //!< Render a textured rotated quad
		static void end();
	private:
		struct InternalData
		{
			std::shared_ptr<Texture> defaultTexture;
			glm::vec4 defaultTint;
			std::shared_ptr<Shader> shader;
			std::shared_ptr<VertexArray> VAO;
			glm::mat4 model;
			
		};
		static std::shared_ptr<InternalData> s_data;
	};
}
