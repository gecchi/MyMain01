#ifndef GGAFDUMMYACTOR_H_
#define GGAFDUMMYACTOR_H_
namespace GgafCore {

/**
 * �_�~�[�A�N�^�[�N���X .
 * �q�A�N�^�[�������Ȃ�Ύ����I�Ɏ��E����߂����ꎞ�I�ȃA�N�^�[�ł��B<BR>
 * �c�̍s�����̂�Ƃ��ɁA�e�A�N�^�[�ɂ���Ɖ����ƕ֗���������Ȃ��B<BR>
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

    virtual void processBehavior() override {
    }

    /**
     * ���t���[����GgafDummyActor���菈��
     * �T�u��������Ύ����I�Ɏ��S���鏈���ɂȂ��Ă���B
     */
    virtual void processJudgement() override {
        if (getSubFirst() == NULL) {
            end(1); //1�t���[����
        }
    }

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    /**
     * �����蔻��s�v�̂��ߏ��false��Ԃ� .
     * @param prm_pOtherActor
     * @return false
     */
    virtual bool processHitChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafActor* prm_pOtherActor) override {
    }

    virtual ~GgafDummyActor();
};

}
#endif /*GGAFDUMMYACTOR_H_*/
