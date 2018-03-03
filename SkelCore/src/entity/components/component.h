/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assun��o
 * @Github https://github.com/dani9bma
 */

#pragma once

#include <string>

namespace Skel
{
	class Entity;

	struct ComponentType
	{
		std::string name;
	};

	class Component
	{
	protected:
		Entity * m_entity;

	public:
		virtual Entity* getEntity() const { return m_entity; }
		virtual ComponentType* getComponentType() const { return nullptr; }
	};

}

