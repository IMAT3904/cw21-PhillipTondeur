/*\ file graphicsContext.h */
#pragma once

namespace
{
	class GraphicsContext
	{
	public:
		virtual void init() = 0; //!< Init the graphics context windowing the given API
		virtual void swapBuffers() = 0; //!< Swap the front and back buffer
	};
}