#ifndef GGAF_LIB_COLLISIONCHECKER2D_B_H_
#define GGAF_LIB_COLLISIONCHECKER2D_B_H_
#include "GgafLibCommonHeader.h"
#include "CollisionChecker.h"

#include "jp/ggaf/core/util/TreeElem.hpp"
namespace GgafLib {

/**
 * 2D�p�Փ�(Board�p)�`�F�b�J�[�N���X.
 * @version 1.00
 * @since 2022/09/13
 * @author Masatoshi Tsuge
 */
class CollisionChecker2D_b : public GgafDx::Checker {

    GgafCore::LinearQuadtree_b* const _pLinearQuadtree_b; //TODO:�ǂ��Ɏ������悤���Y�ނ��Ƃ肠�����R�R��

public:
    /** ���`�����ؓo�^�p�v�f */
    GgafCore::TreeElem<2u>* const _pElem;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �����蔻��@�\��ǉ�����Actor
     */
    explicit CollisionChecker2D_b(GgafDx::GeometricActor* prm_pActor);

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
    bool isHit(const GgafDx::Checker* const prm_pOppChecker) override;


    /**
     * �����蔻��̈�v�f�������s�����̂Ƃ��Ē�` .
     * @param prm_index �����蔻��̈�̗v�f�ԍ�
     * @param x1 �����蔻�蒼���̂̍���X���W�iActor���[�J�����W�j
     * @param y1 �����蔻�蒼���̂̍���Y���W�iActor���[�J�����W�j
     * @param x2 �����蔻�蒼���̂̉E��X���W�iActor���[�J�����W�j
     * @param y2 �����蔻�蒼���̂̉E����Y���W�iActor���[�J�����W�j
     */
    void setColliAABox(int prm_index,
                       coord x1, coord y1,
                       coord x2, coord y2 );

    virtual ~CollisionChecker2D_b();
};

}
#endif /*GGAF_LIB_COLLISIONCHECKER2D_B_H_*/

