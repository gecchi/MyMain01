#ifndef FORMATIONEUNOMIA001A_H_
#define FORMATIONEUNOMIA001A_H_
namespace VioletVreath {

/**
 * �G�@�G�E�m�~�A�p�t�H�[���[�V��������001-a .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia001a : public FormationEunomia001 {
public:

    FormationEunomia001a(const char* prm_name);

    /**
     * ���� .
     */
    void processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) override;

    virtual ~FormationEunomia001a();
};

}
#endif /*FORMATIONEUNOMIA001A_H_*/
