#ifndef GGAFDX9HITAREA_H_
#define GGAFDX9HITAREA_H_
namespace GgafDx9Core {

/**
 * �����蔻��̈�C���^�[�t�F�C�X�N���X
 * @version 1.00
 * @since 2009/08/25
 * @author Masatoshi Tsuge
 */
class GgafDx9HitArea : public GgafCore::GgafObject {

public:

    int _iAreaNum;

    GgafDx9HitArea(int prm_iAreaNum);

    virtual ~GgafDx9HitArea();
};

}
#endif /*GGAFDX9HITAREA_H_*/
