#ifndef GGAFSAYONARAACTOR_H_
#define GGAFSAYONARAACTOR_H_
namespace GgafCore {

/**
 * さよならルートアクター.
 * このアクターに所属したアクターは、遅かれ早かれdeleteされます。<BR>
 * 遅かれ早かれというのは、神(GgafGod)が、Fpsの余裕があるときに delete するという意味です<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
 */
class GgafSayonaraActor : public GgafActor {
public:
    GgafSayonaraActor() :
        GgafActor("SayonaraActor") {
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
    bool processHitChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }
    void onHit(GgafActor* prm_pOtherActor) override {
    }
    GgafGod* askGod() {
        return NULL;
    }
    virtual ~GgafSayonaraActor() {
    }
};

}
#endif /*GGAFSAYONARAACTOR_H_*/
