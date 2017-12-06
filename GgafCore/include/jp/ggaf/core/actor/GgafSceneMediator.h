#ifndef GGAFCORE_GGAFSCENEMEDIATOR_H_
#define GGAFCORE_GGAFSCENEMEDIATOR_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/GgafActor.h"

namespace GgafCore {

/**
 * �V�[���̒���҃N���X .
 * �c��(GgafGroupHead)�̐e�K�w�̃A�N�^�[�ŁA�c���B���Ǘ����܂��B<BR>
 * �܂��A�V�[���N���X�Ƃ̋��n�����s�����ʂȃA�N�^�[�ł�����܂��B<BR>
 * �V�[���N���X�ƃV�[������҂͕��ʂ�hasA�̊֌W�ł��B�i����҂ƒc���͊K�w�֌W�ɂȂ��Ă��܂��j<BR>
 * �S�ẴV�[��(GgafSceane�I�u�W�F�N�g)�ɕK���P�l�V�[������҂����܂��B<BR>
 * ����҂́A�A�N�^�[�B�c���[�̍ł����_�Ɉʒu���܂��B<BR>
 * �����(GgafSceneMediator)�̃T�u�A�N�^�[�͕K���c��(GgafGroupHead)�ɂȂ��Ă��܂��B<BR>
 * ����ɒc���̉��ɕ��ʂ̃A�N�^�[�����܂��B<BR>
 * ����҂ւ̃��\�b�h���s�́A���̔z���S�Ă̒c���{�A�N�^�[�ւ̎w���ƂȂ�܂��B<BR>
 * �c��(GgafGroupHead)�̉�������킹�ĎQ�Ƃ��ĉ������B
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafSceneMediator : public GgafActor {

private:
    /**
     * �g�p�s�� .
     */
    GgafSceneMediator* extract() override {
        throwGgafCriticalException("GgafSceneMediator �� extract() �͎��s�ł��܂���Bname="<<getName());
        return (GgafSceneMediator*)nullptr;
    }

public:
    GgafSceneMediator(GgafScene* prm_pScene_platform);

    /**
     * ��������<BR>
     */
    void initialize() override {
    }

    void processBehavior() override {
    }

    void processSettlementBehavior() override {
    }

    void processPreJudgement() override {
    }

    void processJudgement() override {
    }

    void processPreDraw() override {
    }

    void processDraw() override {
    }

    void processAfterDraw() override {
    }


    void processFinal() override {
    }


    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void throwEventUpperTree(hashval prm_no, void* prm_pSource) override;
    void throwEventUpperTree(hashval prm_no) override {
        throwEventUpperTree(prm_no, this);
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

    void remove();

    /**
     * �O���[�v�Ƃ��Ĉ����̃A�N�^�[���T�u�A�N�^�[�ɒǉ����܂� .
     * ����͎�����GgafGroupHead�I�u�W�F�N�g���Ԃɑ}������܂��B<BR>
     * ���������ăO���[�v��ʂƋ��ɓo�^���K�v�ł��B<BR>
     * ��ʂƂ́A�����Ő�������� GgafGroupHead�� �ɂ��g�p����܂��B<BR>
     * GgafGroupHead�I�u�W�F�N�g �͏����ʓo�^��������������A�Q��ڈȍ~�̓����ʓo�^�́A<BR>
     * ������ GgafGroupHead�I�u�W�F�N�g�̃T�u�ɒǉ�����܂��B<BR>
     * <pre>
     * ���g�p��P��
     *
     *  addSubGroup(KIND_XXX, pActor);
     *
     *  �Ƃ����ꍇ�A�K�w�\���͎��̂悤�ɂȂ�B
     *
     *  this
     *    |
     *    +- pObject(GgafGroupHead[KIND_XXX])
     *         |
     *         +- pActor
     *
     *
     * ���g�p��Q��
     *
     * addSubGroup(KIND_AAA, pActor01);
     * addSubGroup(KIND_BBB, pActor02);
     * addSubGroup(KIND_AAA, pActor03);
     *
     * �Ƃ����ꍇ�A�K�w�\���͎��̂悤�ɂȂ�B
     *
     *  this
     *    |
     *    +- pObject(GgafGroupHead[KIND_AAA]) -- pObject(GgafGroupHead[KIND_BBB])
     *         |                                    |
     *         +- pActor01 -- pActor03              + pActor02
     * </pre>
     * �⑫�F������ prm_pMainActor �ȉ��S�ẴA�N�^�[�Ɋւ��āA
     *       �E�����V�[�������o (_pScene_platform)
     *       �E����҃A�N�^�[�����o(_pSceneMediator)
     *       �E�c���A�N�^�[�����o(_pGroupHead) ���A�����ʂɑ��̒c���������ꍇ�͂����܂�
     *       �̍X�V���s���܂��B
     * @param   prm_kind    ��ʖ��i��GgafGroupHead���j
     * @param   prm_pMainActor   �o�^����A�N�^�[
     */
    GgafGroupHead* addSubGroup(kind_t prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * �P��GgafActor�A������GgafDestructActor���P�Ɛe�ƂȂ�GgafActor�A���̂�<BR>
     * ��ʂ͈����q�A�N�^�[�̃X�e�[�^�X(getStatus())�̍��� 'STAT_DEFAULT_ACTOR_KIND' �̒l���A��ʂƂ���
     * �㏑���R�s�[�����B
     * �{�֐��͂̕��I������ prm_pActor �� GgafGroupHead �̎q�A�N�^�[�Ƃ��Ă��邾���ł���B<BR>
     * @param   prm_pMainActor   �o�^����A�N�^�[
     */
    GgafGroupHead* addSubGroup(GgafMainActor* prm_pMainActor);

    /**
     * �T�u�̒c���A�N�^�[���擾�A�������nullptr���A��
     * @param prm_kind
     * @return
     */
    GgafGroupHead* searchSubGroupHead(kind_t prm_kind);

    void updateActiveInTheTree() override;

    /**
     * �_�ɉy�� .
     * @return    �Ă΂�ďo�Ă����_
     */
    GgafGod* askGod();

    GgafActor* bring(hashval prm_name_hash);

    virtual ~GgafSceneMediator();
};

}
#endif /**GGAFSCENEMEDIATOR_H_*/
