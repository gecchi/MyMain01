#ifndef MYSHIPMOVERASSISTANT_H_
#define MYSHIPMOVERASSISTANT_H_
namespace MyStg2nd {

class MyShipMoverAssistant : public GgafDx9LibStg::DefaultD3DXMeshActor {

public:

    MyShipMoverAssistant(const char* prm_name, const char* prm_model);

    /**
     * ��OverRide �ł���
     */
    virtual void initialize();

    /**
     * ��OverRide �ł���
     */
    virtual void processBehavior();

    /**
     * ��OverRide �ł���
     */
    virtual void processJudgement() {
    }

    /**
     * ��OverRide �ł���
     */
    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual ~MyShipMoverAssistant();

};

}
#endif /*MYSHIPMOVERASSISTANT_H_*/

