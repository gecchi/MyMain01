#ifndef GGAF_CORE_TREEELEM_H_
#define GGAF_CORE_TREEELEM_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/core/util/TreeNode.hpp"


namespace GgafCore {

typedef LinearQuadtree LinearQuadtree_b;

/**
 * 線形N分木配列用空間にぶら下がる要素クラス .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
template<int DIM>
class TreeElem : public Object {

    friend class LinearOctree;
    friend class LinearQuadtree;
public:
    /** 空間の配列 */
    TreeNode<DIM>* _paSpace;
    /** [r]要素オブジェクト（これが本体） */
    Object* const _pObject;
    /** [r]要素オブジェクトの種別 */
    kind_t _kind;
    /** [r]所属空間 */
    TreeNode<DIM>* _pSpace_current;
    /** [r]空間に登録された要素（TreeNode._pBelongElemList）にぶら下がる次要素 */
    TreeElem<DIM>* _pBelongNext;

    /**
     * コンストラクタ .
     * @param prm_paSpace 空間の配列へのポインタ
     * @param prm_pObject 対象オブジェクト(キャラクタなどN分木で管理したい実際の値)
     */
    TreeElem(TreeNode<DIM>* prm_paSpace, Object* prm_pObject) : Object() ,
        _paSpace(prm_paSpace),
        _pObject(prm_pObject)
    {
        _kind = 0;
        _pSpace_current = nullptr;
        _pBelongNext = nullptr;
    }

    void dump() {
        _TRACE_N_("o");
    }

    virtual ~TreeElem() {
    }
};

}
#endif /*GGAF_CORE_TREEELEM_H_*/

