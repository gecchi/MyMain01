#ifndef GGAF_LIB_MASSWALLACTOR_H_
#define GGAF_LIB_MASSWALLACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MassMeshActor.h"

#define FACE_A_IDX 5
#define FACE_B_IDX 4
#define FACE_C_IDX 3
#define FACE_D_IDX 2
#define FACE_E_IDX 1
#define FACE_F_IDX 0

#define FACE_A_BIT 32  // 0b100000
#define FACE_B_BIT 16  // 0b010000
#define FACE_C_BIT 8   // 0b001000
#define FACE_D_BIT 4   // 0b000100
#define FACE_E_BIT 2   // 0b000010
#define FACE_F_BIT 1   // 0b000001

namespace GgafLib {

/**
 * 外壁シーン(WallSectionScene)の壁ブロック基底クラス .
 * 外壁シーン(WallSectionScene)の構成要素の壁ブロックは本クラスを継承する必要がある。
 * @version 1.00
 * @since 2016/03/08
 * @author Masatoshi Tsuge
 */
class MassWallActor : public GgafDx::MassMeshActor {
    friend class EffectManager;

protected:
    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
        float _21, _22, _23, _24;   // : TEXCOORD2  World変換行列、２行目
        float _31, _32, _33, _34;   // : TEXCOORD3  World変換行列、３行目
        float _41, _42, _43, _44;   // : TEXCOORD4  World変換行列、４行目
        float r, g, b, a;           // : TEXCOORD5  マテリアルカラー
        float _wall_draw_face, _pos_info;  // : TEXCOORD6 壁ブロックプリズム位置情報, 壁ブロック表示面
    };
    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info);

public:
    /** プリズム無条件追加描画不要面テーブル */
    static std::map<int, UINT> _draw_face;

    /** [r]壁ブロック情報(0の場合はBOX:0より大きい場合はプリズム又はピラミッド) */
    pos_t _pos_info;
    /** [r]壁ブロック表示面情報 */
    int _wall_draw_face;
    /** [r]壁ブロックの長さ（X座標軸長さ）*/
    coord _wall_dep;
    /** [r]壁ブロックの高さ（Y座標軸長さ）*/
    coord _wall_height;
    /** [r]壁ブロックの幅（Z座標軸長さ）*/
    coord _wall_width;
//    /** [r]壁ブロック移動スピード(値は正、但し移動方向はX軸負の方向) */
//    int _feature_p1;
    WorldCollisionChecker* _pWorldCollisionChecker;
    /** [r]外壁シーン */
    WallSectionScene* _pWallSectionScene;

public:
    MassWallActor(const char* prm_name, const char* prm_model);
    MassWallActor(const char* prm_name,
                  const char* prm_model,
                  const char* prm_effect,
                  const char* prm_technique);
//    MassWallActor(const char* prm_name,
//                  const char* prm_model,
//                  const char* prm_effect_id,
//                  const char* prm_technique);
//                  GgafDx::CollisionChecker* prm_pColliChecker);

    void init();

    static bool initStatic(MassWallActor* prm_pMassWallActor);

    virtual void onCreateModel() override {
    }
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void processPreDraw() override;

    virtual void processDraw() override;

    virtual bool isOutOfSpacetime() const override;

    virtual int isOutOfView() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override {
    }

    virtual void drawHitArea() override;

    /**
     * 壁ブロックを設定する .
     * @param prm_pWallSectionScene WallSectionSceneオブジェクト
     * @param prm_pos_info 0:BOX/1～:プリズムorピラミッド位置番号(POS_***)
     * @param prm_wall_draw_face 壁ブロック表示面情報
     * @param prm_aColliBoxStretch 壁ブロック当たり判定情報
     */
    virtual void config(WallSectionScene* prm_pWallSectionScene,
                        pos_t prm_pos_info, int prm_wall_draw_face, int* prm_aColliBoxStretch);

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

    virtual ~MassWallActor();
};

}
#endif /*GGAF_LIB_WALLPARTSACTOR_H_*/
