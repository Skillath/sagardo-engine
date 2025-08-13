#include "RendererInitializerSystem.h"

#include <print>

#include "Components.h"
#include "Entity.h"
#include "glad/glad.h"

using namespace SagardoEngine;

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
            MeshComponent mesh{};
            ShaderComponent shader{};

            auto vertexShader = glCreateShader(GL_VERTEX_SHADER);

            glShaderSource(vertexShader, 1, &triangle.VertexShaderSource, nullptr);
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
            auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &triangle.FragmentShaderSource, nullptr);
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
            shader.ShaderProgram = glCreateProgram();
            glAttachShader(shader.ShaderProgram, vertexShader);
            glAttachShader(shader.ShaderProgram, fragmentShader);
            glLinkProgram(shader.ShaderProgram);
            // check for linking errors
            glGetProgramiv(shader.ShaderProgram, GL_LINK_STATUS, &success);
            
            if (!success)
            {
                glGetProgramInfoLog(shader.ShaderProgram, 512, nullptr, infoLog);
                std::println("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{0}", infoLog);
                return;
            }
            
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            
            glGenVertexArrays(1, &mesh.VAO);
            glGenBuffers(1, &mesh.VBO);
            glGenBuffers(1, &mesh.EBO);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(mesh.VAO);

            glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
            glBufferData(GL_ARRAY_BUFFER, triangle.NumVertices, triangle.Vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangle.NumIndices, triangle.Indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0); 

            // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
            //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
            // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
            glBindVertexArray(0); 


            // uncomment this call to draw in wireframe polygons.
            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            entity.set<MeshComponent>(mesh);
            entity.set<ShaderComponent>(shader);

            entity.remove<TriangleComponent>();
        })
        .run(deltaTime);
}
