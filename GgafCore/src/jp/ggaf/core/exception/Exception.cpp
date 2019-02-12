#include "jp/ggaf/core/exception/Exception.h"

#include "jp/ggaf/core/God.h"

using namespace GgafCore;

Exception::Exception(std::string prm_message) : Object() {
    _message = prm_message;
    std::string message_dialog = "\n�E"+prm_message+"\n(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
    _TRACE_("�ʏ��O�����I Exception::Exception "<<prm_message);
    timeEndPeriod(1);
    MessageBox(nullptr, message_dialog.c_str(), "�s�{�ӂȎ���", MB_OK|MB_ICONQUESTION|MB_SETFOREGROUND|MB_TOPMOST);
    God::_pGod->oops(); //���܂����`�I
}

std::string Exception::getMsg() {
    return _message;
}

Exception::~Exception() {
}

