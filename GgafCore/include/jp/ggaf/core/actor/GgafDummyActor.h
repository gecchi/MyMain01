#ifndef GGAFDUMMYACTOR_H_
#define GGAFDUMMYACTOR_H_
namespace GgafCore {

/**
 * �_�~�[�A�N�^�[�N���X .
 * �q�A�N�^�[�������Ȃ�Ύ����I�Ɏ��E����߂����ꎞ�I�ȃA�N�^�[�ł��B<BR>
 * �c�̍s�����̂�Ƃ��ɁA�e�A�N�^�[�ɂ���Ɖ����ƕ֗���������܂���B<BR>
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafDummyActor : public GgafMainActor {

public:
    GgafDummyActor(const char* prm_name);

    /**
     * ��������<BR>
     */
    virtual void initialize() override {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processBehavior() override {
    }

    /**
     * �T�u��������Ύ��S���܂��B
     * ��OverRide �ł���<BR>
     */
    virtual void processJudgement() override {
        if (getSubFirst() == NULL) {
            adios(1); //1�t���[����
        }
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processPreDraw() override {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processDraw() override {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processAfterDraw() override {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processHappen(int prm_no) override {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processFinal() override {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual bool processBumpChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processOnHit(GgafActor* prm_pOtherActor) override {
    }

    virtual ~GgafDummyActor();
};

}
#endif /*GGAFDUMMYACTOR_H_*/
