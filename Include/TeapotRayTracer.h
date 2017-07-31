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

#include <RayTracing/RayTracer.h>
#include <OpenGLHelpers/Lights.h>

#include <sutil/OptiXMesh.h>
#include <sutil/sutil.h>

#include "Common.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class TeapotRayTracer : public RayTracer
{
public:
    TeapotRayTracer(const std::shared_ptr<Camera>& camera) : RayTracer(camera) {}
    virtual void createOptiXContext(int width, int height) override;
    virtual void createPrograms() override;
    virtual void createScene() override;
    virtual void render() override;
    virtual void resizeViewport(int, int) override;

    void setRenderGround(bool bGround) { m_bRenderGround = bGround; }
    void setRenderSky(bool bSky) { m_bRenderSky = bSky; }
    void setGroundTexture(const std::shared_ptr<OpenGLTexture>& texture);
    void setSkyTexture(const std::shared_ptr<OpenGLTexture>& texture);
    void setLights(std::shared_ptr<PointLights>& lights);

protected:
    optix::Material createGroundMaterial();
    optix::Material createGlassMaterial();
    optix::Aabb     createGeometry(const std::vector<std::string>& fileNames, const std::vector<optix::Matrix4x4>& xforms,
                                   const optix::Material glassMaterial, const optix::Material groundMaterial,
                                   // output: this is a Group with two GeometryGroup children, for toggling visibility later
                                   optix::Group& topGroup);

    ////////////////////////////////////////////////////////////////////////////////
    optix::Group m_GeometryGroup;
};