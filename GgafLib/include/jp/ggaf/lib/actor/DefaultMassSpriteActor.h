#ifndef GGAF_LIB_DEFAULTMASSSPRITEACTOR_H_
#define GGAF_LIB_DEFAULTMASSSPRITEACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MassSpriteActor.h"

namespace GgafLib {

/**
 * スプライトセットアクターの具象クラス.
 * GgafDx::MassSpriteActor を空実装した具象アクターです。
 * 本クラスを継承してキャラクターを作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getPhase()</TD><TD>フェーズ管理</TD><TD>GgafCore::Phase</TD></TR>
 * <TR><TD>getLocusVehicle()</TD><TD>移動車両。移動回転支援</TD><TD>GgafDx::LocusVehicle</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>パラパラアニメーション支援</TD><TD>GgafDx::UvFlipper</TD></TR>
 * <TR><TD>getSeXmtr()</TD><TD>効果音発生管理</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * <TR><TD>getWorldCollisionChecker()</TD><TD>衝突判定支援</TD><TD>GgafLib::WorldCollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class DefaultMassSpriteActor : public GgafDx::MassSpriteActor {

private:
    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
        float _21, _22, _23, _24;   // : TEXCOORD2  World変換行列、２行目
        float _31, _32, _33, _34;   // : TEXCOORD3  World変換行列、３行目
        float _41, _42, _43, _44;   // : TEXCOORD4  World変換行列、４行目
        float offset_u, offset_v;   // : TEXCOORD5  テクスチャオフセット
        float r, g, b, a;           // : TEXCOORD6  マテリアルカラー
    };
    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info);
public:
    /** 衝突判定支援オブジェクト */
    WorldCollisionChecker* _pWorldCollisionChecker;

    DefaultMassSpriteActor(const char* prm_name, const char* prm_model);

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

    virtual void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual GgafDx::CollisionChecker* createChecker() override;
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

    virtual ~DefaultMassSpriteActor();

};

}
#endif /*GGAF_LIB_DEFAULTMASSSPRITEACTOR_H_*/
