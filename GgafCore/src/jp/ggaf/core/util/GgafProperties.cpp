#include "stdafx.h"


map<string, string>* GgafProperties::_s_pMapProperties = NULL;

DWORD*  GgafProperties::MAX_SKIP_FRAME       = NULL;

void GgafProperties::load(string prm_properties_filename) {
	if (_s_pMapProperties == NULL) {
		_s_pMapProperties = NEW map<string, string>();
		int ret = read(prm_properties_filename);
		if (ret != 0) {
			throw_GgafCriticalException("GgafProperties::load() Error! "<<prm_properties_filename<<"のread()に失敗。ステート→"<<ret);
		}
	}

	MAX_SKIP_FRAME       = getDWORD("MAX_SKIP_FRAME");

	_TRACE_("GGAF_PROPERTY(MAX_SKIP_FRAME)="<<GGAF_PROPERTY(MAX_SKIP_FRAME));
}

int GgafProperties::read(string prm_properties_filename) {
	const char* pChar_Filename = prm_properties_filename.c_str();
	FILE* pFile = NULL;
	int r = 0;
	try	{
		if(!pChar_Filename)  { throw -1; }
		//errno_t e = fopen_s(&pFile, pChar_Filename, "r"); //WIN32
		pFile = fopen(pChar_Filename, "r");
		if(!pFile) {
			perror("fopen error:");
			throw -2;
		}
		struct stat status;
		if(stat(pChar_Filename, &status)) {
			perror("stat error:");
			throw -3;
		}
		vector<char> vecBuffer(status.st_size + 1);
		fread(&vecBuffer[0], vecBuffer.size(), 1, pFile);
		vecBuffer[vecBuffer.size()-1] = '\0';

		parse(&vecBuffer[0]);
	} catch(int e){
		r = e;
	}

	if(pFile) {
		fclose(pFile);
	}
	return r;
}
void GgafProperties::parse(char* p) {
	char* pChar_Token = NULL;
	string key;
	string value;
	for( ; *p != '\0'; p++) {
		if(*p == '#') {
			while( *p++ != '\n' ) {} //空読み
			p--;
			pChar_Token = NULL;
		} else if(*p == '\n' || *p == '\r') {
			*p = '\0';
		} else if(*p == '=') {
			*p = '\0';
			key = pChar_Token;
			pChar_Token = p+1;
			while(*p != '\n' && *p != '\r' && *p != '#') {
				p++;
			}
			*p = '\0';
			value = pChar_Token;
			_s_pMapProperties->insert(map<string, string>::value_type(key, value));
			pChar_Token = NULL;
		} else {
			if(!pChar_Token) {
				pChar_Token = p;
			}
		}
	}
}

void GgafProperties::clean() {
	delete MAX_SKIP_FRAME;
	delete _s_pMapProperties;
}

string* GgafProperties::getStr(string prm_key) {
	if (isExistKey(prm_key)) {
		string* ret = NEW string((*_s_pMapProperties)[prm_key].c_str());
		return ret;
	} else {
		throw_GgafCriticalException("GgafProperties::getStr() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
	}
}

int* GgafProperties::getInt(string prm_key) {
	if (isExistKey(prm_key)) {
		int* iRet = NEW int(atoi((*_s_pMapProperties)[prm_key].c_str()));
		return iRet;
	} else {
		throw_GgafCriticalException("GgafProperties::getInt() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
	}
}

DWORD* GgafProperties::getDWORD(string prm_key) {
	if (isExistKey(prm_key)) {
		DWORD* dwRet = NEW DWORD((DWORD)(atoi((*_s_pMapProperties)[prm_key].c_str())));
		return dwRet;
	} else {
		throw_GgafCriticalException("GgafProperties::getDWORD() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
	}
}

bool* GgafProperties::getBool(string prm_key) {
	if (isExistKey(prm_key)) {
		bool* bRet = NULL;
		if (strcmp((*_s_pMapProperties)[prm_key].c_str(), "true") == 0) {
			bRet = NEW bool(true);
		} else {
			bRet = NEW bool(false);
		}
		return bRet;
	} else {
		throw_GgafCriticalException("GgafProperties::getBool() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
	}
}

double* GgafProperties::getDouble(string prm_key) {
	if (isExistKey(prm_key)) {
		double* dRet = NEW double(atof((*_s_pMapProperties)[prm_key].c_str()));
		return dRet;
	} else {
		throw_GgafCriticalException("GgafProperties::getDouble() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
	}
}

bool GgafProperties::isExistKey(string prm_key) {
	map<string, string>::iterator itr;
	itr = _s_pMapProperties->find(prm_key);
	if (itr != _s_pMapProperties->end()) {
		return true;
	} else {
		return false;
	}
}
