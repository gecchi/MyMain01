#ifndef GGAFDIRECTOR_H_
#define GGAFDIRECTOR_H_
namespace GgafCore {

/**
 * �ēN���X .
 * �c��(GgafGroupHead)�̐e�K�w�̃A�N�^�[�ŁA�c���B���Ǘ����܂��B<BR>
 * �܂��A�V�[���N���X�Ƃ̋��n�����s�����ʂȃA�N�^�[�ł�����܂��B<BR>
 * �V�[���N���X�Ɗē͕��ʂ�hasA�̊֌W�ł��B�i�ēƒc���͊K�w�֌W�ɂȂ��Ă��܂��j<BR>
 * �S�ẴV�[��(GgafSceane�I�u�W�F�N�g)�ɕK���P�l�ē̂����܂��B<BR>
 * �ē́A�K���A�N�^�[�B�c���[�̍ł����_�Ɉʒu���܂��B<BR>
 * �ē�(GgafDirector)�̃T�u�A�N�^�[�͕K���c��(GgafGroupHead)�ɂȂ��Ă��܂��B<BR>
 * ����ɒc���̉��ɕ��ʂ̃A�N�^�[�����܂��B<BR>
 * �ēւ̃��\�b�h���s�́A���̔z���S�Ă̒c���{�A�N�^�[�ւ̎w���ƂȂ�܂��B<BR>
 * �c��(GgafGroupHead)�̉�������킹�ĎQ�Ƃ��ĉ������B
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafDirector : public GgafActor {

private:

    /**
     * �g�p�s�� .
     */
    GgafDirector* extract() override {
        throwGgafCriticalException("GgafDirector �� extract() �͎��s�ł��܂���Bname="<<getName());
    }

public:
    GgafDirector(GgafScene* prm_pScene_Platform);

    /**
     * ��������<BR>
     */
    void initialize() override {
    }

    void processBehavior() override {
    }

    void processSettlementBehavior() override {
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

    void throwEventToUpperTree(hashval prm_no, void* prm_pSource) override {
        GgafScene* s = getPlatformScene();
        if (s) {
            s->throwEventToUpperTree(prm_no, this); //��������ʂ͋��Ȃ��B�����ŏ����V�[���֓�����
        }
    }


    /**
     * �����蔻��s�v�̂��ߏ��false��Ԃ� .
     * @param prm_pOtherActor
     * @return false
     */
    bool processHitChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }

    void onHit(GgafActor* prm_pOtherActor) override {
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
     *       �E�����V�[�������o (_pScene_Platform)
     *       �E�ēA�N�^�[�����o(_pDirector)
     *       �E�c���A�N�^�[�����o(_pGroupHead) ���A�����ʂɑ��̒c���������ꍇ�͂����܂�
     *       �̍X�V���s���܂��B
     * @param   prm_kind    ��ʖ��i��GgafGroupHead���j
     * @param   prm_pMainActor   �o�^����A�N�^�[
     */
    GgafGroupHead* addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * �P��GgafActor�A������GgafDummyActor���P�Ɛe�ƂȂ�GgafActor�A���̂�<BR>
     * ��ʂ͈����q�A�N�^�[�̃X�e�[�^�X(_pStatus)�̍��� 'STAT_DEFAULT_ACTOR_KIND' �̒l���A��ʂƂ���
     * �㏑���R�s�[�����B
     * �{�֐��͂̕��I������ prm_pActor �� GgafGroupHead �̎q�A�N�^�[�Ƃ��Ă��邾���ł���B<BR>
     * @param   prm_pMainActor   �o�^����A�N�^�[
     */
    GgafGroupHead* addSubGroup(GgafMainActor* prm_pMainActor);

    /**
     * �T�u�̒c���A�N�^�[���擾�A�������NULL���A��
     * @param prm_kind
     * @return
     */
    GgafGroupHead* searchSubGroupHead(actorkind prm_kind);



    /**
     * �_�ɉy�� .
     * @return	�Ă΂�ďo�Ă����_
     */
    GgafGod* askGod();

    virtual ~GgafDirector();
};

}
#endif /**GGAFDIRECTOR_H_*/
