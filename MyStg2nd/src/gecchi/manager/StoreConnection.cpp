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
    _TRACE_("StoreConnection::processReleaseResource�ŊJ��(�����łԂ���ꂽ��close()�R��̉\������)");
    prm_pResource->end(); //GgafActorStore�̓S�~���ō폜���邽�߂����ł����ق��͍s��Ȃ�
    //TODO:
    //EnemyAstraea::~EnemyAstraea() {
    //    _pCon_LaserChipStoreDp->close();
    //�ł�����̂ŃR�����g�ɂ������Ē���
    // DELETE_IMPOSSIBLE_NULL(prm_pResource);
}
