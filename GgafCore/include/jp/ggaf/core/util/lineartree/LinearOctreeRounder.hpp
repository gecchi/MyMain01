#ifndef GGAF_CORE_LINEAROCTREEROUNDER_H_
#define GGAF_CORE_LINEAROCTREEROUNDER_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/util/lineartree/LinearTreeRounder.hpp"

namespace GgafCore {

/**
 * T��v�f�Ƃ������蔻��@�\��ǉ��������`8���؂̊e�v�f�ɏ������s�� .
 * @version 1.00
 * @since 2022/12/15
 * @author Masatoshi Tsuge
 */
template<class T>
class LinearOctreeRounder : public LinearTreeRounder<T,3,8> {

public:
    /**
     * �R���X�g���N�^
     * @param prm_level �쐬����N���؋�ԃ��x��
     */
    LinearOctreeRounder(typename LinearTree<T,3,8>::NodeSpace* prm_paLinearTreeSpace, int prm_num_space, void (T::*prm_pFuncHitCheck)(T*))
        : LinearTreeRounder<T,3,8>(prm_paLinearTreeSpace, prm_num_space, prm_pFuncHitCheck)  {
    }


    virtual ~LinearOctreeRounder() {
    }
};

}
#endif /*GGAF_CORE_LINEAROCTREEROUNDER_H_*/

