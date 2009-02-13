#ifndef GGAFLORDACTOR_H_
#define GGAFLORDACTOR_H_
namespace GgafCore {

/**
 * �Ǘ��҃N���X .
 * �c��(GgafHeadActor)�̐e�K�w�̃A�N�^�[�ŁA�c�����Ǘ����܂��B<BR>
 * �܂��A�V�[���N���X�Ƃ̋��n�����s�����ʂȃA�N�^�[�ł�����܂��B<BR>
 * �V�[���N���X�ƊǗ��҂͕��ʂ�hasA�̊֌W�ł��B�i�Ǘ��҂ƒc���͊K�w�֌W�ɂȂ��Ă��܂��j<BR>
 * �S�ẴV�[��(GgafSceane�I�u�W�F�N�g)�ɕK���P�l�Ǘ��҂̃C���^���X������܂��B<BR>
 * �Ǘ��҂́A�K���A�N�^�[�B�c���[�̍ł����_�Ɉʒu���܂��B<BR>
 * �Ǘ���(GgafLordActor)�̃T�u�A�N�^�[�͕K���c��(GgafHeadActor)�ɂȂ��Ă��܂��B<BR>
 * �c��(GgafHeadActor)�̉�������킹�ĎQ�Ƃ��ĉ������B
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
class GgafLordActor : public GgafActor {
public:
    GgafLordActor(GgafScene* prm_pScene_Platform);

    /**
     * ��������<BR>
     */
    void initialize() {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    void processBehavior() {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    void processJudgement() {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    void processDrawPrior() {
    }
    /**
     * ��OverRide �ł���<BR>
     */
    void processDrawMain() {
    }
    /**
     * ��OverRide �ł���<BR>
     */
    void processDrawTerminate() {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    void processHappen(int prm_no) {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processFinal() {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    bool processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
        return false;
    }

    /**
     * ��OverRide �ł���<BR>
     */
    void processOnHit(GgafActor* prm_pActor_Opponent) {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    void remove();

    /**
     * �P��GgafActor�A������GgafDummyActor���P�Ɛe�ƂȂ�GgafActor�A���̂�<BR>
     * ��ʂƋ��ɓo�^����B
     * ��ʂƂ́A�����Ő�������� GgafHeadActor�� �ɂȂ�B<BR>
     * GgafHeadActor �͏����ʓo�^���������������B�Q��ڈȍ~�̓����ʓo�^�́A<BR>
     * ������ GgafHeadActor ���g�p�����B<BR>
     * �{�֐��͂̕��I������ prm_pActor �� GgafHeadActor �̎q�A�N�^�[�Ƃ��Ă��邾���ł���B<BR>
     * @param   prm_kind    ��ʖ��i��GgafHeadActor���j
     * @param   prm_pMainActor   �o�^����A�N�^�[
     */
    void accept(actorkind prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * �P��GgafActor�A������GgafDummyActor���P�Ɛe�ƂȂ�GgafActor�A���̂�<BR>
     * ��ʂ�0(����)�œo�^�����
     * �{�֐��͂̕��I������ prm_pActor �� GgafHeadActor �̎q�A�N�^�[�Ƃ��Ă��邾���ł���B<BR>
     * @param   prm_pMainActor   �o�^����A�N�^�[
     */
    void accept(GgafMainActor* prm_pMainActor);

    bool hasSubHeadActor(actorkind prm_kind);
    GgafHeadActor* getSubHeadActor(actorkind prm_kind);

    /**
     * ������GgafHeadActor���擾����B<BR>
     * @param   prm_kind    ���("*"�ɂ��ȗ��\)
     * @param   prm_pActor   �o�^����A�N�^�[
     */
    //    virtual GgafHeadActor* getHeadActor(std::string prm_kind);


    /**
     * �_�ɉy�� .
     * @return	�Ă΂�ďo�Ă����_
     */
    virtual GgafGod* askGod();

    virtual ~GgafLordActor();
};

}
#endif /**GGAFLORDACTOR_H_*/
