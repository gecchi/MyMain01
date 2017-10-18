#ifndef ENEMYTHAGORAS_H_
#define ENEMYTHAGORAS_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機タゴラス .
 * トランジットレベル１
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class EnemyThagoras : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION ,
    };

    enum {
        PROG_INIT   ,
        PROG_ENTRY  ,
        PROG_MOVE01 ,
        PROG_LEAVE ,
        PROG_BANPEI,
    };

    /** 移動スプラインプログラム */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** 鼓動(スケール)を同期させる為のダミーアクター */
    GgafLib::DefaultGeometricActor* pActor4Sc_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyThagoras(const char* prm_name);

    void onCreateModel() override;

    /**
     * タゴラスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * タゴラスがアクティブになった瞬間の処理 .
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
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyThagoras();
};

}
#endif /*ENEMYTHAGORAS_H_*/

