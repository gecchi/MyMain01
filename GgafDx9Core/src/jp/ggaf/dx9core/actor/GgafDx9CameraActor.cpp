#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CameraActor::GgafDx9CameraActor(string prm_name) : GgafDx9UntransformedActor(prm_name, NEW GgafDx9GeometryMover(this), NULL) {
	_class_name = "GgafDx9CameraActor";
	_gazeX = GgafDx9God::_pVecCamLookatPoint->x * LEN_UNIT * PX_UNIT;
	_gazeY = GgafDx9God::_pVecCamLookatPoint->y * LEN_UNIT * PX_UNIT;
	_gazeZ = GgafDx9God::_pVecCamLookatPoint->z * LEN_UNIT * PX_UNIT;
	_X = GgafDx9God::_pVecCamFromPoint->x * LEN_UNIT * PX_UNIT;
	_Y = GgafDx9God::_pVecCamFromPoint->y * LEN_UNIT * PX_UNIT;
	_Z = GgafDx9God::_pVecCamFromPoint->z * LEN_UNIT * PX_UNIT;
	setBumpable(false);
}

void GgafDx9CameraActor::initialize() {
	_pGeoMover->setMoveVelocity(0);
}

void GgafDx9CameraActor::processDrawPrior() {
	_pGeoMover->behave();
	GgafDx9God::_pVecCamFromPoint->x = (1.0*_X) / LEN_UNIT / PX_UNIT;
	GgafDx9God::_pVecCamFromPoint->y = (1.0*_Y) / LEN_UNIT / PX_UNIT;
	GgafDx9God::_pVecCamFromPoint->z = (1.0*_Z) / LEN_UNIT / PX_UNIT;
	GgafDx9God::_pVecCamLookatPoint->x = (1.0*_gazeX) / LEN_UNIT / PX_UNIT;
	GgafDx9God::_pVecCamLookatPoint->y = (1.0*_gazeY) / LEN_UNIT / PX_UNIT;
	GgafDx9God::_pVecCamLookatPoint->z = (1.0*_gazeZ) / LEN_UNIT / PX_UNIT;
}

GgafDx9CameraActor::~GgafDx9CameraActor() {
}
