#include "stdafx.h"
#include "jp/ggaf/core/exception/GgafException.h"

#include "jp/ggaf/core/GgafGod.h"

using namespace GgafCore;

GgafException::GgafException(std::string prm_message) : GgafObject() {
    _message = prm_message;
    std::string message_dialog = "\n・"+prm_message+"\n(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
    _TRACE_("通常例外発生！ GgafException::GgafException "<<prm_message);
    timeEndPeriod(1);
    MessageBox(nullptr, message_dialog.c_str(), "不本意な事態", MB_OK|MB_ICONQUESTION|MB_SETFOREGROUND|MB_TOPMOST);
    GgafGod::_pGod->oops(); //しまった～！
}

std::string GgafException::getMsg() {
    return _message;
}

GgafException::~GgafException() {
}

