#ifndef GGAF_CORE_DISUSEDACTOR_H_
#define GGAF_CORE_DISUSEDACTOR_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/actor/Actor.h"

namespace GgafCore {

/**
 * 不要になったアクター .
 * GarbageBox（ゴミ箱）に所属し操作されます。<BR>
 * このアクターに所属したアクターは、遅かれ早かれ delete される恐怖のアクターです。<BR>
 * 「遅かれ早かれ delete されるアクター達」ツリーの、トップノードに位置します。<BR>
 * 自身は削除されることはありません。<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
 */
class DisusedActor : public Actor {

public:
    DisusedActor() :
        Actor("DisusedActor") {
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
    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }
    void processFinal() override {
    }
    void onHit(const Checker* prm_pOtherChecker, const Actor* prm_pOtherActor) override {
    }
    Caretaker* askCaretaker() {
        return nullptr;
    }

    void updateActiveInTheTree() override {
        _is_active_in_the_tree_flg = false;
        _is_active_flg = false;
    }

    virtual ~DisusedActor() {
    }
};

}
#endif /*GGAF_CORE_DISUSEDACTOR_H_*/
