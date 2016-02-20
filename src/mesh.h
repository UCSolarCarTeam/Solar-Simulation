#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Mesh
{
	public:
		Mesh(glm::vec3* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
		void Draw();
		virtual ~Mesh();

	protected:
	private:
		Mesh(const Mesh& other);
		void operator=(const Mesh& other) {}
		enum{
			POSITION_VB,
			INDEX_VB,
			NUM_BUFFERS
		};

		GLuint m_vertexArrayObject;
		GLuint m_vertexArrayBuffers[NUM_BUFFERS];
		unsigned int m_drawCount; //Number of drawn indices
};

#endif 