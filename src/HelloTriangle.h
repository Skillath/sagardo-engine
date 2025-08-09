//
// Created by xabi on 15/07/25.
//

#ifndef HELLOTRIANGLE_H
#define HELLOTRIANGLE_H

class HelloTriangle
{
private:
    unsigned int VBO = 0, VAO = 0, EBO = 0;
    unsigned int _shaderProgram;

public:
    HelloTriangle();
    ~HelloTriangle();

    void Draw() const;
};



#endif //HELLOTRIANGLE_H
