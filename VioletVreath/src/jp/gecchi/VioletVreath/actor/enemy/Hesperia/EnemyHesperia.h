#ifndef ENEMYHESPERIA_H_
#define ENEMYHESPERIA_H_
namespace VioletVreath {

/**
 * �G�@�w�X�y���A .
 * ���[�U�[��݂͂����ȁE�E�E
 * @version 1.00
 * @since 2012/08/29
 * @author Masatoshi Tsuge
 */
class EnemyHesperia : public GgafLib::DefaultMorphMeshActor {

private:
    /** ���ˍς݃��[�U�[�`�b�v�� */
    int cnt_laserchip_;

public:
    enum {
        PROG_ENTRY = 1,
        PROG_MOVE,
        PROG_HATCH_OPEN,
        PROG_FIRE,
        PROG_HATCH_CLOSE,
        PROG_NOTHING,
    };

    enum {
        SE_EXPLOSION = 0,
        SE_DAMAGED,
        SE_HATCH_OPEN,
        SE_FIRE,
        SE_HATCH_CLOSE,
    };

    /** �w�X�y���A�P�͂����Ԃ���ۂ̍ő僌�[�U�[Way�� */
    static int max_laser_way_;

    /** ���˃��[�U�[�`�b�v�̐��i���[�U�[�����j */
    int laser_length_;
    coord dX_,dZ_;
    /** ���[�U�[���ˈʒu�̍��W�i�w�X�y���A�̃��[�J�����W�j */
    GgafDxCore::GgafDxGeoElem* paLocalPos_Laser_;
    /** ���[�U�[���ˎ��A�ڕW������ʒu�̍������W�i���@����̑��΍��W�j */
    GgafDxCore::GgafDxGeoElem* paPos_Target_;
    /** ���[�U�[�Z�b�g�̃X�g�A�[(���[�U�[�`�b�v�̃f�|�W�g���̃f�|�W�g��) */
    GgafCore::GgafActorDepositoryStore* pLaserChipDepoStore_;
    /** �f�|�W�g���}�l�[�W���[�ւ̐ڑ� */
    DepositoryConnection* pCon_LaserChipDepoStore_;
    /** ���[�U�[�Z�b�g(���[�U�[�`�b�v�̃f�|�W�g��) */
    GgafLib::LaserChipDepository** papLaserChipDepo_;

    EnemyHesperia(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    /**
     * ���[�U�[��U�艺�낷���߂̏㏸�iY���j���������߂� .
     * <pre>
     *                         ^ Y
     *                         |
     *                         |�c�c�c�c
     *                       �^|     ^
     *                     �^  |     |
     *                   �^    |     | DY�i�Ԃ��l�j
     *                 �^      |     |
     *               �^        |     v
     *             �^         �G�c�c�c�c
     *           �^��=30��     |
     *     ---���@-------------+--------->
     *       �^:               |
     *     �^  :               |
     *   �^    :<------------->|
     *         :     DT(����)  |
     * </pre>
     * @param pThis
     * @param pMyShip
     * @param DT
     * @return �㏸Y�������iDY�j
     */
    static coord getTurnDY(GgafDxCore::GgafDxGeometricActor* pThis,
                           GgafDxCore::GgafDxGeometricActor* pMyShip,
                           coord DT);

    virtual ~EnemyHesperia();
};

}
#endif /*ENEMYHESPERIA_H_*/

