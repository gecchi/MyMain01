#ifndef ENEMYANTIOPE_H_
#define ENEMYANTIOPE_H_
namespace VioletVreath {

/**
 * 敵機アンティオペ .
 * 物質と反物質の瞬きのようなイメージの動き
 * @version 1.00
 * @since 2013/04/08
 * @author Masatoshi Tsuge
 */
class EnemyAntiope :
    public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION = 0,
    };

    enum {
        PROG_INIT = 1 ,
        PROG_ENTRY,
        PROG_MOVE01   ,
        PROG_LEAVE,

    };


    GgafDxCore::GgafDxGeoElem leave_pos_;
public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyAntiope(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    void onCreateModel() override;

    /**
     * サッフォーの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * サッフォーのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * サッフォーの振る舞い .
     */
    void processBehavior() override;

    /**
     * サッフォーの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * サッフォーの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyAntiope();
};

}
#endif /*ENEMYANTIOPE_H_*/

