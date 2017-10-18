#ifndef ENEMYIDA_H_
#define ENEMYIDA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@�C�[�_ .
 * �X�y�n����IDA�݂����Ȃ�ł��������B
 * �ŏ���FK�t�H�[���V�����B
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class EnemyIda : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        PROG_INIT ,
        PROG_ENTRY,
        PROG_MOVE01,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyIda(const char* prm_name);

    void onCreateModel() override;

    /**
     * �C�[�_�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �C�[�_���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �C�[�_�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �C�[�_�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �C�[�_�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyIda();
};

}
#endif /*ENEMYIDA_H_*/

