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

public:
    /** [r]�C���X�^���X��� */
    UINT32 _obj_class;
    GgafObject();
    virtual std::string toString();
    virtual ~GgafObject();
};

}
#endif /*GGAFOBJECT_H_*/
