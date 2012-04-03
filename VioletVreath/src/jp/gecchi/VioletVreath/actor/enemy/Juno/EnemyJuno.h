#ifndef ENEMYJUNO_H_
#define ENEMYJUNO_H_
namespace VioletVreath {

//ジュノー
class EnemyJuno : public GgafLib::DefaultMeshSetActor {

public:
    int iMovePatternNo_;
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;
    bool do_Shot_;
    bool can_Shot_;
    frame frame_when_shot_;
    int max_shots_;
    int shot_num_;
    velo velo_mv_begin_;

    EnemyJuno(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyJuno();

    /**
     * 発射弾設定 .
     * @param prm_pDepo (GgafDxDrawableActor*)にキャスト可能なアクターをサブに持つデポジトリのポインタ
     */
    void setDepository_Shot(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_Shot_ = prm_pDepo;
    }

    static void callbackDispatched(GgafDxCore::GgafDxGeometricActor* prm_pDispatched,
                                   int prm_dispatched_seq,
                                   int prm_set_seq);
};

}
#endif /*ENEMYJUNO_H_*/

