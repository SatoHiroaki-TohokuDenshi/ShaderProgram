//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture	: register(t0);	//テクスチャー
SamplerState	g_sampler	: register(s0);	//サンプラー

Texture2D		g_nmap		: register(t1);	//ノーマルマップ

//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer gModel : register(b0)
{
	float4x4	matWorld;		// ワールド行列
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	matNormal;		// 法線変形行列
	float4		diffuseColor;	// マテリアルの色＝拡散反射係数
	float4		ambientColor;	// 環境光係数
	float4		specularColor;	// 鏡面反射係数
	float		shininess;		// 鏡面反射強度
	bool		isTextured;		// テクスチャーが貼られているかどうか
	bool		isNMap;			// テクスチャーが貼られているかどうか
};

cbuffer gModel : register(b1)
{
	float4		lightPos;		// 光源の位置
	float4		eyePos;			// 視点
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos  : SV_POSITION;		// 位置
	float2 uv	: TEXCOORD;			// UV座標
	float4 eyeDir	: POSITION;		// 視点ベクトル
	float4 nEyeDir	: POSITION1;	// ノーマルマップ用視線ベクトル
	float4 light	: POSITION2;	// ノーマルマップ用光源ベクトル
	float4 normal	: NORMAL;		// 法線
	float4 color	: COLOR;		// 色（明るさ）
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL, float4 tangent : TANGENT)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData = (VS_OUT)0;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);

	// UV座標はそのまま
	outData.uv = uv.xy;

	//従法線
	float3 binormal = cross(normal, tangent);
	binormal = mul(binormal, matNormal);
	binormal = normalize(binormal);

	// 法線を変形
	normal = mul(normal, matNormal);
	normal = normalize(normal);

	outData.normal = normal;
	outData.normal.w = 0;
	
	//接線
	tangent = mul(tangent, matNormal);
	tangent = normalize(tangent);
	tangent.w = 0;

	// 視点ベクトルを獲得
	float4 posWorld = mul(pos, matWorld);
	outData.eyeDir = normalize(posWorld - eyePos);

	outData.nEyeDir.x = dot(outData.eyeDir, tangent);
	outData.nEyeDir.y = dot(outData.eyeDir, binormal);
	outData.nEyeDir.z = dot(outData.eyeDir, outData.normal);
	outData.nEyeDir.w = 0;

	// 光源の位置を正規化
	float4 light = normalize(lightPos);
	light.w = 0;
	light = normalize(light);
	outData.color = mul(light, outData.normal);
	outData.color.w = 0;

	outData.light.x = dot(light, tangent);
	outData.light.y = dot(light, binormal);
	outData.light.z = dot(light, outData.normal);
	outData.light.w = 0;

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightColor = float4(1.0, 1.0, 1.0, 1.0);		// 光源の色(強さ)

	float4 diffuse;		// 拡散反射
	float4 ambient;		// 環境光
	float4 specular;	// 鏡面反射

	if (isNMap) {
		//ノーマルマップから法線を取得
		float4 tmpNormal = g_nmap.Sample(g_sampler, inData.uv) * 2.0f - 1.0f;
		tmpNormal = normalize(tmpNormal);
		tmpNormal.w = 0;

		float4 nLight = saturate(dot(normalize(inData.light), tmpNormal));
		float4 ref = reflect(normalize(inData.light), tmpNormal);
		specular = pow(saturate(dot(ref, normalize(inData.nEyeDir))), shininess) * specularColor;

		if (isTextured) {
			diffuse = lightColor * g_texture.Sample(g_sampler, inData.uv) * nLight;
			ambient = lightColor * g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		else {
			diffuse = lightColor * diffuseColor * nLight;
			diffuse = lightColor * diffuseColor * ambientColor;
		}
	}
	else {
		float4 ref = reflect(normalize(lightPos), inData.normal);
		specular = pow(saturate(dot(ref, inData.eyeDir)), shininess) * specularColor;

		if (isTextured) {
			diffuse = lightColor * g_texture.Sample(g_sampler, inData.uv) * inData.color;
			ambient = lightColor * g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		else {
			diffuse = lightColor * diffuseColor * inData.color;
			ambient = lightColor * diffuseColor * ambientColor;
		}
	}
	//return specular;
	return (diffuse + ambient + specular);
}
