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

#include <OpenGLHelpers/RenderObjects.h>
#include "Common.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// FRMeshRender
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class FRMeshRender : public MeshRender
{
public:
    FRMeshRender(const std::shared_ptr<MeshObject>& meshObj, const std::shared_ptr<Camera>& camera, const std::shared_ptr<PointLights>& light,
                 QString textureFolder,
                 const std::shared_ptr<Material>& material = nullptr, const std::shared_ptr<OpenGLBuffer>& bufferCamData = nullptr) :
        MeshRender(meshObj, camera, light, textureFolder, material, bufferCamData)
    {
        initRenderData();
    }

    FRMeshRender(const std::shared_ptr<MeshObject>& meshObj, const std::shared_ptr<Camera>& camera, const std::shared_ptr<PointLights>& light,
                 const std::shared_ptr<Material>& material = nullptr, const std::shared_ptr<OpenGLBuffer>& bufferCamData = nullptr) :
        MeshRender(meshObj, camera, light, material, bufferCamData)
    {
        initRenderData();
    }

    virtual void render(bool bRenderShadow, bool bVisualizeShadowRegion, float shadowIntensity = 1.0f);

    void setSolidShadowMaps(const std::vector<std::shared_ptr<OpenGLTexture> >& shadowMaps);
    void setFluidShadowMaps(const std::vector<std::shared_ptr<OpenGLTexture> >& shadowMaps);
    void setFluidShadowThickness(const std::vector<std::shared_ptr<OpenGLTexture> >& shadowThickness);

protected:
    virtual void initRenderData() override;

    std::vector<std::shared_ptr<OpenGLTexture> > m_SolidShadowMaps;
    std::vector<std::shared_ptr<OpenGLTexture> > m_FluidShadowMaps;
    std::vector<std::shared_ptr<OpenGLTexture> > m_FluidShadowThickness;

    ////////////////////////////////////////////////////////////////////////////////
    GLuint m_USolidShadowMaps[MAX_NUM_LIGHTS];
    GLuint m_UFluidShadowMaps[MAX_NUM_LIGHTS];
    GLuint m_UFluidShadowThickness[MAX_NUM_LIGHTS];
    GLuint m_UShadowIntensity;
    GLuint m_UVisualizeShadowRegion;
};


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// FRPlaneRender
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class FRPlaneRender : public FRMeshRender
{
public:
    FRPlaneRender(const std::shared_ptr<Camera>& camera, const std::shared_ptr<PointLights>& light, QString textureFolder,
                  const std::shared_ptr<OpenGLBuffer>& bufferCamData = nullptr) :
        FRMeshRender(std::make_shared<GridObject>(), camera, light, textureFolder, nullptr, bufferCamData)
    { }

    FRPlaneRender(const std::shared_ptr<Camera>& camera, const std::shared_ptr<PointLights>& light, const std::shared_ptr<OpenGLBuffer>& bufferCamData = nullptr) :
        FRMeshRender(std::make_shared<GridObject>(), camera, light, nullptr, bufferCamData)
    {}

    virtual void render(bool bRenderShadow, bool bVisualizeShadowRegion, float shadowIntensity = 1.0f);
    void         scaleTexCoord(int scaleX, int scaleY);
};