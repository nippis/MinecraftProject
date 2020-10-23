cbuffer LightCBuf
{
	float3 lightPos;
}

static const float3 matColor = { 0.1f, 0.7f, 0.15f };
static const float3 ambient = { 0.10f, 0.2f, 0.10f };
static const float3 diffuseColor = { 1.0f, 1.0f, 1.0f };
static const float diffuseIntensity = 1.0f;
static const float attConst = 1.0f;
static const float attLin = 1.0f;
static const float attQuad = 1.0f;

float4 main(float3 worldPos : POSITION, float3 n : NORMAL) : SV_TARGET
{
  const float3 vToL = lightPos - worldPos;
  const float distToL = length(vToL);
  const float3 dirToL = vToL / distToL;
  
  const float att = attConst + attLin * distToL + attQuad * (distToL * distToL);
  
  const float3 diffuse = diffuseColor * diffuseIntensity * matColor * dot(dirToL, n);
  
  return float4(saturate(diffuse + ambient), 1.0f);

}