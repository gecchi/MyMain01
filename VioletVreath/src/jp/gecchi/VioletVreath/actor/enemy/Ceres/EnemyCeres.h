#ifndef ENEMYCERES_H_
#define ENEMYCERES_H_
namespace VioletVreath {

/**
 * 敵機ケレス .
 * 画面右端で折り返して左に直進します。<BR>
 * initialize()までに上書き可能な設定可能なパラメータ<BR>
 * ・_X,_Y,_Z 初期位置、但し _Z<0 であること。（折り返しが逆になって変だから）<BR>
 * ・X_turn_, Y_turn_ 折り返し目標XY座標。初期位置からこのこの地点を目指すッス。<BR>
 *
 */
class EnemyCeres : public GgafLib::DefaultMeshSetActor {

private:

public:
    enum {
        SE_EXPLOSION = 0,
    };

    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_EnemyCeresShots001_;
    /** スプラインプログラム */
    GgafLib::SplineSequence* pProgram_CeresMove_;

    /** GgafActorDepositoryをコンストラクタで生成したか否か */
    bool createGgafActorDepository_;

    int X_turn_; // 折り返すX座標
    int Y_turn_; // 折り返すY座標
    int Z_turn_; // 折り返すZ座標

    int iMovePatternNo_;
    frame frame_Active_;
    SplineLineConnection* pSplLineCon_;

    /**
     * コンストラクタ
     * @param prm_name オブジェクト
     * @param prm_pDepo_EnemyCeresShots001 発射弾ストックのアクター発送者
     * @return
     */
    EnemyCeres(const char* prm_name, GgafCore::GgafActorDepository* prm_pDepo_EnemyCeresShots001 = nullptr);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    bool isOutOfUniverse() override;

    void onInactive() override;

    virtual ~EnemyCeres();
};

}
#endif /*ENEMYCERES_H_*/

