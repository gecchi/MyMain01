#ifndef GGAFCORE_GGAFTREEELEM_H_
#define GGAFCORE_GGAFTREEELEM_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"
#include "jp/ggaf/core/util/GgafTreeSpace.hpp"
#include "jp/ggaf/core/util/GgafLinearOctree.h"
namespace GgafCore {

/**
 * 線形N分木配列用空間にぶら下がる要素クラス .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
template<uint32_t BIT_SHIFT_NUM>
class GgafTreeElem : public GgafObject {

    friend class GgafLinearOctree;
    friend class GgafLinearQuadtree;

public:
    /** 空間の配列 */
    GgafTreeSpace<BIT_SHIFT_NUM>*  _paSpace;
    /** [r]要素オブジェクト（これが本体） */
    GgafObject* const _pObject;
    /** [r]要素オブジェクトの種別 */
    actorkind _kindbit;
    /** [r]所属空間 */
    GgafTreeSpace<BIT_SHIFT_NUM>* _pSpace_current;
    /** [r]次要素 */
    GgafTreeElem* _pNext;
    /** [r]前要素 */
    GgafTreeElem* _pPrev;
    /** [r]登録リスト用リンク */
    GgafTreeElem* _pRegLinkNext;

    /**
     * コンストラクタ
     * @param prm_pObject 対象オブジェクト(キャラクタなどN分木で管理したい実際の値)
     * @param prm_kindbit その対象オブジェクの種別、種類分け不要な場合は、任意の数値でよい。
     * @return
     */

    /**
     *
     * @param prm_paSpace
     * @param prm_pObject
     * @param prm_kindbit
     */
    GgafTreeElem(GgafTreeSpace<BIT_SHIFT_NUM>* prm_paSpace, GgafObject* prm_pObject, actorkind prm_kindbit) : GgafObject() ,
            _paSpace(prm_paSpace),
        _pObject(prm_pObject) {
        _kindbit = prm_kindbit;
        _pSpace_current = nullptr;
        _pNext = nullptr;
        _pPrev = nullptr;
        _pRegLinkNext = nullptr;
    }

    void dump() {
        _TRACE_N_("o");
    }

    virtual ~GgafTreeElem() {
    }
};

}
#endif /*GGAFCORE_GGAFTREEELEM_H_*/

