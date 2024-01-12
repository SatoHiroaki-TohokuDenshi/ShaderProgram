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
	float4		ambinetColor;	// 環境光係数
	float4		specularColor;	// 鏡面反射係数
	float		shininess;		// 鏡面反射強度
	bool		isTextured;		// テクスチャーが貼られているかどうか
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos  : SV_POSITION;	// 位置
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	VS_OUT outData;

	// 法線の平行移動の情報を削除
	normal.w = 0;

	// 法線方向に拡大
	pos = pos + normal * 0.05;

	// スクリーン座標に変換
	outData.pos = mul(pos, matWVP);

	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	// 黒を出力
	return (0.0, 0.0, 0.0, 0.0);
}
