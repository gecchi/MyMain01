#ifndef MYSHIPMOVERASSISTANT_H_
#define MYSHIPMOVERASSISTANT_H_
namespace MyStg2nd {

class MyShipMoverAssistant : public GgafDx9LibStg::DefaultD3DXMeshActor {

public:

    MyShipMoverAssistant(const char* prm_name, const char* prm_model);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    virtual void initialize();

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    virtual void processBehavior();

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    virtual void processJudgement() {
    }

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual ~MyShipMoverAssistant();

};

}
#endif /*MYSHIPMOVERASSISTANT_H_*/

