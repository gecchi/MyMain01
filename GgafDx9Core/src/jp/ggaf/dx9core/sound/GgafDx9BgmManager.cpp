#include "stdafx.h"

GgafDx9Bgm* GgafDx9BgmManager::_pBgm_First = NULL;

GgafDx9Bgm* GgafDx9BgmManager::find(string prm_ogg_name) {
	GgafDx9Bgm* pBgm_Current = _pBgm_First;
	while (pBgm_Current != NULL) {
		if (pBgm_Current->_ogg_name == prm_ogg_name) {
			return pBgm_Current;
		}
		pBgm_Current = pBgm_Current -> _pBgm_Next;
	}
	return NULL;
}

void GgafDx9BgmManager::add(GgafDx9Bgm* prm_pBgm_New) {
	if (_pBgm_First == NULL) {
		_pBgm_First = prm_pBgm_New;
		return;
	} else {
		GgafDx9Bgm* pBgm_Current = _pBgm_First;
		while (pBgm_Current -> _pBgm_Next != NULL) {
			pBgm_Current = pBgm_Current -> _pBgm_Next;
		}
		pBgm_Current -> _pBgm_Next = prm_pBgm_New;
		return;
	}
}

void GgafDx9BgmManager::clear() {
	//保持しているGgafDx9Bgmインスタンスを解放
	GgafDx9Bgm* pBgm_Current = _pBgm_First;
	while (pBgm_Current != NULL) {
		GgafDx9Bgm* pBgm_tmp = pBgm_Current -> _pBgm_Next;
		if (pBgm_tmp == NULL) {
			DELETE_IMPOSSIBLE_NULL(pBgm_Current);
			pBgm_Current = NULL;
			break;
		} else {
			DELETE_IMPOSSIBLE_NULL(pBgm_Current);
			pBgm_Current = pBgm_tmp;
		}
	}
}

GgafDx9Bgm* GgafDx9BgmManager::get(string prm_ogg_name) {
	GgafDx9Bgm* pBgm = GgafDx9BgmManager::find(prm_ogg_name);
	if (pBgm == NULL) {
		GgafDx9Bgm* pBgm_New = GgafDx9Sound::createBgm(prm_ogg_name);
		GgafDx9BgmManager::add(pBgm_New);
		return pBgm_New;
	} else {
		return pBgm;
	}
}

