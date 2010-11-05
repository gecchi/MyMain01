#ifndef WALLACTOR_H_
#define WALLACTOR_H_


#define FACE_A_IDX 5
#define FACE_B_IDX 4
#define FACE_C_IDX 3
#define FACE_D_IDX 2
#define FACE_E_IDX 1
#define FACE_F_IDX 0


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

private:
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

public:
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;
    GgafDx9LibStg::CollisionChecker* _pCollisionChecker;

    /** [r]外壁シーン */
    WalledSectionScene* _pWalledSectionScene;
    D3DXHANDLE _h_distance_AlphaTarget;

    WallActor(const char* prm_name, const char* prm_model);


    virtual void executeHitChk_MeAnd(GgafActor* prm_pOtherActor);

    virtual void onCreateModel() override {
    }
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processDraw() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual bool isOutOfUniverse() override;

    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {
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
    virtual void config(WalledSectionScene* prm_pWalledSectionScene, int prm_wall_draw_face, int* prm_aColliBoxStretch);


    virtual ~WallActor();
};

}
#endif /*WALLACTOR_H_*/
