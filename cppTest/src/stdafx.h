// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>
// C �����^�C�� �w�b�_�[ �t�@�C��
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <mmsystem.h>
#include <process.h>
#include <conio.h>
#include <math.h>
#include <limits.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <cstddef>
//#include <crtdbg.h>

//���f
#define OREDEBUG 1


#ifdef OREDEBUG
	#define NEW new(__FILE__, __LINE__ )
	//#define PFUNC std::cout << __PRETTY_FUNCTION__ << std::endl

	//#define TRACE(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss.str()); }
	#define TRACE(X)
	//#define TRACE2(X) {std::stringstream ss; ss << "[�ʃX���b�h]" << X; GgafCore::GgafLogger::write(ss.str()); }
	#define TRACE2(X)
	//�_���v�o�͗p
	#define _TRACE_(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss.str()); }
	//�f�o�b�O�p
	#define _TRACEORE(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss.str()); }

#else
	#define NEW new

	#define TRACE(X)
	#define TRACE2(X)
	//�_���v�o�͗p
	#define _TRACE_(X)
	//�f�o�b�O�p
	#define _TRACEORE(X)

#endif

//����������p�}�N��
//NULL��������Ȃ� delete
#define DELETE_POSSIBLE_NULL(POINTER)       { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
//NULL��������Ȃ� delete[]
#define DELETEARR_POSSIBLE_NULL(POINTER)    { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
//NULL��������Ȃ� Release()
#define RELEASE_POSSIBLE_NULL(POINTER)      { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else { (POINTER)=NULL; } }
//NULL�͂��肦�Ȃ� delete
#define DELETE_IMPOSSIBLE_NULL(POINTER)       { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else {std::stringstream ss; ss << "DELETE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") ����NULL�ł��邽�� "<< #POINTER << " �̉���𖳎����܂������A�{��������NULL�ł���ׂ��ł͖����B�v����"; GgafCore::GgafLogger::write(ss.str()); (POINTER)=NULL; }  }
//NULL�͂��肦�Ȃ� delete[]
#define DELETEARR_IMPOSSIBLE_NULL(POINTER)    { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else {std::stringstream ss; ss << "DELETEARR_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") ����NULL�ł��邽�� "<< #POINTER << "�̉���𖳎����܂������A�{��������NULL�ł���ׂ��ł͖����B�v����"; GgafCore::GgafLogger::write(ss.str()); (POINTER)=NULL; }  }
//NULL�͂��肦�Ȃ� Release()
#define RELEASE_IMPOSSIBLE_NULL(POINTER)      { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else {std::stringstream ss; ss << "RELEASE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") ����NULL�ł��邽�� "<< #POINTER << "�̉���𖳎����܂������A�{��������NULL�ł���ׂ��ł͖����B�v����"; GgafCore::GgafLogger::write(ss.str());  (POINTER)=NULL; }  }


#define MAX_HEADACTOR_PER_SCENE 16

typedef unsigned int actorkind;
#define throw_GgafCriticalException(X)

class GgafActor;
class GgafObject;
class GgafGod;
class GgafLogger;

#include "GgafLogger.h"
#include "GgafObject.h"

#include "GgafNode.hpp"
#include "GgafElement.hpp"
#include "GgafActor.h"
#include "GgafGod.h"

//�ӂӂ�hohohoho
//MAINdesu

