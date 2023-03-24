#ifndef GGAF_CORE_LINEARQUADTREEROUNDER_H_
#define GGAF_CORE_LINEARQUADTREEROUNDER_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/util/lineartree/LinearTreeRounder.hpp"

namespace GgafCore {

/**
 * Tを要素とし当たり判定機能を追加した線形4分木の各要素に処理を行う .
 * @version 1.00
 * @since 2022/12/15
 * @author Masatoshi Tsuge
 */
template<class T>
class LinearQuadtreeRounder : public LinearTreeRounder<T,2,4> {

public:
    /**
     * コンストラクタ
     * @param prm_level 作成するN分木空間レベル
     */
    LinearQuadtreeRounder(typename LinearTree<T,2,4>::NodeSpace* prm_paLinearTreeSpace, int prm_num_space, void (T::*prm_pFuncHitCheck)(T*))
        : LinearTreeRounder<T,2,4>(prm_paLinearTreeSpace, prm_num_space, prm_pFuncHitCheck)  {
    }


    virtual ~LinearQuadtreeRounder() {
    }
};

}
#endif /*GGAF_CORE_LINEARQUADTREEROUNDER_H_*/

