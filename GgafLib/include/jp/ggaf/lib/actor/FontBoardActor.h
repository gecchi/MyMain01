#ifndef GGAF_LIB_FONTBOARDACTOR_H_
#define GGAF_LIB_FONTBOARDACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"

#include "jp/ggaf/dx/actor/MassBoardActor.h"
#include "interface/ICharacterChip.hpp"

namespace GgafLib {

/**
 * 文字キャラクタ表示 .
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class FontBoardActor : public GgafDx::MassBoardActor , public ICharacterChip<FontBoardActor, 256, 1024> {

protected:
    struct VERTEX_instancedata {
        float px_x, px_y, depth_z;         // : TEXCOORD1
        float offset_u, offset_v, alpha;   // : TEXCOORD2
    };
    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info);
public:
    virtual void setAlign(Align prm_align, Valign prm_valign) override;
    virtual void setAlign(Align prm_align) override;
    virtual void setValign(Valign prm_valign) override;
public:

    /** 衝突判定支援オブジェクト */
    ViewCollisionChecker* _pViewCollisionChecker;

    FontBoardActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void onActive() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processDraw() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onInactive() override {
    }

    virtual void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override {
    }

    virtual void drawHitArea() override;

    virtual GgafDx::CollisionChecker* createChecker(kind_t prm_kind = 0) override;

    inline ViewCollisionChecker* getViewCollisionChecker() {
        return _pViewCollisionChecker;
    }

    /**
     * モデル資源を１つ生成して追加する。 .
     * 初めて本メソッドを実行すると、内部リストに保持され、そのモデル資源が有効になります。
     * ２回目以降の実行は、生成したモデル資源を内部リストの末尾に追加します。（有効になりません）
     * @param prm_model モデル定義名
     */
    virtual void addModel(const char* prm_model) override;

    virtual ~FontBoardActor();

};

}
#endif /*GGAF_LIB_FONTBOARDACTOR_H_*/
