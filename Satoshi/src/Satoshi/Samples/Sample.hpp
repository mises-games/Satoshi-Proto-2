#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <Satoshi/Renderer/APIController.hpp>

namespace Satoshi
{
	class Sample
	{
	public:
		virtual void Start(void* data) = 0;
		virtual void Update() = 0;

		static Sample* Create();
	};
}

#endif
