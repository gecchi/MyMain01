#ifndef ENEMYESPERIA_H_
#define ENEMYESPERIA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * 敵機エスペリア .
 * レーザー戦艦みたいな・・・
 * @version 1.00
 * @since 2012/08/29
 * @author Masatoshi Tsuge
 */
class EnemyEsperia : public GgafLib::DefaultMorphMeshActor {

private:
    /** 発射済みレーザーチップ数 */
    int cnt_laserchip_;

public:
    /** [r]エスペリア１艦が発車する際の最大レーザーWay数 */
    static int max_laser_way_;

    /** [r]本エスペリアの今回のレーザーWay数 */
    int now_laser_way_;
    /** [r]発射レーザーチップの数（レーザー長さ） */
    int laser_length_;
    /** [r]レーザー発射時のX軸方向の自機との距離 */
    coord dX_;
    /** [r]レーザー発射時のZ軸方向の自機との距離 */
    coord dZ_;
    /** [r]レーザー発射位置の座標（エスペリアのローカル座標） */
    GgafDxCore::GgafDxGeoElem* paLocalPos_laser_;
    /** [r]レーザー発射時、目標すだれ位置の差分座標（自機からの相対座標） */
    GgafDxCore::GgafDxGeoElem* paPos_target_;
    /** [r]レーザーセットのストアー(レーザーチップのデポジトリのデポジトリ) */
    GgafCore::GgafActorDepositoryStore* pDepoStore_laser_set;
    /** [r]デポジトリマネージャーへの接続 */
    DepositoryConnection* pConn_pDepoStore_laser_set;
    /** [r]レーザーセット(レーザーチップのデポジトリ) */
    GgafLib::LaserChipDepository** papLaserChipDepo_;

public:
    EnemyEsperia(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    /**
     * レーザーを振り下ろすための上昇（Y軸）距離を求める .
     * <pre>
     *                         ^ Y
     *                         |
     *                         |…………
     *                       ／|     ^
     *                     ／  |     |
     *                   ／    |     | DY（返す値）
     *                 ／      |     |
     *               ／        |     v
     *             ／         敵…………
     *           ／θ=５°     |
     *     ---自機-------------+--------->
     *       ／:               |
     *     ／  :               |
     *   ／    :<------------->|
     *         :     DT(引数)  |
     * </pre>
     * @param pThis
     * @param pMyShip
     * @param DT
     * @return 上昇Y軸距離（DY）
     */
    static coord getTurnDY(GgafDxCore::GgafDxGeometricActor* pThis,
                           GgafDxCore::GgafDxGeometricActor* pMyShip,
                           coord DT);

    virtual ~EnemyEsperia();
};

}
#endif /*ENEMYESPERIA_H_*/

