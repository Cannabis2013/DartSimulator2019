#ifndef UIMANAGER_H
#define UIMANAGER_H



template<typename T>
class IGraphicalUserInterface
{
public:
    virtual void setService(T* service)=0;
    virtual T* service()=0;

};

#endif // UIMANAGER_H
