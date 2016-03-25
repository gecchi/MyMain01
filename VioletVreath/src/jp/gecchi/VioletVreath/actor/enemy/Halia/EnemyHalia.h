#ifndef ENEMYHALIA_H_
#define ENEMYHALIA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassMorphMeshActor.h"

namespace VioletVreath {

/**
 * �G�@�n���A .
 * �X�y�n���̃g���X���ǂ��H
 * @version 1.00
 * @since 2010/08/03
 * @author Masatoshi Tsuge
 */
class EnemyHalia : public GgafLib::DefaultMassMorphMeshActor {
//class EnemyHalia : public GgafLib::CubeMapMorphMeshActor {
public:

    enum {
        PROG_INIT   ,
        PROG_ENTRY  ,
        PROG_FIRST_MOVE,
        PROG_MOVE      ,
        PROG_TURN_OPEN ,
        PROG_FIRE_BEGIN,
        PROG_IN_FIRE   ,
        PROG_CLOSE     ,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED  ,
        SE_UNDAMAGED  ,
        SE_EXPLOSION,
        SE_FIRE,
    };

    velo veloTopMv_;
    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** ���_���珉���J����Z�ʒu�̋��� */
    coord dZ_camera_init_;

    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader* pAFader_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyHalia(const char* prm_name);

    void onCreateModel() override;

    /**
     * �n���A�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �n���A���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �n���A�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �n���A�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �n���A�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * �X�v���C���ړ��ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pKurokoLeader
     */
    void setSplineKurokoLeader(GgafLib::SplineKurokoLeader* prm_pKurokoLeader) {
        pKurokoLeader_ = prm_pKurokoLeader;
    }

    virtual ~EnemyHalia();
};

}
#endif /*ENEMYHALIA_H_*/

