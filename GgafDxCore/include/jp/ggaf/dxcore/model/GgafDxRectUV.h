#ifndef GGAFDXUV_H_
#define GGAFDXUV_H_
namespace GgafDxCore {

/**
 * �e�N�X�`���[��U,V���W�R���e�i.
 * @version 1.00
 * @since 2008/02/19
 * @author Masatoshi Tsuge
 */
class GgafDxRectUV : public GgafCore::GgafObject {

    struct UV {
        float tu;
        float tv;
    };

public:
    /** �e�N�X�`���[���W�P�Z�b�g�̔z�� */
    UV _aUV[4];

    GgafDxRectUV();

    virtual ~GgafDxRectUV();
};

}
#endif /*GGAFDXUV_H_*/
