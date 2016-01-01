#include <Mesh.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <Shader.h>

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    this->setupMesh();
}

void Mesh::setupMesh()
{
    /***************************************************************************
    A great thing about struct is that
    THEIR memory layout is sequential for all its items..
    THE effect is that
    WE can simply pass a pointer to the struct and
    IT translates perfectly to a glm::vec3/2 array which
    AGAIN translates to 3/2 floats which translates to a byte array..
    ***************************************************************************/
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // Vertex Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Vertex Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    // Vertex Texture Coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
};

void Mesh::Draw(Shader shader)
{
    /************************************************************************/
    /*  EACH diffuse texture is named texture_diffuseN
    EACH specular texture should be named texture_specularN
    WHERE N is any number ranging from 1 to the maximum number of texture samplers allowed
    */
    /************************************************************************/
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    for (GLuint i = 0; i < this->textures.size(); ++i) {
        // Active proper texture unit before binding
        glActiveTexture(GL_TEXTURE0 + i);

        // Retrieve texture number -The N in diffuse_textureN
        std::stringstream ss;
        std::string number;
        std::string name = this->textures[i].type;
        if (name == "texture_diffuse") {
            ss << diffuseNr++;//transfer GLuint to stream
        }
        else if (name == "texture_diffuse") {
            ss << specularNr++;//transfer GLuint to stream
        }
        number = ss.str();

        glUniform1f(glGetUniformLocation(shader.Program, ("material." + name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
