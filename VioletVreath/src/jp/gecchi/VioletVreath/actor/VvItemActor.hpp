#ifndef VVITEMACTOR_H_
#define VVITEMACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvGeometricActor.hpp"

namespace VioletVreath {

template<class T>
class VvItemActor : public VvGeometricActor<T> {

public:
    VvItemActor(const char* prm_name, const char* prm_model, void* prm_pFuncResetStatus = nullptr)
            : VvGeometricActor<T>(prm_name, prm_model, prm_pFuncResetStatus) {
#ifdef MY_DEBUG
        if (!(T::_pChecker->_kind & KIND_ITEM)) {
            throwCriticalException("KIND_ITEM と、ステータスが異なっています。name="<<prm_name);
        }
#endif
    }

    virtual ~VvItemActor() {
    }
};

}

#endif /* VVITEMACTOR_H_ */
