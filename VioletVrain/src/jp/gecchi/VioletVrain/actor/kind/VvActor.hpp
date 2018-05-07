#ifndef VVACTOR_H_
#define VVACTOR_H_
#include "VioletVrain.h"

template<class T>
class VvActor : public T {

public:
    VvActor(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat)
        : T(prm_name, prm_model_id, prm_pStat) {

    }
    virtual ~VvActor() {

    }
};

#endif /* VVACTOR_H_ */
