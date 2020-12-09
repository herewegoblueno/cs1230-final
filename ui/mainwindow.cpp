#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GL/glew.h"
#include "support/Settings.h"
#include <qgl.h>
#include <QGLFormat>
#include "support/scenegraph/SupportCanvas3D.h"
#include <QFileDialog>
#include <QMessageBox>
#include "support/camera/CamtransCamera.h"
#include "support/lib/CS123XmlSceneParser.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    srcWindow(new ShaderCodeDisplayer(this))

{
    SEManager.init(this);
    ui->setupUi(this);

    srcWindow = new ShaderCodeDisplayer(this);
    srcWindow->setWindowTitle("Shader Source");

    settings.loadSettingsOrDefaults();
    //You can make changes to the scene now

    //Adding in the 3D canvas...
    QGLFormat qglFormat;
    qglFormat.setVersion(4, 3);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    qglFormat.setSampleBuffers(true);

    m_canvas3D = new SupportCanvas3D(qglFormat, this);
    ui->CanvasParent->addWidget(m_canvas3D, 0, 0);

    //Filling the UI elements with the current values from the settings global variable
    //(which I'm assuming is set up before this; fingers crossed that that's true)
    ui->useLightingForShaders->setCheckState((settings.useLighting && settings.usePointLights) ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    ui->mainTabWidget->setCurrentIndex(settings.currentTab);
    ui->useOrbitingCamera->setCheckState(settings.useOrbitCamera ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Called when the window is closed
void MainWindow::closeEvent(QCloseEvent *event) {
    settings.saveSettings();
    QMainWindow::closeEvent(event);
}


void MainWindow::signalSettingsChanged() {
    //The canvas contains scenes, it'll call settingsChanged in those scenes so don't worry about that
    m_canvas3D->settingsChanged();
}


//If you want users to be able to choose the file,
void MainWindow::fileOpen(QString file) {
    // This opens the 3D tab to initialize OGL so parsing
    // the scene doesn't crash. If you can find a better solution
    // feel free to change this.
    //^That comment is form support code...
    if (!file.isNull()) {
        if (file.endsWith(".xml")) {
            CS123XmlSceneParser parser(file.toLatin1().data());
            if (parser.parse()) {
                // Set up the camera
                CS123SceneCameraData camera;
                if (parser.getCameraData(camera)) {
                    camera.pos[3] = 1;
                    camera.look[3] = 0;
                    camera.up[3] = 0;

                    CameraConfig *cam = m_canvas3D->getCurrentSceneCamtasConfig();
                    cam->look = camera.look;
                    cam->pos = camera.pos;
                    cam->up = camera.up;
                    cam->angle = camera.heightAngle;
                }

                  m_canvas3D->loadSceneFromParser(parser);


            } else {
                QMessageBox::critical(this, "Error", "Could not load scene \"" + file + "\"");
            }
        }
        else {
//            if (!ui->canvas2D->loadImage(file)) {
//                QMessageBox::critical(this, "Error", "Could not load image \"" + file + "\"");
//            } else {
//            }
             QMessageBox::critical(this, "Error", "We don't support non-xml stuff yettt");
        }
    }
}

ShaderEvolutionTestingScene* MainWindow::getShaderScene(){
    return m_canvas3D->getShaderScene();
}

//The following funcitons are autogenerated to link UI elements to the C++ backend
//To make one, go to the designer view of our UI, right click a UI element and click
//"Go to slots"

void MainWindow::on_useLightingForShaders_stateChanged(int state)
{
    settings.useLighting = state == Qt::CheckState::Checked;
    settings.usePointLights = state == Qt::CheckState::Checked;
    signalSettingsChanged();
}

void MainWindow::on_mainTabWidget_currentChanged(int index)
{
    settings.currentTab = index;
    signalSettingsChanged();
}

void MainWindow::on_renderLTreesbutton_clicked()
{
    fileOpen(QFileDialog::getOpenFileName(this, QString(), "/course/cs123/data/"));
}

void MainWindow::on_useOrbitingCamera_stateChanged(int state)
{
    settings.useOrbitCamera = state == Qt::CheckState::Checked;
    signalSettingsChanged();
}

void MainWindow::on_showShaderSourceButton_clicked()
{
    srcWindow->reset();
    srcWindow->show();
}

void MainWindow::on_initializeShaderSceneButton_clicked()
{
    SEManager.initializeShaderScene();
}

void MainWindow::on_shader1Box_stateChanged(int arg1)
{
    SEManager.shaderSelections[0] = arg1 == Qt::CheckState::Checked;
}

void MainWindow::on_shader2Box_stateChanged(int arg1)
{
    SEManager.shaderSelections[1] = arg1 == Qt::CheckState::Checked;
}

void MainWindow::on_shader3Box_stateChanged(int arg1)
{
    SEManager.shaderSelections[2] = arg1 == Qt::CheckState::Checked;
}

void MainWindow::on_shader4Box_stateChanged(int arg1)
{
    SEManager.shaderSelections[3] = arg1 == Qt::CheckState::Checked;
}

void MainWindow::on_shader5Box_stateChanged(int arg1)
{
    SEManager.shaderSelections[4] = arg1 == Qt::CheckState::Checked;
}

void MainWindow::on_shader6Box_stateChanged(int arg1)
{
    SEManager.shaderSelections[5] = arg1 == Qt::CheckState::Checked;
}

void MainWindow::on_SelectAll_clicked()
{
    ui->shader1Box->setCheckState(Qt::CheckState::Checked);
    ui->shader1Box->repaint();
    ui->shader2Box->setCheckState(Qt::CheckState::Checked);
    ui->shader2Box->repaint();
    ui->shader3Box->setCheckState(Qt::CheckState::Checked);
    ui->shader3Box->repaint();
    ui->shader4Box->setCheckState(Qt::CheckState::Checked);
    ui->shader4Box->repaint();
    ui->shader5Box->setCheckState(Qt::CheckState::Checked);
    ui->shader5Box->repaint();
    ui->shader6Box->setCheckState(Qt::CheckState::Checked);
    ui->shader6Box->repaint();
}

void MainWindow::on_SelectNone_clicked()
{
    ui->shader1Box->setCheckState(Qt::CheckState::Unchecked);
    ui->shader1Box->repaint();
    ui->shader2Box->setCheckState(Qt::CheckState::Unchecked);
    ui->shader2Box->repaint();
    ui->shader3Box->setCheckState(Qt::CheckState::Unchecked);
    ui->shader3Box->repaint();
    ui->shader4Box->setCheckState(Qt::CheckState::Unchecked);
    ui->shader4Box->repaint();
    ui->shader5Box->setCheckState(Qt::CheckState::Unchecked);
    ui->shader5Box->repaint();
    ui->shader6Box->setCheckState(Qt::CheckState::Unchecked);
    ui->shader6Box->repaint();
}

void MainWindow::on_RefreshButton_clicked()
{
    SEManager.refreshSelected(m_canvas3D->getShaderScene());
}

void MainWindow::on_MutateSelected_clicked()
{
    SEManager.mutateSelected(m_canvas3D->getShaderScene());
}

void MainWindow::on_replaceWithMutations_clicked()
{
    SEManager.replaceWithMutationsOfDonor(m_canvas3D->getShaderScene());
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    SEManager.donorShaderIndex = index;
}


void MainWindow::on_Parent1Chooser_currentIndexChanged(int index)
{
    SEManager.parent1ShaderIndex = index;
}

void MainWindow::on_Parent2Chooser_currentIndexChanged(int index)
{
    SEManager.parent2ShaderIndex = index;

}

void MainWindow::on_Offspringbutton_clicked()
{
    SEManager.replaceSelectedWithOffspring(m_canvas3D->getShaderScene());
}
