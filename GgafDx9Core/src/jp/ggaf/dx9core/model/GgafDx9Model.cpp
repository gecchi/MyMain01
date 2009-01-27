#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

int GgafDx9Model::_id_lastdraw = -1;

GgafDx9Model::GgafDx9Model(string prm_model_name) : GgafObject() {
    TRACE("GgafDx9Model::GgafDx9Model(" <<  prm_model_name << ")");
    _id = GgafDx9ModelManager::getNextId();
	_model_name = prm_model_name;
	_pModel_Next = NULL;
}

GgafDx9Model::~GgafDx9Model() {
    TRACE("GgafDx9Model::~GgafDx9Model() " <<  _model_name << " start-->");
    TRACE("GgafDx9Model::~GgafDx9Model() " <<  _model_name << " <--end");
}

