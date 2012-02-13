#ifndef FORMATIONEUNOMIA001A_H_
#define FORMATIONEUNOMIA001A_H_
namespace VioletVreath {

/**
 * 敵機エウノミア用フォーメーションその001-a .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia001a : public FormationEunomia001 {
public:

    FormationEunomia001a(const char* prm_name);

    /**
     * 調整 .
     */
    void processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) override;

    virtual ~FormationEunomia001a();
};

}
#endif /*FORMATIONEUNOMIA001A_H_*/
