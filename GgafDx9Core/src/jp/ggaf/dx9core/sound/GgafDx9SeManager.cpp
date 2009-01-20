#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Se* GgafDx9SeManager::_pSe_First = NULL;

GgafDx9Se* GgafDx9SeManager::find(string prm_wave_name) {
	GgafDx9Se* pSe_Current = _pSe_First;
	while (pSe_Current != NULL) {
		if (pSe_Current->_wave_name == prm_wave_name) {
			return pSe_Current;
		}
		pSe_Current = pSe_Current -> _pSe_Next;
	}
	return NULL;
}

void GgafDx9SeManager::add(GgafDx9Se* prm_pSe_New) {
	if (_pSe_First == NULL) {
		_pSe_First = prm_pSe_New;
		return;
	} else {
		GgafDx9Se* pSe_Current = _pSe_First;
		while (pSe_Current -> _pSe_Next != NULL) {
			pSe_Current = pSe_Current -> _pSe_Next;
		}
		pSe_Current -> _pSe_Next = prm_pSe_New;
		return;
	}
}

void GgafDx9SeManager::clear() {
	//保持しているGgafDx9Seインスタンスを解放
	GgafDx9Se* pSe_Current = _pSe_First;
	while (pSe_Current != NULL) {
		GgafDx9Se* pSe_tmp = pSe_Current -> _pSe_Next;
		if (pSe_tmp == NULL) {
			DELETE_IMPOSSIBLE_NULL(pSe_Current);
			pSe_Current = NULL;
			break;
		} else {
			DELETE_IMPOSSIBLE_NULL(pSe_Current);
			pSe_Current = pSe_tmp;
		}
	}
}

GgafDx9Se* GgafDx9SeManager::get(string prm_wave_name) {
	GgafDx9Se* pSe = GgafDx9SeManager::find(prm_wave_name);
	if (pSe == NULL) {
		GgafDx9Se* pSe_New = GgafDx9Sound::createSe(prm_wave_name);
		GgafDx9SeManager::add(pSe_New);
		return pSe_New;
	} else {
		return pSe;
	}
}

