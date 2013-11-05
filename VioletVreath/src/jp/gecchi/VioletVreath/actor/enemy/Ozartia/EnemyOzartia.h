#ifndef ENEMYOZARTIA_H_
#define ENEMYOZARTIA_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"


namespace VioletVreath {

/**
 * 敵機オーツァルティア .
 * ちょっと賢い中型機の予定。
 * @version 1.00
 * @since 2013/10/01
 * @author Masatoshi Tsuge
 */
class EnemyOzartia : public GgafLib::DefaultMorphMeshActor {

public:

    enum {
        PROG1_INIT   ,
        PROG1_ENTRY  ,
        PROG1_STAY   ,
        PROG1_MV_POS0 ,
        PROG1_MV_POS1 ,
        PROG1_MV_POS2 ,
        PROG1_MV_POS3 ,
        PROG1_MV_POS4 ,
        PROG1_MV_POS5 ,
        PROG1_MOVE_START ,
        PROG1_MOVING ,
        PROG1_LEAVE ,
        PROG_BANPEI1_,
    };

    enum {
        PROG2_WAIT ,
        PROG2_SHOT01_01 ,
        PROG2_SHOT01_02 ,
        PROG2_SHOT02 ,
        PROG2_SHOT03 ,
        PROG2_SHOT04 ,
        PROG_BANPEI2_,
    };

    enum {
        MPH_CLOSE  ,
        MPH_SHOT01 ,
        MPH_SHOT02 ,
        MPH_SHOT03 ,
        MPH_SHOT04 ,
    };

    enum {
        SE_ENTRY,
        SE_DAMAGED ,
        SE_UNDAMAGED,
        SE_EXPLOSION,
        SE_SHOT01 ,
        SE_SHOT02 ,
        SE_SHOT03 ,
        SE_SHOT04 ,
    };

    /** ショット関連の進捗状態 */
    GgafCore::GgafProgress* pProg2_;

    bool is_hit_;

    GgafCore::GgafActorDepository* pDepo_Shot01_;
    GgafLib::LaserChipDepository*  pDepo_Shot02_;

    GgafDxCore::GgafDxGeoElem posMvTarget_;

    bool faceang_to_ship_;
public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyOzartia(const char* prm_name);

    void onCreateModel() override;

    /**
     * タゴラスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * タゴラスのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * タゴラスの振る舞い .
     */
    void processBehavior() override;

    /**
     * タゴラスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * タゴラスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyOzartia();
};

}
#endif /*ENEMYOZARTIA_H_*/

