#ifndef GGAF_CORE_LINEAROCTREEROUNDER_H_
#define GGAF_CORE_LINEAROCTREEROUNDER_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/util/lineartree/LinearTreeRounder.hpp"

namespace GgafCore {

/**
 * Tを要素とし当たり判定機能を追加した線形8分木の各要素に処理を行う .
 * @version 1.00
 * @since 2022/12/15
 * @author Masatoshi Tsuge
 */
template<class T>
class LinearOctreeRounder : public LinearTreeRounder<T,3,8> {

public:
    /**
     * コンストラクタ
     * @param prm_level 作成するN分木空間レベル
     */
    LinearOctreeRounder(typename LinearTree<T,3,8>::NodeSpace* prm_paLinearTreeSpace, int prm_num_space, void (T::*prm_pFuncHitCheck)(T*))
        : LinearTreeRounder<T,3,8>(prm_paLinearTreeSpace, prm_num_space, prm_pFuncHitCheck)  {
    }


    virtual ~LinearOctreeRounder() {
    }
};

}
#endif /*GGAF_CORE_LINEAROCTREEROUNDER_H_*/

