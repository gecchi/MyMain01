#ifndef TESTPA_H_
#define TESTPA_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestEnemy.h"

namespace VioletVreath {

/**
 * �p�[�����e�X�g .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestPa : public TestEnemy {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    TestPa(const char* prm_name);

    /**
     * �G���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �G�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �G�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �G�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    virtual ~TestPa();
};

}
#endif /*TESTPA_H_*/

