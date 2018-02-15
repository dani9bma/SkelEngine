/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assun��o
 * @Github https://github.com/dani9bma
 */

#include <GL/glew.h>

#include "../../common.h"

namespace Skel { namespace graphics {

	class IndexBuffer
	{
	public:
		IndexBuffer(unsigned int data[], int count);
		~IndexBuffer();
		void bind();
		void unbind();
		void draw();
		inline unsigned int GetBuffer() const { return m_EBO; };
	private:
		unsigned int m_EBO;
		int m_count;
	};

} }