#ifndef GGAFLORDACTOR_H_
#define GGAFLORDACTOR_H_
namespace GgafCore {

/**
 * �Ǘ��҃N���X .
 * �c��(GgafGroupActor)�̐e�K�w�̃A�N�^�[�ŁA�c���B���Ǘ����܂��B<BR>
 * �܂��A�V�[���N���X�Ƃ̋��n�����s�����ʂȃA�N�^�[�ł�����܂��B<BR>
 * �V�[���N���X�ƊǗ��҂͕��ʂ�hasA�̊֌W�ł��B�i�Ǘ��҂ƒc���͊K�w�֌W�ɂȂ��Ă��܂��j<BR>
 * �S�ẴV�[��(GgafSceane�I�u�W�F�N�g)�ɕK���P�l�Ǘ��҂̃C���^���X������܂��B<BR>
 * �Ǘ��҂́A�K���A�N�^�[�B�c���[�̍ł����_�Ɉʒu���܂��B<BR>
 * �Ǘ���(GgafLordActor)�̃T�u�A�N�^�[�͕K���c��(GgafGroupActor)�ɂȂ��Ă��܂��B<BR>
 * �c��(GgafGroupActor)�̉�������킹�ĎQ�Ƃ��ĉ������B
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafLordActor : public GgafActor {
public:
    GgafLordActor(GgafScene* prm_pScene_Platform);

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


    void catchEvent(int prm_no) override {
    }


    virtual void throwUpEvent(int prm_no) {
        GgafScene* s = getPlatformScene();
        if (s != NULL) {
            s->throwUpEvent(prm_no); //��������ʂ͋��Ȃ��B�����ŏ����V�[���֓�����
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
     * ����͎�����GgafGroupActor�I�u�W�F�N�g���Ԃɑ}������܂��B<BR>
     * ���������ăO���[�v��ʂƋ��ɓo�^���K�v�ł��B<BR>
     * ��ʂƂ́A�����Ő�������� GgafGroupActor�� �ɂ��g�p����܂��B<BR>
     * GgafGroupActor�I�u�W�F�N�g �͏����ʓo�^��������������A�Q��ڈȍ~�̓����ʓo�^�́A<BR>
     * ������ GgafGroupActor�I�u�W�F�N�g�̃T�u�ɒǉ�����܂��B<BR>
     * <pre>
     * ���g�p��P��
     *
     *  addSubGroup(KIND_XXX, pActor);
     *
     *  �Ƃ����ꍇ�A�K�w�\���͎��̂悤�ɂȂ�B
     *
     *  this
     *    |
     *    +- pObject(GgafGroupActor[KIND_XXX])
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
     *    +- pObject(GgafGroupActor[KIND_AAA]) -- pObject(GgafGroupActor[KIND_BBB])
     *         |                                    |
     *         +- pActor01 -- pActor03              + pActor02
     * </pre>
     * @param   prm_kind    ��ʖ��i��GgafGroupActor���j
     * @param   prm_pMainActor   �o�^����A�N�^�[
     */
    GgafGroupActor* addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * �P��GgafActor�A������GgafDummyActor���P�Ɛe�ƂȂ�GgafActor�A���̂�<BR>
     * ��ʂ�0(����)�œo�^�����
     * �{�֐��͂̕��I������ prm_pActor �� GgafGroupActor �̎q�A�N�^�[�Ƃ��Ă��邾���ł���B<BR>
     * @param   prm_pMainActor   �o�^����A�N�^�[
     */
    GgafGroupActor* addSubGroup(GgafMainActor* prm_pMainActor);

    /**
     * �T�u�̒c���A�N�^�[���擾�A�������NULL���A��
     * @param prm_kind
     * @return
     */
    GgafGroupActor* getSubGroupActor(actorkind prm_kind);


    /**
     * �_�ɉy�� .
     * @return	�Ă΂�ďo�Ă����_
     */
    GgafGod* askGod();

    virtual ~GgafLordActor();
};

}
#endif /**GGAFLORDACTOR_H_*/
