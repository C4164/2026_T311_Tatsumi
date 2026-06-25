cbuffer TransformCB : register(b0)
{
    row_major float4x4 world;
};

cbuffer CameraCB : register(b1)
{
    row_major float4x4 viewProj;
};

struct VSInput
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VSOutput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    float4 pos = float4(input.pos, 1.0f);

    // ê≥ÇµÇ¢èáî‘ÅiDirectXMath Ç∆àÍívÅj
    pos = mul(pos, world);
    pos = mul(pos, viewProj);

    output.pos = pos;
    output.uv = input.uv;

    return output;
}
