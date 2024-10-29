#ifndef VVMYACTOR_H_
#define VVMYACTOR_H_

#include "VvGeometricActor.h"

template<class T>
class VvMyActor : public VvGeometricActor<T> {

public:
    VvMyActor(const char* prm_name, const char* prm_model, void* prm_pPrm1 = nullptr);

    virtual ~VvMyActor();
};

#endif /* VVMIKATAACTOR_H_ */
