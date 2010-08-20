#ifndef GGAFDISUSEDSCENE_H_
#define GGAFDISUSEDSCENE_H_
namespace GgafCore {

/**
 * 不要になったシーン .
 * このシーンに所属したシーンは、遅かれ早かれdeleteされます。<BR>
 * 遅かれ早かれというのは、神(GgafGod)が、Fpsの余裕があるときに delete するという意味です<BR>
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
