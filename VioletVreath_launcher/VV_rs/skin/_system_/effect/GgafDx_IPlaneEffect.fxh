/** レンダリングターゲットの横幅(px) */
float g_dbd_offset_x;
/** レンダリングターゲットの縦幅(px) */
float g_dbd_offset_y;


/**
 * dot by dot 考慮
 */
float4 adjustDotByDot(float4 pos) {
    pos.x += g_dbd_offset_x*pos.w;
    pos.y += g_dbd_offset_y*pos.w;
    return pos;
}
