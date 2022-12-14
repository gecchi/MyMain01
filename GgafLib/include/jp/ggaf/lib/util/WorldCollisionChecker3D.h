#ifndef GGAF_LIB_WORLDCOLLISIONCHECKER3D_H_
#define GGAF_LIB_WORLDCOLLISIONCHECKER3D_H_
#include "GgafLibCommonHeader.h"
#include "WorldCollisionChecker.h"

#include "jp/ggaf/core/util/lineartree/LinearOctree.hpp"

namespace GgafLib {

/**
 * ���[���h��Ԃ�3D���[�h�p�Փ˃`�F�b�J�[�N���X.
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class WorldCollisionChecker3D : public WorldCollisionChecker {

    GgafCore::LinearOctree<GgafCore::Actor>* const _pWorldLinearOctree; //TODO:�ǂ��Ɏ������悤���Y�ނ��Ƃ肠�����R�R��

public:
    /** ���`�����ؓo�^�p�v�f */
    GgafCore::LinearOctree<GgafCore::Actor>::NodeElem* const _pNodeElem;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �����蔻��@�\��ǉ�����Actor
     */
    explicit WorldCollisionChecker3D(GgafDx::GeometricActor* prm_pActor);

    /**
     * �����蔻��̈�BOX�̉�]���s�ړ��ƁA�����ؓo�^���s���܂� .
     * �����蔻��@�\���g�p����ɂ́A���̃��\�b�h�𖈃t���[�����s����K�v������܂��B<br>
     * �������A�t���[�����[�N�ɑg�ݍ��܂�Ă��邽�߁A�����҂͓��ɋC�ɂ���K�v���Ȃ��B<br>
     * ���݂� GgafDx::GeometricActor::processSettlementBehavior ���疈�t���[���R�[������Ă���B<br>
     * ���� processSettlementBehavior() �����ʂŃI�[�o�[���C�h����ꍇ�͋C��t����ׂ��I<br>
     */
    virtual void updateHitArea() override;

    /**
     * ���g�̔���̈�Ƒ��̓����蔻��̈�ƐڐG���Ă��邩���ׂ�
     * @param prm_pOppChecker ���̓����蔻��̈�
     * @return true:�������Ă��� / false:�������Ă��Ȃ�
     */
    bool isHit(const GgafDx::CollisionChecker* const prm_pOppChecker) override;

    virtual ~WorldCollisionChecker3D();
};

}
#endif /*GGAF_LIB_WORLDCOLLISIONCHECKER3D_H_*/

