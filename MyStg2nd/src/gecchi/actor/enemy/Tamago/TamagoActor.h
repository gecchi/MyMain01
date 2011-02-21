#ifndef TAMAGOACTOR_H_
#define TAMAGOACTOR_H_
namespace MyStg2nd {

/**
 * ç≈èâÇ…çÏÇ¡ÇΩ3DÇÃìG(åªç›ñ¢égóp)
 * @version 1.00
 * @since 2008/07/23
 * @author Masatoshi Tsuge
 */
class TamagoActor : public  GgafDx9LibStg::DefaultD3DXAniMeshActor {

    int _rnd;
    double _track0time;
public:
    TamagoActor(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    int isOutOfView() override {
        return 0;
    }

    bool isOutOfUniverse() override {
        return false;
    }

    virtual ~TamagoActor();
};

}
#endif /*TAMAGOACTOR_H_*/

