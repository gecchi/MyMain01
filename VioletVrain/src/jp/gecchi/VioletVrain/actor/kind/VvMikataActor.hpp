#ifndef VVMIKATAACTOR_H_
#define VVMIKATAACTOR_H_
#include "VvActor.hpp"

#include "jp/ggaf/core/actor/GgafActor.h"

template<class T>
class VvMikataActor : public VvActor<T> {

public:
    VvMikataActor(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat)
        : VvActor<T>(prm_name, prm_model_id, prm_pStat) {

    }

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
        _TRACE_("VvMikataActor::onHit!!!! ëäéËÅÅ"<<prm_pOtherActor->getName()<<"");
    }

    virtual ~VvMikataActor() {

    }
};

#endif /* VVMIKATAACTOR_H_ */
