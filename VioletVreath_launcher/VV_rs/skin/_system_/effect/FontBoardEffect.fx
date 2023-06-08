#include "GgafDx_Fix2DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

////////////////////////////////////////////////////////////////////////////////
// ggaf ���C�u�����AFontBoardActor�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2016/03/14
////////////////////////////////////////////////////////////////////////////////
float g_tex_blink_power;
float g_tex_blink_threshold;

//s0���W�X�^�̃T���v�����g��(���Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj : POSITION;
    float4 color         : COLOR0;
    float2 uv            : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//FontBoardActor�W�����_�V�F�[�_�[
OUT_VS VS_FontBoard(
      float4 prm_posModel_Local   : POSITION,      // ���f���̒��_
      float3 prm_vecNormal_Local  : NORMAL,        // ���f���̒��_�̖@��(���g�p)
      float2 prm_uv               : TEXCOORD0,     // ���f���̒��_��UV

      float3 prm_pos              : TEXCOORD1,     // px_x, px_y, depth_z
      float3 prm_info             : TEXCOORD2      // offset_u, offset_v, alpha
) {
    OUT_VS out_vs = (OUT_VS)0;
    float px_x = prm_pos.x; //�ϊ��ς�X���W(px)
    float px_y = prm_pos.y; //�ϊ��ς�Y���W(px)
    float depthZ = prm_pos.z; //�[�xZ (0 �` +1)
    float offset_u = prm_info.x; //�e�N�X�`��U���W����
    float offset_v = prm_info.y; //�e�N�X�`��V���W����
    float alpha = prm_info.z; //��

    //X���WY���W���� -1 �` +1 �ɉ������߂�B
    out_vs.posModel_Proj.x = - 1 + ((2*prm_posModel_Local.x + 2*px_x) * g_inv_game_buffer_width);
    out_vs.posModel_Proj.y =   1 - ((2*prm_posModel_Local.y + 2*px_y) * g_inv_game_buffer_height);
    out_vs.posModel_Proj.z = depthZ;
    out_vs.posModel_Proj.w = 1.0;
    //dot by dot�l��
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);
    //UV�̃I�t�Z�b�g�����Z
    out_vs.uv.x = prm_uv.x + offset_u;
    out_vs.uv.y = prm_uv.y + offset_v;
    out_vs.color.a = alpha;
    return out_vs;
}


//FontBoardActor�W���s�N�Z���V�F�[�_�[
float4 PS_FontBoard(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color  : COLOR0
) : COLOR  {
    float4 colOut = tex2D( MyTextureSampler, prm_uv);
    if (colOut.r >= g_tex_blink_threshold || colOut.g >= g_tex_blink_threshold || colOut.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power;
    }
    //���l��
    colOut.a = colOut.a * prm_color.a * g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    //�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
    float4 colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR * prm_color;
    //���l��
    colOut.a = colOut.a * prm_color.a * g_alpha_master;
    return colOut;

}

//���e�N�j�b�N�FFontBoardTechnique��
//�y�@�\�z
//FontBoardActor�p�W���V�F�[�_�[
//�y�T�v�z
//D3DFVF_XYZRHW �ŕ`�悵���悤�Ȏd�l�łQ�c�\�����܂��B
//��ʍ������(0,0)�ŉ�ʉE�������i��ʕ�(px), ��ʍ���(px))�ƂȂ���W�n��
//�v���~�e�B�u�i�|���j�̊�_�͍�����ɂȂ�܂��B
//--- VS ---
//�E���_�� -1 �` +1�։�������(�����ˉe�ϊ�)�AY���W���]
//--- PS ---
//�E�I�u�W�F�N�g�̃e�N�X�`��
//�E��������
//
//�y�ݒ�O���[�o���z
// float g_alpha			:	���l
// float g_px_x		: 	�ϊ��ς�X���W(px)
// float g_px_y		:	�ϊ��ς�Y���W(px)
// float g_depth_z			:	�[�xZ (0 �` +1)
// float g_game_buffer_width		:	��ʕ�(px)
// float g_game_buffer_height		:	��ʍ���(px)
// float g_offset_u			:	�e�N�X�`��U���W����
// float g_offset_v			:	�e�N�X�`��V���W����
// s0���W�X�^				:	2D�e�N�X�`��
technique FontBoardTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_FontBoard();
        PixelShader  = compile PS_VERSION PS_FontBoard();
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
        VertexShader = compile VS_VERSION VS_FontBoard();
        PixelShader  = compile PS_VERSION PS_FontBoard();
    }
}

technique Flush
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_FontBoard();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
