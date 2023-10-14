cbuffer SamplingPixelConstantData : register(b0)
{
    float dx;
    float dy;
    float threshold;
    float strength;
    float iTime;
    float dummy[3];
};
#define S smoothstep

struct PixelShaderInput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
};

float4 Line(float2 uv, float speed, float height, float3 col)
{
    uv.y += S(1.0, 0.0, abs(uv.x)) * sin(iTime * speed + uv.x * height) * 0.2;
    return float4(S(.06 * S(0.2, 0.9, abs(uv.x)), 0.0, abs(uv.y) - 0.004) * col, 1.0) * S(1.0, 0.3, abs(uv.x));
}

float4 main(PixelShaderInput input) : SV_TARGET
{
    float2 uv = input.texcoord;
    
    //화면비 위치 조정
    uv.y = 1.0 - uv.y;
    uv = uv * 2.0 - 1.0;
    
    //결과값 저장
    float4 O = float4(0.f, 0.f, 0.f, 1.f);
    
    //선 갯수
    for (float i = 0.; i <= 8.; i += 1.)
    {
        float t = i / 5.;
        O += Line(uv, 1. + t, 4. + t, float3(.2 + t * .7, .2 + t * .4, 0.3));
    }
    return O;
}