#ifndef GGAFCORE_GGAFOBJECT_H_
#define GGAFCORE_GGAFOBJECT_H_
namespace GgafCore {

/** �N���X��� */
typedef uint32_t classkind;

/**
 * ���N���X
 * @version 1.00
 * @since 2007/12/24
 * @author Masatoshi Tsuge
 */
class GgafObject {
    static uint64_t _obj_seq;
    uint64_t _id;
public:

    /** [r]�C���X�^���X��� */
    classkind _obj_class;

public:
    GgafObject();
    uint64_t getId() {
        return _id;
    }
    /**
     * ���ʖ��擾 .
     * @return ���ʖ�
     */
    virtual char* toString();

    /**
     * �I�u�W�F�N�g�����̃N���X�R�����𒲂ׂ�B
     * _obj_class �����o�ϐ��� Obj_xxxx �}�N���萔���ݒ肳��Ă��邱�Ƃ��O��B
     * @param prm_Obj_xxxx ���ׂ�N���X�̃}�N���萔
     * @return
     */
    virtual bool instanceOf(classkind prm_Obj_xxxx) {
        if ((_obj_class & prm_Obj_xxxx) == prm_Obj_xxxx) {
            return true;
        } else {
            return false;
        }
    }

    virtual ~GgafObject();
};

}
#endif /*GGAFCORE_GGAFOBJECT_H_*/
