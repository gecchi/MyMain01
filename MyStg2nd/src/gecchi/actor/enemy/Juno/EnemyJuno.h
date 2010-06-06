#ifndef ENEMYJUNO_H_
#define ENEMYJUNO_H_
namespace MyStg2nd {

//ジュノー
class EnemyJuno : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    int _iMovePatternNo;
    /** 弾ストック */
    GgafCore::GgafActorDispatcher* _pDispatcher_Shot;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDispatcher* _pDispatcher_ShotEffect;
    bool _do_Shot;
    bool _can_Shot;
    DWORD _frame_when_shot;
    int _nMaxShot;
    int _nShot;
    velo _veloMv_begin;

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
     * @param prm_pDispatcher (GgafDx9DrawableActor*)にキャスト可能なアクターをサブに持つディスパッチャーのポインタ
     */
    void setDispatcher_Shot(GgafCore::GgafActorDispatcher* prm_pDispatcher) {
        _pDispatcher_Shot = prm_pDispatcher;
    }
};

}
#endif /*ENEMYJUNO_H_*/

