#ifndef FORMATIONHEBE001_H_
#define FORMATIONHEBE001_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Hebe/FormationHebe.h"

namespace VioletVreath {

/**
 * 敵機ヘーベ用フォーメーション001グループ .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationHebe001 : public FormationHebe {
    /** スプライン定義資源への接続 */
    GgafLib::SplineManufactureConnection* pSplManufConnection_;
public:

    FormationHebe001(const char* prm_name);

    void onCallUpHebe(EnemyHebe* pEnemyHebe) override;

    virtual void processBehavior() override;

    GgafLib::SplineManufacture* getSplManuf() override;

    virtual ~FormationHebe001();
};

}
#endif /*FORMATIONEUNOMIA001_H_*/
