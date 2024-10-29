#ifndef VVCHIKEIACTOR_H_
#define VVCHIKEIACTOR_H_

#include "VvGeometricActor.h"

template<class T>
class VvChikeiActor : public VvGeometricActor<T> {

public:
    VvChikeiActor(const char* prm_name, const char* prm_model, void* prm_pPrm1 = nullptr);

    virtual ~VvChikeiActor();
};

#endif /* VVCHIKEIACTOR_H_ */
