#include "GgafDx_World3DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

float4x4 g_matWorld;  //World�ϊ��s��

float g_dist_CamZ_default;
float g_TexSize;  //�ǂݍ��񂾃e�N�X�`���i�����`���O��j�̕��e�N�Z����
int g_TextureSplitRowcol; //�e�N�X�`���̏c���������B
                            //1�F�c���P���������������B
                            //2�F�c���Q�������S�̃A�j���p�^�[��
                            //3�F�c���R�������X�̃A�j���p�^�[��
float g_InvTextureSplitRowcol;
float g_UvFlipPtnNo;

//float3 g_vecLightFrom_World; // ���C�g�̕���
//float4 g_colLightAmbient;   // Ambien���C�g�F�i���ːF�j
//float4 g_colLightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_colMaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF

//s0���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj : POSITION;
    float  psize         : PSIZE;
    float4 color         : COLOR0;
    float4 uv_ps         : COLOR1;  //�X�y�L������ׂ��ĕ\��������UV���W����̏���PS�ɓn��
};

OUT_VS VS_DefaultPointSprite(
    float4 prm_posModel_Local : POSITION,  //�|�C���g�X�v���C�g�̃|�C���g�Q
    float  prm_psize_rate     : PSIZE,     //PSIZE�ł͖����āA�X�P�[���̗�(0.0�`N (1.0=���{)) �������Ă���
    float4 prm_color          : COLOR0,     //�I�u�W�F�N�g�̃J���[
    float1 prm_ptn_no         : TEXCOORD0 //UV�ł͖����āAprm_ptn_no.x�ɂ́A�\���������A�j���[�V�����p�^�[���ԍ������ߍ���ł���
) {
    OUT_VS out_vs = (OUT_VS)0;
    const float4 posModel_View = mul(mul(prm_posModel_Local, g_matWorld), g_matView);
    const float dep = posModel_View.z + 1.0; //+1.0�̈Ӗ���
                                    //VIEW�ϊ���(0.0, 0.0, -1.0) ���� (0.0, 0.0, 0.0) �����Ă��邽�߁A
                                    //�����ɉ�����B
    out_vs.posModel_Proj = mul(posModel_View, g_matProj);  //�ˉe�ϊ�
//	out_vs.psize = (g_TexSize / g_TextureSplitRowcol) * (g_dist_CamZ_default / dep) * prm_psize_rate;
    out_vs.psize = (g_TexSize*g_dist_CamZ_default*prm_psize_rate) / (g_TextureSplitRowcol*dep) ;
    //psize�͉�ʏ�̃|�C���g �X�v���C�g�̕� (�s�N�Z���P��)

    //�X�y�L�����Z�}���e�b�N�X(COLOR1)��ׂ��ĕ\��������UV���W����̏���PS�ɓn��
    int ptnno = (int)prm_ptn_no.x + (int)g_UvFlipPtnNo;
    if (ptnno >= g_TextureSplitRowcol*g_TextureSplitRowcol) {
        ptnno -= (g_TextureSplitRowcol*g_TextureSplitRowcol);
    }
    out_vs.uv_ps.x = fmod(ptnno, g_TextureSplitRowcol) * g_InvTextureSplitRowcol;
    out_vs.uv_ps.y = trunc(ptnno * g_InvTextureSplitRowcol) * g_InvTextureSplitRowcol;

    out_vs.color = prm_color;
    if (out_vs.posModel_Proj.z > g_zf*0.98) {
        out_vs.posModel_Proj.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
    }
    //dot by dot�l��
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);
    return out_vs;
}

float4 PS_DefaultPointSprite(
    float2 prm_uv_pointsprite	  : TEXCOORD0,   //(0.F, 0.F), (0.F, 1.F), (1.F, 0.F), (1.F, 1.F)������
    float4 prm_color              : COLOR0,
    float4 prm_uv_ps              : COLOR1  //�X�y�L�����ł͖����āA�\��������UV���W����̏�񂪓����Ă���
) : COLOR  {
    float2 uv = (float2)0;
    uv.x = prm_uv_pointsprite.x * g_InvTextureSplitRowcol + prm_uv_ps.x;
    uv.y = prm_uv_pointsprite.y * g_InvTextureSplitRowcol + prm_uv_ps.y;
    float4 colOut = tex2D( MyTextureSampler, uv) * prm_color * g_colMaterialDiffuse;
    colOut.a *= g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv_pointsprite	  : TEXCOORD0,
    float4 prm_color                : COLOR0,
    float4 prm_uv_ps              : COLOR1
) : COLOR  {
    const float2 uv = { prm_uv_pointsprite.x * g_InvTextureSplitRowcol + prm_uv_ps.x,
                        prm_uv_pointsprite.y * g_InvTextureSplitRowcol + prm_uv_ps.y };
    float4 colOut = tex2D( MyTextureSampler, uv) * prm_color * FLUSH_COLOR * g_colMaterialDiffuse;
    colOut.a *= g_alpha_master;
    return colOut;
}

technique DefaultPointSpriteTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultPointSprite();
        PixelShader  = compile PS_VERSION PS_DefaultPointSprite();
    }
}

technique DestBlendOne
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultPointSprite();
        PixelShader  = compile PS_VERSION PS_DefaultPointSprite();
    }
}

technique Flush
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultPointSprite();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

