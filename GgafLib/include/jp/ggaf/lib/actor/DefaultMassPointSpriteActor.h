#ifndef GGAF_LIB_DEFAULTMASSPOINTSPRITEACTOR_H_
#define GGAF_LIB_DEFAULTMASSPOINTSPRITEACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MassPointSpriteActor.h"

namespace GgafLib {

/**
 * TODO: 使えません、環境依存すぎる.
 */
class DefaultMassPointSpriteActor : public GgafDx::MassPointSpriteActor {

private:
    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
        float _21, _22, _23, _24;   // : TEXCOORD2  World変換行列、２行目
        float _31, _32, _33, _34;   // : TEXCOORD3  World変換行列、３行目
        float _41, _42, _43, _44;   // : TEXCOORD4  World変換行列、４行目
        float r, g, b, a;           // : TEXCOORD5  マテリアルカラー
        float pattno_uvflip_now;    // : TEXCOORD6

    };
    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info);

public:
    /** 衝突判定支援オブジェクト */
    WorldCollisionChecker* _pWorldCollisionChecker;

    DefaultMassPointSpriteActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processDraw() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override {
    }

    virtual void drawHitArea() override;

    virtual GgafDx::CollisionChecker* createChecker(kind_t prm_kind = 0) override;
    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pWorldCollisionChecker;
    }

    /**
     * モデル資源を１つ生成して追加する。 .
     * 初めて本メソッドを実行すると、内部リストに保持され、そのモデル資源が有効になります。
     * ２回目以降の実行は、生成したモデル資源を内部リストの末尾に追加します。（有効になりません）
     * @param prm_model モデル定義名
     */
    virtual void addModel(const char* prm_model) override;
    virtual ~DefaultMassPointSpriteActor();
};

}
#endif /*GGAF_LIB_DEFAULTMASSMESHACTOR_H_*/
