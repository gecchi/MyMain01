#include "stdafx.h"

DWORD GgafUtil::_timex = 0;

DWORD GgafUtil::getSystemTime() {

	return timeGetTime();
	//return _timex++;
}

char* GgafUtil::getFileText(string prm_filename ){
	ifstream ifs(prm_filename.c_str());
	if(!ifs.is_open()) {
		return NULL;
	} else {
		DWORD dwSize = 0;
		// �T�C�Y���擾
		while(!ifs.eof()) {
			ifs.ignore();
			dwSize++;
		}
		ifs.clear();
		ifs.seekg(0, ios_base::beg);
		//�T�C�Y���w�肵�ēǍ���
		char* pa_char = NEW char[dwSize];
		ZeroMemory(pa_char, dwSize);
		ifs.read(pa_char, dwSize-1);
		return pa_char;
	}
}


