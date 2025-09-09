#ifndef SAGARDOENGINE_IRENDERPIPELINE_H
#define SAGARDOENGINE_IRENDERPIPELINE_H

class IRenderPipeline
{
public:
    virtual void Render() = 0;
        
protected:
    virtual ~IRenderPipeline() = default;
};

#endif //SAGARDOENGINE_IRENDERPIPELINE_H
