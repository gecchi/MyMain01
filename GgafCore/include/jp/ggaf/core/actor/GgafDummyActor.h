#ifndef GGAFDUMMYACTOR_H_
#define GGAFDUMMYACTOR_H_
namespace GgafCore {

/**
 * �_�~�[�A�N�^�[�N���X .
 * �q�A�N�^�[�������Ȃ�Ύ����I�Ɏ��E����߂����ꎞ�I�ȃA�N�^�[�ł��B<BR>
 * �c�̍s�����̂�Ƃ��ɁA�e�A�N�^�[�ɂ���Ɖ����ƕ֗���������܂���B<BR>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
class GgafDummyActor : public GgafMainActor {

public:
    GgafDummyActor(const char* prm_name);

    /**
     * ��������<BR>
     */
    virtual void initialize() {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processBehavior() {
    }

    /**
     * �T�u��������Ύ��S���܂��B
     * ��OverRide �ł���<BR>
     */
    virtual void processJudgement() {
        if (getSubFirst() == NULL) {
            adios();
        }
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processPreDraw() {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processDraw() {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processAfterDraw() {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processHappen(int prm_no) {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processFinal() {
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual bool processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
        return false;
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processOnHit(GgafActor* prm_pActor_Opponent) {
    }

    virtual ~GgafDummyActor();
};

}
#endif /*GGAFDUMMYACTOR_H_*/
