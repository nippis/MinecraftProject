cbuffer LightCBuf
{
	float4 lightPos;
}

static const float diffuseIntensity = 0.7f;
static const float ambientIntensity = 0.3f;

float AngleCosNormalized(float4 vec1, float4 vec2)
{
    const float lightAngleCos = dot(normalize(vec1), normalize(vec2));
    return (lightAngleCos + 1) / 2;
}

float4 main(float4 worldPos : TEXCOORD0, float4 n : TEXCOORD1, float4 position : SV_POSITION, float4 col : TEXCOORD2) : SV_TARGET
{
    const float diffuse = diffuseIntensity * AngleCosNormalized(lightPos - worldPos, n);
    
    const float totalIntensity = diffuse + ambientIntensity;
    return saturate(col * totalIntensity);

}