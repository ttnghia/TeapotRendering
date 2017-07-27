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

#include <QMouseEvent>
#include <Banana/NumberHelpers.h>
#include <Banana/Macros.h>
#include "MainWindow.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
MainWindow::MainWindow(QWidget* parent) : OpenGLMainWindow(parent)
{
    instantiateOpenGLWidget();
    setupRenderWidgets();
    setupStatusBar();
    connectWidgets();
    setArthurStyle();

    setWindowTitle("Real-time Teapot Rendering by OptiX");
    setFocusPolicy(Qt::StrongFocus);
    showFPS(false);
    showCameraPosition(false);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void MainWindow::instantiateOpenGLWidget()
{
    if(m_GLWidget != nullptr)
    {
        delete m_GLWidget;
    }

    m_RenderWidget = new RenderWidget(this);
    setupOpenglWidget(m_RenderWidget);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
bool MainWindow::processKeyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_O:
//            m_OutputPath->browse();
            return true;

        //    case Qt::Key_C:
        //        renderer->resetCameraPosition();

        case Qt::Key_Space:
            m_Controller->m_btnPause->click();
            return true;

        ////////////////////////////////////////////////////////////////////////////////
        default:
            return OpenGLMainWindow::processKeyPressEvent(event);
    }
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void MainWindow::setupRenderWidgets()
{
    ////////////////////////////////////////////////////////////////////////////////
    // setup layouts
    QVBoxLayout* renderLayout = new QVBoxLayout;
    renderLayout->addWidget(m_GLWidget, 1);

    m_Controller = new Controller(this);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(renderLayout);
    mainLayout->addWidget(m_Controller);

    QWidget* mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void MainWindow::setupStatusBar()
{
//    m_lblStatusReadInfo = new QLabel(this);
//    m_lblStatusReadInfo->setMargin(5);
//    statusBar()->addPermanentWidget(m_lblStatusReadInfo, 1);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void MainWindow::connectWidgets()
{
    ////////////////////////////////////////////////////////////////////////////////
    // textures
    connect(m_Controller->m_cbSkyTexture->getComboBox(),   SIGNAL(currentIndexChanged(int)),   m_RenderWidget, SLOT(setSkyBoxTexture(int)));
    connect(m_Controller->m_cbFloorTexture->getComboBox(), SIGNAL(currentIndexChanged(int)),   m_RenderWidget, SLOT(setFloorTexture(int)));
    connect(m_Controller->m_sldFloorSize->getSlider(),     SIGNAL(valueChanged(int)),          m_RenderWidget, SLOT(setFloorSize(int)));
    connect(m_Controller->m_sldFloorExposure->getSlider(), SIGNAL(valueChanged(int)),          m_RenderWidget, SLOT(setFloorExposure(int)));

    connect(m_Controller->m_msMeshMaterial,                &MaterialSelector::materialChanged, [&](const Material::MaterialData& material)
            {
                m_RenderWidget->setMeshMaterial(material, m_Controller->m_cbMeshMaterialID->currentIndex());
            });

    ////////////////////////////////////////////////////////////////////////////////
    // buttons
    connect(m_Controller->m_btnReloadTextures, SIGNAL(clicked(bool)), m_RenderWidget, SLOT(reloadTextures()));
    connect(m_Controller->m_btnReloadTextures, SIGNAL(clicked(bool)), m_Controller,   SLOT(loadTextures()));
//    connect(m_Controller->m_btnPause,          SIGNAL(clicked(bool)), m_DataReader.get(), SLOT(pause(bool)));

//    connect(m_InputPath,                       SIGNAL(pathChanged(QString)), this,           SLOT(loadDataInfo(QString)));

    ////////////////////////////////////////////////////////////////////////////////
    // lights
    connect(m_Controller->m_LightEditor, &PointLightEditor::lightsChanged, m_RenderWidget,              &RenderWidget::updateLights);
    connect(m_RenderWidget,              &RenderWidget::lightsObjChanged,  m_Controller->m_LightEditor, &PointLightEditor::setLights);
}
