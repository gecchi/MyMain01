#ifndef GGAFCORE_GGAFGROUPHEAD_H_
#define GGAFCORE_GGAFGROUPHEAD_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/GgafActor.h"

namespace GgafCore {

/**
 * �c��(GgafGroupHead)�N���X .
 * �Ƃ���Ӗ������œZ�����A�N�^�[�B�̃c���[���_�Ɉʒu����A�N�^�[�ł��B<BR>
 * ������w��ʁx���Ӗ��t����������������A�N�^�[�ŁA��ۂȃA�N�^�[�ł͂���܂���B<BR>
 * �c���z���̑S�ẴA�N�^�[�́w��ʁx�́A�c���́w��ʁx�ƈ�v����B�Ƃ����d�g�݂ɂȂ��Ă��܂��B<BR>
 * �w��ʁx�Ƃ́A�����蔻�莞�� [���@�̒e]��[�G�{��] �� [] �̒��g�̎����w���܂��B�i���ނƕ\�����ׂ��Ȃ̂�������܂���j<BR>
 * �c���͔z���̃A�N�^�[�����ł���ƁA���t���[���Ɏ��g���₵���Ȃ��Ď��E���܂��B�����������Ȃ�����͖��Ӗ��ł��I<BR>
 * �����(GgafSceneMediator)�̒����̃T�u�A�N�^�[�́A�S�ĕK�����̒c���ɂȂ��Ă��܂��B<BR>
 * �܂��A�c���z���̃A�N�^�[�ɁA����ɒc�������݂��邱�Ƃ��\�ł��B<BR>
 * �A���c���̒��ڔz���ɒc���͒u���܂���B����́A�c���̔z���ɂ͏��Ȃ��Ƃ���l�͕��ʂ̃A�N�^�[�����݂��Ȃ���΂����Ȃ��Ƃ����d�g�ݏ�̖��ł��B<BR>
 * �����̒c�����o�����[�̃A�N�^�[�̎�ʂ́A���߂̒c���̎�ʂ��D�悳��܂��B<BR>
 * ���⑫�F�c���N���X(GgafGroupHead)�̃I�u�W�F�N�g�C���[�W�}��<BR>
 * <PRE>
 *         �E�E�E�� GgafScene �� GgafScene �́E�E�E
 *                   �b
 *                   �������o�[
 *           GgafSceneMediator  �i��1��Scene�ɕK���P��Mediator�j
 *               �b
 *               �bgetSubFirst()
 *               ��
 *     GgafGroupHead �� GgafGroupHead �� GgafGroupHead ��
 *           �b                �b                �b
 *           �bgetSubFirst()   �b                �b
 *           ��                ��                ��
 *     �L�����̃A�N�^�[�B  �L�����̃A�N�^�[�B  �L�����̃A�N�^�[
 * </PRE>
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafGroupHead : public GgafActor {

public:
    /** [r]�V�[������� */
    GgafSceneMediator* _pSceneMediator;
    /** [r/w]�{�O���[�v�̎�� */
    kind_t _kind;

public:
    GgafGroupHead(kind_t prm_kind, GgafStatus* prm_pStat = nullptr);

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
     * ���t���[����GgafGroupHead���菈�� .
     * �T�u��������Ύ����I�Ɏ��S���鏈���ɂȂ��Ă���B
     */
    void processJudgement() override {
        if (getSubFirst() == nullptr) {
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
    bool processHitChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }

    void onHit(const GgafActor* prm_pOtherActor) override {
    }

    /**
     * ���g���Ǘ�����Ă���V�[���̒���҂��擾 .
     * @return �V�[�������
     */
    GgafSceneMediator* getMySceneMediator();

    /**
     * �V�[�������(GgafSceneMediator)��ݒ� .
     * @param prm_pSceneMediator �����
     */
    void setMySceneMediator(GgafSceneMediator* prm_pSceneMediator);

    /**
     * �_�ɉy�� .
     * @return    �Ă΂�ďo�Ă����_
     */
    GgafGod* askGod();

    void updateActiveInTheTree() override;


    virtual ~GgafGroupHead();
};

}
#endif /*GGAFCORE_GGAFGROUPHEADACTOR_H_*/
