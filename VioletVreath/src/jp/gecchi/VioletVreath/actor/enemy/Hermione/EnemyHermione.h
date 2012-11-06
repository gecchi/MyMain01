#ifndef ENEMYHERMIONE_H_
#define ENEMYHERMIONE_H_
namespace VioletVreath {


/**
 * �G�@�w���~�I�l  .
 * �O���̐G��ɒ���b�b�I�I�I
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyHermione :
  public GgafLib::DefaultMorphMeshActor {
//class EnemyHermione : public GgafLib::CubeMapMorphMeshActor {

    /** ���_���珉���J����Z�ʒu�̋��� */
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
        EnemyHermioneArmBody** papArmBody_;
        EnemyHermioneArmHead* pArmHead_;
        Arm() : pos_Rz_(0),pos_Ry_(0),papArmBody_(NULL),pArmHead_(NULL) {}
        ~Arm() {
            DELETEARR_IMPOSSIBLE_NULL(papArmBody_);
        }
    };
    int num_arm_; //�r�̐�
    int num_arm_body_;  //ArmBody�̌��i�P�ȏ�j
    Arm* paArm_;

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyHermione(const char* prm_name);

    void onCreateModel() override;

    /**
     * �w���~�I�l�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �w���~�I�l���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �w���~�I�l�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �w���~�I�l�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �w���~�I�l�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;
    void addArm(angle prm_rz, angle prm_ry);
    virtual ~EnemyHermione();
};

}
#endif /*ENEMYHERMIONE_H_*/

