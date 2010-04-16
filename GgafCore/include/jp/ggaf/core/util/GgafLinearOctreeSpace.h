﻿#ifndef GGAFLINEAROCTREESPACE_H_
#define GGAFLINEAROCTREESPACE_H_
namespace GgafCore {

/**
 * 線形八分木配列用空間クラス .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class GgafLinearOctreeSpace {
public:
    /** 線形八分木配列の自身の要素番号 */
    int _my_index;
    /** 所属してる要素の種別情報 */
    DWORD _kindinfobit;
    /** ぶら下がる要素の先頭 */
    GgafLinearOctreeElem* _pElemFirst;
    /** ぶら下がる要素の末尾 */
    GgafLinearOctreeElem* _pElemLast;

    /**
     * コンストラクタ
     * @return
     */
    GgafLinearOctreeSpace() {
        _pElemFirst = NULL;
        _pElemLast = NULL;
        _kindinfobit = 0;
        _my_index = -1; //ありえない-1を入れておく
    }

    void dump();

    virtual ~GgafLinearOctreeSpace();
};


}
#endif /*GGAFLINEAROCTREESPACE_H_*/

