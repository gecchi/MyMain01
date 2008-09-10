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
	//�����蔻��̈�\��
	DelineateActor::get()->drawHitarea(_pChecker);
}

#else

void DefaultSpriteActor::processDrawTerminate() {}

#endif


bool DefaultSpriteActor::isOffScreen() {
	if (_X < _X_OffScreenLeft) {
		return true;
	} else {
		if (_X > _X_OffScreenRight) {
			return true;
		} else {
			if (_Y > _Y_OffScreenTop) {
				return true;
			} else {
				if (_Y < _Y_OffScreenBottom) {
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
