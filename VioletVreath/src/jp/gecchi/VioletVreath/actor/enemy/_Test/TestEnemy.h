#ifndef TESTENEMY_H_
#define TESTENEMY_H_
namespace VioletVreath {

/**
 * テスト .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestEnemy :
  public GgafLib::DefaultMeshActor {

public:

    SpriteLabelTest* pMoji_;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    TestEnemy(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    void initialize() override;

    void dispStamina();

    virtual ~TestEnemy();
};

}
#endif /*TESTENEMY_H_*/

