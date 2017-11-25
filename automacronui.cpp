#include "automacronui.h"
#include "ui_automacronui.h"
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

using namespace std;

RecordMacro *record = new RecordMacro();
EditMacro *edit = new EditMacro();
PlaybackMacro *playback = new PlaybackMacro();
QStringListModel *kView = new QStringListModel();
QStringListModel *mView = new QStringListModel();
QShortcut *pgup, *scrolls;
QStringList keyboardAc, mouseAc;
QPushButton *clickMe;
QString fileName;


bool delays = true;
bool positions = true;
bool recording = false;
int edit_mode = 0, cleaner = 0;
QFuture<void> *myThread;

AutoMacronUI::AutoMacronUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AutoMacronUI)
{
    ui->setupUi(this);
    ui->Tabs->setCurrentIndex(0);
    this->setFixedSize(386,332);
    kView->setStringList(keyboardAc);
    ui->KeyboardListRecW->setModel(kView);
    ui->MouseListRecW->setModel(mView);
    record->clear();
}

AutoMacronUI::~AutoMacronUI()
{

    delete ui;
}

void AutoMacronUI::on_RecordNew_clicked()
{
    ui->KeyboardListRecW->setEnabled(true);
    if(positions)
        ui->MouseListRecW->setEnabled(true);
    ui->EndRecordRecW->setEnabled(true);
    ui->RecordNew->setEnabled(false);
    ui->Tabs->setTabEnabled(1, false);
    ui->Tabs->setTabEnabled(2, false);
    ui->RWD->setEnabled(false);
    ui->RMP->setEnabled(false);
    clickMe = ui->EndRecordRecW;
    scrolls = new QShortcut(QKeySequence(Qt::Key_ScrollLock), clickMe, SLOT(click()));
    pgup = new QShortcut(QKeySequence(Qt::Key_PageUp), clickMe, SLOT(click()));
    myThread = new QFuture<void>(QtConcurrent::run(record, &RecordMacro::recordMacro, delays, positions, cleaner));
}

void AutoMacronUI::on_RWD_toggled(bool checked)
{
    if(checked)
        delays = true;
    else
        delays = false;
}


void AutoMacronUI::on_RMP_toggled(bool checked)
{
    if(checked)
        positions = true;
        positions = false;
}

void AutoMacronUI::on_EndRecordRecW_clicked()
{
    myThread->waitForFinished();

    delete myThread;
    delete scrolls;
    delete pgup;
    myThread = NULL;
    scrolls = NULL;
    pgup = NULL;
    ui->SaveRecW->setEnabled(true);
    ui->EndRecordRecW->setEnabled(false);
    ui->DiscardRecW->setEnabled(true);
    vector<string> getKeyboard;

    getKeyboard = record->displayMacro();
    for(int i = 0; i < getKeyboard.size(); i++)
        cout << getKeyboard[i];

    for(int i = 0; i < getKeyboard.size(); i++)
        {
            keyboardAc << QString::fromStdString(getKeyboard[i]);
        }


        kView->setStringList(keyboardAc);
        ui->KeyboardListRecW->update();
        getKeyboard.clear();
        keyboardAc.clear();

        vector<string> temp;
        vector<string> mouseX;
        vector<string> mouseY;

        temp = record->mouseInfo('x');
        for(int i = 0; i < temp.size(); i++)
            mouseX.push_back(temp[i]);

        temp.clear();

        temp = record->mouseInfo('y');
        for(int i = 0; i < temp.size(); i++)
            mouseY.push_back(temp[i]);

        for(int i = 0; i < mouseX.size(); i++)
        {
            if(i%2 == 0)
                mouseAc << "(" + QString::fromStdString(mouseX[i]) + "," + QString::fromStdString(mouseY[i]) + ")";
            else
                mouseAc << "Delay: " + QString::fromStdString(mouseX[i]) + " ms";
        }
    mView->setStringList(mouseAc);
    ui->MouseListRecW->update();
    mouseX.clear();
    mouseY.clear();
    mouseAc.clear();


}


void AutoMacronUI::on_SaveRecW_clicked()
{

    fileName = "";

    fileName = QFileDialog::getSaveFileName(this, tr("Save Your Macro"), tr("/macros/"), tr("Macro Files (*.mcr)"));
    if(fileName != "")
    {
        record->saveMacro(fileName.toStdString());
        ui->SaveRecW->setEnabled(false);
        ui->DiscardRecW->setEnabled(false);
        ui->RecordNew->setEnabled(true);
        ui->MouseListRecW->setEnabled(false);
        ui->KeyboardListRecW->setEnabled(false);
        ui->Tabs->setTabEnabled(1, true);
        ui->Tabs->setTabEnabled(2, true);
        ui->RWD->setEnabled(true);
        ui->RMP->setEnabled(true);
        keyboardAc.clear();
        kView->setStringList(keyboardAc);
        mView->setStringList(mouseAc);
        ui->KeyboardListRecW->update();
        ui->MouseListRecW->update();
        record->clear();
    }

}


void AutoMacronUI::on_DiscardRecW_clicked()
{

    ui->SaveRecW->setEnabled(false);
    ui->DiscardRecW->setEnabled(false);
    ui->RecordNew->setEnabled(true);
    ui->MouseListRecW->setEnabled(false);
    ui->KeyboardListRecW->setEnabled(false);
    ui->Tabs->setTabEnabled(1, true);
    ui->Tabs->setTabEnabled(2, true);
    ui->RWD->setEnabled(true);
    ui->RMP->setEnabled(true);
    kView->setStringList(keyboardAc);
    mView->setStringList(mouseAc);
    ui->KeyboardListRecW->update();
    ui->MouseListRecW->update();
    record->clear();

}

void AutoMacronUI::on_Tabs_currentChanged(int index)
{
    if(index == 0)
    {
        ui->RWD->setEnabled(true);
        ui->RMP->setEnabled(true);
        ui->RecordNew->setEnabled(true);
        ui->EndRecordRecW->setEnabled(false);
        ui->KeyboardListRecW->setEnabled(false);
        ui->MouseListRecW->setEnabled(false);
        ui->SaveRecW->setEnabled(false);
        ui->DiscardRecW->setEnabled(false);

        record->clear();
        edit->clear();
        playback->clear();
    }

    if(index == 1)
    {
        ui->NewMacroEditW->setEnabled(true);
        ui->RWDEdit->setChecked(true);
        ui->RMPEdit->setChecked(true);
        ui->DiscardEditW->setEnabled(false);
        ui->SaveEditW->setEnabled(false);
        ui->KeyboardListEditW->setEnabled(false);
        ui->MouseListEditW->setEnabled(false);
        ui->LoadMacroEditW->setEnabled(true);
        record->clear();
        edit->clear();
        playback->clear();
    }

    if(index == 2)
    {
        ui->PBXtimes->setEnabled(false);
        ui->StartPB->setEnabled(false);
        ui->LoopPB->setEnabled(false);
        ui->NumberOfLoops->setEnabled(false);
        ui->NumberOfLoops->setText("1");
        ui->SpeedInputPB->setEnabled(false);
        ui->SpeedInputPB->setText("1.0");
        ui->KeyboardListPB->setEnabled(false);
        ui->MouseListPB->setEnabled(false);
        record->clear();
        edit->clear();
        playback->clear();
    }

}

void AutoMacronUI::on_NewMacroEditW_clicked()
{
    edit_mode = 1;
    ui->RecordMacroEditW->setEnabled(true);
    ui->MouseListEditW->setEnabled(true);
    ui->KeyboardListEditW->setEnabled(true);
    ui->NewMacroEditW->setEnabled(false);
    ui->LoadMacroEditW->setEnabled(false);
}



void AutoMacronUI::on_RecordMacroEditW_clicked()
{
    if(recording)
    {
        ui->RecordMacroEditW->setText("Record");
        ui->SaveEditW->setEnabled(true);
        ui->DiscardEditW->setEnabled(true);
        ui->RWDEdit->setEnabled(true);
        ui->RMPEdit->setEnabled(true);
        ui->Tabs->setTabEnabled(0, true);
        ui->Tabs->setTabEnabled(2, true);
        delete scrolls;
        delete pgup;
        scrolls = NULL;
        pgup = NULL;
        clickMe = NULL;
        recording = false;
    }
    else
    {
        clickMe = ui->RecordMacroEditW;
        ui->RWDEdit->setEnabled(false);
        ui->RMPEdit->setEnabled(false);
        ui->RecordMacroEditW->setText("Stop");
        ui->Tabs->setTabEnabled(0, false);
        ui->Tabs->setTabEnabled(2, false);
        ui->SaveEditW->setEnabled(false);
        ui->DiscardEditW->setEnabled(false);
        recording = true;
        scrolls = new QShortcut (QKeySequence(Qt::Key_ScrollLock), clickMe, SLOT(click()));
        pgup = new QShortcut (QKeySequence(Qt::Key_PageUp), clickMe, SLOT(click()));
    }
}



void AutoMacronUI::on_SaveEditW_clicked()
{
    if(edit_mode == 1)
    {
        fileName = "";
        fileName = QFileDialog::getSaveFileName(this, tr("Save Your Macro"), tr("/macros/"), tr("Macro Files (*.mcr)")));
        if(fileName != "")
           {
                edit->saveMacro(fileName.toStdString());
                ui->NewMacroEditW->setEnabled(true);
                ui->LoadMacroEditW->setEnabled(true);
                ui->SaveEditW->setEnabled(false);
                ui->DiscardEditW->setEnabled(false);
                edit_mode = 0;
            }
    }
    else
    {
        edit->saveMacro(fileName.toStdString());
        ui->NewMacroEditW->setEnabled(true);
        ui->LoadMacroEditW->setEnabled(true);
        ui->SaveEditW->setEnabled(false);
        ui->DiscardEditW->setEnabled(false);
    }


}

void AutoMacronUI::on_LoadMacroEditW_clicked()
{
    edit_mode = 2;
    fileName = QFileDialog::getOpenFileName(this, tr("Open Your Macro"), tr("/macros/"), tr("Macro Files (*.mcr)")));
    ui->RecordMacroEditW->setEnabled(true);
    ui->KeyboardListEditW->setEnabled(true);
    ui->MouseListEditW->setEnabled(true);
}

void AutoMacronUI::on_DiscardEditW_clicked()
{
    ui->SaveEditW->setEnabled(false);
    ui->RecordMacroEditW->setEnabled(false);
    ui->NewMacroEditW->setEnabled(true);
    ui->LoadMacroEditW->setEnabled(true);
    ui->DiscardEditW->setEnabled(false);
    ui->KeyboardListEditW->setEnabled(false);
    ui->MouseListEditW->setEnabled(false);

}

void AutoMacronUI::on_LoadMacroPB_clicked()
{
    QFile in_file(QFileDialog::getOpenFileName(this, tr("Open Your Macro"), tr("/macros/"), tr("Macro Files (*.mcr)")));
    ui->PBXtimes->setEnabled(true);
    ui->StartPB->setEnabled(true);
    ui->LoopPB->setEnabled(true);
    ui->NumberOfLoops->setEnabled(true);
    ui->NumberOfLoops->setText("1");
    ui->SpeedInputPB->setEnabled(true);
    ui->SpeedInputPB->setText("1.0");
    ui->KeyboardListPB->setEnabled(true);
    ui->MouseListPB->setEnabled(true);
}




void AutoMacronUI::on_StartPB_clicked()
{
    ui->LoadMacroPB->setEnabled(false);
    ui->PBXtimes->setEnabled(false);
    ui->StartPB->setEnabled(false);
    ui->LoopPB->setEnabled(false);
    ui->NumberOfLoops->setEnabled(false);
    ui->SpeedInputPB->setEnabled(false);
    ui->StopPB->setEnabled(true);
}



void AutoMacronUI::on_StopPB_clicked()
{
    ui->LoadMacroPB->setEnabled(false);
    ui->PBXtimes->setEnabled(true);
    ui->StartPB->setEnabled(true);
    ui->LoopPB->setEnabled(true);
    ui->NumberOfLoops->setEnabled(true);
    ui->SpeedInputPB->setEnabled(true);
    ui->StopPB->setEnabled(false);
    ui->LoadMacroPB->setEnabled(true);
}


void AutoMacronUI::on_PBXtimes_clicked()
{
    ui->LoadMacroPB->setEnabled(false);
    int loops;
    loops = (ui->NumberOfLoops->text().toInt());
    ui->PBXtimes->setEnabled(false);
    ui->StartPB->setEnabled(false);
    ui->LoopPB->setEnabled(false);
    ui->NumberOfLoops->setEnabled(false);
    ui->SpeedInputPB->setEnabled(false);
    ui->StopPB->setEnabled(true);
}



void AutoMacronUI::on_LoopPB_clicked()
{
    ui->LoadMacroPB->setEnabled(false);
    ui->PBXtimes->setEnabled(false);
    ui->StartPB->setEnabled(false);
    ui->LoopPB->setEnabled(false);
    ui->NumberOfLoops->setEnabled(false);
    ui->SpeedInputPB->setEnabled(false);
    ui->StopPB->setEnabled(true);
}


