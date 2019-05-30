#pragma once
#include "IndexBuffer.h"
#include "YogShader.h"
#include "VertexBuffer.h"
#include "graphic.h"
#include "../../yogcore/Entity/Entity.h"
#include "Mesh.h"
#include "../../yogcore/Resource/ModelResource.h"
struct aiMesh;
struct aiScene;
struct aiNode;

class YogModel{
private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;
	//ID3D11ShaderResourceView* m_texture;
	XMMATRIX worldMatrix =XMMatrixIdentity();
	ConstantBuffer<VS_CB_DATA>* m_cbData;
	std::string directory = "";
	std::vector<Mesh> meshes;

public:
	void UpdateWorldMatrix();
	void UpdateFromTransform(Entity* entity);

	YogModel();
	~YogModel();
	ModelResource* resource;

	Mesh ProcessMesh(const aiMesh* mesh, const aiScene* scene, const XMMATRIX& transformMatrix);
	void ProcessNode(aiNode* const aiNode, const aiScene* pScene, const XMMATRIX& parentTransformMatrix);
	bool LoadModel(const std::string& cs);
	bool InitSpirte(const std::string& cs);
	bool Initialize(const std::string& filepath, ID3D11Device* device, ID3D11DeviceContext* context, ConstantBuffer<VS_CB_DATA> &cb_vs_data);
	TextureStorageType DetermineTextureStorageType(const aiScene* aiScene, aiMaterial* pMaterial, UINT uint, aiTextureType aiTexture);
	int GetTextureIndex(aiString* path);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* pMaterial, aiTextureType textureType, const aiScene* aiScene);
	bool Initialize(Environment* environment,ModelResource* modelResource);
	//void SetTexture(ID3D11ShaderResourceView *m_texture);
	

	void Draw(const XMMATRIX& viewProjectionMatrix);
	XMVECTOR posVector;
	XMVECTOR rotVector;
	XMVECTOR scaleVector;
	XMFLOAT3 pos;
	XMFLOAT3 rot;
	XMFLOAT3 scale;
};

