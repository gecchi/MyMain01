#ifndef VVMIKATAACTOR_H_
#define VVMIKATAACTOR_H_
#include "VvActor.hpp"

#include "jp/ggaf/core/actor/Actor.h"

template<class T>
class VvMikataActor : public VvActor<T> {

public:
    VvMikataActor(const char* prm_name, const char* prm_model_id)
        : VvActor<T>(prm_name, prm_model_id) {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
        _TRACE_("VvMikataActor::onHit!!!! ëäéËÅÅ"<<prm_pOtherActor->getName()<<"");
    }

    virtual ~VvMikataActor() {

    }
};

#endif /* VVMIKATAACTOR_H_ */
