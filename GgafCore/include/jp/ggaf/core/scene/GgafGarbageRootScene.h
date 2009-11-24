#ifndef GGAFGARBAGEROOTSCENE_H_
#define GGAFGARBAGEROOTSCENE_H_
namespace GgafCore {

/**
 * お疲れルートシーン
 * このシーンに所属したシーンは、遅かれ早かれdeleteされます。<BR>
 * 遅かれ早かれというのは、神(GgafGod)が、Fpsの余裕があるときに delete するという意味です<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
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
    virtual ~GgafGarbageRootScene() {
    }
};

}
#endif /*GGAFGARBAGEROOTSCENE_H_*/
