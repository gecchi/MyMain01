#ifndef VVCHIKEIACTOR_H_
#define VVCHIKEIACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvGeometricActor.hpp"

namespace VioletVreath {

template<class T>
class VvChikeiActor : public VvGeometricActor<T> {

public:
    VvChikeiActor(const char* prm_name, const char* prm_model, void* prm_pFuncResetStatus = nullptr)
            : VvGeometricActor<T>(prm_name, prm_model, prm_pFuncResetStatus) {
#ifdef MY_DEBUG
        if (!(T::_pChecker->_kind & KIND_CHIKEI)) {
            throwCriticalException("KIND_CHIKEI と、ステータスが異なっています。name="<<prm_name);
        }
#endif
    }

    virtual ~VvChikeiActor() {

    }
};

}

#endif /* VVCHIKEIACTOR_H_ */
