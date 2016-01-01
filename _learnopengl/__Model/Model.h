#pragma once

#include <glew.h>
#include <string>
#include <vector>

#include <SOIL.h>
#include <Mesh.h>

class Shader;

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

enum aiTextureType;

class Model
{
public:
    /* functions */
    Model(GLchar* path);
    void Draw(Shader shader);

private:
    /* model data */
    std::vector<Mesh>     meshes;
    std::vector<Texture>  textures_loaded;
    std::string directory;

    /* functions */
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};

GLint TextureFromFile(const char* path, std::string directory);
