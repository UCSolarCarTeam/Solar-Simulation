#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "ObjectLoader.h"
#include "Mesh.h"

/**
 * Here is a short list of features a real function would provide :
 *  - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
 *  - Multiple UVs
 *  - All attributes should be optional, not "forced"
 *  - More stable. Change a line in the OBJ file and it crashes.
 *  - More secure. Change another line and you can inject code.
 *  - Loading from memory, stream, etc
 */

bool loadObject(const char* path, ModelData& data)
{
    std::cout << "Loading OBJ file " << path << "..." << std::endl;

    std::vector<unsigned int> vertexIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec3> temp_normals;

    FILE* file = fopen(path, "r");
    if ( file == NULL )
    {
        std::cout << "Error! Unable to open file. Please check that the correct directory has been specified." << std::endl;
        getchar();
        return false;
    }
    int whileLoops = 0;
    int commentLines = 0;
    for (;;)
    {
        char lineHeader[128];
        int res = fscanf(file, "%127s", lineHeader);// read the first word of the line
        whileLoops++;
        if (res == EOF) {
            break; // EOF = End Of File. Quit the loop.
        } // else : parse lineHeader
        if ( strcmp( lineHeader, "v" ) == 0 )
        {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 )
        {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }
        else if ( strcmp( lineHeader, "f" ) == 0 )
        {
            unsigned int vertexIndex[3], normalIndex[3];
            int numbersRead = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
            if (numbersRead != 6)
            {
                std::cout << "The file could not be read by our parser! Try exporting with other options." << std::endl;
                std::cout << "The loop ran: " << whileLoops << " times" << std::endl;
                std::cout << "Commented lines: " << commentLines << std::endl;
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
        else // Probably a comment, eat up the rest of the line
        {
            char garbageBuffer[500];
            fgets(garbageBuffer, 500, file);
            commentLines++;
        }
    }
	std::vector <glm::vec3> out_vertices;
	std::vector <glm::vec2> out_texCoords;
	std::vector <glm::vec3> out_normals;
    for ( unsigned int i = 0; i < vertexIndices.size(); i++ ) // For each vertex get indices of attributes
    {
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int normalIndex = normalIndices[i];

        out_vertices.push_back(temp_vertices[vertexIndex - 1]); // Get the attributes thanks to the index
		out_normals.push_back(temp_normals[normalIndex - 1]);
		out_texCoords.push_back(glm::vec2(0.5, 0.5)); //Set the texture coordinate to an arbitrary value
    }
	data.setPos(&out_vertices);// Put the attributes in buffers
	data.setNormal(&out_normals);
	data.setTexCoord(&out_texCoords);
	unsigned int numVertices = data.getPos().size();
	std::cout << "Size inside of object loader: " << numVertices << std::endl;
    std::cout << "The .obj file was loaded successfully!" << std::endl;
    return true;
}
