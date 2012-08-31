#ifndef ENEMYHESPERIA_H_
#define ENEMYHESPERIA_H_
namespace VioletVreath {

/**
 * 敵機ヘスペリア .
 * レーザー戦艦みたいな・・・
 * @version 1.00
 * @since 2012/08/29
 * @author Masatoshi Tsuge
 */
class EnemyHesperia : public GgafLib::DefaultMorphMeshActor {

private:
    /** 発射済みレーザーチップ数 */
    int cnt_laserchip_;

public:
    enum {
        PROG_ENTRY = 1,
        PROG_MOVE,
        PROG_HATCH_OPEN,
        PROG_FIRE,
        PROG_HATCH_CLOSE,
        PROG_NOTHING,
    };

    enum {
        SE_EXPLOSION = 0,
        SE_DAMAGED,
        SE_HATCH_OPEN,
        SE_FIRE,
        SE_HATCH_CLOSE,
    };

    /** ヘスペリア１艦が発車する際の最大レーザーWay数 */
    static int max_laser_way_;

    /** 発射レーザーチップの数（レーザー長さ） */
    int laser_length_;
    coord dX_,dZ_;
    /** レーザー発射位置の座標（ヘスペリアのローカル座標） */
    GgafDxCore::GgafDxGeoElem* paLocalPos_Laser_;
    /** レーザー発射時、目標すだれ位置の差分座標（自機からの相対座標） */
    GgafDxCore::GgafDxGeoElem* paPos_Target_;
    /** レーザーセットのストアー(レーザーチップのデポジトリのデポジトリ) */
    GgafCore::GgafActorDepositoryStore* pLaserChipDepoStore_;
    /** デポジトリマネージャーへの接続 */
    DepositoryConnection* pCon_LaserChipDepoStore_;
    /** レーザーセット(レーザーチップのデポジトリ) */
    GgafLib::LaserChipDepository** papLaserChipDepo_;

    EnemyHesperia(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

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
     *           ／θ=30°     |
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

    virtual ~EnemyHesperia();
};

}
#endif /*ENEMYHESPERIA_H_*/

