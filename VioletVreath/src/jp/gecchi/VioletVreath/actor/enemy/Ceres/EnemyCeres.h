#ifndef ENEMYCERES_H_
#define ENEMYCERES_H_
namespace VioletVreath {

/**
 * 敵機ケレス .
 * 画面右端で折り返して左に直進します。<BR>
 * initialize()までに上書き可能な設定可能なパラメータ<BR>
 * ・_X,_Y,_Z 初期位置、但し _Z<0 であること。（折り返しが逆になって変だから）<BR>
 * ・_X_turn, _Y_turn 折り返し目標XY座標。初期位置からこのこの地点を目指すッス。<BR>
 * ・_veloBegin 折り返し地点に行くまでの加速度<BR>
 *
 */
class EnemyCeres : public GgafLib::DefaultMeshSetActor {

private:

public:
    /** 弾ストック */
    GgafCore::GgafActorDepository* _pDepo_EnemyCeresShots001;
    /** スプラインプログラム */
    GgafLib::SplineSequence* _pProgram_CeresMove;

    /** GgafActorDepositoryをコンストラクタで生成したか否か */
    bool _createGgafActorDepository;

    int _X_turn; // 折り返すX座標
    int _Y_turn; // 折り返すY座標
    int _Z_turn; // 折り返すZ座標
    int _veloBegin;
    int _incZ;

    int _iMovePatternNo;
    frame _frame_Active;
    SplineLineConnection* _pSplLineCon;

    /**
     * コンストラクタ
     * @param prm_name オブジェクト
     * @param prm_pDepo_EnemyCeresShots001 発射弾ストックのアクター発送者
     * @return
     */
    EnemyCeres(const char* prm_name, GgafCore::GgafActorDepository* prm_pDepo_EnemyCeresShots001 = NULL);

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

