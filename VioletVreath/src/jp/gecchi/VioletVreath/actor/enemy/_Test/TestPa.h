#ifndef TESTPA_H_
#define TESTPA_H_
namespace VioletVreath {

/**
 * パー属性テスト .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestPa :
  public TestEnemy {

public:

      enum {
          SE_DAMAGED   = 0,
          SE_EXPLOSION ,
      };

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    TestPa(const char* prm_name);

    /**
     * 敵のがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * 敵の振る舞い .
     */
    void processBehavior() override;

    /**
     * 敵の振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * 敵の衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~TestPa();
};

}
#endif /*TESTPA_H_*/

