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
    static int _iSeq;

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

    virtual std::string toString();
    virtual ~GgafObject();
};

}
#endif /*GGAFOBJECT_H_*/
