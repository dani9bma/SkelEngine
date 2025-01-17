#pragma once

#include "component.h"
#include "../entity.h"
#include "Model.h"
#include "../../Graphics/shader.h"

namespace Skel
{
	class SKEL_API MeshComponent : public Component
	{
	private:
		Model * m_mesh;

	public:
		MeshComponent(Model* mesh);
		void draw(Shader* shader);

		static ComponentType* getStaticType()
		{
			static ComponentType type({ "Mesh" });
			return &type;
		}

		inline virtual ComponentType* getComponentType() const override { return getStaticType(); }
	};

}