#include "DemoMaterial.hpp"

void DemoMaterial::initBlueWorld(GameRoot& gameRoot)
{
	//Setup camera
	ModuleInfo<Camera> camera = gameRoot.hCamera.create();
	camera->setPosition(Vec3(50, 10, 20), 0, 180);
	camera->setPerspective(45, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.01f, 10000.0f);
	camera->setStatic(false);

	//Setup scene and root node
	ModuleInfo<Scene> scene = gameRoot.hScene.create();
	ModuleInfo<SceneNode> rootNode = gameRoot.hSceneNode.create();

	mainScene = scene.ID;
	scenes.push_back(scene.ID);
	scene->addRootNode(rootNode.ID);
	scene->m_activeCamera = camera.ID;
	scene->m_skyboxID = gameRoot.hSkybox.getID("bluesky");

	ModuleInfo<Texture2D> textureChristmas = gameRoot.hTexture.create2D("textures//ChristmasTreeOrnament01_col.jpg");
	ModuleInfo<Texture2D> textureChristmasNM = gameRoot.hTexture.create2D("textures//ChristmasTreeOrnament01_nrm.jpg");

	ModuleInfo<Texture2D> textureFabric = gameRoot.hTexture.create2D("textures//Fabric24_col.jpg");
	ModuleInfo<Texture2D> textureFabricNM = gameRoot.hTexture.create2D("textures//Fabric24_nrm.jpg");

	ModuleInfo<Texture2D> textureRock = gameRoot.hTexture.create2D("textures//Rock23_col.jpg");
	ModuleInfo<Texture2D> textureRockNM = gameRoot.hTexture.create2D("textures//Rock23_nrm.jpg");

	ModuleInfo<Texture2D> textureTile = gameRoot.hTexture.create2D("textures//Tiles56_col.jpg");
	ModuleInfo<Texture2D> TextureTileNM = gameRoot.hTexture.create2D("textures//Tiles56_nrm.jpg");

	ModuleInfo<Texture2D> texturePlanks = gameRoot.hTexture.create2D("textures//Planks12_col.jpg");
	ModuleInfo<Texture2D> texturePlanksNM = gameRoot.hTexture.create2D("textures//Planks12_nrm.jpg");
	
	ModuleInfo<ModuleMaterial> christmasMat = gameRoot.hMaterial.create();
	christmasMat->setAmbientColor(Vec4(1, 1, 1, 1));
	christmasMat->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	christmasMat->setSpecularColor(Vec4(235, 242, 242, 1));
	christmasMat->setAmbientStrength(0.2f);
	christmasMat->setSpecularStrength(0.0005f);
	christmasMat->setTextureID(textureChristmas.ID);
	christmasMat->setNormalMapID(textureChristmasNM.ID);

	ModuleInfo<ModuleMaterial> fabricMat = gameRoot.hMaterial.create();
	fabricMat->setAmbientColor(Vec4(1, 1, 1, 1));
	fabricMat->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	fabricMat->setSpecularColor(Vec4(235, 242, 242, 1));
	fabricMat->setAmbientStrength(0.2f);
	fabricMat->setSpecularStrength(0.0005f);
	fabricMat->setTextureID(textureFabric.ID);
	fabricMat->setNormalMapID(textureFabricNM.ID);

	ModuleInfo<ModuleMaterial> rockMat = gameRoot.hMaterial.create();
	rockMat->setAmbientColor(Vec4(1, 1, 1, 1));
	rockMat->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	rockMat->setSpecularColor(Vec4(235, 242, 242, 1));
	rockMat->setAmbientStrength(0.2f);
	rockMat->setSpecularStrength(0.0005f);
	rockMat->setTextureID(textureRock.ID);
	rockMat->setNormalMapID(textureRockNM.ID);

	ModuleInfo<ModuleMaterial> tileMat = gameRoot.hMaterial.create();
	tileMat->setAmbientColor(Vec4(1, 1, 1, 1));
	tileMat->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	tileMat->setSpecularColor(Vec4(235, 242, 242, 1));
	tileMat->setAmbientStrength(0.2f);
	tileMat->setSpecularStrength(0.0005f);
	tileMat->setTextureID(textureTile.ID);
	tileMat->setNormalMapID(TextureTileNM.ID);

	ModuleInfo<ModuleMaterial> plankMat = gameRoot.hMaterial.create();
	plankMat->setAmbientColor(Vec4(1, 1, 1, 1));
	plankMat->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	plankMat->setSpecularColor(Vec4(235, 242, 242, 1));
	plankMat->setAmbientStrength(0.2f);
	plankMat->setSpecularStrength(0.0005f);
	plankMat->setTextureID(texturePlanks.ID);
	plankMat->setNormalMapID(texturePlanksNM.ID);

	ModuleInfo<ModuleMaterial> christmasMat1 = gameRoot.hMaterial.create();
	christmasMat1->setAmbientColor(Vec4(1, 1, 1, 1));
	christmasMat1->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	christmasMat1->setSpecularColor(Vec4(235, 242, 242, 1));
	christmasMat1->setAmbientStrength(0.2f);
	christmasMat1->setSpecularStrength(0.01f);
	christmasMat1->setTextureID(textureChristmas.ID);
	christmasMat1->setNormalMapID(textureChristmasNM.ID);

	ModuleInfo<ModuleMaterial> fabricMat1 = gameRoot.hMaterial.create();
	fabricMat1->setAmbientColor(Vec4(1, 1, 1, 1));
	fabricMat1->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	fabricMat1->setSpecularColor(Vec4(235, 242, 242, 1));
	fabricMat1->setAmbientStrength(0.1f);
	fabricMat1->setSpecularStrength(0.01f);
	fabricMat1->setTextureID(textureFabric.ID);
	fabricMat1->setNormalMapID(textureFabricNM.ID);

	ModuleInfo<ModuleMaterial> rockMat1 = gameRoot.hMaterial.create();
	rockMat1->setAmbientColor(Vec4(1, 1, 1, 1));
	rockMat1->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	rockMat1->setSpecularColor(Vec4(235, 242, 242, 1));
	rockMat1->setAmbientStrength(0.1f);
	rockMat1->setSpecularStrength(0.001f);
	rockMat1->setTextureID(textureRock.ID);
	rockMat1->setNormalMapID(textureRockNM.ID);

	ModuleInfo<ModuleMaterial> tileMat1 = gameRoot.hMaterial.create();
	tileMat1->setAmbientColor(Vec4(1, 1, 1, 1));
	tileMat1->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	tileMat1->setSpecularColor(Vec4(235, 242, 242, 1));
	tileMat1->setAmbientStrength(0.1f);
	tileMat1->setSpecularStrength(0.01f);
	tileMat1->setTextureID(textureTile.ID);
	tileMat1->setNormalMapID(TextureTileNM.ID);

	ModuleInfo<ModuleMaterial> plankMat1 = gameRoot.hMaterial.create();
	plankMat1->setAmbientColor(Vec4(1, 1, 1, 1));
	plankMat1->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	plankMat1->setSpecularColor(Vec4(235, 242, 242, 1));
	plankMat1->setAmbientStrength(0.1f);
	plankMat1->setSpecularStrength(0.01f);
	plankMat1->setTextureID(texturePlanks.ID);
	plankMat1->setNormalMapID(texturePlanksNM.ID);

	ModuleInfo<ModuleMaterial> christmasMat2 = gameRoot.hMaterial.create();
	christmasMat2->setAmbientColor(Vec4(1, 1, 1, 1));
	christmasMat2->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	christmasMat2->setSpecularColor(Vec4(235, 242, 242, 1));
	christmasMat2->setAmbientStrength(0.1f);
	christmasMat2->setSpecularStrength(1.0f);
	christmasMat2->setTextureID(textureChristmas.ID);
	christmasMat2->setNormalMapID(textureChristmasNM.ID);

	ModuleInfo<ModuleMaterial> fabricMat2 = gameRoot.hMaterial.create();
	fabricMat2->setAmbientColor(Vec4(1, 1, 1, 1));
	fabricMat2->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	fabricMat2->setSpecularColor(Vec4(235, 242, 242, 1));
	fabricMat2->setAmbientStrength(0.1f);
	fabricMat2->setSpecularStrength(1.0f);
	fabricMat2->setTextureID(textureFabric.ID);
	fabricMat2->setNormalMapID(textureFabricNM.ID);

	ModuleInfo<ModuleMaterial> rockMat2 = gameRoot.hMaterial.create();
	rockMat2->setAmbientColor(Vec4(1, 1, 1, 1));
	rockMat2->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	rockMat2->setSpecularColor(Vec4(235, 242, 242, 1));
	rockMat2->setAmbientStrength(0.1f);
	rockMat2->setSpecularStrength(1.0f);
	rockMat2->setTextureID(textureRock.ID);
	rockMat2->setNormalMapID(textureRockNM.ID);

	ModuleInfo<ModuleMaterial> tileMat2 = gameRoot.hMaterial.create();
	tileMat2->setAmbientColor(Vec4(1, 1, 1, 1));
	tileMat2->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	tileMat2->setSpecularColor(Vec4(235, 242, 242, 1));
	tileMat2->setAmbientStrength(0.1f);
	tileMat2->setSpecularStrength(1.0f);
	tileMat2->setTextureID(textureTile.ID);
	tileMat2->setNormalMapID(TextureTileNM.ID);

	ModuleInfo<ModuleMaterial> plankMat2 = gameRoot.hMaterial.create();
	plankMat2->setAmbientColor(Vec4(1, 1, 1, 1));
	plankMat2->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	plankMat2->setSpecularColor(Vec4(235, 242, 242, 1));
	plankMat2->setAmbientStrength(0.1f);
	plankMat2->setSpecularStrength(1.0f);
	plankMat2->setTextureID(texturePlanks.ID);
	plankMat2->setNormalMapID(texturePlanksNM.ID);

	std::vector<int32_t> materials = {
		gameRoot.hMaterial.getID("default"), gameRoot.hMaterial.getID("orange"), gameRoot.hMaterial.getID("blue"), gameRoot.hMaterial.getID("green"), gameRoot.hMaterial.getID("red"),
		christmasMat.ID, fabricMat.ID, rockMat.ID, tileMat.ID, plankMat.ID,
		christmasMat1.ID, fabricMat1.ID, rockMat1.ID, tileMat1.ID, plankMat1.ID,
		christmasMat2.ID, fabricMat2.ID, rockMat2.ID, tileMat2.ID, plankMat2.ID,
	};

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 5; x++) {
			ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
			ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

			transformation->scaleAbsolute(5, 5, 5);
			transformation->translateAbsolute(x * 20, 0, y * 20);

			m_transformations.push_back(transformation.ID);

			go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("ape"));
			go->addModule<ModuleTransformation>(transformation.ID);
			go->addModule<ModuleMaterial>(materials[(y * 5) + x]);
			go->setSceneID(scene.ID);

			rootNode->addGameObject(go.ID);
		}
	}

	scenes.push_back(scene.ID);
}

void DemoMaterial::init(GameRoot& gameRoot)
{
	initBlueWorld(gameRoot);
}


void DemoMaterial::run(GameRoot& gameRoot)
{
	gameRoot.m_mainScene = mainScene;
	gameRoot.m_activeScenes = scenes;
}

void DemoMaterial::update(const float fTimeDelta, GameRoot& gameRoot)
{
	for (const int32_t transformationID : m_transformations) {
		ModuleTransformation* transformation = gameRoot.hTransformation.get(transformationID);
		transformation->rotateZ(0.0005f);
	}
}
