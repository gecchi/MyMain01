#ifndef TESTENEMY_H_
#define TESTENEMY_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

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

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    TestEnemy(const char* prm_name, const char* prm_model);

    void initialize() override;

    void dispStamina();

    virtual ~TestEnemy();
};

}
#endif /*TESTENEMY_H_*/

