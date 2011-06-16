#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

StoreConnection::StoreConnection(char* prm_idstr, GgafActorStore* prm_pResource) :
    GgafResourceConnection<GgafActorStore> (prm_idstr, prm_pResource) {
}

void StoreConnection::processReleaseResource(GgafActorStore* prm_pResource) {
    _TRACE_("StoreConnection::processReleaseResourceで開放(ここでぶっ壊れたらclose()漏れの可能性あり)");
    prm_pResource->end(); //GgafActorStoreはゴミ箱で削除するためここでかいほうは行わない
    //TODO:
    //EnemyAstraea::~EnemyAstraea() {
    //    _pCon_LaserChipStoreDp->close();
    //でこけるのでコメントにしたが再調査
    // DELETE_IMPOSSIBLE_NULL(prm_pResource);
}
