#ifndef ENEMYEMUS_H_
#define ENEMYEMUS_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * 敵機エムス .
 * レーザーハッチ。
 * @version 1.00
 * @since 2012/10/22
 * @author Masatoshi Tsuge
 */
class EnemyEmus : public GgafLib::DefaultMorphMeshActor {

public:
    enum {
        PROG_INIT       ,
        PROG_HATCH_CLOSE,
        PROG_HATCH_OPEN ,
        PROG_FIRE       ,
        PROG_NOTHING    ,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* pScaler_;

    /** [r]状況 */
    bool is_open_hatch_;
    /** [r/w]ハッチが開いているフレーム間隔 */
    frame frame_of_open_interval_;
    /** [r/w]ハッチが閉じていているフレーム間隔 */
    frame frame_of_close_interval_;
    /** [r/w]ハッチ開＞閉 及び、閉＞開 のモーフアニメーションフレーム数 */
    frame frame_of_morph_interval_;

//    /** [r]レーザーセットのストアー(レーザーチップのデポジトリのデポジトリ) */
//    GgafCore::GgafActorDepositoryStore* pDepoStore_laser_set;
//    /** [r]デポジトリマネージャーへの接続 */
//    DepositoryConnection* pConn_pDepoStore_laser_set;
    /** [r]レーザーセット(レーザーチップのデポジトリ) */
    GgafCore::GgafActorDepository* pDepo_;

    bool is_firing_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyEmus(const char* prm_name);

    /**
     * エムスモデルが生成された際に１回だけ実行される処理
     */
    void onCreateModel() override;
    /**
     * エムスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * エムスがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * エムスの振る舞い .
     */
    void processBehavior() override;
    void processChangeGeoFinal() override;
    /**
     * エムスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * エムスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    virtual ~EnemyEmus();
};

}
#endif /*ENEMYEMUS_H_*/

