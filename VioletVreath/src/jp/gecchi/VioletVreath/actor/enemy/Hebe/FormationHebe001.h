#ifndef FORMATIONHEBE001_H_
#define FORMATIONHEBE001_H_
namespace VioletVreath {

/**
 * �G�@�w�[�x�p�t�H�[���[�V����001�O���[�v .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationHebe001 : public FormationHebe {
    /** �X�v���C����`�����ւ̐ڑ� */
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
