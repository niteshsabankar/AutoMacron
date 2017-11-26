#ifndef AUTOMACRONUI_H
#define AUTOMACRONUI_H

#include <QMainWindow>
#include <windows.h>
#include "Macro.h"
#include "EditMacro.h"
#include "PlaybackMacro.h"
#include "RecordMacro.h"
#include <string>
#include <cstdio>
#include <iostream>
#include <qfiledialog.h>
#include <QShortcut>
#include <QStringListModel>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QListView>
#include <QInputDialog>

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

    void set_lists(QListView*, QListView* , vector<string>, vector<string>, vector<string>);

    void on_LoopPB_clicked();

    void on_KeyboardListEditW_pressed(const QModelIndex &index);

    void on_KeyboardListEditW_customContextMenuRequested(const QPoint &pos);

    void on_RWDEdit_toggled(bool checked);

    void on_RMPEdit_toggled(bool checked);

    void ibef_triggered(bool);

    void iaft_triggered(bool);

    void cdel_triggered(bool);

private:
    Ui::AutoMacronUI *ui;
};

#endif // AUTOMACRONUI_H
