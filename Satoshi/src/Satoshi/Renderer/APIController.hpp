#ifndef API_CONTROLLER_HPP
#define API_CONTROLLER_HPP

namespace Satoshi
{
	enum class RendererAPI
	{
		None = 0,
		GL4 = 1, //OpenGL 4
		D3D11 = 2 //Direct3D 11
	};

	class APIController
	{
	public:
		static void SetAPI(RendererAPI api) { s_API = api; }
		static RendererAPI GetAPI() { return s_API; }
	private:
		static RendererAPI s_API;
	};
}

#endif

