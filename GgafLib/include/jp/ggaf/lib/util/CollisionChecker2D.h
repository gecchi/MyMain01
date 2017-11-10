#ifndef GGAFLIB_COLLISIONCHECKER2D_H_
#define GGAFLIB_COLLISIONCHECKER2D_H_
#include "GgafLibCommonHeader.h"
#include "CollisionChecker.h"

#include "jp/ggaf/core/util/GgafTreeElem.hpp"
namespace GgafLib {

/**
 * 2D�p�Փ˃`�F�b�J�[�N���X.
 * @version 1.00
 * @since 2017/08/04
 * @author Masatoshi Tsuge
 */
class CollisionChecker2D : public CollisionChecker {

    GgafCore::GgafLinearQuadtree* const _pLinearQuadtree; //TODO:�ǂ��Ɏ������悤���Y�ނ��Ƃ肠�����R�R��

public:
    /** ���`�����ؓo�^�p�v�f */
    GgafCore::GgafTreeElem<2u>* const _pElem;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �����蔻��@�\��ǉ�����Actor
     */
    explicit CollisionChecker2D(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �����蔻��̈�BOX�̉�]���s�ړ��ƁA�����ؓo�^���s���܂� .
     * �����蔻��@�\���g�p����ɂ́A���̃��\�b�h�𖈃t���[�����s����K�v������܂��B<br>
     * �������A�t���[�����[�N�ɑg�ݍ��܂�Ă��邽�߁A�����҂͓��ɋC�ɂ���K�v���Ȃ��B<br>
     * ���݂� GgafDxGeometricActor::processSettlementBehavior ���疈�t���[���R�[������Ă���B<br>
     * ���� processSettlementBehavior() �����ʂŃI�[�o�[���C�h����ꍇ�͋C��t����ׂ��I<br>
     */
    virtual void updateHitArea() override;

    /**
     * ���g�̔���̈�Ƒ��̓����蔻��̈�ƐڐG���Ă��邩���ׂ�
     * @param prm_pOppChecker ���̓����蔻��̈�
     * @return true:�������Ă��� / false:�������Ă��Ȃ�
     */
    bool isHit(const GgafDxCore::GgafDxChecker* const prm_pOppChecker) override;

    virtual ~CollisionChecker2D();
};

}
#endif /*GGAFLIB_COLLISIONCHECKER2D_H_*/
