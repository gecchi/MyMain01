#ifndef GGAFDX9CHECKER_H_
#define GGAFDX9CHECKER_H_
namespace GgafDx9Core {

class GgafDx9Checker : public GgafCore::GgafObject {

protected:
    /** �ΏۃA�N�^�[ */
    GgafDx9UntransformedActor* _pActor;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    GgafDx9Checker(GgafDx9UntransformedActor* prm_pActor);

    virtual void behave();

    //virtual void draw();

    GgafDx9UntransformedActor* getTargetActor() {
        if (_pActor == NULL) {
            _TRACE_("GgafDx9Checker::getTargetActor NULL�ł��邪�悢�̂��I");
        }
        return _pActor;
    }

    virtual bool isBump(GgafDx9Checker* prm_pOtherChecker) = 0;

    virtual ~GgafDx9Checker();
};

}
#endif /*GGAFDX9CHECKER_H_*/

