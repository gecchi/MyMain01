#ifndef ENEMYERES_H_
#define ENEMYERES_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機エレス .
 * 画面右端で折り返して左に直進します。<BR>
 * initialize()までに上書き可能な設定可能なパラメータ<BR>
 * ・_X,_Y,_Z 初期位置、但し _Z<0 であること。（折り返しが逆になって変だから）<BR>
 * ・X_turn_, Y_turn_ 折り返し目標XY座標。初期位置からこのこの地点を目指すッス。<BR>
 *
 */
class EnemyEres : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION ,
    };

    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_EnemyEresShots001_;
    /** スプラインプログラム */
    GgafLib::SplineKurokoLeader* pProgram_EresMove_;

    /** GgafActorDepositoryをコンストラクタで生成したか否か */
    bool createGgafActorDepository_;

    int X_turn_; // 折り返すX座標
    int Y_turn_; // 折り返すY座標
    int Z_turn_; // 折り返すZ座標

    int iMovePatternNo_;
    frame frame_Active_;
    SplineLineConnection* pSplLineConnection_;

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

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    bool isOutOfUniverse() override;

    void onInactive() override;

    virtual ~EnemyEres();
};

}
#endif /*ENEMYERES_H_*/

