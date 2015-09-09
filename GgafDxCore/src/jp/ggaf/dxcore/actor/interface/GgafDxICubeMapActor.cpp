#include "jp/ggaf/dxcore/actor/interface/GgafDxICubeMapActor.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxICubeMapActor::GgafDxICubeMapActor() {
    _pCubeMapTextureConnection = nullptr;
    _reflectance = 0.0f;
    _cubemap_tex = "alpha_zero_cubemap.dds";
}

void GgafDxICubeMapActor::setCubeMap(const char* prm_cubemap_tex, float prm_reflectance) {
    setCubeMapTexture(prm_cubemap_tex);
    setCubeMapReflectance(prm_reflectance);
}

void GgafDxICubeMapActor::setCubeMapTexture(const char* prm_cubemap_tex) {
    _cubemap_tex = prm_cubemap_tex;
    if (_pCubeMapTextureConnection) {
        _pCubeMapTextureConnection->close();
    }
    _pCubeMapTextureConnection = (GgafDxTextureConnection*)(GgafDxGod::_pCubeMapTextureManager->connect(prm_cubemap_tex,this));
}
void GgafDxICubeMapActor::setCubeMapReflectance(float prm_reflectance) {
    _reflectance = prm_reflectance;
}

IDirect3DBaseTexture9* GgafDxICubeMapActor::getCubeMapTexture() {
    if (!_pCubeMapTextureConnection) {
        _pCubeMapTextureConnection = (GgafDxTextureConnection*)(GgafDxGod::_pCubeMapTextureManager->connect("alpha_zero_cubemap.dds",this));
    }
    return _pCubeMapTextureConnection->peek()->_pIDirect3DBaseTexture9;
}

GgafDxICubeMapActor::~GgafDxICubeMapActor() {
    //�����擾�� connet() �̓��C���X���b�h�ł���B
    //������ close() �i�f�X�g���N�^�j�͍H��X���b�h�Ŏ��s�B
    //�{���͔�����ׂ������AGgafResourceConnection����close()�����ǂ��A
    //�ʃX���b�h�����close()�ɂ��Ή������BTODO:�v�e�X�g
    if (_pCubeMapTextureConnection) {
        _pCubeMapTextureConnection->close();
    }
}
