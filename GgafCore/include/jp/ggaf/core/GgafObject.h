#ifndef GGAFOBJECT_H_
#define GGAFOBJECT_H_
namespace GgafCore {

/**
 * ���N���X
 * @version 1.00
 * @since 2007/12/24
 * @author Masatoshi Tsuge
 */
class GgafObject {
    static int _obj_seq;

public:
    int _id;
    /** [r]�C���X�^���X��� */
    UINT32 _obj_class;

    GgafObject();

    /**
     * ���ʖ��擾 .
     * @return ���ʖ�
     */
//    virtual char* getName();

    virtual char* toString();


    virtual bool instanceOf(UINT32 prm_Obj_xxxx) {
        if ((_obj_class & prm_Obj_xxxx) == prm_Obj_xxxx) {
            return true;
        } else {
            return false;
        }
    }

    virtual ~GgafObject();
};

}
#endif /*GGAFOBJECT_H_*/
