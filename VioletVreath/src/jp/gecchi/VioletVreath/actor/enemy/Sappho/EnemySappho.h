#ifndef ENEMYSAPPHO_H_
#define ENEMYSAPPHO_H_
namespace VioletVreath {

/**
 * 敵機サッフォー .
 * 超連射６８Kの雑魚のように、
 * 現れて、目の前でちょっとウロウロして、逃げる。
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class EnemySappho :
    public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION = 0,
    };

    enum {
        PROG_INIT = 1 ,
        PROG_ENTRY,
        PROG_MOVE01   ,
        PROG_MOVE02  ,
        PROG_MOVE03   ,
        PROG_MOVE04   ,
    };
    /** [r]出現座標(フォーメーションオブジェクトが設定) */
    GgafDxCore::GgafDxGeoElem entry_pos_;
    /** [r]ウロウロする座標(フォーメーションオブジェクトが設定) */
    GgafDxCore::GgafDxGeoElem hanging_pos_;
    /** [r]退出座標(フォーメーションオブジェクトが設定) */
    GgafDxCore::GgafDxGeoElem leave_pos_;
public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemySappho(const char* prm_name);

    void onCreateModel() override;

    /**
     * パラスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * パラスのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * パラスの振る舞い .
     */
    void processBehavior() override;

    /**
     * パラスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * パラスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemySappho();
};

}
#endif /*ENEMYSAPPHO_H_*/

