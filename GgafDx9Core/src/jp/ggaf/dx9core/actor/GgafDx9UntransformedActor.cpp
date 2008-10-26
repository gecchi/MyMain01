#include "stdafx.h"

GgafDx9UntransformedActor::GgafDx9UntransformedActor(string prm_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9MainActor(prm_name),
_X_OffScreenLeft((int)(-1*GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)),
_X_OffScreenRight((int)(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)),
_Y_OffScreenTop((int)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2)),
_Y_OffScreenBottom((int)(-1*GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2))
{
	_class_name = "GgafDx9UntransformedActor";
	_X  = _Y  = _Z  = 0;
	_RX = _RY = _RZ = 0;
	_SX = _SY = _SZ = LEN_UNIT;
//	_incX  = _incY  = _incZ  = 0;
//	_incRX = _incRY = _incRZ = 0;
	_pGeoMover = prm_pGeoMover;
	_pGeoChecker = prm_pGeoChecker;
}

bool GgafDx9UntransformedActor::processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
	_TRACE_(this->getName()<<"("<<this->_class_name<<") Å~ "<<prm_pActor_Opponent->getName()<<"("<<prm_pActor_Opponent->_class_name<<")");
	GgafDx9UntransformedActor* pActor_Opponent = dynamic_cast<GgafDx9UntransformedActor*>(prm_pActor_Opponent);
	if (pActor_Opponent != NULL) {
		return _pGeoChecker -> isBump(pActor_Opponent->_pGeoChecker);
	} else {
		return false;
	}
}

void GgafDx9UntransformedActor::processDrawPrior() {
	//TODO:óvåüèÿ
	if (_isPlaying && !_wasBlinded && _isAlive && !_wasDrawed) {
		GgafDx9World::setDrawDepthLevel(((_Z/LEN_UNIT)+(GgafDx9God::_iPxDep / 2)) / (GgafDx9God::_iPxDep / MAX_DRAW_DEPTH_LEVEL), this);
	}
}

GgafDx9UntransformedActor::~GgafDx9UntransformedActor() {
	if (_pGeoMover == NULL) {
		_TRACE_("GgafDx9UntransformedActor::~GgafDx9UntransformedActor() _pGeoMoverÇ™Ç†ÇËÇ‹ÇπÇÒ");
	} else {
		delete _pGeoMover;
	}

	if (_pGeoMover == NULL) {
		_TRACE_("GgafDx9UntransformedActor::~GgafDx9UntransformedActor() _pGeoCheckerÇ™Ç†ÇËÇ‹ÇπÇÒ");
	} else {
		delete _pGeoChecker;
	}

}
