#ifndef SPRITEMESHWORLDBOUNDACTOR_H_
#define SPRITEMESHWORLDBOUNDACTOR_H_
namespace GgafDx9LibStg {

/**
 * ���E���E.
 * @version 1.00
 * @since 2010/06/16
 * @author Masatoshi Tsuge
 */
class SpriteMeshWorldBoundActor : public GgafDx9Core::GgafDx9SpriteMeshActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9Scaler* _pScaler;

    frame _offset_frames;

    SpriteMeshWorldBoundActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

   virtual void processSettlementBehavior() override;
//
//    virtual void processPreDraw() override;

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override {
    }

    int isOutOfView() override {
        //��ʊO���薳��
        return 0;
    }

    bool isOutOfUniverse() override {;
        //�Q�[�����W�͈͊O���薳��
        return false;
    }
    virtual ~SpriteMeshWorldBoundActor();
};

}
#endif /*WORLDBOUNDACTOR_H_*/
