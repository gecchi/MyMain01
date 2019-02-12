#ifndef GGAF_CORE_GROUPHEAD_H_
#define GGAF_CORE_GROUPHEAD_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/Actor.h"

namespace GgafCore {

/**
 * �c��(GroupHead)�N���X .
 * �Ƃ���Ӗ������œZ�����A�N�^�[�B�̃c���[���_�Ɉʒu����A�N�^�[�ł��B<BR>
 * ������w��ʁx���Ӗ��t����������������A�N�^�[�ŁA��ۂȃA�N�^�[�ł͂���܂���B<BR>
 * �c���z���̑S�ẴA�N�^�[�́w��ʁx�́A�c���́w��ʁx�ƈ�v����B�Ƃ����d�g�݂ɂȂ��Ă��܂��B<BR>
 * �w��ʁx�Ƃ́A�����蔻�莞�� [���@�̒e]��[�G�{��] �� [] �̒��g�̎����w���܂��B�i���ނƕ\�����ׂ��Ȃ̂�������܂���j<BR>
 * �c���͔z���̃A�N�^�[�����ł���ƁA���t���[���Ɏ��g���₵���Ȃ��Ď��E���܂��B�����������Ȃ�����͖��Ӗ��ł��I<BR>
 * �����(SceneMediator)�̒����̎q�A�N�^�[�́A�S�ĕK�����̒c���ɂȂ��Ă��܂��B<BR>
 * �܂��A�c���z���̃A�N�^�[�ɁA����ɒc�������݂��邱�Ƃ��\�ł��B<BR>
 * �A���c���̒��ڔz���ɒc���͒u���܂���B����́A�c���̔z���ɂ͏��Ȃ��Ƃ���l�͕��ʂ̃A�N�^�[�����݂��Ȃ���΂����Ȃ��Ƃ����d�g�ݏ�̖��ł��B<BR>
 * �����̒c�����o�����[�̃A�N�^�[�̎�ʂ́A���߂̒c���̎�ʂ��D�悳��܂��B<BR>
 * ���⑫�F�c���N���X(GroupHead)�̃I�u�W�F�N�g�C���[�W�}��<BR>
 * <PRE>
 *         �E�E�E�� Scene �� Scene �́E�E�E
 *                   �b
 *                   �������o�[
 *           SceneMediator  �i��1��Scene�ɕK���P��Mediator�j
 *               �b
 *               �bgetChildFirst()
 *               ��
 *     GroupHead �� GroupHead �� GroupHead ��
 *           �b                �b                �b
 *           �bgetChildFirst()   �b                �b
 *           ��                ��                ��
 *     �L�����̃A�N�^�[�B  �L�����̃A�N�^�[�B  �L�����̃A�N�^�[
 * </PRE>
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GroupHead : public Actor {

public:
    /** [r]�V�[������� */
    SceneMediator* _pSceneMediator;
    /** [r/w]�{�O���[�v�̎�� */
    kind_t _kind;

public:
    GroupHead(kind_t prm_kind, Status* prm_pStat = nullptr);

    void setKind(kind_t prm_kind);

    /**
     * �������� .
     */
    void initialize() override {
    }

    void processBehavior() override {
    }
    void processPreJudgement() override {
    }
    /**
     * ���t���[����GroupHead���菈�� .
     * �q��������Ύ����I�Ɏ��S���鏈���ɂȂ��Ă���B
     */
    void processJudgement() override {
        if (getChildFirst() == nullptr) {
            //�c�������Ȃ���΃V�[������҂��s�v�A���悤�Ȃ�B
            sayonara();
        }
    }

    void processPreDraw() override {
    }

    void processDraw() override {
    }

    void processAfterDraw() override {
    }

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void processFinal() override {
    }

    /**
     * �����蔻��s�v�̂��ߏ��false��Ԃ� .
     * @param prm_pOtherActor
     * @return false
     */
    bool processHitChkLogic(Actor* prm_pOtherActor) override {
        return false;
    }

    void onHit(const Actor* prm_pOtherActor) override {
    }

    /**
     * ���g���Ǘ�����Ă���V�[���̒���҂��擾 .
     * @return �V�[�������
     */
    SceneMediator* getMySceneMediator();

    /**
     * �V�[�������(SceneMediator)��ݒ� .
     * @param prm_pSceneMediator �����
     */
    void setMySceneMediator(SceneMediator* prm_pSceneMediator);

    /**
     * �_�ɉy�� .
     * @return    �Ă΂�ďo�Ă����_
     */
    God* askGod();

    void updateActiveInTheTree() override;


    virtual ~GroupHead();
};

}
#endif /*GGAF_CORE_GROUPHEADACTOR_H_*/
