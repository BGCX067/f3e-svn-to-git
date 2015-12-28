
Texture2D texture0;
SamplerState linearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Border;
    AddressV = Border;
};

matrix World;
matrix View;
matrix Projection;

struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input , unsigned int InstanceID : SV_InstanceID )
{
	PS_INPUT output;
	
	int row = InstanceID / 80;

	float fac = 1.1f;

	float4 position = input.Pos + float4(InstanceID%80 * fac, row * fac, 0, 1);
	position.xy = position.xy - float2(45,45);
	output.Pos = mul( position, World );
    output.Pos = mul( output.Pos, View );    
    output.Pos = mul( output.Pos, Projection );
	output.Tex = input.Tex;
	
    return output;  
}
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input) : SV_Target
{

   return texture0.Sample( linearSampler, input.Tex ); 
}


//--------------------------------------------------------------------------------------
technique10 Render
{
    pass P0
    {        
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}
