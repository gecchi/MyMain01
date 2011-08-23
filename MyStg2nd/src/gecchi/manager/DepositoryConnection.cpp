#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DepositoryConnection::DepositoryConnection(char* prm_idstr, GgafActorDepository* prm_pResource) :
    GgafResourceConnection<GgafActorDepository> (prm_idstr, prm_pResource) {
}

void DepositoryConnection::processReleaseResource(GgafActorDepository* prm_pResource) {
    _TRACE_("DepositoryConnection::processReleaseResourceで開放(ここでぶっ壊れたらclose()漏れの可能性あり)");
    prm_pResource->end(); //GgafActorDepositoryはゴミ箱で削除するためここでかいほうは行わない
    //TODO:
    //EnemyAstraea::~EnemyAstraea() {
    //    _pCon_LaserChipDepoStore->close();
    //でこけるのでコメントにしたが再調査
    // DELETE_IMPOSSIBLE_NULL(prm_pResource);
}
