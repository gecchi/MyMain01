#ifndef GGAFHEADACTOR_H_
#define GGAFHEADACTOR_H_
namespace GgafCore {

/**
 * �c���N���X .
 * �Ƃ���Z�����A�N�^�[(GgafMainActor)�B�́A�K�w�c���[���_�̃A�N�^�[�ł��B<BR>
 * ���_�ƌ����Ă��A�����ЂƂ�1��ʊK�w�ɂ́A�Ǘ���(GgafLoadActor�j�����܂��B�A�N�^�[�̖�E�I��No.2�ȃ|�W�V�����ł��B<BR>
 * �L�����N�^��\������A�N�^�[��Z�߂ăO���[�v�ɂ��A�z���̃A�N�^�[�̎�ʂ�\�����Ă���A�N�^�[�ɂ��Ȃ�܂��B<BR>
 * ��ʂƂ́A�����蔻�莞�� [���@�̒e]��[�G�{��] ���� [] �̒��g��\�����Ă���悤�ȕ��ނ��w���܂��B<BR>
 * �c���͔z���̃A�N�^�[�����ł���ƁA���̃t���[���Ɏ��g�����E���܂��B�����������Ȃ���i�͕s�v�Ƃ����킯�ł��B<BR>
 * �Ǘ��҂̃T�u�A�N�^�[�́A�S�ĕK�����̒c���ɂȂ��Ă��܂��B<BR>
 * �܂��A�c���z���ɒc�������݂��Ă͂����Ȃ����ƂɂȂ��Ă��܂��B<BR>
 * ���⑫�F�I�u�W�F�N�g�C���[�W�}��<BR>
 * <PRE>
 * �@�@�@�@����� GgafScene �� GgafScene �̥��
 * �@�@�@�@�@�@�@�@�@�b
 * �@�@�@�@�@�@�@�@�@�������o�[
 * �@�@�@�@�@GgafLordActor�@�i��1��Scene�ɕK���P��LordActor�j
 * �@�@�@�@�@�@�@�b
 * �@�@�@�@�@�@�@�bSubFirst
 * �@�@�@�@�@�@�@��
 * �@�@GgafHeadActor �� GgafHeadActor �� GgafHeadActor ��
 * �@�@�@�@�@�@�b�@�@�@�@�@�@�@�@�b�@�@�@�@�@�@�@�@�@�b
 * �@�@�@�@�@�@�bSubFirst�@�@�@�b�@�@�@�@�@�@�@�@�@�b
 * �@�@�@�@�@�@���@�@�@�@�@�@�@�@���@�@�@�@�@�@�@�@�@��
 * �@�@�L�����̃A�N�^�[�B�@�@�L�����̃A�N�^�[�B�@�@�L�����̃A�N�^�[
 * </PRE>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
class GgafHeadActor : public GgafActor {

public:

    actorkind _kind;

    GgafHeadActor(actorkind prm_kind);

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
    void processJudgement();

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
     * �_�ɉy�� .
     * @return	�Ă΂�ďo�Ă����_
     */
    virtual GgafGod* askGod();

    virtual ~GgafHeadActor();
};

}
#endif /*GGAFHEADACTOR_H_*/
