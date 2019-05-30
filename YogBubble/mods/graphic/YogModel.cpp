#include "YogModel.h"
#include "Environment.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

void YogModel::UpdateWorldMatrix(){
	worldMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z) * XMMatrixScaling(scale.x, scale.y, scale.z) *
		XMMatrixTranslation(pos.x, pos.y, pos.z);
	//XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, 0);
}

void YogModel::UpdateFromTransform(Entity* entity){
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

void YogModel::ProcessNode(aiNode* const aiNode, const aiScene* pScene,const XMMATRIX& parentTransformMatrix){
	XMMATRIX transformMatrix = XMMatrixTranspose(XMMATRIX(&aiNode->mTransformation.a1))*parentTransformMatrix;
	for (UINT i = 0; i < aiNode->mNumMeshes; i++){
		aiMesh* mesh = pScene->mMeshes[aiNode->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, pScene,transformMatrix));
	}
	for (UINT i = 0; i < aiNode->mNumChildren; i++){
		ProcessNode(aiNode->mChildren[i], pScene,transformMatrix);
	}


}

bool YogModel::LoadModel(const std::string& filepath){
	Assimp::Importer importer;
	directory = YogString::GetDirectoryFromPath(filepath);
	const aiScene* pScene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
	if (pScene == nullptr)
		return false;
	if(pScene->HasAnimations()){
		LOG_N_F(YOG_INFO, "%s", "this have animation");
		
	}
	this->ProcessNode(pScene->mRootNode, pScene,XMMatrixIdentity());
	return true;
}

bool YogModel::InitSpirte(const std::string& cs){
	return false;
}

bool YogModel::Initialize(const std::string& filepath, ID3D11Device* device, ID3D11DeviceContext* context,
                          ConstantBuffer<VS_CB_DATA>& cb_vs_data){
	m_device = device;
	m_context = context;
	m_cbData = &cb_vs_data;
	try{
		if (!this->LoadModel(filepath)){
			return false;
		}
	}
	catch (...){

	}
	return true;

}


//! Returns an embedded texture

TextureStorageType YogModel::DetermineTextureStorageType(const aiScene* aiScene, aiMaterial* pMaterial, UINT uint,
                                                         aiTextureType aiTexture){
	if (pMaterial->GetTextureCount(aiTexture) == 0){
		return TextureStorageType::None;
	}
	aiString path;
	pMaterial->GetTexture(aiTexture, uint, &path);
	std::string texturePath = path.C_Str();
	if (texturePath[0] == '*'){
		if (aiScene->mTextures[0]->mHeight == 0){
			return TextureStorageType::EmbeddedIndexCompressed;
		}
		assert("SUPPORT DOES NOT EXIST YET");
		return TextureStorageType::EmbeddedIndexNonCompressed;
	}
	if (auto pTex = aiScene->GetEmbeddedTexture(texturePath.c_str())){
		if (pTex->mHeight == 0){
			return TextureStorageType::EmbeddedCompressed;
		}
		return TextureStorageType::EmbeddedNonCompressed;
	}
	if (texturePath.find('.') != std::string::npos){
		return TextureStorageType::Disk;
	}
	return TextureStorageType::None;
}

int YogModel::GetTextureIndex(aiString* path){
	assert(path->length > 2);
	return atoi(&path->C_Str()[1]);
	return 0;
}

std::vector<Texture> YogModel::LoadMaterialTextures(aiMaterial* pMaterial, aiTextureType textureType,
                                                    const aiScene* aiScene){
	std::vector<Texture> materialTexture;
	TextureStorageType storeType = TextureStorageType::Invalid;
	unsigned int count = pMaterial->GetTextureCount(textureType);
	if (count == 0){
		storeType = TextureStorageType::None;
		aiColor3D aiColor(0, 0, 0);
		switch (textureType){
		case aiTextureType_DIFFUSE: {
			pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor);
			if (aiColor.IsBlack()){
				materialTexture.push_back(Texture(m_device, Color::UnloaededTextureColor, aiTextureType_DIFFUSE));
				return materialTexture;
			}
			materialTexture.push_back(Texture(m_device, Color(255 * aiColor.r, 255 * aiColor.r, 255 * aiColor.r),
			                                  aiTextureType_DIFFUSE));
			return materialTexture;
		}
		}
	}
	else{
		for (UINT i = 0; i < count; i++){
			aiString path;
			pMaterial->GetTexture(textureType, i, &path);
			TextureStorageType storage = DetermineTextureStorageType(aiScene, pMaterial, i, textureType);
			switch (storage){
			case TextureStorageType::Disk: {
				std::string filename = this->directory + '\\' + path.C_Str();
				Texture diskTexture(this->m_device, filename, textureType);
				materialTexture.push_back(diskTexture);
				break;
			}
			case TextureStorageType::EmbeddedCompressed: {
				const aiTexture * pTexture = aiScene->GetEmbeddedTexture(path.C_Str());
				Texture embeddedTexture(m_device, reinterpret_cast<uint8_t*>(pTexture->pcData), pTexture->mWidth, textureType);
				materialTexture.push_back(embeddedTexture);
				break;
			}
			case TextureStorageType::EmbeddedIndexCompressed:{
				int index = GetTextureIndex(&path);
				Texture embeddedIndexTexture(m_device, reinterpret_cast<uint8_t*>(aiScene->mTextures[index]->pcData), aiScene->mTextures[index]->mWidth, textureType);
				materialTexture.push_back(embeddedIndexTexture);
				break;
			}
			}

		}

	}
	if (materialTexture.size() == 0){
		materialTexture.push_back(Texture(m_device, Color::UnloaededTextureColor, aiTextureType_DIFFUSE));
	}
	return materialTexture;
}

bool YogModel::Initialize(Environment* environment, ModelResource* modelResource){
	resource = modelResource;
	return Initialize(modelResource->m_resourceAddress, environment->m_device.Get(), environment->m_deviceContext.Get(),
	                  environment->vs_cb_data);

}

Mesh YogModel::ProcessMesh(const aiMesh* mesh, const aiScene* scene,const XMMATRIX& transformMatrix){
	std::vector<Dot> vertices;
	std::vector<UINT> indices;
	for (UINT i = 0; i < mesh->mNumVertices; i++){
		Dot ver;
		ver.pos.x = mesh->mVertices[i].x;
		ver.pos.y = mesh->mVertices[i].y;
		ver.pos.z = mesh->mVertices[i].z;

		ver.nom.x = mesh->mNormals[i].x;
		ver.nom.y = mesh->mNormals[i].y;
		ver.nom.z = mesh->mNormals[i].z;
		if (mesh->mTextureCoords[0]){
			ver.tex.x = mesh->mTextureCoords[0][i].x;
			ver.tex.y = mesh->mTextureCoords[0][i].y;
		}
		vertices.push_back(ver);
	}
	for (UINT i = 0; i < mesh->mNumFaces; i++){
		aiFace face = mesh->mFaces[i];
		for (UINT j = 0; j < face.mNumIndices; j++){
			indices.push_back(face.mIndices[j]);
		}
	}
	std::vector<Texture> textures;
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	std::vector<Texture> diffuseTextures = LoadMaterialTextures(material, aiTextureType_DIFFUSE, scene);
	textures.insert(textures.end(), diffuseTextures.begin(), diffuseTextures.end());
	return Mesh(this->m_device, m_context, vertices, indices, textures, transformMatrix);
}

void YogModel::Draw(const XMMATRIX& viewProjectionMatrix){
	m_context->VSSetConstantBuffers(0, 1, m_cbData->GetAddressOf());
	for (auto user : resource->m_users){
		if(*user==nullptr){
			continue;
		}
		UpdateFromTransform(*user);
		UINT stride = sizeof(Dot);
		UINT offset = 0;
		for (auto& mesh : meshes){
			m_cbData->data.wvpMatrix =mesh.GetTransformMatrix()* worldMatrix * viewProjectionMatrix;
			m_cbData->data.worldMatrix =mesh.GetTransformMatrix()* worldMatrix ;

			m_cbData->ApplyChanges(m_context);
			mesh.Draw();
		}
	}
}
