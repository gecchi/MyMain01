#ifndef VVCHIKEIACTOR_H_
#define VVCHIKEIACTOR_H_

#include "VvActor.h"

template<class T>
class VvChikeiActor : public VvActor<T> {

public:
    VvChikeiActor(const char* prm_name, const char* prm_model_id, void* prm_pPrm1 = nullptr);

    virtual ~VvChikeiActor();
};

#endif /* VVCHIKEIACTOR_H_ */
