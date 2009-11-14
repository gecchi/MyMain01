#ifndef GGAFLINEAROCTREESPACE_H_
#define GGAFLINEAROCTREESPACE_H_
namespace GgafCore {

/**
 * ��ԃN���X .
 */
class GgafLinearOctreeSpace {
public:
    /** �v�f�̐擪 */
    int _my_index;
    /** �������Ă�v�f�̎�ʏ�� */
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

