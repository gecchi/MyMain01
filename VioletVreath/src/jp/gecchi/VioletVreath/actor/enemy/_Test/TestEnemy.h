#ifndef TESTENEMY_H_
#define TESTENEMY_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * テスト .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestEnemy :
  public VvEnemyActor<GgafLib::DefaultMeshActor> {

public:
    SpriteLabelTest* pMoji_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    TestEnemy(const char* prm_name, const char* prm_model, void* prm_pStatusReset);

    void initialize() override;

    void dispStamina();

    virtual ~TestEnemy();
};

}
#endif /*TESTENEMY_H_*/

