#ifndef FORMATIONEUNOMIA001_H_
#define FORMATIONEUNOMIA001_H_
namespace VioletVreath {

/**
 * 敵機エウノミア用フォーメーション001グループ .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia001 : public FormationEunomia {

public:

    FormationEunomia001(const char* prm_name);

    virtual void processBehavior() override;

    virtual ~FormationEunomia001();
};

}
#endif /*FORMATIONEUNOMIA001_H_*/
