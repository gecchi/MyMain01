#ifndef FORMATIONEBE001_H_
#define FORMATIONEBE001_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Ebe/FormationEbe.h"

namespace VioletVreath {

/**
 * 敵機エーベ用フォーメーション001グループ .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationEbe001 : public FormationEbe {
    /** スプライン定義資源への接続 */
    GgafLib::SplineManufactureConnection* pConn_pSplManuf_;
public:

    FormationEbe001(const char* prm_name);

    void onCallUpEbe(EnemyEbe* pEnemyEbe) override;

    virtual void processBehavior() override;

    GgafLib::SplineManufacture* getSplManuf() override;

    virtual ~FormationEbe001();
};

}
#endif /*FORMATIONUNOMIA001_H_*/
