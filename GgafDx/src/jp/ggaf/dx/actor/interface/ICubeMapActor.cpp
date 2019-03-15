#include "jp/ggaf/dx/actor/interface/ICubeMapActor.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"


using namespace GgafDx;

ICubeMapActor::ICubeMapActor() {
    _pCubeMapTextureConnection = nullptr;
    _reflectance = 0.0f;
    _cubemap_tex = "alpha_zero_cubemap.dds";
}

void ICubeMapActor::setCubeMap(const char* prm_cubemap_tex, float prm_reflectance) {
    setCubeMapTexture(prm_cubemap_tex);
    setCubeMapReflectance(prm_reflectance);
}

void ICubeMapActor::setCubeMapTexture(const char* prm_cubemap_tex) {
    _cubemap_tex = prm_cubemap_tex;
    if (_pCubeMapTextureConnection) {
        _pCubeMapTextureConnection->close();
    }
    _pCubeMapTextureConnection = (TextureConnection*)(pGOD->_pCubeMapTextureManager->connect(prm_cubemap_tex,this));
}
void ICubeMapActor::setCubeMapReflectance(float prm_reflectance) {
    _reflectance = prm_reflectance;
}

IDirect3DBaseTexture9* ICubeMapActor::getCubeMapTexture() {
    if (!_pCubeMapTextureConnection) {
        _pCubeMapTextureConnection = (TextureConnection*)(pGOD->_pCubeMapTextureManager->connect("alpha_zero_cubemap.dds",this));
    }
    return _pCubeMapTextureConnection->peek()->_pIDirect3DBaseTexture9;
}

ICubeMapActor::~ICubeMapActor() {
    //�����擾�� connet() �̓��C���X���b�h�ł���B
    //������ close() �i�f�X�g���N�^�j�͈��X���b�h�Ŏ��s�B
    //�{���͔�����ׂ������AGgafCore::ResourceConnection����close()�����ǂ��A
    //�ʃX���b�h�����close()�ɂ��Ή������BTODO:�v�e�X�g
    if (_pCubeMapTextureConnection) {
        _pCubeMapTextureConnection->close();
    }
}