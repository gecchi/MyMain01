#include "stdafx.h"

DefaultSpriteActor::DefaultSpriteActor(string prm_name, string prm_xname)
	: GgafDx9SpriteActor(prm_name, prm_xname, NEW StgMover(this), NEW StgChecker(this))
{
	_class_name = "DefaultSpriteActor";
	_dwFrameOffset = 0;
	_pMover = (StgMover*)_pGeoMover;
	_pChecker = (StgChecker*)_pGeoChecker;
}

#ifdef OREDEBUG

void DefaultSpriteActor::processDrawTerminate() {
	//“–‚½‚è”»’è—Ìˆæ•\Ž¦
	DelineateActor::get()->drawHitarea(_pChecker);
}

#else

void DefaultSpriteActor::processDrawTerminate() {}

#endif


bool DefaultSpriteActor::isOffScreen() {
	if (_X < _X_OffScreen_Left) {
		return true;
	} else {
		if (_X > _X_OffScreen_Right) {
			return true;
		} else {
			if (_Y > _Y_OffScreen_Top) {
				return true;
			} else {
				if (_Y < _Y_OffScreen_Bottom) {
					return true;
				} else {
					return false;
				}
			}
		}
	}
}
DefaultSpriteActor::~DefaultSpriteActor() {
	TRACE("DefaultSpriteActor::~DefaultSpriteActor() "<<getName()<<" start--->");
	TRACE("DefaultSpriteActor::~DefaultSpriteActor() "<<getName()<<" <---end");
}
