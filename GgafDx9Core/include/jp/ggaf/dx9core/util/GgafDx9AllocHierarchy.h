#ifndef GGAFDX9ALLOCHIERARCHY_H_
#define GGAFDX9ALLOCHIERARCHY_H_

namespace GgafDx9Core {



//http://www36.atwiki.jp/directx/m/pages/33.html?guid=on
//
////�K�w���蓖�ăN���X
//class CAllocateHierarchy: public ID3DXAllocateHierarchy {
//public:
//    STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);//�t���[���쐬
//    STDMETHOD(CreateMeshContainer)(THIS_ //���b�V���R���e�i�쐬
//            LPCSTR Name, //���O
//            CONST D3DXMESHDATA *pMeshData,//���b�V���f�[�^
//            CONST D3DXMATERIAL *pMaterials, //�}�e���A��
//            CONST D3DXEFFECTINSTANCE *pEffectInstances, //�G�t�F�N�g�̎���
//            DWORD NumMaterials, //�}�e���A����
//            CONST DWORD *pAdjacency, //�אڊ֌W
//            LPD3DXSKININFO pSkinInfo, //�X�L�����
//            LPD3DXMESHCONTAINER *ppNewMeshContainer);//���b�V���R���e�i�̃|�C���^
//    STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);//�t���[���폜
//    STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);//���b�V���R���e�i�폜
//
//    CAllocateHierarchy() {
//    }
//};
//
//WCHAR ShaderSource[4][30] = { L"skinmesh1.vsh",
//L"skinmesh2.vsh",
//L"skinmesh3.vsh",
//L"skinmesh4.vsh"
//};
//
//
//




class GgafDx9AllocHierarchy : public ID3DXAllocateHierarchy
{
protected:
    // �폜�l
    class deleterBase {
    public:
        virtual ~deleterBase() {}
    };

    template< class T >
    class deleter : public deleterBase {
    public:
        T* pObj;
        bool isAry;

        deleter( T* deletePtr, bool is_Ary = false ) : pObj(deletePtr), isAry( is_Ary ) {};
        virtual ~deleter(){
            if ( isAry ) {
                T* pa = (T*)pObj;
                delete[] pa;
            } else {
                T* p = (T*)pObj;
                delete p;
            }
        }
    };

protected:
    list<deleterBase*> m_DelList;   // �������X�g
    list<IUnknown*> m_ReleaseList;   // �����[�X���X�g

public:
    GgafDx9AllocHierarchy(void);
    virtual ~GgafDx9AllocHierarchy(void);

    // �t���[���𐶐�����
    STDMETHOD(CreateFrame)(THIS_
        LPCSTR Name,
        LPD3DXFRAME *ppNewFrame
    );

    // �R���e�i�𐶐�����
    STDMETHOD(CreateMeshContainer)(THIS_
        LPCSTR Name,
        CONST D3DXMESHDATA *pMeshData,
        CONST D3DXMATERIAL *pMaterials,
        CONST D3DXEFFECTINSTANCE *pEffectInstances,
        DWORD NumMaterials,
        CONST DWORD *pAdjacency,
        LPD3DXSKININFO pSkinInfo,
        LPD3DXMESHCONTAINER *ppNewMeshContainer
    );

    // �t���[�����폜����
    STDMETHOD(DestroyFrame)(THIS_
        LPD3DXFRAME pFrameToFree
    );

    // �R���e�i���폜����
    STDMETHOD(DestroyMeshContainer)(THIS_
        LPD3DXMESHCONTAINER pMeshContainerToFree
    );


protected:
    // �������X�g�ɓo�^����
    virtual void AddDelList( deleterBase* ptr, bool isAry = false );

    // ��������R�s�[����
    virtual LPSTR CopyStr(LPCSTR name);

    // �t���[���\���̂𐶐�����
    virtual D3DXFRAME* CreateNewFrame();

    // ���b�V���R���e�i�\���̂𐶐�����
    virtual D3DXMESHCONTAINER* CreateNewMeshContainer();

    // ���b�V���f�[�^��o�^
    virtual void RegistMeshData(CONST D3DXMESHDATA *pSrc, D3DXMESHDATA *pDest);

    // �����[�X���X�g�ɓo�^
    virtual void AddReleaseList( IUnknown *comptr);

    // �}�e���A���o�^
    virtual void RegistMaterial(CONST D3DXMATERIAL *pSrc, DWORD num, D3DXMATERIAL **pDest);

    // �G�t�F�N�g�o�^
    virtual void RegistEffect(CONST D3DXEFFECTINSTANCE *pSrc, D3DXEFFECTINSTANCE **ppDest);

    // �אڃ|���S���o�^
    virtual void RegistAdjacency(CONST DWORD *Src, DWORD polynum, DWORD **Dest);

    // �X�L���o�^
    virtual void RegistSkin( CONST LPD3DXSKININFO Src, LPD3DXSKININFO *Dest);
};

}

#endif /*GGAFDX9ALLOCHIERARCHY_H_*/
