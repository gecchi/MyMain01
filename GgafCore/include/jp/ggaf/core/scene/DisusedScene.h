#ifndef GGAF_CORE_DISUSEDSCENE_H_
#define GGAF_CORE_DISUSEDSCENE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/scene/Scene.h"

namespace GgafCore {

/**
 * 不要になったシーン .
 * GarbageBox（ゴミ箱）に所属し操作されます。<BR>
 * このシーンに所属したシーンは、遅かれ早かれ delete される恐怖のシーンです。<BR>
 * 「遅かれ早かれ delete されるシーン達」ツリーの、トップノードに位置します。<BR>
 * 自身は削除されることはありません。<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
 */
class DisusedScene : public Scene {
public:
    DisusedScene() :
        Scene("DisusedScene") {
        _obj_class |= Obj_ggaf_DisusedScene;
        _class_name = "DisusedScene";
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
    void updateActiveInTheTree() override {
        _is_active_in_the_tree_flg = false;
        _is_active_flg = false;
    }
    virtual ~DisusedScene() {
    }
};

}
#endif /*GGAF_CORE_DISUSEDSCENE_H_*/
