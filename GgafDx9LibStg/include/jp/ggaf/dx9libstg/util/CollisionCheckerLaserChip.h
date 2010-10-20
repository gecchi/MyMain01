#ifndef COLLISIONCHECKERLASERCHIP_H_
#define COLLISIONCHECKERLASERCHIP_H_
namespace GgafDx9LibStg {

/**
 * ���[�U�[�`�b�v�Փ˃`�F�b�J�[�N���X.
 * @version 1.00
 * @since 2010/10/20
 * @author Masatoshi Tsuge
 */
class CollisionCheckerLaserChip : public CollisionChecker {

public:

    CollisionCheckerLaserChip(GgafDx9Core::GgafDx9GeometricActor* prm_pActor);
    /**
     * ���g�̔���̈�Ƒ��̓����蔻��̈�ƐڐG���Ă��邩���ׂ�
     * @param prm_pOtherChecker ���̓����蔻��̈�
     * @return true:�������Ă��� / false:�������Ă��Ȃ�
     */
    virtual bool isHit(GgafDx9Core::GgafDx9Checker* prm_pOtherChecker) override;

    virtual ~CollisionCheckerLaserChip();
};

}
#endif /*COLLISIONCHECKERLASERCHIP_H_*/

