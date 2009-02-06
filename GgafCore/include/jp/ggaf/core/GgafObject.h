#ifndef GGAFOBJECT_H_
#define GGAFOBJECT_H_
namespace GgafCore {

class GgafObject {

public:
    GgafObject();
    virtual std::string toString();
    virtual ~GgafObject();
};

}
#endif /*GGAFOBJECT_H_*/
