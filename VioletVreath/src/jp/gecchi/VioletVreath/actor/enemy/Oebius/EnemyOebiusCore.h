#ifndef ENEMYOEBIUSCORE_H_
#define ENEMYOEBIUSCORE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * エビウスのコア .
 * @version 1.00
 * @since 2014/11/11
 * @author Masatoshi Tsuge
 */
class EnemyOebiusCore : public GgafLib::DefaultMorphMeshActor {

public:

    enum {
        PROG_INIT  ,
        PROG_ENTRY ,
        PROG_WAIT01 ,
        PROG_LEAVE ,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED  ,
        SE_UNDAMAGED  ,
        SE_EXPLOSION,
        SE_FIRE,
    };

    EnemyOebiusController* pController_;

    /** フィードイン・フェードアウト支援 */
    GgafDxCore::GgafDxAlphaFader* pAFader_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyOebiusCore(const char* prm_name, EnemyOebiusController* prm_pController);

    void onCreateModel() override;

    /**
     * エビウスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * エビウスのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * エビウスの振る舞い .
     */
    void processBehavior() override;

    /**
     * エビウスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * エビウスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyOebiusCore();
};

}
#endif /*ENEMYOEBIUSCORE_H_*/

