#ifndef GGAFGARBAGEROOTACTOR_H_
#define GGAFGARBAGEROOTACTOR_H_
namespace GgafCore {

/**
 * ����ꃋ�[�g�A�N�^�[.
 * ���̃A�N�^�[�ɏ��������A�N�^�[�́A�x���ꑁ����delete����܂��B<BR>
 * �x���ꑁ����Ƃ����̂́A�_(GgafGod)���AFps�̗]�T������Ƃ��� delete ����Ƃ����Ӗ��ł�<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
 */
class GgafGarbageRootActor : public GgafActor {
public:
    GgafGarbageRootActor() :
        GgafActor("GarbageRootActor") {
    }
    void initialize() override {
    }
    void processBehavior() override {
    }
    void processJudgement() override {
    }
    void processPreDraw() override {
    }
    void processDraw() override {
    }
    void processAfterDraw() override {
    }
    void processHappen(int prm_no) override {
    }
    void processFinal() override {
    }
    bool processBumpChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }
    void processOnHit(GgafActor* prm_pOtherActor) override {
    }
    GgafGod* askGod() {
        return NULL;
    }
    virtual ~GgafGarbageRootActor() {
    }
};

}
#endif /*GGAFGARBAGEROOTACTOR_H_*/
