#ifndef FORMATIONEUNOMIA002A_H_
#define FORMATIONEUNOMIA002A_H_
namespace MyStg2nd {

/**
 * �G�@�G�E�m�~�A�p�t�H�[���[�V��������002-a .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia002a : public FormationEunomia002 {
public:

    FormationEunomia002a(const char* prm_name);

    /**
     * ���� .
     */
    void processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) override;

    virtual ~FormationEunomia002a();
};

}
#endif /*FORMATIONEUNOMIA002A_H_*/
