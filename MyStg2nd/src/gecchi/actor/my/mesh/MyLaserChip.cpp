#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyLaserChip::MyLaserChip(const char* prm_name, MyLaserChipRotationActor* prm_pRotation) :
    GgafDx9MeshActor(prm_name,
                     "X/laser_chip",
                     "X/LaserChipEffect",
                     "LaserChipTechnique",
                     NEW GgafDx9GeometryMover(this),
                     NEW StgChecker(this) ) {
    _pChecker = (StgChecker*)_pGeoChecker;
    _class_name = "MyLaserChip";
    _pChip_front = NULL;
    _pChip_behind = NULL;
    _pRotation = prm_pRotation;
}

void MyLaserChip::initialize() {
    _hX = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_X" );
    _hY = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Y" );
    _hZ = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Z" );


    _prevX = _X;
    _prevY = _Y;
    _prevZ = _Z;

    _pGeoMover->setMoveVelocity(32000);
    //_pGeoMover->setRotAngleVelocity(AXIS_X, 300);
    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -10000, -10000, -10000, 10000, 10000, 10000);
    _pActor_Radical = NULL;
    _SX = 15*1000; _SY=15*1000; _SZ=15*1000;
    _fAlpha = 0.7; //両面あるので
}

void MyLaserChip::processBehavior() {
    if (onChangeToActive()) {
        _pRotation->_num_chip_active++;
    }
    if (_pChip_front != NULL) {
        _prevX = _pChip_front->_X;
        _prevY = _pChip_front->_Y;
        _prevZ = _pChip_front->_Z;
    }


    //座標に反映
    _pGeoMover->behave();

}

void MyLaserChip::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
    if (isOffScreen()) {
        inactivateTree();
        _pRotation->_num_chip_active--;
        _pChip_front = NULL;
		if (_pChip_behind != NULL) {
			_pChip_behind->_pChip_front = NULL;
		}
        _pChip_behind = NULL;
    }
}

void MyLaserChip::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    static D3DXMATRIX matWorld; //WORLD変換行列
    GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(this, matWorld);

    HRESULT hr;
    hr = pID3DXEffect->SetTechnique(_technique);
    potentialDx9Exception(hr, S_OK, "MyLaserChip::processDrawMain() SetTechnique("<<_technique<<") に失敗しました。");


    if (_pChip_front != NULL) {
		//_TRACE_("_pChip_front=("<<_prevX<<","<<_prevY<<","<<_prevZ<<")");
        hr = pID3DXEffect->SetFloat(_hX, 1.0*_prevX/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hX) に失敗しました。1");
        hr = pID3DXEffect->SetFloat(_hY, 1.0*_prevY/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hY) に失敗しました。1");
        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_prevZ/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hZ) に失敗しました。1");
    } else {
        hr = pID3DXEffect->SetFloat(_hX, 1.0*_X/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hX) に失敗しました。2");
        hr = pID3DXEffect->SetFloat(_hY, 1.0*_Y/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hY) に失敗しました。2");
        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_Z/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hZ) に失敗しました。2");

    }


    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &matWorld );
    potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(g_matWorld) に失敗しました。");

	    // アルファブレンドＯFF
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    //ピクセル単位のアルファテストを無効
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);  
    //上に書く画像の合成法(シェーダーに影響)
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //SRC,D3DBLEND_SRCALPHA=普通に描く。ポリゴンのアルファ値の濃さで描く。アルファ値の値が高ければ高いほど、濃く描く。
    //下地の画像の合成法(シェーダーに影響)
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //DIST,D3DBLEND_INVSRCALPHA=上に描くポリゴンのアルファ値の濃さによって、下地の描画を薄くする。

	
	
	
	UINT numPass;
    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE | D3DXFX_DONOTSAVESHADERSTATE );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() Begin() に失敗しました。");
    for (UINT pass = 0; pass < numPass; pass++) {
        hr = pID3DXEffect->BeginPass(pass);
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() BeginPass("<<pass<<") に失敗しました。");
        _pMeshModel->draw(this);
        hr = pID3DXEffect->EndPass();
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() EndPass() に失敗しました。");
    }
    hr = pID3DXEffect->End();
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() End() に失敗しました。");

	    // アルファブレンドＯＮ
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    //ピクセル単位のアルファテストを有効
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);  
    //上に書く画像の合成法(シェーダーに影響)
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //SRC,D3DBLEND_SRCALPHA=普通に描く。ポリゴンのアルファ値の濃さで描く。アルファ値の値が高ければ高いほど、濃く描く。
    //下地の画像の合成法(シェーダーに影響)
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //DIST,D3DBLEND_INVSRCALPHA=上に描くポリゴンのアルファ値の濃さによって、下地の描画を薄くする。

}

#ifdef OREDEBUG

void MyLaserChip::processDrawTerminate() {
    //当たり判定領域表示
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    DelineateActor::get()->drawHitarea(_pChecker);
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
}

#else

void DefaultMeshActor::processDrawTerminate() {}

#endif

void MyLaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
}


bool MyLaserChip::isOffScreen() {
    if (_X < _X_OffScreenLeft*2) {
        return true;
    } else {
        if (_X > _X_OffScreenRight*2) {
            return true;
        } else {
            if (_Y > _Y_OffScreenTop*2) {
                return true;
            } else {
                if (_Y < _Y_OffScreenBottom*2) {
                    return true;
                } else {
                    if (_Z < GgafDx9God::_dCamZ * LEN_UNIT * 10) {
                        return true;
                    } else {
                        if (_Z > -1 * GgafDx9God::_dCamZ * LEN_UNIT * 30) {
                            return true;
                        } else {
                            return false;
                        }
                    }
                }
            }
        }
    }
}

MyLaserChip::~MyLaserChip() {

}

