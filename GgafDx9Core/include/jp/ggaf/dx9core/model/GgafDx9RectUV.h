#ifndef GGAFDX9UV_H_
#define GGAFDX9UV_H_
namespace GgafDx9Core {

/**
 * �e�N�X�`���[��U,V���W�R���e�i.
 */
class GgafDx9RectUV : public GgafCore::GgafObject {

    struct UV {
        float tu;
        float tv;
    };

public:
    /** �e�N�X�`���[���W�P�Z�b�g�̔z�� */
    UV _aUV[4];

    GgafDx9RectUV();

    virtual ~GgafDx9RectUV();
};

}
#endif /*GGAFDX9UV_H_*/
