#ifndef VVITEMACTOR_H_
#define VVITEMACTOR_H_

#include "VvActor.h"

template<class T>
class VvItemActor : public VvActor<T> {

public:
    VvItemActor(const char* prm_name, const char* prm_model_id, void* prm_pPrm1 = nullptr);

    virtual ~VvItemActor();
};

#endif /* VVITEMACTOR_H_ */
