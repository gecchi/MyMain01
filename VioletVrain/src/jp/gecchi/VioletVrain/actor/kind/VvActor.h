#ifndef VVACTOR_H_
#define VVACTOR_H_
#include "jp/gecchi/VioletVrain/VioletVrain.h"

template<class T>
class VvActor : public T {

public:
    VvActor(const char* prm_name, const char* prm_model)
        : T(prm_name, prm_model) {
    }

    virtual ~VvActor() {
    }
};

#endif /* VVACTOR_H_ */
