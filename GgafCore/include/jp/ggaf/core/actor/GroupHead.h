#ifndef GGAF_CORE_GROUPHEAD_H_
#define GGAF_CORE_GROUPHEAD_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/actor/Actor.h"

namespace GgafCore {

/**
 * �c��(GroupHead)�N���X .
 * �Ƃ���Ӗ������œZ�����A�N�^�[�B�̃c���[���_�Ɉʒu����A�N�^�[�ł��B<BR>
 * ������w��ʁx���Ӗ��t����������������A�N�^�[�ŁA��ۂȃA�N�^�[�ł͂���܂���B<BR>
 * ���̃A�N�^�[�̑��݈Ӌ`�́A��ʂ�Z�߂Đ؂�ւ��邱�Ƃ��ł��鎖�ł��B<BR>
 * �c���z���̑S�ẴA�N�^�[�́w��ʁx�́A�c���́w��ʁx�ƈ�v����B�Ƃ����d�g�݂ɂȂ��Ă��܂��B<BR>
 * �w��ʁx�Ƃ́A�����蔻�莞�� [���@�̒e]��[�G�{��] �� [] �̒��g�̎����w���܂��B�i���ނƕ\�����ׂ��Ȃ̂�������܂���j<BR>
 * �c���͔z���̃A�N�^�[�����ł���ƁA���t���[���Ɏ��g���₵���Ȃ��Ď��E���܂��B�����������Ȃ�����͖��Ӗ��ł��I<BR>
 * �`�[�t(SceneChief)�̒����̎q�A�N�^�[�́A�S�ĕK�����̒c���ɂȂ��Ă��܂��B<BR>
 * �܂��A�c���z���̃A�N�^�[�ɁA����ɒc�������݂��邱�Ƃ��\�ł��B<BR>
 * �A���c���̒��ڔz���ɒc���͒u���܂���B����́A�c���̔z���ɂ͏��Ȃ��Ƃ���l�͕��ʂ̃A�N�^�[�����݂��Ȃ���΂����Ȃ��Ƃ����d�g�ݏ�̖��ł��B<BR>
 * �����̒c�����o�����[�̃A�N�^�[�̎�ʂ́A���߂̒c���̎�ʂ��D�悳��܂��B<BR>
 * ���⑫�F�c���N���X(GroupHead)�̃I�u�W�F�N�g�C���[�W�}��<BR>
 * <PRE>
 *         �E�E�E�� Scene �� Scene �́E�E�E
 *                   �b
 *                   �������o�[
 *           SceneChief  �i��1��Scene�ɕK���P��Chief�j
 *               �b
 *               �bgetChildFirst()
 *               ��
 *          GroupHead �� GroupHead �� GroupHead ��
 *           �b                �b                �b
 *           �bgetChildFirst() �b                �b
 *           ��                ��                ��
 *     �L�����̃A�N�^�[�B  �L�����̃A�N�^�[�B  �L�����̃A�N�^�[
 * </PRE>
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GroupHead : public Actor {

public:
    /** [r]�V�[���`�[�t */
    SceneChief* _pSceneChief;
    /** [r/w]�z���A�N�^�[�O���[�v�̎�� */
    kind_t _kind;

public:
    GroupHead(kind_t prm_kind);

    /**
     * �z���A�N�^�[�O���[�v�̎�ʂ�ݒ� .
     * @param prm_kind �A�N�^�[�O���[�v�̎��
     */
    void setKind(kind_t prm_kind);

    /**
     * �������� .
     */
    void initialize() override {
    }

    void processBehavior() override {
    }
    /**
     * ���t���[����GroupHead���菈�� .
     * �q��������Ύ����I�Ɏ��S���鏈���ɂȂ��Ă���B
     */
    void processJudgement() override {
        if (getChildFirst() == nullptr) {
            //�c�������Ȃ���΃V�[���`�[�t���s�v�A���悤�Ȃ�B
            sayonara();
        }
    }
    bool processHitChkLogic(Actor* prm_pOtherActor) override {
        return false;
    }
    void processPreDraw() override {
    }

    void processDraw() override {
    }

    void processAfterDraw() override {
    }

    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    void processFinal() override {
    }
    void onHit(const Actor* prm_pOtherActor) override {
    }

    /**
     * ���g���Ǘ�����Ă���V�[���̃`�[�t���擾 .
     * @return �V�[���`�[�t
     */
    SceneChief* getSceneChief();

    /**
     * �V�[���`�[�t(SceneChief)��ݒ� .
     * @param prm_pSceneChief �`�[�t
     */
    void setSceneChief(SceneChief* prm_pSceneChief);

    /**
     * �Ǘ��҂ɉy�� .
     * @return    �Ă΂�ďo�Ă����Ǘ���
     */
    Caretaker* askCaretaker();

    void updateActiveInTheTree() override;


    virtual ~GroupHead();
};

}
#endif /*GGAF_CORE_GROUPHEADACTOR_H_*/
