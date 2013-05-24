#ifndef TESTGU_H_
#define TESTGU_H_
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestEnemy.h"

namespace VioletVreath {

/**
 * �O�[�����e�X�g .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestGu : public TestEnemy {

public:
      enum {
          SE_DAMAGED   ,
          SE_EXPLOSION ,
      };

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    TestGu(const char* prm_name);

    /**
     * �G�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
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
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~TestGu();
};

}
#endif /*TESTGU_H_*/

