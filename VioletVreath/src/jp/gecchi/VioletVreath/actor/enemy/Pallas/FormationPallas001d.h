#ifndef FORMATIONPALLAS001D_H_
#define FORMATIONPALLAS001D_H_
namespace VioletVreath {

/**
 * �G�@�p���X�p�t�H�[���[�V��������001-d .
 * @version 1.00
 * @since 2010/06/27
 * @author Masatoshi Tsuge
 */
class FormationPallas001d : public FormationPallas001 {

public:
    FormationPallas001d(const char* prm_name);

    virtual void onCallUpPallas(EnemyPallas* prm_pPallas) override;

    virtual ~FormationPallas001d();
};

}
#endif /*FORMATIONPALLAS001D_H_*/
