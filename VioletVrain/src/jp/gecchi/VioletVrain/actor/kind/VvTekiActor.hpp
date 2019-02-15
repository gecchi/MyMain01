#ifndef VVTEKIACTOR_H_
#define VVTEKIACTOR_H_

#include "VvActor.hpp"

#include "jp/ggaf/core/actor/Actor.h"

template<class T>
class VvTekiActor : public VvActor<T> {

public:
    VvTekiActor(const char* prm_name, const char* prm_model_id)
        : VvActor<T>(prm_name, prm_model_id) {

    }
    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
        _TRACE_("VvTekiActor::onHit!!!! ���聁"<<prm_pOtherActor->getName()<<"");
    }

    virtual ~VvTekiActor() {

    }
};

#endif /* VVTEKIACTOR_H_ */
