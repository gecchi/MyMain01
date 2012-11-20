#ifndef ENEMYHERMIONE_H_
#define ENEMYHERMIONE_H_
namespace VioletVreath {

HASHVAL(EVENT_HERMIONE_SAYONARA);

/**
 * 敵機ヘルミオネ  .
 * グラの触手に挑戦ッッ！！！
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyHermione :
  public GgafLib::DefaultMorphMeshActor {
//class EnemyHermione : public GgafLib::CubeMapMorphMeshActor {

    /** 原点から初期カメラZ位置の距離 */
    int dZ_camera_init_;
public:
    enum {
        PROG_MOVE = 1  ,
    };

    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION,
    };

    class Arm {
    public:
        angle pos_Rz_;
        angle pos_Ry_;
        EnemyHermioneArm** papArmPart_;
        Arm() : pos_Rz_(0),pos_Ry_(0),papArmPart_(nullptr) {}
        ~Arm() {
            DELETEARR_IMPOSSIBLE_NULL(papArmPart_);
        }
    };
    int num_arm_; //腕の数
    int num_arm_part_;  //腕の節数（3以上）
    Arm* paArm_;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyHermione(const char* prm_name);

    void onCreateModel() override;

    /**
     * ヘルミオネの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * ヘルミオネがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * ヘルミオネの振る舞い .
     */
    void processBehavior() override;

    /**
     * ヘルミオネの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * ヘルミオネの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;
    void addArm(angle prm_rz, angle prm_ry);
    virtual ~EnemyHermione();
};

}
#endif /*ENEMYHERMIONE_H_*/

