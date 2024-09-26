#ifndef GGAF_CORE_ITREENODEELEM_H_
#define GGAF_CORE_ITREENODEELEM_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/util/Util.h"

namespace GgafCore {

/**
 * 線形N分木配列用空間にぶら下がる要素クラス .
 * @version 1.00
 * @since 2022/12/16
 * @author Masatoshi Tsuge
 */
class ITreeNodeElem  {
public:
    /** [r]要素オブジェクトの種別 */
    kind_t _kind;
//    kind_t _sub_kind;
    /** [r]空間に登録された要素（NodeSpace._pRootNodeElem）にぶら下がる次要素 */
    ITreeNodeElem* _pNextNodeElem;
    /**
     * コンストラクタ .
     * @param prm_pObject 対象オブジェクト(キャラクタなどN分木で管理したい実際の値)
     */
    ITreeNodeElem() {
        _kind = 0;
//        _sub_kind = 0;
        _pNextNodeElem = nullptr;
    }

    void dump() {
        _TRACE_N_("("<<UTIL::dec2hex(_kind)<<")");
    }

    virtual ~ITreeNodeElem() {
    }
};

}
#endif /*GGAF_CORE_ITREENODEELEM_H_*/

