#ifndef GGAFDISUSEDSCENE_H_
#define GGAFDISUSEDSCENE_H_
namespace GgafCore {

/**
 * �s�v�ɂȂ����V�[�� .
 * ���̃V�[���ɏ��������V�[���́A�x���ꑁ����delete����܂��B<BR>
 * �x���ꑁ����Ƃ����̂́A�_(GgafGod)���AFps�̗]�T������Ƃ��� delete ����Ƃ����Ӗ��ł�<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
 */
class GgafDisusedScene : public GgafScene {
public:
    GgafDisusedScene() :
        GgafScene("DisusedScene") {
        _scene_class |= Obj_GgafDisusedScene;
        _class_name = "GgafDisusedScene";
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
    void catchEvent(UINT32 prm_no) override {
    }
    void processFinal() override {
    }
    virtual ~GgafDisusedScene() {
    }
};

}
#endif /*GGAFDISUSEDSCENE_H_*/
