#ifndef TESTCHOKI_H_
#define TESTCHOKI_H_
namespace VioletVreath {

/**
 * �`���L�����e�X�g .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestChoki :
  public GgafLib::DefaultMeshActor {

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
    TestChoki(const char* prm_name);

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


    virtual ~TestChoki();
};

}
#endif /*TESTCHOKI_H_*/

