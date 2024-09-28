#ifndef VVITEMACTOR_H_
#define VVITEMACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvActor.hpp"

namespace VioletVreath {

template<class T>
class VvItemActor : public VvActor<T> {

public:
    VvItemActor(const char* prm_name, const char* prm_model, void* prm_pFuncResetStatus = nullptr)
            : VvActor<T>(prm_name, prm_model, prm_pFuncResetStatus) {
#ifdef MY_DEBUG
        if (!(T::_pChecker->_kind & KIND_ITEM)) {
            throwCriticalException("KIND_ITEM �ƁA�X�e�[�^�X���قȂ��Ă��܂��Bname="<<prm_name);
        }
#endif
    }

    virtual ~VvItemActor() {
    }
};

}

#endif /* VVITEMACTOR_H_ */
