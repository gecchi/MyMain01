#ifndef ENEMYESPERIA_H_
#define ENEMYESPERIA_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * �G�@�G�X�y���A .
 * ���[�U�[��݂͂����ȁE�E�E
 * @version 1.00
 * @since 2012/08/29
 * @author Masatoshi Tsuge
 */
class EnemyEsperia : public GgafLib::DefaultMorphMeshActor {

private:
    /** ���ˍς݃��[�U�[�`�b�v�� */
    int cnt_laserchip_;

public:
    enum {
        PROG_ENTRY,
        PROG_MOVE,
        PROG_HATCH_OPEN,
        PROG_FIRE,
        PROG_HATCH_CLOSE,
        PROG_NOTHING,
        _BANPEI_,
    };

    enum {
        SE_EXPLOSION,
        SE_DAMAGED,
        SE_HATCH_OPEN,
        SE_FIRE,
        SE_HATCH_CLOSE,
    };

    /** [r]�G�X�y���A�P�͂����Ԃ���ۂ̍ő僌�[�U�[Way�� */
    static int max_laser_way_;
    /** [r]�{�G�X�y���A�̍���̃��[�U�[Way�� */
    int now_laser_way_;
    /** [r]���˃��[�U�[�`�b�v�̐��i���[�U�[�����j */
    int laser_length_;
    /** [r]���[�U�[���ˎ���X�������̎��@�Ƃ̋��� */
    coord dX_;
    /** [r]���[�U�[���ˎ���Z�������̎��@�Ƃ̋��� */
    coord dZ_;
    /** [r]���[�U�[���ˈʒu�̍��W�i�G�X�y���A�̃��[�J�����W�j */
    GgafDxCore::GgafDxGeoElem* paLocalPos_Laser_;
    /** [r]���[�U�[���ˎ��A�ڕW������ʒu�̍������W�i���@����̑��΍��W�j */
    GgafDxCore::GgafDxGeoElem* paPos_Target_;
    /** [r]���[�U�[�Z�b�g�̃X�g�A�[(���[�U�[�`�b�v�̃f�|�W�g���̃f�|�W�g��) */
    GgafCore::GgafActorDepositoryStore* pLaserChipDepoStore_;
    /** [r]�f�|�W�g���}�l�[�W���[�ւ̐ڑ� */
    DepositoryConnection* pConn_LaserChipDepoStore_;
    /** [r]���[�U�[�Z�b�g(���[�U�[�`�b�v�̃f�|�W�g��) */
    GgafLib::LaserChipDepository** papLaserChipDepo_;

public:
    EnemyEsperia(const char* prm_name);

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
     *           �^��=�T��     |
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

    virtual ~EnemyEsperia();
};

}
#endif /*ENEMYESPERIA_H_*/

