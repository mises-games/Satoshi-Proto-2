#ifndef LAYER_HPP
#define LAYER_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Events/Event.hpp>

namespace Satoshi 
{
	class Layer 
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const;
	private:
		std::string m_DebugName;
	};
}

#endif
