#ifndef GGAF_CORE_OBJECT_H_
#define GGAF_CORE_OBJECT_H_
#include "jp/ggaf/GgafCommonHeader.h"

#ifndef _MSC_VER
    #include <atomic>
#endif
#include <string>

namespace GgafCore {

/**
 * ���N���X
 * @version 1.00
 * @since 2007/12/24
 * @author Masatoshi Tsuge
 */
class Object {
public:
#ifdef _MSC_VER
    //x86�nVC�Ȃ�΃A�g�~�b�N�������邩���E�E64bit�ł��H�H�E�E�E�B
    /** �C���X�^���XID�̃V�[�N�G���X */
    static uint64_t _obj_seq;
#else
    /** �C���X�^���XID�̃V�[�N�G���X */
    static std::atomic<uint64_t> _obj_seq;
#endif
    /** [r]�C���X�^���XID(�V�[�N�G���X) */
    uint64_t _id;
    /** [r]�C���X�^���X��� */
    uint64_t _obj_class;

public:
    Object();

    /**
     * �C���X�^���XID���擾 .
     * @return �C���X�^���XID
     */
    inline uint64_t getId() {
        return _id;
    }

    /**
     * ���ʖ��擾 .
     * @return ���ʖ�
     */
    virtual std::string toString();

    /**
     * �I�u�W�F�N�g�����̃N���X�R�����𒲂ׂ�B
     * _obj_class �����o�ϐ��� Obj_xxxx �}�N���萔���ݒ肳��Ă��邱�Ƃ��O��B
     * @param prm_Obj_xxxx ���ׂ�N���X�̃}�N���萔
     * @return
     */
    inline virtual bool instanceOf(uint64_t Obj_xxxx) const {
        if ((_obj_class & Obj_xxxx) == Obj_xxxx) {
            return true;
        } else {
            return false;
        }
    }

    virtual ~Object();
};

}
#endif /*GGAF_CORE_OBJECT_H_*/
