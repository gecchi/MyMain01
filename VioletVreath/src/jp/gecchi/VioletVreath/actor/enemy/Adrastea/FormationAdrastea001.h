#ifndef FORMATIONADRASTEA001_H_
#define FORMATIONADRASTEA001_H_
namespace VioletVreath {

/**
 * 敵機アドラステアのフォーメーションその１ .
 * @version 1.00
 * @since 2012/08/06
 * @author Masatoshi Tsuge
 */
class FormationAdrastea001 : public GgafLib::TreeFormation {

public:
    FormationAdrastea001(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~FormationAdrastea001();
};

}
#endif /*FORMATIONADRASTEA001_H_*/
