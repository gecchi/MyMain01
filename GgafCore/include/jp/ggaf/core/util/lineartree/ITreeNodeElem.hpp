#ifndef GGAF_CORE_ITREENODEELEM_H_
#define GGAF_CORE_ITREENODEELEM_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/util/Util.h"

namespace GgafCore {

/**
 * ���`N���ؔz��p��ԂɂԂ牺����v�f�N���X .
 * @version 1.00
 * @since 2022/12/16
 * @author Masatoshi Tsuge
 */
class ITreeNodeElem  {
public:
    /** [r]�v�f�I�u�W�F�N�g�̎�� */
    kind_t _kind;
//    kind_t _sub_kind;
    /** [r]��Ԃɓo�^���ꂽ�v�f�iNodeSpace._pRootNodeElem�j�ɂԂ牺���鎟�v�f */
    ITreeNodeElem* _pNextNodeElem;
    /**
     * �R���X�g���N�^ .
     * @param prm_pObject �ΏۃI�u�W�F�N�g(�L�����N�^�Ȃ�N���؂ŊǗ����������ۂ̒l)
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

