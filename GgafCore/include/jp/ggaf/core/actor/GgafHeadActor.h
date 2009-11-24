#ifndef GGAFHEADACTOR_H_
#define GGAFHEADACTOR_H_
namespace GgafCore {

/**
 * �c���N���X .
 * �Ƃ���Z�����A�N�^�[�B�́A�K�w�c���[���_�̃A�N�^�[�ł��B<BR>
 * ���_�ƌ����Ă��A�����ЂƂ�1��ʊK�w�ɂ́A�Ǘ���(GgafLoadActor�j�����܂��B�A�N�^�[�̖�E�I��No.2�ȃ|�W�V�����ł��B<BR>
 * �L�����N�^��\������A�N�^�[��Z�߂ăO���[�v�ɂ��A�z���̃A�N�^�[�̎�ʂ�\�����Ă���A�N�^�[�ɂ��Ȃ�܂��B<BR>
 * ��ʂƂ́A�����蔻�莞�� [���@�̒e]��[�G�{��] ���� [] �̒��g��\�����Ă���悤�ȕ��ނ��w���܂��B<BR>
 * �c���͔z���̃A�N�^�[�����ł���ƁA���̃t���[���Ɏ��g�����E���܂��B�����������Ȃ���i�͕s�v�Ƃ����킯�ł��B<BR>
 * �Ǘ��҂̃T�u�A�N�^�[�́A�S�ĕK�����̒c���ɂȂ��Ă��܂��B<BR>
 * �܂��A�c���z���ɒc�������݂��Ă͂����Ȃ����ƂɂȂ��Ă��܂��B<BR>
 * ���⑫�F�c���N���X(GgafHeadActor)�̃I�u�W�F�N�g�C���[�W�}��<BR>
 * <PRE STYLE="font-size:18px">
 * �@�@�@�@����� GgafScene �� GgafScene �̥��
 * �@�@�@�@�@�@�@�@�@�b
 * �@�@�@�@�@�@�@�@�@�������o�[
 * �@�@�@�@�@GgafLordActor�@�i��1��Scene�ɕK���P��LordActor�j
 * �@�@�@�@�@�@�@�b
 * �@�@�@�@�@�@�@�bgetSubFirst()
 * �@�@�@�@�@�@�@��
 * �@�@GgafHeadActor �� GgafHeadActor �� GgafHeadActor ��
 * �@�@�@�@�@�b�@�@�@�@�@�@�@�@�@�b�@�@�@�@�@�@�@�@�@�b
 * �@�@�@�@�@�bgetSubFirst()�@�@ �b�@�@�@�@�@�@�@�@�@�b
 * �@�@�@�@�@���@�@�@�@�@�@�@�@�@���@�@�@�@�@�@�@�@�@��
 * �@�@�L�����̃A�N�^�[�B�@�@�L�����̃A�N�^�[�B�@�@�L�����̃A�N�^�[
 * </PRE>
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafHeadActor : public GgafActor {

public:
    /** �Ǘ��� */
    GgafLordActor* _pLordActor;

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
    void processPreDraw() {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    void processDraw() {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    void processAfterDraw() {
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



    GgafLordActor* getLordActor();
    void setLordActor(GgafLordActor* prm_pLordActor);



    /**
     * �_�ɉy�� .
     * @return	�Ă΂�ďo�Ă����_
     */
    virtual GgafGod* askGod();

    virtual ~GgafHeadActor();
};

}
#endif /*GGAFHEADACTOR_H_*/
