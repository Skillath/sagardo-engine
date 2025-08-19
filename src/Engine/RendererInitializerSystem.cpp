#include "RendererInitializerSystem.h"

#include <print>
#include "IO/File.h"
#include "Components.h"
#include "Entity.h"
#include "GlTextureLoader.h"
#include "Shader.h"
#include "glad/glad.h"

namespace SagardoEngine
{
    void RendererInitializerSystem::Run(
        flecs::world& world,
        const float deltaTime)
    {
        world
            .system<TriangleComponent>()
            .kind(flecs::OnStart)
            .each([](
                const flecs::entity entity,
                const TriangleComponent& triangle)
            {
                const Shader shaderProgram(
                    triangle.VertexShaderPath,
                    triangle.FragmentShaderPath);
                
                const ShaderComponent shader(shaderProgram.GetId());
                
                MeshComponent mesh {};
                
                glGenVertexArrays(1, &mesh.VertexArrayObject);
                glGenBuffers(1, &mesh.VertexBufferObject);
                glGenBuffers(1, &mesh.ElementBufferObject);
                // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
                glBindVertexArray(mesh.VertexArrayObject);
                
                glBindBuffer(GL_ARRAY_BUFFER, mesh.VertexBufferObject);
                glBufferData(GL_ARRAY_BUFFER, triangle.VerticesSize, triangle.Vertices, GL_STATIC_DRAW);
                
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ElementBufferObject);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangle.IndicesSize, triangle.Indices, GL_STATIC_DRAW);
                
                // position attribute
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);
                // texture coord attribute
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
                glEnableVertexAttribArray(1);
                
                // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
                //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                
                // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
                // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
                //glBindVertexArray(0); 
                
                
                // uncomment this call to draw in wireframe polygons.
                //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

                const auto texture = GlTextureLoader::LoadTextureFromFile(triangle.TexturePath, false);
                const auto awesomeFaceTexture = GlTextureLoader::LoadTextureFromFile(triangle.AwesomeFaceTexturePath, false);
                
                const TextureComponent textureComponent
                {
                    .TextureId = texture.Id,
                    .Texture0Id = awesomeFaceTexture.Id,
                };
                
                shaderProgram.Use();
                shaderProgram.SetInt("texture1", 0);
                shaderProgram.SetInt("texture2", 1);
                
                entity
                    .set<MeshComponent>(mesh)
                    .set<TextureComponent>(textureComponent)
                    .set<ShaderComponent>(shader)
                    .remove<TriangleComponent>();
            });
    }
}
