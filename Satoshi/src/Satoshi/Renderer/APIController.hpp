#ifndef API_CONTROLLER_HPP
#define API_CONTROLLER_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Core/Base.hpp>

namespace Satoshi
{
	enum class RendererAPI
	{
		None = 0,
		GL4 = 1,
		D3D11 = 2
	};

	class APIController
	{
	public:
		static RendererAPI GetRendererAPI() { return s_RendererAPI; }
		static void SetRendererAPI(RendererAPI api) { s_RendererAPI = api; }
	private:
		static RendererAPI s_RendererAPI;
	};
}

#endif
