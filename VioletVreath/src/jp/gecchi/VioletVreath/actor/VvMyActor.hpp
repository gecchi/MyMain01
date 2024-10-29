#ifndef VVMYACTOR_H_
#define VVMYACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvGeometricActor.hpp"

namespace VioletVreath {

template<class T>
class VvMyActor : public VvGeometricActor<T> {

public:
    VvMyActor(const char* prm_name, const char* prm_model, void* prm_pFuncResetStatus = nullptr)
            : VvGeometricActor<T>(prm_name, prm_model, prm_pFuncResetStatus) {
#ifdef MY_DEBUG
        if (!(T::_pChecker->_kind & KIND_MY)) {
            throwCriticalException("KIND_MY と、ステータスが異なっています。name="<<prm_name);
        }
#endif
    }

    virtual ~VvMyActor() {
    }
};

}

#endif /* VVMIKATAACTOR_H_ */
