#ifndef TAMAGOACTOR_H_
#define TAMAGOACTOR_H_
namespace MyStg2nd {

/**
 * �ŏ��ɍ����3D�̓G(���ݖ��g�p)
 * @version 1.00
 * @since 2008/07/23
 * @author Masatoshi Tsuge
 */
class TamagoActor : public GgafDx9LibStg::DefaultD3DXAniMeshActor {

    int _rnd;

public:
    TamagoActor(const char* prm_name);

    void initialize();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    virtual ~TamagoActor();
};

}
#endif /*TAMAGOACTOR_H_*/

