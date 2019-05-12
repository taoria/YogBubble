#include "YogModel.h"
#include "Environment.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
void YogModel::UpdateWorldMatrix(){
	worldMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z) *XMMatrixScaling(scale.x,scale.y,scale.z)* XMMatrixTranslation(pos.x, pos.y, pos.z);
	//XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, 0);
}

void YogModel::UpdateFromTransform(Entity *entity){
	Vec3 vec3 = entity->GetRotation();
	Vec3 pos3 = entity->GetPosition();
	Vec3 scale3 = entity->GetScale();
	pos = static_cast<XMFLOAT3>(pos3);
	rot = static_cast<XMFLOAT3>(vec3);
	scale = static_cast<XMFLOAT3>(scale3);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->posVector = XMLoadFloat3(&this->pos);
	this->scaleVector = XMLoadFloat3(&this->scale);
	UpdateWorldMatrix();
}

YogModel::YogModel(){

}


YogModel::~YogModel(){
}

void YogModel::ProcessNode(aiNode* const aiNode, const aiScene* pScene){
	for (UINT i = 0; i < aiNode->mNumMeshes;i++){
		aiMesh * mesh = pScene->mMeshes[aiNode->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, pScene));
	}
	for(UINT i=0;i<aiNode->mNumChildren;i++){
		ProcessNode(aiNode->mChildren[i], pScene);
	}


}
bool YogModel::LoadModel(const std::string& filepath){
	Assimp::Importer importer;
	
	const aiScene *pScene = importer.ReadFile(filepath, aiProcess_Triangulate|aiProcess_ConvertToLeftHanded);
	if (pScene == nullptr)
		return  false;
	this->ProcessNode(pScene->mRootNode, pScene);
	return true;
}

bool YogModel::Initialize(const std::string& filepath, ID3D11Device* device, ID3D11DeviceContext* context,
                          ConstantBuffer<VS_CB_DATA>& cb_vs_data){
	m_device = device;
	m_context = context;
	m_cbData = &cb_vs_data;
	try{
		if(!this->LoadModel(filepath)){
			return  false;
		}
	}catch(...){
		
	}
	return true;

}


//! Returns an embedded texture

TextureStorageType YogModel::DetermineTextureStorageType(const aiScene* aiScene, aiMaterial* pMaterial, UINT uint,
	aiTextureType aiTexture){
	if(pMaterial->GetTextureCount(aiTexture)==0){
		return TextureStorageType::None;
	}
	aiString path;
	pMaterial->GetTexture(aiTexture, uint, &path);
	std::string texturePath = path.C_Str();
	if(texturePath[0] =='*'){
		if(aiScene->mTextures[0]->mHeight==0){
			return TextureStorageType::EmbeddedIndexCompressed;
		}else{
			assert("SUPPORT DOES NOT EXIST YET");
			return TextureStorageType::EmbeddedIndexNonCompressed;
		}
	}
	if(auto pTex = aiScene->GetEmbeddedTexture(texturePath.c_str())){
		if(pTex->mHeight==0){
			return TextureStorageType::EmbeddedCompressed;
		}else{
			return TextureStorageType::EmbeddedNonCompressed;
		}
	}
	
}

std::vector<Texture> YogModel::LoadMaterialTextures(aiMaterial* pMaterial, aiTextureType textureType,const aiScene* aiScene){
	std::vector<Texture> materialTexture;
	TextureStorageType storeType = TextureStorageType::Invalid;
	unsigned int count = pMaterial->GetTextureCount(textureType);
	if(count==0){
		storeType = TextureStorageType::None;
		aiColor3D aiColor(0, 0, 0);
		switch (textureType){
		case aiTextureType_DIFFUSE:{
			pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor);
			if(aiColor.IsBlack()){
				materialTexture.push_back(Texture(m_device, Color::UnloaededTextureColor,aiTextureType_DIFFUSE));
				return materialTexture;
			}
			materialTexture.push_back(Texture(m_device, Color(255 * aiColor.r, 255 * aiColor.r, 255 * aiColor.r), aiTextureType_DIFFUSE));
			return materialTexture;
		}
		}
	}else{
		for(UINT i =0;i<count;i++){
			aiString path;
			pMaterial->GetTexture(textureType, i, &path);
			TextureStorageType storage = DetermineTextureStorageType(aiScene, pMaterial, i, textureType);
		}
	}
	if(materialTexture.size()==0){
		materialTexture.push_back(Texture(m_device, Color::UnloaededTextureColor, aiTextureType_DIFFUSE));
	}
	return materialTexture;
}

bool YogModel::Initialize(Environment* environment,ModelResource* modelResource){
	resource = modelResource;
	return Initialize(modelResource->m_resourceAddress, environment->m_device.Get(), environment->m_deviceContext.Get(), environment->vs_cb_data);
	
}

Mesh YogModel::ProcessMesh(const aiMesh* mesh, const aiScene* scene){
	std::vector<Dot> vertices;
	std::vector<UINT> indices;
	for(UINT i=0;i< mesh->mNumVertices;i++){
		Dot ver;
		ver.pos.x = mesh->mVertices[i].x;
		ver.pos.y= mesh->mVertices[i].y;
		ver.pos.z= mesh->mVertices[i].z;
		if (mesh->mTextureCoords[0]) {
			ver.tex.x = mesh->mTextureCoords[0][i].x;
			ver.tex.y = mesh->mTextureCoords[0][i].y;
		}
		vertices.push_back(ver);
	}
	for(UINT i=0;i<mesh->mNumFaces;i++){
		aiFace face = mesh->mFaces[i];
		for(UINT j=0;j <face.mNumIndices;j++){
			indices.push_back(face.mIndices[j]);
		}
	}
	std::vector<Texture> textures;
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	std::vector<Texture> diffuseTextures = LoadMaterialTextures(material,aiTextureType_DIFFUSE,scene);
	
	textures.insert(textures.end(), diffuseTextures.begin(), diffuseTextures.end());
	return Mesh(this->m_device, m_context, vertices, indices,textures);
}

void YogModel::Draw(const XMMATRIX& viewProjectionMatrix){
	for(auto user :resource->m_users){
		UpdateFromTransform(user);
		m_cbData->data.mat = this->worldMatrix * viewProjectionMatrix;
		m_cbData->data.mat = XMMatrixTranspose(m_cbData->data.mat);
		m_cbData->ApplyChanges(m_context);
		UINT stride = sizeof(Dot);
		UINT offset = 0;
	//	m_context->PSSetShaderResources(0, 1, &this->m_texture);
		//	m_context->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_context->VSSetConstantBuffers(0, 1, m_cbData->GetAddressOf());
		//	m_context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
		for (auto& mesh : meshes) {
			mesh.Draw();
		}
	}
}

