#ifndef WALLACTOR_H_
#define WALLACTOR_H_


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

namespace GgafDx9LibStg {

/**
 * 外壁シーン(WalledSectionScene)の壁ブロック基底クラス .
 * 外壁シーン(WalledSectionScene)の構成要素の壁ブロックは本クラスを継承する必要がある。
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class WallActor : public GgafDx9Core::GgafDx9MeshSetActor {
    friend class GgafDx9EffectManager;

public:
    /** [r]壁ブロックプリズム位置情報(> 0の場合はプリズム、0の場合はBOX) */
    int _pos_prism;
    /** [r]壁ブロック表示面情報 */
    int _wall_draw_face;
    /** [r]壁ブロックの長さ（X座標軸長さ）*/
    int _wall_dep;
    /** [r]壁ブロックの高さ（Y座標軸長さ）*/
    int _wall_height;
    /** [r]壁ブロックの幅（Z座標軸長さ）*/
    int _wall_width;
//    /** [r]壁ブロック移動スピード(値は正、但し移動方向はX軸負の方向) */
//    int _scrool_speed;


    GgafDx9Core::GgafDx9GeometricScaler* _pScaler;
    GgafDx9LibStg::CollisionChecker* _pCollisionChecker;

    /** [r]外壁シーン */
    WalledSectionScene* _pWalledSectionScene;


    WallActor(const char* prm_name,
              const char* prm_model_id,
              const char* prm_effect_id,
              const char* prm_technique);


    virtual void executeHitChk_MeAnd(GgafActor* prm_pOtherActor);

    virtual void onCreateModel() override {
    }
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processDraw() = 0;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual bool isOutOfUniverse() override;

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    /**
     * 壁ブロックを設定する
     * @param prm_wall_draw_face 壁ブロック表示面情報
     * @param prm_aColliBoxStretch 壁ブロック当たり判定情報
     */
    virtual void config(WalledSectionScene* prm_pWalledSectionScene,
                        int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch);


    virtual ~WallActor();
};

}
#endif /*WALLACTOR_H_*/
