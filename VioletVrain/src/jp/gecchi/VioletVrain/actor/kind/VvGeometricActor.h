#ifndef VVGEOMETRICACTOR_H_
#define VVGEOMETRICACTOR_H_
#include "jp/gecchi/VioletVrain/VioletVrain.h"

template<class T>
class VvGeometricActor : public T {

public:
    VvGeometricActor(const char* prm_name, const char* prm_model)
        : T(prm_name, prm_model) {
    }

    virtual ~VvGeometricActor() {
    }
};

#endif /* VVGEOMETRICACTOR_H_ */
