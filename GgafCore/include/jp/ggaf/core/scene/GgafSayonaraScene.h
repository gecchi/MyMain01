#ifndef GGAFSAYONARASCENE_H_
#define GGAFSAYONARASCENE_H_
namespace GgafCore {

/**
 * さよならルートシーン .
 * このシーンに所属したシーンは、遅かれ早かれdeleteされます。<BR>
 * 遅かれ早かれというのは、神(GgafGod)が、Fpsの余裕があるときに delete するという意味です<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
 */
class GgafSayonaraScene : public GgafScene {
public:
    GgafSayonaraScene() :
        GgafScene("SayonaraScene") {
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
