/** (1.0 / CONFIG::RENDER_TARGET_BUFFER_WIDTH) / 2.0 */
float g_dbd_offset_x;
/** (1.0 / CONFIG::RENDER_TARGET_BUFFER_HEIGHT) / 2.0 */
float g_dbd_offset_y;


/**
 * dot by dot 考慮
 */
float4 adjustDotByDot(float4 pos) {
    float w = pos.w;
    pos /= w; //wで割って -1 〜 1 x -1 〜 1 の座標系に戻す
    pos.x -= g_dbd_offset_x; // -0.5px 分ずらす
    pos.y += g_dbd_offset_x; // +0.5px 分ずらす
    pos *= w; //wを乗じ もとの値に戻す
    return pos;
}
