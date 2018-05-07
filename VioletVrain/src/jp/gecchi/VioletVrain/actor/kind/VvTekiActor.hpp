#ifndef VVTEKIACTOR_H_
#define VVTEKIACTOR_H_

#include "VvActor.hpp"

#include "jp/ggaf/core/actor/GgafActor.h"

template<class T>
class VvTekiActor : public VvActor<T> {

public:
    VvTekiActor(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat)
        : VvActor<T>(prm_name, prm_model_id, prm_pStat) {

    }
    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
        _TRACE_("VvTekiActor::onHit!!!! ëäéËÅÅ"<<prm_pOtherActor->getName()<<"");
    }

    virtual ~VvTekiActor() {

    }
};

#endif /* VVTEKIACTOR_H_ */
