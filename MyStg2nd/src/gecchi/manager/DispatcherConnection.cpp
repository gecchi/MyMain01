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
    _TRACE_("DispatcherConnection::processReleaseResourceÇ≈äJï˙");
	prm_pResource->retire(); //GgafActorDispatcherÇÕÉSÉ~î†Ç≈çÌèúÇ∑ÇÈÇΩÇﬂÇ±Ç±Ç≈Ç©Ç¢ÇŸÇ§ÇÕçsÇÌÇ»Ç¢
	// DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

