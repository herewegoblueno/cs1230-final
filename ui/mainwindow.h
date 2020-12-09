#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include "shaderevolution/ShaderEvolutionManager.h"
#include "shadercodedisplayer.h"


class SupportCanvas3D;
class ShaderEvolutionManager;
class ShaderCodeDisplayer;
class ShaderEvolutionTestingScene;

namespace Ui {
    class MainWindow;
}

/**
 * @class MainWindow
 *
 * The main graphical user interface class (GUI class) for our application.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void fileOpen(QString file);
    ShaderEvolutionTestingScene* getShaderScene();

protected:

    // Overridden from QWidget. Handles the window close event.
    virtual void closeEvent(QCloseEvent *e);
    void signalSettingsChanged(); //We could have done this with signals and slots; not a priority now

private slots:

    void on_useLightingForShaders_stateChanged(int arg1);

    void on_mainTabWidget_currentChanged(int index);

    void on_renderLTreesbutton_clicked();

    void on_useOrbitingCamera_stateChanged(int arg1);

    void on_showShaderSourceButton_clicked();

    void on_initializeShaderSceneButton_clicked();

    void on_shader1Box_stateChanged(int arg1);

    void on_shader2Box_stateChanged(int arg1);

    void on_shader3Box_stateChanged(int arg1);

    void on_shader4Box_stateChanged(int arg1);

    void on_shader5Box_stateChanged(int arg1);

    void on_shader6Box_stateChanged(int arg1);

    void on_SelectAll_clicked();

    void on_SelectNone_clicked();

    void on_RefreshButton_clicked();

    void on_MutateSelected_clicked();

    void on_replaceWithMutations_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_Offspringbutton_clicked();

    void on_Parent1Chooser_currentIndexChanged(int index);

    void on_Parent2Chooser_currentIndexChanged(int index);

private:
    // Auto-generated by Qt. DO NOT RENAME!
    Ui::MainWindow *ui;

    SupportCanvas3D *m_canvas3D;
    ShaderCodeDisplayer *srcWindow;

};

#endif // MAINWINDOW_H
