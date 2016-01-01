#pragma once

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>

class Shader;
struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    GLuint id;
    std::string type;
    aiString path;
};

class Mesh
{
public:
    /* mesh data */
    std::vector<Vertex>  vertices;
    std::vector<GLuint>  indices;
    std::vector<Texture>  textures;

    /* functions */
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
    void Draw(Shader shader);

private:
    /* render data */
    GLuint VAO, VBO, EBO;

    /* functions */
    void setupMesh();
};
