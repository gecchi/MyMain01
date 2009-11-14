#ifndef GGAFLINEAROCTREESPACE_H_
#define GGAFLINEAROCTREESPACE_H_
namespace GgafCore {

/**
 * 空間クラス .
 */
class GgafLinearOctreeSpace {
public:
    /** 要素の先頭 */
    int _my_index;
    /** 所属してる要素の種別情報 */
    DWORD _kindinfobit;
    GgafLinearOctreeElem* _pElemFirst;
    GgafLinearOctreeElem* _pElemLast;
    GgafLinearOctreeSpace() {
        _pElemFirst = NULL;
        _pElemLast = NULL;
        _kindinfobit = 0;
        _my_index -1;
    }
    void dump();
    virtual ~GgafLinearOctreeSpace();
};


}
#endif /*GGAFLINEAROCTREESPACE_H_*/

