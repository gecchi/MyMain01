#include "stdafx.h"

using namespace Ggaf;

GgafException::GgafException(string prm_message) : GgafObject() {
	_message = prm_message;
}

string GgafException::getMsg() {
	return _message;
}

GgafException::~GgafException() {
}

