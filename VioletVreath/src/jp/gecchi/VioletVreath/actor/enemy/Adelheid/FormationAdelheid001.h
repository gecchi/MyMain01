#ifndef FORMATIONADELHEID001_H_
#define FORMATIONADELHEID001_H_

namespace VioletVreath {

/**
 * 敵機アーデルハイド用フォーメーション001グループ .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationAdelheid001 : public FormationAdelheid {

public:

    GgafLib::SplineManufactureConnection* pSplManufConnection_;

    FormationAdelheid001(const char* prm_name);

    void onCallUpAdelheid(EnemyAdelheid* pEnemyAdelheid) override;

    GgafLib::SplineManufacture* getFormationSplManuf() override;

    virtual void processBehavior() override;

    virtual ~FormationAdelheid001();
};

}
#endif /*FORMATIONADELHEID001_H_*/
