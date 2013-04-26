#ifndef FORMATIONADELHEID001_H_
#define FORMATIONADELHEID001_H_

namespace VioletVreath {

/**
 * �G�@�A�[�f���n�C�h�p�t�H�[���[�V����001�O���[�v .
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
