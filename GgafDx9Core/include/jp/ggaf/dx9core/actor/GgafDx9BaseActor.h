#ifndef GGAFDX9BASEACTOR_H_
#define GGAFDX9BASEACTOR_H_
namespace GgafDx9Core {

/**
 * GgafDx9Core名前空間の基底アクタークラス.
 * GgafMainActorを継承しただけです。<BR>
 * GgafDx9Core名前空間内では、このクラスを基底アクターとします。<BR>
 */
class GgafDx9BaseActor : public GgafCore::GgafMainActor {

public:

    GgafDx9BaseActor(const char* prm_name);

    virtual ~GgafDx9BaseActor(); //デストラクタ

};

}
#endif /*GGAFDX9BASEACTOR_H_*/
