#include <Satoshi/stpch.hpp>
#include "Layer.hpp"

Satoshi::Layer::Layer(const std::string& debugName) :
	m_DebugName(debugName)
{
}

Satoshi::Layer::~Layer()
{
}

const std::string& Satoshi::Layer::GetName() const
{
	return m_DebugName;
}
