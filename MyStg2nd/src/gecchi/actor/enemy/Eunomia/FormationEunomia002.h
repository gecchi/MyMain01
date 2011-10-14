#ifndef FORMATIONEUNOMIA002_H_
#define FORMATIONEUNOMIA002_H_
namespace MyStg2nd {

/**
 * �G�@�G�E�m�~�A�p�t�H�[���[�V����002�O���[�v .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia002 : public FormationEunomia {

public:

    FormationEunomia002(const char* prm_name);

    virtual void processBehavior() override;

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ
     * @param prm_pActorLast �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void onDestroyedAll(GgafDxCore::GgafDxGeometricActor* prm_pActor_LastDestroyed) override;

    virtual ~FormationEunomia002();
};

}
#endif /*FORMATIONEUNOMIA002_H_*/
