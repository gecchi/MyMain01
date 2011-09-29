#ifndef DEFAULTGEOMETRICACTOR_H_
#define DEFAULTGEOMETRICACTOR_H_
namespace GgafLib {

/**
 * 表示不要のダミー用
 * @version 1.00
 * @since 2010/09/08
 * @author Masatoshi Tsuge
 */
class DefaultGeometricActor : public GgafDxCore::GgafDxGeometricActor {

public:
    DefaultGeometricActor(const char* prm_name, GgafCore::GgafStatus* prm_pStat, GgafDxCore::GgafDxChecker* prm_pChecker = NULL);


    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~DefaultGeometricActor();

};

}
#endif /*DEFAULTGEOMETRICACTOR_H_*/
