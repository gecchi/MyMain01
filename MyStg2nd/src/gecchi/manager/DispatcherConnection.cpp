#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DispatcherConnection::DispatcherConnection(char* prm_idstr, ActorDispatcher* prm_pResource) :
    GgafResourceConnection<ActorDispatcher> (prm_idstr, prm_pResource) {
}

void DispatcherConnection::processReleaseResource(ActorDispatcher* prm_pResource) {
    _TRACE_("DispatcherConnection::processReleaseResource�ŊJ��");
	prm_pResource->sayonara(); //ActorDispatcher�̓S�~���ō폜���邽�߂����ł����ق��͍s��Ȃ�
	// DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

