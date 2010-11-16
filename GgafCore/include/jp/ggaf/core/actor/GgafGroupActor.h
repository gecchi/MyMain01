#ifndef GGAFGROUPACTOR_H_
#define GGAFGROUPACTOR_H_
namespace GgafCore {

/**
 * �c��(GgafGroupActor)�N���X .
 * �Ƃ���Ӗ������œZ�����A�N�^�[�B�̃c���[���_�Ɉʒu���܂��B
 * ������w��ʁx��\������������������A�N�^�[�ŁA��̓I�ȃL�����N�^�[�ł͂���܂���B<BR>
 * �c���z���̑S�ẴA�N�^�[�́w��ʁx�́A�c���́w��ʁx�Ƃ���B�Ƃ����d�g�݂ł��B
 * �w��ʁx�Ƃ́A�����蔻�莞�� [���@�̒e]��[�G�{��] ���� [] �̒��g�̎����w���܂��B���ނƌ����ׂ��Ȃ̂�������܂���B<BR>
 * �c���͔z���̃A�N�^�[�����ł���ƁA���̃t���[���Ɏ��g���₵���Ȃ��Ď��E���܂��B�����������Ȃ�����͖��Ӗ��ł��I<BR>
 * �Ǘ���(GgafLordActor)�̒����̃T�u�A�N�^�[�́A�S�ĕK�����̒c���ɂȂ��Ă��܂��B<BR>
 * �܂��A�c���z���̃A�N�^�[�ɁA����ɒc�������݂��邱�Ƃ��\�ł��B<BR>
 * �A���c���̒��ڔz���ɒc���͒u���܂���B����́A�c���̔z���ɂ͏��Ȃ��Ƃ���l�͕��ʂ̃A�N�^�[�����݂��Ȃ���΂����Ȃ��Ƃ����d�g�ݏ�̖��ł��B<BR>
 * �����̒c�����o�����[�̃A�N�^�[�̎�ʂ́A���߂̒c���̎�ʂ��D�悳��܂��B<BR>
 * ���⑫�F�c���N���X(GgafGroupActor)�̃I�u�W�F�N�g�C���[�W�}��<BR>
 * <PRE>
 * �@�@�@�@�E�E�E�� GgafScene �� GgafScene �́E�E�E
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
    /** [r]�Ǘ��� */
    GgafLordActor* _pLordActor;
    /** [r/w]��� */
    actorkind _kind;

    GgafGroupActor(actorkind prm_kind);

    /**
     * �������� .
     */
    void initialize() override {
    }

    void processBehavior() override {
    }

    /**
     * ���t���[����GgafGroupActor���菈�� .
     * �T�u��������Ύ����I�Ɏ��S���鏈���ɂȂ��Ă���B
     */
    void processJudgement() override {
        //�T�u��������Ύ��E
        if (getSubFirst() == NULL) {
            sayonara();
        }
    }

    void processPreDraw() override {
    }

    void processDraw() override {
    }

    void processAfterDraw() override {
    }

    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
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

    void onHit(GgafActor* prm_pOtherActor) override {
    }

    /**
     * �Ǘ���(GgafLordActor)���擾 .
     * @return ���g���Ǘ�����Ă���Ǘ���
     */
    GgafLordActor* getLordActor();

    /**
     * �Ǘ���(GgafLordActor)��ݒ� .
     * @param prm_pLordActor �Ǘ���
     */
    void setLordActor(GgafLordActor* prm_pLordActor);

    /**
     * �_�ɉy�� .
     * @return	�Ă΂�ďo�Ă����_
     */
    GgafGod* askGod();

    virtual ~GgafGroupActor();
};

}
#endif /*GGAFGROUPACTOR_H_*/
