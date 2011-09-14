#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

CameraWorkerConnection::CameraWorkerConnection(char* prm_idstr, CameraWorker* prm_pResource) :
    GgafResourceConnection<CameraWorker> (prm_idstr, prm_pResource) {
}

void CameraWorkerConnection::processReleaseResource(CameraWorker* prm_pResource) {
    _TRACE_("CameraWorkerConnection::processReleaseResourceで"<<prm_pResource->getName()<<"開放というかend() (ここでぶっ壊れたらclose()漏れの可能性あり)");
    //DELETE_IMPOSSIBLE_NULL(prm_pResource);
    prm_pResource->end();
    //本メソッドはActorやSceneのデストラクタでコネクションクローズによりリソース解放が行われたならば、
    //工場スレッドからの神がdeleteし、 DepositoryConnection を解放することになる。
    //end() はメインスレッドから呼び出されるように設計しているので、
    //ココに処理きたときに、本来end()は排他処理しなければいけない。
    //しかしタイミング的にほぼありえないので、面倒なためやっていない。
    //TODO:いずれしよう。
}

