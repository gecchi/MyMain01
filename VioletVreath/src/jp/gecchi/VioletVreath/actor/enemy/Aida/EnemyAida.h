#ifndef ENEMYAIDA_H_
#define ENEMYAIDA_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@�A�C�[�_ .
 * �X�y�n����IDA�݂����Ȃ�ŁB
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class EnemyAida : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        PROG_INIT ,
        PROG_ENTRY,
        PROG_MOVE01,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    /** [r]����G�t�F�N�g */
    GgafDxCore::GgafDxDrawableActor* pEntryEffect_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyAida(const char* prm_name);

    void onCreateModel() override;

    /**
     * �A�C�[�_�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �A�C�[�_�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �A�C�[�_�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �A�C�[�_�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �A�C�[�_�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyAida();
};

}
#endif /*ENEMYAIDA_H_*/

