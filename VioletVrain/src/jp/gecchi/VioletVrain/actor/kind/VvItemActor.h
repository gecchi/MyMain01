#ifndef VVITEMACTOR_H_
#define VVITEMACTOR_H_

#include "VvGeometricActor.h"

template<class T>
class VvItemActor : public VvGeometricActor<T> {

public:
    VvItemActor(const char* prm_name, const char* prm_model, void* prm_pPrm1 = nullptr);

    virtual ~VvItemActor();
};

#endif /* VVITEMACTOR_H_ */
