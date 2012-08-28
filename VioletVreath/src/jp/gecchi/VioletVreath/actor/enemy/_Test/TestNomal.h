#ifndef TESTNOMAL_H_
#define TESTNOMAL_H_
namespace VioletVreath {

/**
 * �p�[�����e�X�g .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestNomal : public TestEnemy {

public:

      enum {
          SE_DAMAGED   = 0,
          SE_EXPLOSION ,
      };

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    TestNomal(const char* prm_name);

    /**
     * �G�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

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


    virtual ~TestNomal();
};

}
#endif /*TESTNOMAL_H_*/

