#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DispatcherConnection::DispatcherConnection(char* prm_idstr, GgafActorDispatcher* prm_pResource) :
    GgafResourceConnection<GgafActorDispatcher> (prm_idstr, prm_pResource) {
}

void DispatcherConnection::processReleaseResource(GgafActorDispatcher* prm_pResource) {
    _TRACE_("DispatcherConnection::processReleaseResourceで開放(ここでぶっ壊れたらclose()漏れの可能性あり)");
    prm_pResource->end(); //GgafActorDispatcherはゴミ箱で削除するためここでかいほうは行わない
    //TODO:
    //EnemyAstraea::~EnemyAstraea() {
    //    _pDispatcherCon_DpDpEnemyAstraeaLaserChip->close();
    //でこけるのでコメントにしたが再調査
    // DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

