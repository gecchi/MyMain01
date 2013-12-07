#ifndef ENEMYHALIA_H_
#define ENEMYHALIA_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * 敵機ハリア .
 * スペハリのトモスもどき？
 * @version 1.00
 * @since 2010/08/03
 * @author Masatoshi Tsuge
 */
class EnemyHalia : public GgafLib::DefaultMorphMeshActor {
//class EnemyHalia : public GgafLib::CubeMapMorphMeshActor {

    /** 黒衣の助手A */
    GgafDxCore::GgafDxKurokoAsstA* pKurokoAsstA_;
    /** 移動スプラインプログラム */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;

    /** 原点から初期カメラZ位置の距離 */
    int dZ_camera_init_;
public:
    enum {
        PROG_MOVE      ,
        PROG_TURN_OPEN ,
        PROG_FIRE_BEGIN,
        PROG_IN_FIRE   ,
        PROG_CLOSE     ,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED  ,
        SE_UNDAMAGED  ,
        SE_EXPLOSION,
        SE_FIRE,
    };
    /** 行動パターン番号 */
    int iMovePatternNo_;

    velo veloTopMv_;

    GgafLib::LaserChipDepository* pLaserChipDepo_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyHalia(const char* prm_name);

    void onCreateModel() override;

    /**
     * ハリアの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * ハリアがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * ハリアの振る舞い .
     */
    void processBehavior() override;

    /**
     * ハリアの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * ハリアの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * スプライン移動設定 .
     * initialize() までに設定して下さい。
     * @param prm_pKurokoLeader
     */
    void setSplineKurokoLeader(GgafLib::SplineKurokoLeader* prm_pKurokoLeader) {
        pKurokoLeader_ = prm_pKurokoLeader;
    }

    virtual ~EnemyHalia();
};

}
#endif /*ENEMYHALIA_H_*/

