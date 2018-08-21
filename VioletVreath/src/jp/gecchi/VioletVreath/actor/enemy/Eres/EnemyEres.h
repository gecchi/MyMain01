#ifndef ENEMYERES_H_
#define ENEMYERES_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機エレス .
 * 画面右端で折り返して左に直進します。<BR>
 * initialize()までに上書き可能な設定可能なパラメータ<BR>
 * ・_x,_y,_z 初期位置、但し _z<0 であること。（折り返しが逆になって変だから）<BR>
 * ・X_turn_, Y_turn_ 折り返し目標XY座標。初期位置からこのこの地点を目指すッス。<BR>
 *
 */
class EnemyEres : public GgafLib::DefaultMeshSetActor {

public:
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_shot001_;
    /** スプラインプログラム */
    GgafLib::SplineLeader* pSplineLeader_;
    /** GgafActorDepositoryをコンストラクタで生成したか否か */
    bool createGgafActorDepository_;

    int iMovePatternNo_;
    GgafLib::SplineManufactureConnection* pSplManufConn_;

public:
    /**
     * コンストラクタ
     * @param prm_name オブジェクト
     * @param prm_pDepo_EnemyEresShots001 発射弾ストックのアクター発送者
     * @return
     */
    EnemyEres(const char* prm_name, GgafCore::GgafActorDepository* prm_pDepo_EnemyEresShots001 = nullptr);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    bool isOutOfSpacetime() const override;

    void onInactive() override;

    virtual ~EnemyEres();
};

}
#endif /*ENEMYERES_H_*/

