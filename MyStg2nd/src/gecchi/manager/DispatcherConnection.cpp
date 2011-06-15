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
    _TRACE_("DispatcherConnection::processReleaseResource�ŊJ��(�����łԂ���ꂽ��close()�R��̉\������)");
    prm_pResource->end(); //GgafActorDispatcher�̓S�~���ō폜���邽�߂����ł����ق��͍s��Ȃ�
    //TODO:
    //EnemyAstraea::~EnemyAstraea() {
    //    _pDispatcherCon_DpDpEnemyAstraeaLaserChip->close();
    //�ł�����̂ŃR�����g�ɂ������Ē���
    // DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

