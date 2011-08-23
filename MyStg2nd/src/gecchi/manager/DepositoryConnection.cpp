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
    _TRACE_("DepositoryConnection::processReleaseResource�ŊJ��(�����łԂ���ꂽ��close()�R��̉\������)");
    prm_pResource->end(); //GgafActorDepository�̓S�~���ō폜���邽�߂����ł����ق��͍s��Ȃ�
    //TODO:
    //EnemyAstraea::~EnemyAstraea() {
    //    _pCon_LaserChipDepoStore->close();
    //�ł�����̂ŃR�����g�ɂ������Ē���
    // DELETE_IMPOSSIBLE_NULL(prm_pResource);
}
