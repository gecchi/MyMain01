#ifndef FORMATIONSAPPHO001B_H_
#define FORMATIONSAPPHO001B_H_
namespace VioletVreath {

/**
 * �G�@�T�b�t�H�[�p�t�H�[���[�V��������001-b .
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class FormationSappho001b : public FormationSappho001 {

public:
    FormationSappho001b(const char* prm_name);

    virtual void onCallUpSappho(EnemySappho* prm_pSappho, int prm_index) override;

    virtual ~FormationSappho001b();
};

}
#endif /*FORMATIONSAPPHO001B_H_*/
