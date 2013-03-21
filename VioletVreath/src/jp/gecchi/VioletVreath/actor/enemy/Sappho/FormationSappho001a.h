#ifndef FORMATIONSAPPHO001A_H_
#define FORMATIONSAPPHO001A_H_
namespace VioletVreath {

/**
 * 敵機サッフォー用フォーメーションその001-a .
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class FormationSappho001a : public FormationSappho001 {

public:
    FormationSappho001a(const char* prm_name);

    virtual void onCallUpSappho(EnemySappho* prm_pSappho) override;

    virtual ~FormationSappho001a();
};

}
#endif /*FORMATIONSAPPHO001A_H_*/
