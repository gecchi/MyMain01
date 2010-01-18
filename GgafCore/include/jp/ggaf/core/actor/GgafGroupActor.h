#ifndef GGAFGROUPACTOR_H_
#define GGAFGROUPACTOR_H_
namespace GgafCore {

/**
 * �c��(GgafGroupActor)�N���X .
 * �Ƃ����ʂœZ�����A�N�^�[�B�́A�K�w�c���[���_�̃A�N�^�[�Ŏ�ʂ�\������������������A�N�^�[�ł��B<BR>
 * ���_�ƌ����Ă��A�����ЂƂ�1��ʊK�w�ɂ́A�Ǘ���(GgafLoadActor�j�����܂��B�A�N�^�[�̖�E�I��No.2�ȃ|�W�V�����ł��B<BR>
 * �z���̃A�N�^�[�̎�ʂ�\�����Ă���A�N�^�[�ŁA�����蔻�蓙�ɗ��p����܂��B<BR>
 * ��ʂƂ́A�����蔻�莞�� [���@�̒e]��[�G�{��] ���� [] �̒��g��\�����Ă���悤�ȕ��ޕ\�����Ӗ����܂��B<BR>
 * �c���͔z���̃A�N�^�[�����ł���ƁA���̃t���[���Ɏ��g���₵���Ȃ��Ď��E���܂��B�����������Ȃ�����͎����̖��ʎg���ł��I<BR>
 * �Ǘ���(GgafLordActor)�̃T�u�A�N�^�[�́A�S�ĕK�����̒c���ɂȂ��Ă��܂��B<BR>
 * �܂��A�c���z���̃A�N�^�[�ɁA����ɒc�������݂��邱�Ƃ��\�ł��B�i�A���c���̒��ڔz���ɒc���͒u���܂���j
 * ���̏ꍇ�A���[�̃A�N�^�[��ʂ́A���߂̒c���̎�ʂ��D�悳��܂��B<BR>
 * ���⑫�F�c���N���X(GgafGroupActor)�̃I�u�W�F�N�g�C���[�W�}��<BR>
 * <PRE STYLE="font-size:18px">
 * �@�@�@�@����� GgafScene �� GgafScene �̥��
 * �@�@�@�@�@�@�@�@�@�b
 * �@�@�@�@�@�@�@�@�@�������o�[
 * �@�@�@�@�@GgafLordActor�@�i��1��Scene�ɕK���P��LordActor�j
 * �@�@�@�@�@�@�@�b
 * �@�@�@�@�@�@�@�bgetSubFirst()
 * �@�@�@�@�@�@�@��
 * �@�@GgafGroupActor �� GgafGroupActor �� GgafGroupActor ��
 * �@�@�@�@�@�b�@�@�@�@�@�@�@�@�@�b�@�@�@�@�@�@�@�@�@�b
 * �@�@�@�@�@�bgetSubFirst()�@�@ �b�@�@�@�@�@�@�@�@�@�b
 * �@�@�@�@�@���@�@�@�@�@�@�@�@�@���@�@�@�@�@�@�@�@�@��
 * �@�@�L�����̃A�N�^�[�B�@�@�L�����̃A�N�^�[�B�@�@�L�����̃A�N�^�[
 * </PRE>
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafGroupActor : public GgafActor {

public:
    /** �Ǘ��� */
    GgafLordActor* _pLordActor;

    actorkind _kind;

    GgafGroupActor(actorkind prm_kind);

    /**
     * ��������<BR>
     */
    void initialize() override {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    void processBehavior() override {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    void processJudgement() override;

    /**
     * ��OverRide �ł���<BR>
     */
    void processPreDraw() override {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    void processDraw() override {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    void processAfterDraw() override {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    void processHappen(int prm_no) override {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processFinal() override {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    bool processBumpChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }

    /**
     * ��OverRide �ł���<BR>
     */
    void processOnHit(GgafActor* prm_pOtherActor) override {
    }

    GgafLordActor* getLordActor();

	void setLordActor(GgafLordActor* prm_pLordActor);



    /**
     * �_�ɉy�� .
     * @return	�Ă΂�ďo�Ă����_
     */
    virtual GgafGod* askGod();

    virtual ~GgafGroupActor();
};

}
#endif /*GGAFGROUPACTOR_H_*/
