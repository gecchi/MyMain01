#ifndef GGAFLINEAROCTREESPACE_H_
#define GGAFLINEAROCTREESPACE_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafCore {

/**
 * ���`�����ؔz��p��ԃN���X .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class GgafLinearOctreeSpace : public GgafObject {

public:
    /** [r]���`�����ؔz��̎��g�̗v�f�ԍ� */
    uint32_t _my_index;
    /** [r]�������Ă�v�f�̎�ʏ�� */
    uint32_t _kindinfobit;
    /** [r]�Ԃ牺����v�f�̐擪 */
    GgafLinearOctreeElem* _pElem_first;
    /** [r]�Ԃ牺����v�f�̖��� */
    GgafLinearOctreeElem* _pElem_last;

public:
    /**
     * �R���X�g���N�^
     * @return
     */
    GgafLinearOctreeSpace() : GgafObject() {
        _pElem_first = nullptr;
        _pElem_last = nullptr;
        _kindinfobit = 0;
        _my_index = 0xffffffff; //���肦�Ȃ�0xffffffff�����Ă���
    }

    void dump();

    virtual ~GgafLinearOctreeSpace();
};


}
#endif /*GGAFLINEAROCTREESPACE_H_*/

