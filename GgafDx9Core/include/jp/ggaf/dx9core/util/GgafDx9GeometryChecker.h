#ifndef GGAFDX9GEOMETRYCHECKER_H_
#define GGAFDX9GEOMETRYCHECKER_H_
namespace GgafDx9Core {

class GgafDx9GeometryChecker : public GgafCore::GgafObject {

protected:
    /** �ΏۃA�N�^�[ */
    GgafDx9UntransformedActor* _pActor;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    GgafDx9GeometryChecker(GgafDx9UntransformedActor* prm_pActor);

    virtual void behave();

    //virtual void draw();

    GgafDx9UntransformedActor* getTargetActor() {
        if (_pActor == NULL) {
            _TRACE_("GgafDx9GeometryChecker::getTargetActor NULL�ł��邪�悢�̂��I");
        }
        return _pActor;
    }

    virtual bool isBump(GgafDx9GeometryChecker* prm_pOtherChecker) = 0;

    virtual ~GgafDx9GeometryChecker();
};

}
#endif /*GGAFDX9GEOMETRYCHECKER_H_*/

