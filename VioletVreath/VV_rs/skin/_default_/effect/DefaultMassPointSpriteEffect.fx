#include "GgafEffectConst.fxh"
// author : Masatoshi Tsuge
// date:2016/05/17

float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float g_dist_CamZ_default;
float g_zn;
float g_zf;
float g_TexSize;  //�ǂݍ��񂾃e�N�X�`���i�����`���O��j�̕��e�N�Z����
int g_TextureSplitRowcol; //�e�N�X�`���̏c���������B
                            //1�F�c���P���������������B
                            //2�F�c���Q�������S�̃A�j���p�^�[��
                            //3�F�c���R�������X�̃A�j���p�^�[��
float g_InvTextureSplitRowcol;

float3 g_vecLightFrom_World; // ���C�g�̕���
float4 g_colLightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_colLightDiffuse;   // Diffuse���C�g�F�i���ːF�j

//float g_tex_blink_power;
//float g_tex_blink_threshold;
float g_alpha_master;

//s0���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj : POSITION;
    float  psize         : PSIZE;
    float4 color         : COLOR0;
    float4 uv_pos        : COLOR1;  //�X�y�L������ׂ��ĕ\��������UV���W����̏���PS�ɓn��
};

OUT_VS VS_DefaultMassPointSprite(
    float4 prm_posModel_Local : POSITION,  //�|�C���g�X�v���C�g�̃|�C���g�Q
    float  prm_psize_rate     : PSIZE,     //PSIZE�ł͖����āA�X�P�[���̗�(0.0�`N (1.0=���{)) �������Ă���
    float4 prm_p_color        : COLOR0,     //�I�u�W�F�N�g�̃J���[
    float2 prm_ptn_no         : TEXCOORD0 , //UV�ł͖����āAprm_ptn_no.x�ɂ́A�\���������A�j���[�V�����p�^�[���ԍ������ߍ���ł���

    float4 prm_world0         : TEXCOORD1,
    float4 prm_world1         : TEXCOORD2,
    float4 prm_world2         : TEXCOORD3,
    float4 prm_world3         : TEXCOORD4,
    float4 prm_color          : TEXCOORD5,
    float prm_pattno_uvflip_now  : TEXCOORD6
) {
    OUT_VS out_vs = (OUT_VS)0;
    float4x4 matWorld = {prm_world0, prm_world1, prm_world2, prm_world3};
    const float4 posModel_View = mul(mul(prm_posModel_Local, matWorld), g_matView);
    const float dep = posModel_View.z + 1.0; //+1.0�̈Ӗ���
                                    //VIEW�ϊ���(0.0, 0.0, -1.0) ���� (0.0, 0.0, 0.0) �����Ă��邽�߁A
                                    //�����ɉ�����B
    out_vs.posModel_Proj = mul(posModel_View, g_matProj);  //�ˉe�ϊ�
    out_vs.psize = (g_TexSize / g_TextureSplitRowcol) * (g_dist_CamZ_default / dep) * prm_psize_rate;

    //psize�͉�ʏ�̃|�C���g �X�v���C�g�̕� (�s�N�Z���P��)
    //�X�y�L�����Z�}���e�b�N�X(COLOR1)��ׂ��ĕ\��������UV���W����̏���PS�ɓn��
    int ptnno = prm_ptn_no.x + prm_pattno_uvflip_now;
    if (ptnno >= g_TextureSplitRowcol*g_TextureSplitRowcol) {
        ptnno -= (g_TextureSplitRowcol*g_TextureSplitRowcol);
    }
    out_vs.uv_pos.x = fmod(ptnno, g_TextureSplitRowcol) / g_TextureSplitRowcol;
    out_vs.uv_pos.y = trunc(ptnno / g_TextureSplitRowcol) / g_TextureSplitRowcol;

    out_vs.color = prm_p_color * prm_color;
    out_vs.color.a = prm_p_color.a * prm_color.a;
    if (out_vs.posModel_Proj.z > g_zf*0.98) {
        out_vs.posModel_Proj.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
    }
    return out_vs;
}

float4 PS_DefaultMassPointSprite (
    float2 prm_uv_pointsprite	  : TEXCOORD0,  //(0.0, 0.0), (0.0, 1.0), (1.0, 0.0), (1.0, 1.0) �͈̔͂ŗ���
    float4 prm_color              : COLOR0,
    float4 prm_uv_pos             : COLOR1      //�X�y�L�����ł͖����āA�\��������UV���W����̏�񂪓����Ă���
) : COLOR  {
    const float2 uv = { prm_uv_pointsprite.x * (1.0 / g_TextureSplitRowcol) + prm_uv_pos.x,
                        prm_uv_pointsprite.y * (1.0 / g_TextureSplitRowcol) + prm_uv_pos.y };
    float4 colOut = tex2D( MyTextureSampler, uv) * prm_color;
    colOut.a *= g_alpha_master;
    return colOut;
}


float4 PS_Flush(
    float2 prm_uv_pointsprite : TEXCOORD0,
    float4 prm_color          : COLOR0,
    float4 prm_uv_pos         : COLOR1
) : COLOR  {
    const float2 uv = { prm_uv_pointsprite.x * (1.0 / g_TextureSplitRowcol) + prm_uv_pos.x,
                        prm_uv_pointsprite.y * (1.0 / g_TextureSplitRowcol) + prm_uv_pos.y };
    float4 colOut = tex2D( MyTextureSampler, uv) * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
    return colOut;
}

technique DefaultMassPointSpriteTechnique
{
    pass P0 {
        PointSpriteEnable = true;
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        //BlendOpAlpha = Add;       //default
        VertexShader = compile VS_VERSION VS_DefaultMassPointSprite();
        PixelShader  = compile PS_VERSION PS_DefaultMassPointSprite();
    }
}

technique DestBlendOne
{
    pass P0 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        //BlendOpAlpha = Add;       //default
        VertexShader = compile VS_VERSION VS_DefaultMassPointSprite();
        PixelShader  = compile PS_VERSION PS_DefaultMassPointSprite();
    }
}

technique Flush
{
    pass P0 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        //BlendOpAlpha = Add;       //default
        VertexShader = compile VS_VERSION VS_DefaultMassPointSprite();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

