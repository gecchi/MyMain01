#ifndef GGAFSAYONARASCENE_H_
#define GGAFSAYONARASCENE_H_
namespace GgafCore {

/**
 * ����Ȃ烋�[�g�V�[�� .
 * ���̃V�[���ɏ��������V�[���́A�x���ꑁ����delete����܂��B<BR>
 * �x���ꑁ����Ƃ����̂́A�_(GgafGod)���AFps�̗]�T������Ƃ��� delete ����Ƃ����Ӗ��ł�<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
 */
class GgafSayonaraScene : public GgafScene {
public:
    GgafSayonaraScene() :
        GgafScene("SayonaraScene") {
        _scene_class |= Obj_GgafSayonaraScene;
        _class_name = "GgafSayonaraScene";
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
    virtual ~GgafSayonaraScene() {
    }
};

}
#endif /*GGAFSAYONARASCENE_H_*/
