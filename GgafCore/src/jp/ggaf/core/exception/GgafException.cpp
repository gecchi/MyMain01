#include "stdafx.h"
#include "jp/ggaf/core/exception/GgafException.h"

#include "jp/ggaf/core/GgafGod.h"

using namespace GgafCore;

GgafException::GgafException(std::string prm_message) : GgafObject() {
    _message = prm_message;
    std::string message_dialog = "\n�E"+prm_message+"\n(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
    _TRACE_("�ʏ��O�����I GgafException::GgafException "<<prm_message);
    timeEndPeriod(1);
    MessageBox(nullptr, message_dialog.c_str(), "�s�{�ӂȎ���", MB_OK|MB_ICONQUESTION|MB_SETFOREGROUND|MB_TOPMOST);
    GgafGod::_pGod->oops(); //���܂����`�I
}

std::string GgafException::getMsg() {
    return _message;
}

GgafException::~GgafException() {
}

