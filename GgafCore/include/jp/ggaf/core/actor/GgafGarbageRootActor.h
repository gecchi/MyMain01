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
    void initialize() {
    }
    void processBehavior() {
    }
    void processJudgement() {
    }
    void processPreDraw() {
    }
    void processDraw() {
    }
    void processAfterDraw() {
    }
    void processHappen(int prm_no) {
    }
    void processFinal() {
    }
    bool processBumpChkLogic(GgafActor* prm_pOtherActor) {
        return false;
    }
    void processOnHit(GgafActor* prm_pOtherActor) {
    }
    GgafGod* askGod() {
        return NULL;
    }
    virtual ~GgafGarbageRootActor() {
    }
};

}
#endif /*GGAFGARBAGEROOTACTOR_H_*/
