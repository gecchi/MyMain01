#ifndef FORMATIONDELHEID_H_
#define FORMATIONDELHEID_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DepositoryFormation.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機デルヘイド用フォーメーション基底 .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationDelheid : public GgafLib::DepositoryFormation {

public:
    /** デルヘイド借り入れ元Depository資源への接続 */
    DepositoryConnection* pConn_pDelheidDepo_;
    /** デルヘイドの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* pConn_pShotDepo_;
    /** 始点・終点の座標計算のためのダミー */
    EnemyDelheid* pDummy_;

    /** 始点のアリサナ */
    EnemyAlisana* pAlisana_start;
    /** 終点のアリサナ */
    EnemyAlisana* pAlisana_goal;
    /** [r]設置座標と向き */
    GgafDx::GeoElem geoLocate_;

    /** 編隊数(RANK変動) */
    int RV_Num_;
    /** 編隊メンバーの出現間隔フレーム(RANK変動) */
    frame RV_LaunchInterval;
    /** 編隊メンバーの初期移動速度(RANK変動) */
    velo RV_MvVelo_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     */
    FormationDelheid(const char* prm_name) ;

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCalledUpDelheid(EnemyDelheid* pEnemyDelheid) = 0;

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合の処理実装 .
     * @param prm_pActor_last_destroyed  最後に破壊されたアクター
     */
    virtual void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override;

    virtual void processBehavior() override;
    /**
     * スプライン情報を取得。
     * 下位で実装して下さい。
     * @return
     */
    virtual GgafDx::CurveManufacture* getSplManuf() = 0;

    virtual void onSayonaraAll() override;


    static void order1(GgafCore::Actor* prm_pDelheid, void* prm1, void* prm2, void* prm3);

    static void order2(GgafCore::Actor* prm_pDelheid, void* prm1, void* prm2, void* prm3);

    static void order3(GgafCore::Actor* prm_pDelheid, void* prm1, void* prm2, void* prm3);

    /**
     * 設置座標と向きをセット .
     */
    void setPosition(coord x, coord y, coord z,
                  angle rx, angle rz, angle ry) {
        geoLocate_.x = x;
        geoLocate_.y = y;
        geoLocate_.z = z;
        geoLocate_.rx = rx;
        geoLocate_.rz = rz;
        geoLocate_.ry = ry;
    }

    virtual ~FormationDelheid();
};

}
#endif /*FORMATIONDELHEID_H_*/
