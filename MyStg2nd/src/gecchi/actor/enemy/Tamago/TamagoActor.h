#ifndef TAMAGOACTOR_H_
#define TAMAGOACTOR_H_
namespace MyStg2nd {

/**
 * ç≈èâÇ…çÏÇ¡ÇΩ3DÇÃìG(åªç›ñ¢égóp)
 * @version 1.00
 * @since 2008/07/23
 * @author Masatoshi Tsuge
 */
class TamagoActor : public GroundMeshActor {

    int _rnd;

public:
    TamagoActor(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    bool isOffScreen() {
        return 0;
    }
    virtual ~TamagoActor();
};

}
#endif /*TAMAGOACTOR_H_*/

