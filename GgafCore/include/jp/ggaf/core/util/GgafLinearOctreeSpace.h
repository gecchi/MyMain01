#ifndef GGAFLINEAROCTREESPACE_H_
#define GGAFLINEAROCTREESPACE_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafCore {

/**
 * 線形八分木配列用空間クラス .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class GgafLinearOctreeSpace : public GgafObject {

public:
    /** [r]線形八分木配列の自身の要素番号 */
    uint32_t _my_index;
    /** [r]所属してる要素の種別情報 */
    uint32_t _kindinfobit;
    /** [r]ぶら下がる要素の先頭 */
    GgafLinearOctreeElem* _pElem_first;
    /** [r]ぶら下がる要素の末尾 */
    GgafLinearOctreeElem* _pElem_last;

public:
    /**
     * コンストラクタ
     * @return
     */
    GgafLinearOctreeSpace() : GgafObject() {
        _pElem_first = nullptr;
        _pElem_last = nullptr;
        _kindinfobit = 0;
        _my_index = 0xffffffff; //ありえない0xffffffffを入れておく
    }

    void dump();

    virtual ~GgafLinearOctreeSpace();
};


}
#endif /*GGAFLINEAROCTREESPACE_H_*/

