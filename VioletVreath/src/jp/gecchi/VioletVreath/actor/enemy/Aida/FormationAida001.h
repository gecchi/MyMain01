#ifndef FORMATIONHEBE001_H_
#define FORMATIONHEBE001_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Aida/FormationAida.h"

namespace VioletVreath {

/**
 * 敵機ヘーベ用フォーメーション001グループ .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationAida001 : public FormationAida {
    /** スプライン定義資源への接続 */
    GgafLib::SplineManufactureConnection* pSplManufConnection_;
public:

    FormationAida001(const char* prm_name);

    void onCallUpAida(EnemyAida* pEnemyAida) override;

    virtual void processBehavior() override;

    GgafLib::SplineManufacture* getSplManuf() override;

    virtual ~FormationAida001();
};

}
#endif /*FORMATIONEUNOMIA001_H_*/
