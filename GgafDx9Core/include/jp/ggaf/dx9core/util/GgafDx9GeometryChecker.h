#ifndef GGAFDX9GEOMETRYCHECKER_H_
#define GGAFDX9GEOMETRYCHECKER_H_
namespace GgafDx9Core {

class GgafDx9GeometryChecker : public GgafCore::GgafObject {

protected:
    /** 対象アクター */
    GgafDx9UntransformedActor* _pActor;

public:
    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    GgafDx9GeometryChecker(GgafDx9UntransformedActor* prm_pActor);

    virtual void behave();

    //virtual void draw();

    GgafDx9UntransformedActor* getTargetActor() {
        if (_pActor == NULL) {
            _TRACE_("GgafDx9GeometryChecker::getTargetActor NULLであるがよいのか！");
        }
        return _pActor;
    }

    virtual bool isBump(GgafDx9GeometryChecker* prm_pOtherChecker) = 0;

    virtual ~GgafDx9GeometryChecker();
};

}
#endif /*GGAFDX9GEOMETRYCHECKER_H_*/

