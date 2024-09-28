#ifndef VVEFFECTACTOR_H_
#define VVEFFECTACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvActor.hpp"

namespace VioletVreath {

template<class T>
class VvEffectActor : public VvActor<T> {

public:
    VvEffectActor(const char* prm_name, const char* prm_model, void* prm_pFuncResetStatus = nullptr)
            : VvActor<T>(prm_name, prm_model, prm_pFuncResetStatus) {
#ifdef MY_DEBUG
        if (!(T::_pChecker->_kind == KIND_EFFECT)) {
            throwCriticalException("KIND_EFFECT と、ステータスが異なっています。name="<<prm_name);
        }
#endif
    }

    virtual ~VvEffectActor() {
    }
};

}
#endif /* VVEFFECTACTOR_H_ */
