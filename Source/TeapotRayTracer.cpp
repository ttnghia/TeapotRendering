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

#include "TeapotRayTracer.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void TeapotRayTracer::createOptiXContext(int width, int height)
{
    RayTracer::createOptiXContext(width, height);

    ////////////////////////////////////////////////////////////////////////////////
    m_Width  = width;
    m_Height = height;
    m_OptiXContext->setRayTypeCount(1);
    m_OptiXContext->setEntryPointCount(1);

    // Note: this sample does not need a big stack size even with high ray depths,
    // because rays are not shot recursively.
    m_OptiXContext->setStackSize(800);

    // Note: high max depth for reflection and refraction through glass
    m_OptiXContext["max_depth"]->setInt(DEFAULT_MAX_DEPTH);
    m_OptiXContext["cutoff_color"]->setFloat(0.2f, 0.2f, 0.2f);
    m_OptiXContext["frame"]->setUint(0u);
    m_OptiXContext["scene_epsilon"]->setFloat(1.e-3f);
    m_OptiXContext["bad_color"]->setFloat(1.0f, 0.0f, 1.0f);
    m_OptiXContext["background_light"]->setFloat(1.0f, 1.0f, 1.0f);
    m_OptiXContext["background_dark"]->setFloat(0.3f, 0.3f, 0.3f);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void TeapotRayTracer::createPrograms()
{
    Q_ASSERT(m_OptiXContext != 0);

    ////////////////////////////////////////////////////////////////////////////////
    // Accumulation buffer
    optix::Buffer accum_buffer = m_OptiXContext->createBuffer(RT_BUFFER_INPUT_OUTPUT | RT_BUFFER_GPU_LOCAL, RT_FORMAT_FLOAT4, m_Width, m_Height);
    m_OptiXContext["accum_buffer"]->set(accum_buffer);

    // Ray generation program
    std::string    ptxPath(getPtxPath("PathTraceCamera.cu"));
    optix::Program ray_gen_program = m_OptiXContext->createProgramFromPTXFile(ptxPath, "pinhole_camera");
    m_OptiXContext->setRayGenerationProgram(0, ray_gen_program);

    // Exception program
    optix::Program exception_program = m_OptiXContext->createProgramFromPTXFile(ptxPath, "exception");
    m_OptiXContext->setExceptionProgram(0, exception_program);

    // Miss program
    ptxPath = getPtxPath("GradientBG.cu");
    m_OptiXContext->setMissProgram(0, m_OptiXContext->createProgramFromPTXFile(ptxPath, "miss"));

    // align background's up direction with camera's look direction
    optix::float3 bg_up = optix::normalize(optix::make_float3(0.0f, -1.0f, -1.0f));

    // tilt the background's up direction in the direction of the camera's up direction
    bg_up.y += 1.0f;
    bg_up    = optix::normalize(bg_up);
    m_OptiXContext["up"]->setFloat(bg_up.x, bg_up.y, bg_up.z);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void TeapotRayTracer::resizeViewport(int width, int height)
{
    RayTracer::resizeViewport(width, height);
    resizeBuffer(m_OptiXContext["accum_buffer"]->getBuffer(), width, height);

    // need this?
    m_Width  = width;
    m_Height = height;
}

void TeapotRayTracer::setGroundTexture(const std::shared_ptr<OpenGLTexture>& texture)
{}

void TeapotRayTracer::setSkyTexture(const std::shared_ptr<OpenGLTexture>& texture)
{}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void TeapotRayTracer::setLights(std::shared_ptr<PointLights>& lights)
{}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void TeapotRayTracer::render()
{
    if(updateCamera())
        m_FrameNumber = 0;

    //    m_OptiXContext["unit_transmittance"]->setFloat(t.x, t.y, t.z);
//    m_OptiXContext["max_depth"]->setInt(max_depth);
    if(m_bRenderGround)
    {
        m_OptiXContext["top_object"]->set(m_GeometryGroup);
    }
    else
    {
        // assume group has two children: mesh and ground
        optix::GeometryGroup geomGroup = m_GeometryGroup->getChild<optix::GeometryGroup>(0);
        m_OptiXContext["top_object"]->set(geomGroup);
    }

    m_OptiXContext["frame"]->setUint(m_FrameNumber++);
    m_OptiXContext->launch(0, m_Width, m_Height);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void TeapotRayTracer::createScene()
{
    std::vector<std::string>      meshFiles;
    std::vector<optix::Matrix4x4> meshXforms;
    const optix::Matrix4x4        xform = optix::Matrix4x4::rotate(-M_PIf / 2.0f, optix::make_float3(0.0f, 1.0f, 0.0f));

#if 0
    for(int i = 0; i < 16; ++i)
    {
        char buff[512];
        sprintf_s(buff, "C:/Users/Nghia/Downloads/dragon/models/Mesh%03d.obj", i);
        meshFiles.push_back(std::string(buff));
        meshXforms.push_back(xform);
    }
#else
    meshFiles.push_back("D:/GoogleDrive/Programming/References/optix_advanced_samples/src/data/teapot_lid.ply");
    meshXforms.push_back(xform);
    meshFiles.push_back("D:/GoogleDrive/Programming/References/optix_advanced_samples/src/data/teapot_body.ply");
    meshXforms.push_back(xform);
#endif

    ////////////////////////////////////////////////////////////////////////////////
    optix::Material   groundMaterial = createGroundMaterial();
    optix::Material   glassMaterial  = createGlassMaterial();
    const optix::Aabb aabb           = createGeometry(meshFiles, meshXforms, glassMaterial, groundMaterial, m_GeometryGroup);


    glm::vec3 camPos   = glm::vec3(0.0f, 1.5f * aabb.extent(1), 1.5f * aabb.extent(2));
    glm::vec3 camFocus = glm::vec3(aabb.center().x, aabb.center().y, aabb.center().z);
    glm::vec3 camUp    = glm::vec3(0.0f, 1.0f, 0.0f);
    m_Camera->setDefaultCamera(camPos, camFocus, camUp);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
optix::Material TeapotRayTracer::createGroundMaterial()
{
    std::string    ptxPath(getPtxPath("Diffuse.cu"));
    optix::Program ch_program = m_OptiXContext->createProgramFromPTXFile(ptxPath, "closest_hit_radiance");

    optix::Material material = m_OptiXContext->createMaterial();
    material->setClosestHitProgram(0, ch_program);

    const std::string texture_filename = std::string(sutil::samplesDir()) + "/data/grid.ppm";
    material["Kd_map"]->setTextureSampler(sutil::loadTexture(m_OptiXContext, texture_filename, optix::make_float3(1.0f)));
    material["Kd_map_scale"]->setFloat(optix::make_float2(0.05f, 0.05f));

    return material;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
optix::Material TeapotRayTracer::createGlassMaterial()
{
    const std::string ptxPath    = getPtxPath("Glass.cu");
    optix::Program    ch_program = m_OptiXContext->createProgramFromPTXFile(ptxPath, "closest_hit_radiance");

    optix::Material material = m_OptiXContext->createMaterial();
    material->setClosestHitProgram(0, ch_program);

    material["fresnel_exponent"]->setFloat(4.0f);
    material["fresnel_minimum"]->setFloat(0.1f);
    material["fresnel_maximum"]->setFloat(1.0f);
    material["refraction_index"]->setFloat(1.4f);
    material["refraction_color"]->setFloat(0.99f, 0.99f, 0.99f);
    material["reflection_color"]->setFloat(0.99f, 0.99f, 0.99f);

    // Set this on the global context so it's easy to change in the gui
    const optix::float3 transmittance = DEFAULT_GLASS_TRANSMITTANCE;
    m_OptiXContext["unit_transmittance"]->setFloat(transmittance.x, transmittance.y, transmittance.z);

    return material;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
optix::GeometryInstance createOptiXGroundPlane(optix::Context     context,
                                               const std::string& parallelogram_ptx,
                                               const optix::Aabb& aabb,
                                               optix::Material    material,
                                               float              scale)
{
    optix::Geometry parallelogram = context->createGeometry();
    parallelogram->setPrimitiveCount(1u);
    parallelogram->setBoundingBoxProgram(context->createProgramFromPTXFile(parallelogram_ptx, "bounds"));
    parallelogram->setIntersectionProgram(context->createProgramFromPTXFile(parallelogram_ptx, "intersect"));
    const float         extent = scale * fmaxf(aabb.extent(0), aabb.extent(2));
    const optix::float3 anchor = optix::make_float3(aabb.center(0) - 0.5f * extent, aabb.m_min.y - 0.001f * aabb.extent(1), aabb.center(2) - 0.5f * extent);
    optix::float3       v1     = optix::make_float3(0.0f, 0.0f, extent);
    optix::float3       v2     = optix::make_float3(extent, 0.0f, 0.0f);
    const optix::float3 normal = optix::normalize(cross(v1, v2));
    float               d      = optix::dot(normal, anchor);
    v1 *= 1.0f / optix::dot(v1, v1);
    v2 *= 1.0f / optix::dot(v2, v2);
    optix::float4 plane = optix::make_float4(normal, d);
    parallelogram["plane"]->setFloat(plane);
    parallelogram["v1"]->setFloat(v1);
    parallelogram["v2"]->setFloat(v2);
    parallelogram["anchor"]->setFloat(anchor);

    optix::GeometryInstance instance = context->createGeometryInstance(parallelogram, &material, &material + 1);
    return instance;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
optix::Aabb TeapotRayTracer::createGeometry(const std::vector<std::string>& fileNames, const std::vector<optix::Matrix4x4>& xforms,
                                            const optix::Material glassMaterial, const optix::Material groundMaterial,
                                            optix::Group& topGroup)
{
    const std::string ptxPath = getPtxPath("TriangleMesh.cu");

    topGroup = m_OptiXContext->createGroup();
    topGroup->setAcceleration(m_OptiXContext->createAcceleration("Trbvh"));

    int         num_triangles = 0;
    optix::Aabb aabb;

#if 1
    {
        optix::GeometryGroup geometry_group = m_OptiXContext->createGeometryGroup();
        geometry_group->setAcceleration(m_OptiXContext->createAcceleration("Trbvh"));
        topGroup->addChild(geometry_group);
        for(size_t i = 0; i < fileNames.size(); ++i)
        {
            OptiXMesh mesh;
            mesh.context = m_OptiXContext;

            // override defaults
            mesh.intersection = m_OptiXContext->createProgramFromPTXFile(ptxPath, "mesh_intersect_refine");
            mesh.bounds       = m_OptiXContext->createProgramFromPTXFile(ptxPath, "mesh_bounds");
            mesh.material     = glassMaterial;

            loadMesh(fileNames[i], mesh, xforms[i]);
            geometry_group->addChild(mesh.geom_instance);

            aabb.include(mesh.bbox_min, mesh.bbox_max);

            std::cerr << fileNames[i] << ": " << mesh.num_triangles << std::endl;
            num_triangles += mesh.num_triangles;
        }
        std::cerr << "Total triangle count: " << num_triangles << std::endl;
    }


    {
        // Ground plane
        optix::GeometryGroup geometry_group = m_OptiXContext->createGeometryGroup();
        geometry_group->setAcceleration(m_OptiXContext->createAcceleration("NoAccel"));
        topGroup->addChild(geometry_group);
        const std::string       floor_ptx = getPtxPath("ParallelogramIterative.cu");
        optix::GeometryInstance instance  = createOptiXGroundPlane(m_OptiXContext, floor_ptx, aabb, groundMaterial, 3.0f);
        geometry_group->addChild(instance);
    }
#endif
    m_OptiXContext["top_object"]->set(topGroup);

    return aabb;
}
