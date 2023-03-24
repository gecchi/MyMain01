#ifndef FORMATIONEBE001_H_
#define FORMATIONEBE001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ebe/FormationEbe.h"

namespace VioletVreath {

/**
 * 敵機エーベ用フォーメーション001グループ .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationEbe001 : public FormationEbe {
    /** 曲線移動の情報資源への接続 */
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;
public:

    FormationEbe001(const char* prm_name);

    void onCalledUpEbe(EnemyEbe* pEnemyEbe) override;

    virtual void processBehavior() override;

    GgafDx::CurveManufacture* getSplManuf() override;

    virtual ~FormationEbe001();
};

}
#endif /*FORMATIONUNOMIA001_H_*/
