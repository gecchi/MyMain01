#ifndef ENEMYHALIA_H_
#define ENEMYHALIA_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * �G�@�n���A .
 * �X�y�n���̃g���X���ǂ��H
 * @version 1.00
 * @since 2010/08/03
 * @author Masatoshi Tsuge
 */
class EnemyHalia : public GgafLib::DefaultMorphMeshActor {
//class EnemyHalia : public GgafLib::CubeMapMorphMeshActor {

    /** ���߂̏���A */
    GgafDxCore::GgafDxKurokoAsstA* pKurokoAsstA_;
    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;

    /** ���_���珉���J����Z�ʒu�̋��� */
    int dZ_camera_init_;
public:
    enum {
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
    /** �s���p�^�[���ԍ� */
    int iMovePatternNo_;

    velo veloTopMv_;

    GgafLib::LaserChipDepository* pLaserChipDepo_;

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
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


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

