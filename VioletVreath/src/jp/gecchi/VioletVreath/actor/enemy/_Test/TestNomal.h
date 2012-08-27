#ifndef TESTNOMAL_H_
#define TESTNOMAL_H_
namespace VioletVreath {

/**
 * パー属性テスト .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestNomal :
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
    TestNomal(const char* prm_name);

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


    virtual ~TestNomal();
};

}
#endif /*TESTNOMAL_H_*/

