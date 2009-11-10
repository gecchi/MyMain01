#ifndef GGAFDX9CHECKER_H_
#define GGAFDX9CHECKER_H_
namespace GgafDx9Core {

class GgafDx9Checker : public GgafCore::GgafObject {

protected:
    /** 対象アクター */
    GgafDx9GeometricActor* _pActor;

public:
    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    GgafDx9Checker(GgafDx9GeometricActor* prm_pActor);

    virtual void updateHitArea() {}

    //virtual void draw();

    GgafDx9GeometricActor* getTargetActor() {
        if (_pActor == NULL) {
            _TRACE_("GgafDx9Checker::getTargetActor NULLであるがよいのか！");
        }
        return _pActor;
    }

    virtual bool isBump(GgafDx9Checker* prm_pOtherChecker) {
        return false;
    }

    virtual ~GgafDx9Checker();
};

}
#endif /*GGAFDX9CHECKER_H_*/

