#ifndef AUTOMACRONUI_H
#define AUTOMACRONUI_H

#include <QMainWindow>
#include <windows.h>

namespace Ui {
class AutoMacronUI;
}

class AutoMacronUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit AutoMacronUI(QWidget *parent = 0);
    ~AutoMacronUI();

private slots:
    void on_RecordNew_clicked();

    void on_RWD_toggled(bool checked);

    void on_RMP_toggled(bool checked);

    void on_EndRecordRecW_clicked();

    void on_SaveRecW_clicked();

    void on_DiscardRecW_clicked();

    void on_Tabs_currentChanged(int index);

    void on_NewMacroEditW_clicked();

    void on_RecordMacroEditW_clicked();

    void on_SaveEditW_clicked();

    void on_LoadMacroEditW_clicked();

    void on_LoadMacroPB_clicked();

    void on_DiscardEditW_clicked();

    void on_StartPB_clicked();

    void on_StopPB_clicked();

    void on_PBXtimes_clicked();

    void on_LoopPB_clicked();

private:
    Ui::AutoMacronUI *ui;
};

#endif // AUTOMACRONUI_H
