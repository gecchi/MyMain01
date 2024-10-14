#ifndef TESTNOMAL_H_
#define TESTNOMAL_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestEnemy.h"

namespace VioletVreath {

/**
 * �p�[�����e�X�g .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestNomal : public TestEnemy {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    TestNomal(const char* prm_name);

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
    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;


    virtual ~TestNomal();
};

}
#endif /*TESTNOMAL_H_*/

