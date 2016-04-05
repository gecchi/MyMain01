#ifndef GGAFLIB_MASSWALLACTOR_H_
#define GGAFLIB_MASSWALLACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassMeshActor.h"

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
class MassWallActor : public GgafDxCore::GgafDxMassMeshActor {
    friend class GgafDxEffectManager;

protected:
    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
        float _21, _22, _23, _24;   // : TEXCOORD2  World変換行列、２行目
        float _31, _32, _33, _34;   // : TEXCOORD3  World変換行列、３行目
        float _41, _42, _43, _44;   // : TEXCOORD4  World変換行列、４行目
        float _wall_draw_face, _pos_info;  // : TEXCOORD5 壁ブロックプリズム位置情報, 壁ブロック表示面
    };
    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstaceData(void* prm, GgafDxCore::GgafDxMassModel::VertexInstaceDataInfo* out_info);

public:
    static D3DXHANDLE _h_distance_AlphaTarget;
    static D3DXHANDLE _h_wall_dep;
    static D3DXHANDLE _h_wall_height;
    static D3DXHANDLE _h_wall_width;
    static D3DXHANDLE _h_ah_POS_PRISM_ZX;
    static D3DXHANDLE _h_fh_POS_PRISM_ZX;
    static D3DXHANDLE _h_ah_POS_PRISM_YZ;
    static D3DXHANDLE _h_fh_POS_PRISM_YZ;
    static D3DXHANDLE _h_ah_POS_PRISM_XY;
    static D3DXHANDLE _h_fh_POS_PRISM_XY;
    static D3DXHANDLE _h_reflectance;

    /** プリズム無条件追加描画不要面テーブル */
    static std::map<int, UINT> _delface;

    /** [r]壁ブロックプリズム位置情報(> 0の場合はプリズム又はピラミッド、0の場合はBOX) */
    int _pos_info;
    /** [r]壁ブロック表示面情報 */
    int _wall_draw_face;
    /** [r]壁ブロックの長さ（X座標軸長さ）*/
    coord _wall_dep;
    /** [r]壁ブロックの高さ（Y座標軸長さ）*/
    coord _wall_height;
    /** [r]壁ブロックの幅（Z座標軸長さ）*/
    coord _wall_width;
//    /** [r]壁ブロック移動スピード(値は正、但し移動方向はX軸負の方向) */
//    int _scroll_speed;
    GgafLib::CollisionChecker3D* _pColliChecker;
    /** [r]外壁シーン */
    WallSectionScene* _pWallSectionScene;

public:
    MassWallActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);
    MassWallActor(const char* prm_name,
                  const char* prm_model,
                  const char* prm_effect,
                  const char* prm_technique,
                  GgafCore::GgafStatus* prm_pStat=nullptr);
//    MassWallActor(const char* prm_name,
//                  const char* prm_model_id,
//                  const char* prm_effect_id,
//                  const char* prm_technique,
//                  GgafCore::GgafStatus* prm_pStat,
//                  GgafDxCore::GgafDxChecker* prm_pChecker);

    void init();

    static bool initStatic(MassWallActor* prm_pMassWallActor);

    virtual void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

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

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    /**
     * 壁ブロックを設定する .
     * @param prm_pWallSectionScene WallSectionSceneオブジェクト
     * @param prm_pos_info プリズム位置番号（プリズム型ブロックの場合のみ）
     * @param prm_wall_draw_face 壁ブロック表示面情報
     * @param prm_aColliBoxStretch 壁ブロック当たり判定情報
     */
    virtual void config(WallSectionScene* prm_pWallSectionScene,
                        int prm_pos_info, int prm_wall_draw_face, int* prm_aColliBoxStretch);

    inline CollisionChecker3D* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~MassWallActor();
};

}
#endif /*GGAFLIB_WALLPARTSACTOR_H_*/
