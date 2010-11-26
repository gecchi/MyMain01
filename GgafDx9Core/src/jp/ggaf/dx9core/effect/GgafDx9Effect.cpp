#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9Effect::GgafDx9Effect(char* prm_effect_name) : GgafObject() {
    _TRACE_("GgafDx9Effect::GgafDx9Effect(" << prm_effect_name << ")");
    _effect_name = NEW char[51];
    strcpy(_effect_name, prm_effect_name);

    ID3DXBuffer* pError = NULL;
#ifdef _DEBUG
    DWORD dwFlags = D3DXSHADER_DEBUG|D3DXFX_NOT_CLONEABLE;
#else
    DWORD dwFlags = D3DXSHADER_SKIPVALIDATION|D3DXFX_NOT_CLONEABLE;
#endif



    string effect_file_name = GGAFDX9_PROPERTY(DIR_EFFECT) + string(prm_effect_name) + ".fx";
    HRESULT hr = D3DXCreateEffectFromFile(
                     GgafDx9God::_pID3DDevice9, // [in] LPDIRECT3DDEVICE9 pDevice
                     effect_file_name.c_str(),  // [in] LPCTSTR pSrcFile
                     0,                         // [in] CONST D3DXMACRO* pDefines
                     0,                         // [in] LPD3DXINCLUDE pInclude
                     dwFlags,                   // [in] DWORD Flags
                     0,                         // [in] LPD3DXEFFECTPOOL pPool
                     &_pID3DXEffect,         // [out] LPD3DXEFFECT* ppEffect
                     &pError                    // [out] LPD3DXBUFFER *ppCompilationxErrors
                );
    if (hr != D3D_OK && pError == NULL) {
        throwGgafCriticalException("GgafDx9Effect::GgafDx9Effect "<<effect_file_name<<" �����݂��Ȃ��̂ł͂Ȃ����낤���E�E�E");
    }
    checkDxException(hr, D3D_OK, "GgafDx9Effect::GgafDx9Effect ["<<effect_file_name<<"]\n"<<(const char*)(pError->GetBufferPointer()));
    _TRACE_(" GgafDx9Effect::GgafDx9Effect "<<prm_effect_name<<" �̃G�t�F�N�g�𐶐����܂����BADD:"<<this);
    _h_alpha_master = _pID3DXEffect->GetParameterByName( NULL, "g_alpha_master" ); //�}�X�^�[��
    _begin = false;
}

GgafDx9Effect::~GgafDx9Effect() {
    _TRACE_("GgafDx9Effect::~GgafDx9Effect("<<_effect_name<<") ADD:"<<this);
    HRESULT hr;
    hr = _pID3DXEffect->EndPass();
    //checkDxException(hr, D3D_OK, "GgafDx9Effect::~GgafDx9Effect() EndPass() �Ɏ��s���܂����B");
    hr = _pID3DXEffect->End();
    //checkDxException(hr, D3D_OK, "GgafDx9Effect::~GgafDx9Effect() End() �Ɏ��s���܂����B");
    DELETEARR_IMPOSSIBLE_NULL(_effect_name);

    //TODO�F�{��������_pID3DXEffect�͉������ׂ��ƍl���邪�A�}�l�[�W��������ɔC����B
    RELEASE_IMPOSSIBLE_NULL(_pID3DXEffect);

    //�J���@��(HP DV9200, Vista, GeForce go 7600) �̏ꍇ�AID3DXEffect��������悤�Ƃ���� nvd3dum.dll ���ŋH�ɗ�����B
    //���Ƀt���X�N���[���������׏�����̉�����ɃN���b�V������m���������悤���B
    //�b��I�ɃR�����g�ɂ��Ă���B

    //���Ȃ�̎��Ԃ��₵�Ă�����p�^�[���𒲍������B
    //���̒m�����̑��̊��ł̓R�����g���O�� ID3DXEffect �̉���������s���Ă��������ăN���b�V�����Ȃ��B
    //���ǐ^�̌����͂킩�炸�A�߂������ƂɁu�r�f�I�J�[�h���h���C�o�������v�Ƃ������_�Ŏ�����[�������邱�Ƃɂ����B
    //�N�������Ă��������B
}

