#include <Satoshi/stpch.hpp>
#include "Sample.hpp"

#include "GL4Samples.hpp"
#include "D3D11Samples.hpp"

Satoshi::Sample* Satoshi::Sample::Create()
{
	switch (APIController::GetRendererAPI())
	{
		case RendererAPI::None:	ST_CORE_ASSERT(false, "You must choose a valid Graphic API!"); return nullptr;
		case RendererAPI::GL4:	return new GL4Sample1();
		#ifdef ST_PLATFORM_WINDOWS
		case RendererAPI::D3D11: return new D3D11Sample1();
		#endif
		default: ST_CORE_ASSERT(false, "Window not implemented in this OS"); return nullptr;
	}
}
