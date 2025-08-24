//
// Created by xabi on 24/8/25.
//

#ifndef SAGARDOENGINE_MESH_H
#define SAGARDOENGINE_MESH_H

#define MAX_BONE_INFLUENCE 4

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"

namespace SagardoEngine
{
    struct Vertex final
    {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;
        //bone indexes which will influence this vertex
        unsigned int m_BoneIDs[MAX_BONE_INFLUENCE];
        //weights from each bone
        float m_Weights[MAX_BONE_INFLUENCE];
    };

    struct Texture final
    {
        unsigned int Id;
        std::string Type;
        std::filesystem::path Path;
    };
    
    class Mesh final
    {
    private:
        std::vector<Vertex> _vertices;
        std::vector<unsigned int> _indices;
        std::vector<Texture> _textures;

        // render data 
        unsigned int VAO, VBO, EBO;
        
    public:
        Mesh(
            const std::vector<Vertex>& vertices,
            const std::vector<unsigned int>& indices,
            const std::vector<Texture>& textures);
        
        void Draw(const Shader& shader) const;
    private:

        void SetupMesh();
    };
}

#endif //SAGARDOENGINE_MESH_H