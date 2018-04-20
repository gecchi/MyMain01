#ifndef GGAFCORE_GGAFOBJECT_H_
#define GGAFCORE_GGAFOBJECT_H_
#include "GgafCommonHeader.h"

#ifndef _MSC_VER
    #include <atomic>
#endif
#include <string>

namespace GgafCore {

/** �m�[�h��� */
typedef uint64_t nodekind;

/**
 * ���N���X
 * @version 1.00
 * @since 2007/12/24
 * @author Masatoshi Tsuge
 */
class GgafObject {
public:
#ifdef _MSC_VER
    //x86�nVC�Ȃ�΃A�g�~�b�N��������E�E64bit�ł��H�H�E�E�E�B
    //�܂�_obj_seq�������Ă�DEBUG�̎��ɂ�����ƕs�ւȂ����Ȃ̂ŁE�E�E�G
    static uint64_t _obj_seq;
#else
    static std::atomic<uint64_t> _obj_seq;
#endif
    uint64_t _id;


    /** [r]�C���X�^���X��� */
    nodekind _obj_class;

public:
    GgafObject();
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
    inline virtual bool instanceOf(nodekind Obj_xxxx) const {
        if ((_obj_class & Obj_xxxx) == Obj_xxxx) {
            return true;
        } else {
            return false;
        }
    }

    virtual ~GgafObject();
};

}
#endif /*GGAFCORE_GGAFOBJECT_H_*/
