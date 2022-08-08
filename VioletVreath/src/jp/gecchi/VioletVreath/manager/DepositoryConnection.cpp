#include "DepositoryConnection.h"



using namespace GgafLib;
using namespace VioletVreath;

DepositoryConnection::DepositoryConnection(const char* prm_idstr, GgafCore::ActorDepository* prm_pResource) :
    GgafCore::ResourceConnection<GgafCore::ActorDepository> (prm_idstr, prm_pResource) {
}

void DepositoryConnection::processReleaseResource(GgafCore::ActorDepository* prm_pResource) {
    _TRACE_("DepositoryConnection::processReleaseResourceで、"<<prm_pResource->getName()<<"開放というかend()(ここでぶっ壊れたらclose()漏れの可能性あり)");
    prm_pResource->end();
    //本メソッドはActorやSceneのデストラクタでコネクションクローズによりリソース解放が行われたならば、
    //愛スレッドからの管理者がdeleteし、 DepositoryConnection を解放することになる。
    //end() はメインスレッドから呼び出されるように設計しているので、
    //ココに処理きたときに、本来end()は排他処理しなければいけない。
    //しかしタイミング的にほぼありえないので、面倒なためやっていない。
    //TODO:いずれしよう。
}
