#ifndef GGAFGARBAGEROOTSCENE_H_
#define GGAFGARBAGEROOTSCENE_H_
namespace GgafCore {

/**
 * ����ꃋ�[�g�V�[��
 * ���̃V�[���ɏ��������V�[���́A�x���ꑁ����delete����܂��B<BR>
 * �x���ꑁ����Ƃ����̂́A�_(GgafGod)���AFps�̗]�T������Ƃ��� delete ����Ƃ����Ӗ��ł�<BR>
 */
class GgafGarbageRootScene : public GgafScene {
public:
    GgafGarbageRootScene() :
        GgafScene("GarbageRootScene") {
    }
    void initialize() {
    }
    void processBehavior() {
    }
    void processJudgement() {
    }
    void processDrawPrior() {
    }
    void processDrawMain() {
    }
    void processDrawTerminate() {
    }
    void processHappen(int prm_no) {
    }
    void processFinal() {
    }
    virtual ~GgafGarbageRootScene() {
    }
};

}
#endif /*GGAFGARBAGEROOTSCENE_H_*/
