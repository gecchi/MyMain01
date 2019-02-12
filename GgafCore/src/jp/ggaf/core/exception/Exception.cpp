#include "jp/ggaf/core/exception/Exception.h"

#include "jp/ggaf/core/God.h"

using namespace GgafCore;

Exception::Exception(std::string prm_message) : Object() {
    _message = prm_message;
    std::string message_dialog = "\n・"+prm_message+"\n(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
    _TRACE_("通常例外発生！ Exception::Exception "<<prm_message);
    timeEndPeriod(1);
    MessageBox(nullptr, message_dialog.c_str(), "不本意な事態", MB_OK|MB_ICONQUESTION|MB_SETFOREGROUND|MB_TOPMOST);
    God::_pGod->oops(); //しまった～！
}

std::string Exception::getMsg() {
    return _message;
}

Exception::~Exception() {
}

