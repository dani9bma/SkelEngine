#include "mesh.h"

namespace Skel
{
	Mesh::Mesh(EAVector<Vertices> vertices, EAVector<unsigned int> indices, EAVector<TextureMesh> texture)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = texture;

		setupMesh();
	}


	Mesh::~Mesh() = default;

	void Mesh::setupMesh()
	{
		m_vao.bind();
		m_vbo = VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertices), BufferUsage::STATIC);
		IndexBuffer ibo = IndexBuffer(&indices[0], indices.size() * sizeof(unsigned int));

		m_vao.addBuffer(0, 3, m_vbo, sizeof(Vertices), (void*)0);
		m_vao.addBuffer(1, 2, m_vbo, sizeof(Vertices), (void*)offsetof(Vertices, TexCoords));
		m_vao.addBuffer(2, 3, m_vbo, sizeof(Vertices), (void*)offsetof(Vertices, Normal));
		m_vao.addBuffer(3, 3, m_vbo, sizeof(Vertices), (void*)offsetof(Vertices, Tangent));
		m_vao.addBuffer(4, 3, m_vbo, sizeof(Vertices), (void*)offsetof(Vertices, Bitangent));

		m_vao.unbind();

	}

	void Mesh::Draw(Shader* shader)
	{
		// bind appropriate textures
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++)
		{

			std::stringstream ss;
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				ss << diffuseNr++; // transfer unsigned int to stream
			else if (name == "texture_specular")
				ss << specularNr++; // transfer unsigned int to stream
			else if (name == "texture_normal")
				ss << normalNr++; // transfer unsigned int to stream
			else if (name == "texture_height")
				ss << heightNr++; // transfer unsigned int to stream
			number = ss.str();
			// now set the sampler to the correct texture unit
			shader->setUniform1i((name + number).c_str(), 1);
			// and finally bind the texture
			Texture tex = Texture(textures[i].id);
			tex.draw(i);
		}

		// draw mesh
		m_vao.bind();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
		m_vao.unbind();
		// always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);
	}
}