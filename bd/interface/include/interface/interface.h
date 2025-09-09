#ifndef BD_INTERFACE_H
#define BD_INTERFACE_H
#include <vector>
class interface {
public:
    virtual ~interface() = default;
    virtual bool disconnect();
    virtual bool isconnected();
    virtual void write();
    virtual void read();
private:
};


#endif //BD_INTERFACE_H