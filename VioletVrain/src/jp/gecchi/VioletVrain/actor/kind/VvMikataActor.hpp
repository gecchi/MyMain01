#ifndef VVMIKATAACTOR_H_
#define VVMIKATAACTOR_H_
#include "VvActor.hpp"

#include "jp/ggaf/core/actor/Actor.h"

template<class T>
class VvMikataActor : public VvActor<T> {

public:
    VvMikataActor(const char* prm_name, const char* prm_model_id, GgafCore::Status* prm_pStat)
        : VvActor<T>(prm_name, prm_model_id, prm_pStat) {

    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
        _TRACE_("VvMikataActor::onHit!!!! ���聁"<<prm_pOtherActor->getName()<<"");
    }

    virtual ~VvMikataActor() {

    }
};

#endif /* VVMIKATAACTOR_H_ */
