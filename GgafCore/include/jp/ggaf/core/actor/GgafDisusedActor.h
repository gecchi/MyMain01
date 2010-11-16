#ifndef GGAFDISUSEDACTOR_H_
#define GGAFDISUSEDACTOR_H_
namespace GgafCore {

/**
 * 不要になったアクター.
 * このアクターに所属したアクターは、遅かれ早かれdeleteされます。<BR>
 * 遅かれ早かれというのは、神(GgafGod)が、Fpsの余裕があるときに delete するという意味です<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
 */
class GgafDisusedActor : public GgafActor {
public:
    GgafDisusedActor() :
        GgafActor("DisusedActor") {
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
    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
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
    virtual ~GgafDisusedActor() {
    }
};

}
#endif /*GGAFDISUSEDACTOR_H_*/
