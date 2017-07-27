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

#include <Banana/Data/ParticleSystemData.h>

#include <QtAppHelpers/QtAppMacros.h>
#include <QtAppHelpers/OpenGLWidget.h>

#include <OpenGLHelpers/ShaderProgram.h>
#include <OpenGLHelpers/OpenGLBuffer.h>
#include <OpenGLHelpers/OpenGLTexture.h>
#include <OpenGLHelpers/RenderObjects.h>

#include <map>
#include <memory>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class RenderWidget : public OpenGLWidget
{
    Q_OBJECT

public:
    RenderWidget(QWidget* parent = 0);
    const std::vector<std::shared_ptr<MeshObject> >& getMeshObjs() const;

    void setCamera(const glm::vec3& cameraPosition, const glm::vec3& cameraFocus);
    void setBox(const glm::vec3& boxMin, const glm::vec3& boxMax);

protected:
    virtual void initOpenGL();
    virtual void resizeOpenGLWindow(int, int) {}
    virtual void renderOpenGL();

public slots:
    void uploadMesh();
    void updateNumMeshes(int numMeshes);
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
    void renderLight();

    ////////////////////////////////////////////////////////////////////////////////
    void initRDataSkyBox();
    void renderSkyBox();

    ////////////////////////////////////////////////////////////////////////////////
    void initRDataFloor();
    void renderFloor();

    ////////////////////////////////////////////////////////////////////////////////
    void initRDataBox();
    void renderBox();

    ////////////////////////////////////////////////////////////////////////////////
    void initRDataMeshes();
    void renderMeshes();

    ////////////////////////////////////////////////////////////////////////////////
    int m_NumMeshes = 0;

    ////////////////////////////////////////////////////////////////////////////////
    std::vector<std::shared_ptr<MeshObject> > m_MeshObjs;
    std::shared_ptr<PointLights>              m_Lights;

    std::unique_ptr<SkyBoxRender>       m_SkyBoxRender       = nullptr;
    std::unique_ptr<PlaneRender>        m_FloorRender        = nullptr;
    std::unique_ptr<PointLightRender>   m_LightRender        = nullptr;
    std::unique_ptr<WireFrameBoxRender> m_WireFrameBoxRender = nullptr;
};