//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//  Copyright (c) 2017 by
//       __      _     _         _____
//    /\ \ \__ _| |__ (_) __ _  /__   \_ __ _   _  ___  _ __   __ _
//   /  \/ / _` | '_ \| |/ _` |   / /\/ '__| | | |/ _ \| '_ \ / _` |
//  / /\  / (_| | | | | | (_| |  / /  | |  | |_| | (_) | | | | (_| |
//  \_\ \/ \__, |_| |_|_|\__,_|  \/   |_|   \__,_|\___/|_| |_|\__, |
//         |___/                                              |___/
//
//  <nghiatruong.vn@gmail.com>
//  All rights reserved.
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#pragma once

#include "Common.h"
#include "TeapotRayTracer.h"

#include <Banana/Data/ParticleSystemData.h>

#include <QtAppHelpers/QtAppMacros.h>
#include <QtAppHelpers/OpenGLWidget.h>
#include <QtAppHelpers/EnhancedMessageBox.h>

#include <OpenGLHelpers/Material.h>
#include <OpenGLHelpers/Lights.h>
//#include <OpenGLHelpers/ShaderProgram.h>
//#include <OpenGLHelpers/OpenGLBuffer.h>
#include <OpenGLHelpers/OpenGLTexture.h>
#include <OpenGLHelpers/RenderObjects.h>

#include "CUDA/Common.cuh"
#include "CUDA/Camera.h"
//#include <sutil/OptiXMesh.h>

#include <map>
#include <memory>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class RenderWidget : public OpenGLWidget
{
    Q_OBJECT

public:
    RenderWidget(QWidget* parent = 0);

    void setCamera(const glm::vec3& cameraPosition, const glm::vec3& cameraFocus);

protected:
    virtual void initOpenGL();
    virtual void resizeOpenGLWindow(int, int);
    virtual void renderOpenGL();

public slots:
//    void uploadMesh();
//    void updateNumMeshes(int numMeshes);
    void updateLights();

    void setSkyBoxTexture(int texIndex);
    void setFloorTexture(int texIndex);
    void setFloorSize(int size);
    void setFloorExposure(int exposure);
    void setMeshMaterial(const Material::MaterialData& material, int meshID);

    void reloadTextures();

signals:
    void lightsObjChanged(const std::shared_ptr<PointLights>& lights);

private:
    ////////////////////////////////////////////////////////////////////////////////
    void initRDataLight();

    ////////////////////////////////////////////////////////////////////////////////
    void initRDataSkyBox();
    void renderSkyBox();

    ////////////////////////////////////////////////////////////////////////////////
    void initRDataFloor();
    void renderFloor();

    ////////////////////////////////////////////////////////////////////////////////
    void initRDataMeshes();
    void renderMeshes();

    ////////////////////////////////////////////////////////////////////////////////
    int m_NumMeshes = 0;

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    void initRayTracer();
    void renderRayTracingBuffer();
    ////////////////////////////////////////////////////////////////////////////////
//    std::vector<std::shared_ptr<MeshObject> > m_MeshObjs;
//    std::shared_ptr<PointLights>              m_Lights;

//    std::unique_ptr<SkyBoxRender>       m_SkyBoxRender       = nullptr;
//    std::unique_ptr<PlaneRender>        m_FloorRender        = nullptr;
//    std::unique_ptr<PointLightRender>   m_LightRender        = nullptr;
//    std::unique_ptr<WireFrameBoxRender> m_WireFrameBoxRender = nullptr;
    std::unique_ptr<OpenGLTexture>           m_RenderTexture      = nullptr;
    std::unique_ptr<ScreenQuadTextureRender> m_ScreenQuadRenderer = nullptr;
    std::unique_ptr<TeapotRayTracer>         m_RayTracer          = nullptr;
};