#ifndef VVEFFECTACTOR_H_
#define VVEFFECTACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvActor.hpp"

namespace VioletVreath {

template<class T>
class VvEffectActor : public VvActor<T> {

public:
    VvEffectActor(const char* prm_name, const char* prm_model, void* prm_pPrm1 = nullptr)
            : VvActor<T>(prm_name, prm_model) {
        T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pPrm1);
#ifdef MY_DEBUG
        if (!(T::getDefaultKind() == KIND_EFFECT)) {
            throwCriticalException("KIND_EFFECT と、ステータスが異なっています。name="<<prm_name);
        }
#endif
    }

    virtual ~VvEffectActor() {
    }
};

}
#endif /* VVEFFECTACTOR_H_ */
