#ifndef GGAFCORE_GGAFDISUSEDSCENE_H_
#define GGAFCORE_GGAFDISUSEDSCENE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/scene/GgafScene.h"

namespace GgafCore {

/**
 * 不要になったシーン .
 * GgafGarbageBox（ゴミ箱）に所属し操作されます。<BR>
 * このシーンに所属したシーンは、遅かれ早かれ delete される恐怖のシーンです。<BR>
 * 「遅かれ早かれ delete されるシーン達」ツリーの、トップノードに位置します。<BR>
 * 自身は削除されることはありません。<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
 */
class GgafDisusedScene : public GgafScene {
public:
    GgafDisusedScene() :
        GgafScene("DisusedScene") {
        _obj_class |= Obj_GgafDisusedScene;
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
    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void processFinal() override {
    }
    void updateActiveInTheTree() override {
        _is_active_in_the_tree_flg = false;
        _is_active_flg = false;
    }
    virtual ~GgafDisusedScene() {
    }
};

}
#endif /*GGAFCORE_GGAFDISUSEDSCENE_H_*/
