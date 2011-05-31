#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafException::GgafException(string prm_message) : GgafObject() {
    _message = prm_message;
    string message_dialog = "\n�E"+prm_message+"\n(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
    _TRACE_("�ʏ��O�����I GgafException::GgafException "<<prm_message);
    MessageBox(NULL, message_dialog.c_str(), "�s�{�ӂȎ��Ԃ�����", MB_OK|MB_ICONQUESTION);
    GgafGod::_pGod->oops(); //���܂����`�I
}

string GgafException::getMsg() {
    return _message;
}

GgafException::~GgafException() {
}

