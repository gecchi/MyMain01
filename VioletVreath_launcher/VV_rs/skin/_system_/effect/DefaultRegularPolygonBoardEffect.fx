#include "GgafDx_Fix2DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

////////////////////////////////////////////////////////////////////////////////
// ggaf ���C�u�����AGgafDx::RegularPolygonBoardModel�p�V�F�[�_�[
//�y�T�v�z
// D3DFVF_XYZRHW �ŕ`�悵���悤�Ȏd�l�łQ�c�\�����܂��B
// ��ʍ������(0,0)�ŉ�ʉE�������i��ʕ�(px), ��ʍ���(px))�ƂȂ���W�n��
// �v���~�e�B�u�i�|���j�̊�_�͍�����ɂȂ�܂��B
// author : Masatoshi Tsuge
// date:2009/03/06
////////////////////////////////////////////////////////////////////////////////
float4 g_colMaterialDiffuse;
float g_offset_u; //�e�N�X�`��U���W����
float g_offset_v; //�e�N�X�`��V���W����
float g_transformed_x; //�A���C�������g���l���A�ϊ��ς�X���W(px)
float g_transformed_y; //�A���C�������g���l���A�ϊ��ς�Y���W(px)
float g_local_left_top_x;  //���[�J������ϊ��ς�X���W(px)
float g_local_left_top_y;  //���[�J������ϊ��ς�Y���W(px)
float g_depth_z; //�[�xZ (0 �` +1)
float g_sx; //X�������g�嗦(1.0�œ��{)
float g_sy; //Y�������g�嗦(1.0�œ��{)
float g_rz; //Z����]�p�i���W�A���j0�`2��
float g_sin_rz;
float g_cos_rz;
float g_x_center;
float g_y_center;
float g_u_center;
float g_v_center;
//s0���W�X�^�̃T���v�����g��(���Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj : POSITION;
    float2 uv            : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//RegularPolygonBoardModel�W�����_�V�F�[�_�[
OUT_VS VS_DefaultRegularPolygonBoard(
      float4 prm_posModel_Local : POSITION,  // ���f���̒��_
      float2 prm_uv             : TEXCOORD0  // ���f���̒��_��UV
) {
    OUT_VS out_vs = (OUT_VS)0;

    float x = prm_posModel_Local.x - g_x_center;
    float y = prm_posModel_Local.y - g_y_center;
    prm_posModel_Local.x = (x*g_cos_rz + y*g_sin_rz);
    prm_posModel_Local.y = (x*-g_sin_rz + y*g_cos_rz);
    prm_posModel_Local.x += g_x_center;
    prm_posModel_Local.y += g_y_center;

    if (g_rz == 0.0f) {
        //X���WY���W���� -1 �` +1 �ɉ������߂�B
        out_vs.posModel_Proj.x = - 1 + ( (2*( ((prm_posModel_Local.x + g_local_left_top_x)*g_sx) + g_transformed_x) ) * g_inv_game_buffer_width);
        out_vs.posModel_Proj.y =   1 - ( (2*( ((prm_posModel_Local.y + g_local_left_top_y)*g_sy) + g_transformed_y) ) * g_inv_game_buffer_height);
    } else {
        //�g��k��
        const float lx = (prm_posModel_Local.x + g_local_left_top_x) * g_sx;
        const float ly = (prm_posModel_Local.y + g_local_left_top_y) * g_sy;
        //��] �� X���WY���W���� -1 �` +1 �ɉ������߂�B
        out_vs.posModel_Proj.x = - 1 + ( (2*( (lx * cos(g_rz) - ly * sin(g_rz))                  + g_transformed_x) ) * g_inv_game_buffer_width);
        out_vs.posModel_Proj.y =   1 - ( (2*( (lx * sin(g_rz) + ly * cos(g_rz))                  + g_transformed_y) ) * g_inv_game_buffer_height);
    }
    out_vs.posModel_Proj.z = g_depth_z;
    out_vs.posModel_Proj.w = 1.0;

    //UV�̃I�t�Z�b�g�����Z
    x = prm_uv.x - g_u_center;
    y = prm_uv.y - g_v_center;
    out_vs.uv.x = (x*g_cos_rz + y*g_sin_rz);
    out_vs.uv.y = (x*-g_sin_rz + y*g_cos_rz);
    out_vs.uv.x += (g_u_center + g_offset_u);
    out_vs.uv.y += (g_v_center + g_offset_v);
    //dot by dot�l��
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);
    return out_vs;
}


float4 PS_DefaultRegularPolygonBoard(
    float2 prm_uv      : TEXCOORD0
) : COLOR  {
    float4 colOut = tex2D( MyTextureSampler, prm_uv);
    //Blinker���l��
    colOut = getBlinkColor(colOut);
    colOut *= g_colMaterialDiffuse;
    colOut.a *= g_alpha_master;
    return colOut;
}



float4 PS_Flush(
    float2 prm_uv      : TEXCOORD0
) : COLOR  {
    //�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
    float4 colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;
    colOut *= g_colMaterialDiffuse;
    colOut.a *= g_alpha_master;
    return colOut;
}

//���e�N�j�b�N�FDefaultRegularPolygonBoardTechnique��
//RegularPolygonBoardModel�p�W���V�F�[�_�[
technique DefaultRegularPolygonBoardTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultRegularPolygonBoard();
        PixelShader  = compile PS_VERSION PS_DefaultRegularPolygonBoard();
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
        VertexShader = compile VS_VERSION VS_DefaultRegularPolygonBoard();
        PixelShader  = compile PS_VERSION PS_DefaultRegularPolygonBoard();
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
        VertexShader = compile VS_VERSION VS_DefaultRegularPolygonBoard();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
