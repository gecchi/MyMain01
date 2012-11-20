#ifndef GGAFDISUSEDACTOR_H_
#define GGAFDISUSEDACTOR_H_
namespace GgafCore {

/**
 * 不要になったアクター .
 * GgafGarbageBox（ゴミ箱）に所属し操作されます。<BR>
 * このアクターに所属したアクターは、遅かれ早かれ delete される恐怖のアクターです。<BR>
 * 「遅かれ早かれ delete されるアクター達」ツリーの、トップノードに位置します。<BR>
 * 自身は削除されることはありません。<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
 */
class GgafDisusedActor : public GgafActor {
public:
    GgafDisusedActor() :
        GgafActor("DisusedActor", nullptr) {
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
    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void processFinal() override {
    }
    bool processHitChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }
    void onHit(GgafActor* prm_pOtherActor) override {
    }
    GgafGod* askGod() {
        return nullptr;
    }

    virtual void updateActiveInTheTree() override {
        _is_active_in_the_tree_flg = false;
        _is_active_flg = false;
    }

    virtual ~GgafDisusedActor() {
    }
};

}
#endif /*GGAFDISUSEDACTOR_H_*/
