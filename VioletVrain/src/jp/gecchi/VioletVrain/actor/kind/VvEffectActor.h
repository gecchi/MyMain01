#ifndef VVEFFECTACTOR_H_
#define VVEFFECTACTOR_H_

#include "VvGeometricActor.h"

template<class T>
class VvEffectActor : public VvGeometricActor<T> {

public:
    VvEffectActor(const char* prm_name, const char* prm_model, void* prm_pPrm1 = nullptr);

    virtual ~VvEffectActor();
};

#endif /* VVEFFECTACTOR_H_ */
