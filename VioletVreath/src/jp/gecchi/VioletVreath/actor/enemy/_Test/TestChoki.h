#ifndef TESTCHOKI_H_
#define TESTCHOKI_H_
namespace VioletVreath {

/**
 * チョキ属性テスト .
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
     * コンストラクタ
     * @param prm_name
     * @return
     */
    TestChoki(const char* prm_name);

    /**
     * 敵の初期処理（インスタンス生成後保証）
     */
    void initialize() override;

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


    virtual ~TestChoki();
};

}
#endif /*TESTCHOKI_H_*/

