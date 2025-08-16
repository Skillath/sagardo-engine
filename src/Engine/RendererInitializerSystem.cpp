#include "RendererInitializerSystem.h"

#include <print>
#include "IO/File.h"
#include "Components.h"
#include "Entity.h"
#include "GlTextureLoader.h"
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
                auto vertexShaderSource = IO::File::ReadAllText("src/res/shaders/color.vert");
                auto vertexShaderSourceStr = vertexShaderSource.c_str();
                auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
                
                glShaderSource(vertexShader, 1, &vertexShaderSourceStr, nullptr);
                glCompileShader(vertexShader);
                // check for shader compile errors
                int success;
                char infoLog[512];
                glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
                    std::println("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{0}", infoLog);
                    return;
                }
                
                // fragment shader
                const auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                const auto fragmentShaderSource = IO::File::ReadAllText("src/res/shaders/color.frag");
                const auto fragmentShaderSourceStr = fragmentShaderSource.c_str();
                glShaderSource(fragmentShader, 1, &fragmentShaderSourceStr, nullptr);
                glCompileShader(fragmentShader);
                // check for shader compile errors
                glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
                    std::println("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{0}", infoLog);
                    return;
                }
                
                // link shaders
                const ShaderComponent shader(glCreateProgram());
                glAttachShader(shader.ShaderProgramId, vertexShader);
                glAttachShader(shader.ShaderProgramId, fragmentShader);
                glLinkProgram(shader.ShaderProgramId);
                // check for linking errors
                glGetProgramiv(shader.ShaderProgramId, GL_LINK_STATUS, &success);
                
                if (!success)
                {
                    glGetProgramInfoLog(shader.ShaderProgramId, 512, nullptr, infoLog);
                    std::println("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{0}", infoLog);
                    return;
                }
                
                glDeleteShader(vertexShader);
                glDeleteShader(fragmentShader);

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
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);
                // color attribute
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
                glEnableVertexAttribArray(1);
                // texture coord attribute
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
                glEnableVertexAttribArray(2);
                
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

                glUseProgram(shader.ShaderProgramId);
                glUniform1i(glGetUniformLocation(shader.ShaderProgramId, "texture1"), 0); 
                glUniform1i(glGetUniformLocation(shader.ShaderProgramId, "texture2"), 1);
                
                
                entity.set<MeshComponent>(mesh);
                entity.set<ShaderComponent>(shader);
                entity.set<TextureComponent>(textureComponent);
                
                
                entity.remove<TriangleComponent>();
            })
            .run();
    }
}
