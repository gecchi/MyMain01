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
    static const char* NANASHI;
    static int _iSeq;

public:
    int _id;
    /** [r]�m�[�h���ʖ�(50�����܂�) */
    char* _name;
    /** [r]�C���X�^���X��� */
    UINT32 _obj_class;

    GgafObject(const char* prm_name = GgafObject::NANASHI);

    /**
     * ���O�擾 .
     * @return ���O
     */
    virtual char* getName() {
        return _name;
    }

    virtual std::string toString();
    virtual ~GgafObject();
};

}
#endif /*GGAFOBJECT_H_*/
