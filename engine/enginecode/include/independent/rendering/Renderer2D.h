/**\file Renderer2D.h*/

#pragma once

#include <glm/glm.hpp>
#include "RendererCommon.h"

namespace Engine
{
	class Quad;

	/**\class Renderer
	**\brief Class which allows simple 2D
	*/
	class Renderer2D
	{
	public:
		static void init(); //!< Init the internal data of the renderer 
		static void begin(const SceneWideUniforms& swu); //!< Begin a 2D Scene
		static void submit(Quad& quad, const glm::vec4& tint); //!< Render a tinted quad
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
