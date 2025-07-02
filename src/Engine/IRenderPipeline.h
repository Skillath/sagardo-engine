//
// Created by xabi on 2/07/25.
//

#ifndef IRENDERPIPELINE_H
#define IRENDERPIPELINE_H

class IRenderPipeline
{
public:
    virtual void Render() = 0;
        
protected:
    virtual ~IRenderPipeline() = default;
};

#endif //IRENDERPIPELINE_H
