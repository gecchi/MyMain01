#ifndef FORMATIONEUNOMIA002A_H_
#define FORMATIONEUNOMIA002A_H_
namespace MyStg2nd {

/**
 * 敵機エウノミア用フォーメーションその002-a .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia002a : public FormationEunomia002 {
public:

    FormationEunomia002a(const char* prm_name);

    /**
     * 調整 .
     */
    void processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) override;

    virtual ~FormationEunomia002a();
};

}
#endif /*FORMATIONEUNOMIA002A_H_*/
