#ifndef FORMATIONEUNOMIA001_H_
#define FORMATIONEUNOMIA001_H_
namespace MyStg2nd {

/**
 * �G�@�G�E�m�~�A�p�t�H�[���[�V����001�O���[�v .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia001 : public FormationEunomia {

public:

    FormationEunomia001(const char* prm_name);

    virtual void processBehavior() override;

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ
     * @param prm_pActorLast �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void onDestroyedAll(GgafCore::GgafActor* prm_pActor_LastDestroyed) override;

    virtual ~FormationEunomia001();
};

}
#endif /*FORMATIONEUNOMIA001_H_*/
