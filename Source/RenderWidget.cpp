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

#include "RenderWidget.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
RenderWidget::RenderWidget(QWidget* parent) : OpenGLWidget(parent)
{
    m_DefaultSize = QSize(1200, 1000);
    setCamera(DEFAULT_CAMERA_POSITION, DEFAULT_CAMERA_FOCUS);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//const std::vector<std::shared_ptr<MeshObject> >& RenderWidget::getMeshObjs() const
//{
//    return m_MeshObjs;
//}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::setCamera(const glm::vec3& cameraPosition, const glm::vec3& cameraFocus)
{
    m_Camera->setDefaultCamera(cameraPosition, cameraFocus, glm::vec3(0, 1, 0));
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::initOpenGL()
{
    initRDataSkyBox();
    initRDataLight();
    initRDataFloor();
    initRDataMeshes();

    qDebug() << width() << height();
    ////////////////////////////////////////////////////////////////////////////////
    m_RayTracer->createOptiXContext(width(), height());
    m_RayTracer->createMaterials();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::resizeOpenGLWindow(int width, int height)
{
    m_RayTracer->resizeViewport(width, height);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::renderOpenGL()
{
    renderSkyBox();
    renderFloor();
    renderMeshes();
    renderRayTracingBuffer();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//void RenderWidget::uploadMesh()
//{
//    makeCurrent();

//    for(auto& mesh : m_MeshObjs)
//    {
//        mesh->uploadDataToGPU();
//    }

//    doneCurrent();
//}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//void RenderWidget::updateNumMeshes(int numMeshes)
//{
//    m_NumMeshes = numMeshes;
//    makeCurrent();

//    doneCurrent();
//}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::updateLights()
{
//    makeCurrent();
//    m_Lights->uploadDataToGPU();
//    doneCurrent();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::initRDataLight()
{
//    m_Lights = std::make_shared<PointLights>();
//    m_Lights->setNumLights(2);

//    m_Lights->setLightPosition(glm::vec4(0, 100, -100, 1.0), 0);
//    m_Lights->setLightPosition(glm::vec4(0, 100, 100, 1.0),  1);
//    m_Lights->setLightDiffuse(glm::vec4(0.7), 0);
//    m_Lights->setLightDiffuse(glm::vec4(0.7), 1);

//    m_Lights->setSceneCenter(glm::vec3(0, 0, 0));
//    m_Lights->setLightViewPerspective(30);
//    m_Lights->uploadDataToGPU();

//    m_LightRender = std::make_unique<PointLightRender>(m_Camera, m_Lights, m_UBufferCamData);
//    emit lightsObjChanged(m_Lights);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::setSkyBoxTexture(int texIndex)
{
//    m_SkyBoxRender->setRenderTextureIndex(texIndex);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::initRDataSkyBox()
{
//    Q_ASSERT(m_UBufferCamData != nullptr);

//    m_SkyBoxRender = std::make_unique<SkyBoxRender>(m_Camera, QDir::currentPath() + "/Textures/Sky/", m_UBufferCamData);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::renderSkyBox()
{
//    Q_ASSERT(m_SkyBoxRender != nullptr);
//    m_SkyBoxRender->render();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::setFloorTexture(int texIndex)
{
//    Q_ASSERT(m_FloorRender != nullptr);
//    m_FloorRender->setRenderTextureIndex(texIndex);
}

void RenderWidget::setFloorSize(int size)
{
//    m_FloorRender->transform(glm::vec3(0), glm::vec3(static_cast<float>(size)));
//    m_FloorRender->scaleTexCoord(static_cast<float>(size), static_cast<float>(size));
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::setFloorExposure(int exposure)
{
//    m_FloorRender->setExposure(static_cast<float>(exposure) / 100.0f);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::initRDataFloor()
{
//    Q_ASSERT(m_UBufferCamData != nullptr && m_Lights != nullptr);

//    m_FloorRender = std::make_unique<PlaneRender>(m_Camera, m_Lights, QDir::currentPath() + "/Textures/Floor/", m_UBufferCamData);
//    m_FloorRender->transform(glm::vec3(0.0f, -0.01f, 0.0f), glm::vec3(10.0f));
//    m_FloorRender->scaleTexCoord(10, 10);
//    m_FloorRender->setAllowNonTextureRender(false);
//    m_FloorRender->setExposure(0.5f);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::renderFloor()
{
//    Q_ASSERT(m_FloorRender != nullptr);
//    m_FloorRender->render();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::reloadTextures()
{
//    makeCurrent();
//    m_SkyBoxRender->clearTextures();
//    m_SkyBoxRender->loadTextures(QDir::currentPath() + "/Textures/Sky/");

//    m_FloorRender->clearTextures();
//    m_FloorRender->loadTextures(QDir::currentPath() + "/Textures/Floor/");
//    doneCurrent();

    ////////////////////////////////////////////////////////////////////////////////
    EnhancedMessageBox msgBox(this);
    msgBox.setAutoCloseTimeout(2000);
    msgBox.setText("Textures reloaded!");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setAutoClose(true);
    msgBox.exec();
//    QMessageBox::information(this, "Info", "Textures reloaded!");
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::setMeshMaterial(const Material::MaterialData& material, int meshID)
{
    makeCurrent();
//    m_MeshRenders[meshID]->getMaterial()->setMaterial(material);
//    m_MeshRenders[meshID]->getMaterial()->uploadDataToGPU();
    doneCurrent();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::initRDataMeshes()
{
//    Q_ASSERT(m_UBufferCamData != nullptr && m_Lights != nullptr);

//    for(int i = 0; i < MAX_NUM_MESHES; ++i)
//    {
//        std::shared_ptr<MeshObject> mesh       = std::make_shared<MeshObject>();;
//        std::unique_ptr<MeshRender> meshRender = std::make_unique<MeshRender>(mesh, m_Camera, m_Lights, nullptr, m_UBufferCamData);

//        meshRender->getMaterial()->setMaterial(DEFAULT_MESH_MATERIAL);
//        meshRender->getMaterial()->uploadDataToGPU();

//        m_MeshObjs.push_back(std::move(mesh));;
//    }
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::renderMeshes()
{
//    for(auto& meshRender : m_MeshRenders)
//    {
//        meshRender->render();
    //    }
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::initRayTracer()
{
    m_RayTracer = std::make_unique<TeapotRayTracer>();

    m_RayTracer->createOptiXContext(width(), height());
    m_RayTracer->createScene();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void RenderWidget::renderRayTracingBuffer()
{
    optix::Buffer buffer = m_RayTracer->getOptiXOutputBuffer();

    // Query buffer information
    RTsize buffer_width_rts, buffer_height_rts;
    buffer->getSize(buffer_width_rts, buffer_height_rts);
    uint32_t width         = static_cast<int>(buffer_width_rts);
    uint32_t height        = static_cast<int>(buffer_height_rts);
    RTformat buffer_format = buffer->getFormat();

    GLboolean use_SRGB = GL_FALSE;
    if(buffer_format == RT_FORMAT_FLOAT4 || buffer_format == RT_FORMAT_FLOAT3)
    {
        glGetBooleanv(GL_FRAMEBUFFER_SRGB_CAPABLE_EXT, &use_SRGB);
        if(use_SRGB)
            glEnable(GL_FRAMEBUFFER_SRGB_EXT);
    }

    // Check if we have a GL interop display buffer
    const unsigned pboId = buffer->getGLBOId();
    Q_ASSERT(pboId != 0);

    static unsigned int gl_tex_id = 0;
    if(!gl_tex_id)
    {
        glGenTextures(1, &gl_tex_id);
        glBindTexture(GL_TEXTURE_2D, gl_tex_id);

        // Change these to GL_LINEAR for super- or sub-sampling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // GL_CLAMP_TO_EDGE for linear filtering, not relevant for nearest.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
    }

    glBindTexture(GL_TEXTURE_2D, gl_tex_id);

    // send PBO to texture
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboId);

    RTsize elmt_size = buffer->getElementSize();
    if(elmt_size % 8 == 0)
        glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
    else if(elmt_size % 4 == 0)
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    else if(elmt_size % 2 == 0)
        glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
    else
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if(buffer_format == RT_FORMAT_UNSIGNED_BYTE4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);
    else if(buffer_format == RT_FORMAT_FLOAT4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, width, height, 0, GL_RGBA, GL_FLOAT, 0);
    else if(buffer_format == RT_FORMAT_FLOAT3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F_ARB, width, height, 0, GL_RGB, GL_FLOAT, 0);
    else if(buffer_format == RT_FORMAT_FLOAT)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE32F_ARB, width, height, 0, GL_LUMINANCE, GL_FLOAT, 0);
    else
        __BNN_DIE("Unknown buffer format");

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    // 1:1 texel to pixel mapping with glOrtho(0, 1, 0, 1, -1, 1) setup:
    // The quad coordinates go from lower left corner of the lower left pixel
    // to the upper right corner of the upper right pixel.
    // Same for the texel coordinates.

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    if(use_SRGB)
        glDisable(GL_FRAMEBUFFER_SRGB_EXT);
}
