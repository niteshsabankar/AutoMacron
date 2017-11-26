#include "automacronui.h"
#include "ui_automacronui.h"


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
int edit_mode = 0, cleaner = 0, edit_index;
QFuture<void> *myThread;

AutoMacronUI::AutoMacronUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AutoMacronUI)
{
    ui->setupUi(this);
    ui->Tabs->setCurrentIndex(0);
    this->setFixedSize(386,332);
    kView->setStringList(keyboardAc);
    mView->setStringList(mouseAc);
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
    delays = checked;
}


void AutoMacronUI::on_RMP_toggled(bool checked)
{
    positions = checked;
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
    vector<string> keys, moux, mouy;
    keys = record->displayMacro();
    moux = record->mouseInfo('x');
    mouy = record->mouseInfo('y');
    set_lists(ui->KeyboardListRecW,
              ui->MouseListRecW,
              keys, moux, mouy);
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
        positions = true;
        delays = true;
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
        positions = true;
        delays = true;
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

        vector<string> keys, moux, mouy;
        keys = edit->displayMacro();
        moux = edit->mouseInfo('x');
        mouy = edit->mouseInfo('y');
        set_lists(ui->KeyboardListEditW,
                  ui->MouseListEditW,
                  keys, moux, mouy);
    }
    else
    {
        clickMe = ui->RecordMacroEditW;
        ui->RWDEdit->setEnabled(false);
        ui->RMPEdit->setEnabled(false);
        ui->RecordMacroEditW->setText("Stop=PgUp/Scr lock");
        ui->Tabs->setTabEnabled(0, false);
        ui->Tabs->setTabEnabled(2, false);
        ui->SaveEditW->setEnabled(false);
        ui->DiscardEditW->setEnabled(false);
        recording = true;
        scrolls = new QShortcut (QKeySequence(Qt::Key_ScrollLock), clickMe, SLOT(click()));
        pgup = new QShortcut (QKeySequence(Qt::Key_PageUp), clickMe, SLOT(click()));
        if(edit->actionSize() == 0)
                myThread = new QFuture<void>(QtConcurrent::run(edit, &EditMacro::recordMacro, delays, positions, edit_index));
        else if(edit_index == 0 && edit->actionSize() != 0)
        {
            edit_index = edit->actionSize() - 1;
            myThread = new QFuture<void>(QtConcurrent::run(edit, &EditMacro::recordMacro, delays, positions, edit_index));
        }
    }
}



void AutoMacronUI::on_SaveEditW_clicked()
{
    if(edit_mode == 1)
    {
        fileName = "";
        fileName = QFileDialog::getSaveFileName(this, tr("Save Your Macro"), tr("/macros/"), tr("Macro Files (*.mcr)"));
        if(fileName != "")
           {
                edit->saveMacro(fileName.toStdString());
                ui->NewMacroEditW->setEnabled(true);
                ui->LoadMacroEditW->setEnabled(true);
                ui->SaveEditW->setEnabled(false);
                ui->DiscardEditW->setEnabled(false);
                keyboardAc.clear();
                mouseAc.clear();
                kView->setStringList(keyboardAc);
                mView->setStringList(mouseAc);
                ui->KeyboardListEditW->update();
                ui->MouseListEditW->update();
            }
    }
    else
    {
        edit->saveMacro(fileName.toStdString());
        ui->NewMacroEditW->setEnabled(true);
        ui->LoadMacroEditW->setEnabled(true);
        ui->SaveEditW->setEnabled(false);
        ui->DiscardEditW->setEnabled(false);
        kView->setStringList(keyboardAc);
        mView->setStringList(mouseAc);
        ui->KeyboardListEditW->update();
        ui->MouseListEditW->update();
    }


}

void AutoMacronUI::on_LoadMacroEditW_clicked()
{
    fileName = "";
    fileName = QFileDialog::getOpenFileName(this, tr("Open Your Macro"), tr("/macros/"), tr("Macro Files (*.mcr)"));
    if(fileName != "")
    {
        edit_mode = 2;
        edit->loadMacro(fileName.toStdString());
        ui->RecordMacroEditW->setEnabled(true);
        ui->KeyboardListEditW->setEnabled(true);
        ui->MouseListEditW->setEnabled(true);
        vector<string> keys, moux, mouy;
        keys = edit->displayMacro();
        moux = edit->mouseInfo('x');
        mouy = edit->mouseInfo('y');
        set_lists(ui->KeyboardListEditW,
                  ui->MouseListEditW,
                  keys, moux, mouy);

    }
}

void AutoMacronUI::on_DiscardEditW_clicked()
{
    if(edit_mode == 1)
    {
        ui->SaveEditW->setEnabled(false);
        ui->RecordMacroEditW->setEnabled(false);
        ui->NewMacroEditW->setEnabled(true);
        ui->LoadMacroEditW->setEnabled(true);
        ui->DiscardEditW->setEnabled(false);
        ui->KeyboardListEditW->setEnabled(false);
        ui->MouseListEditW->setEnabled(false);
        kView->setStringList(keyboardAc);
        mView->setStringList(mouseAc);
        ui->KeyboardListEditW->update();
        ui->MouseListEditW->update();
        edit->clear();
    }
    if(edit_mode == 2)
       {
            ui->SaveEditW->setEnabled(false);
            ui->RecordMacroEditW->setEnabled(false);
            ui->NewMacroEditW->setEnabled(true);
            ui->LoadMacroEditW->setEnabled(true);
            ui->DiscardEditW->setEnabled(false);
            kView->setStringList(keyboardAc);
            mView->setStringList(mouseAc);
            ui->KeyboardListEditW->update();
            ui->MouseListEditW->update();
       }
}

void AutoMacronUI::on_LoadMacroPB_clicked()
{
    fileName = "";
    fileName = QFileDialog::getOpenFileName(this, tr("Open Your Macro"), tr("/macros/"), tr("Macro Files (*.mcr)"));
    if(fileName != "")
    {
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

void AutoMacronUI::set_lists(QListView* key, QListView* mouse, vector<string> keybo, vector<string>mouX, vector<string> mouY)
{
    for(int i = 0; i < keybo.size(); i++)
        {
            keyboardAc << QString::fromStdString(keybo[i]);
        }

        key->setModel(kView);
        kView->setStringList(keyboardAc);
        key->update();
        keyboardAc.clear();


        for(int i = 0; i < mouX.size(); i++)
        {
            if(i%2 == 0)
                mouseAc << "(" + QString::fromStdString(mouX[i]) + "," + QString::fromStdString(mouY[i]) + ")";
            else
                mouseAc << "Delay: " + QString::fromStdString(mouX[i]) + " ms";
        }
        mouse->setModel(mView);
        mView->setStringList(mouseAc);
        mouse->update();
        mouseAc.clear();
}

void AutoMacronUI::on_KeyboardListEditW_pressed(const QModelIndex &index)
{
    edit_index = index.row();
}


void AutoMacronUI::on_KeyboardListEditW_customContextMenuRequested(const QPoint &pos)
{
    QAction *ibef, *iaft, *cdel;
    ibef = new QAction("Insert Action Before", this);
    iaft = new QAction("Insert Action After", this);
    cdel = new QAction("Change Delay", this);
    ibef->setObjectName("ibef");
    iaft->setObjectName("iaft");
    cdel->setObjectName("cdel");
    QMenu *menu=new QMenu(this);

    menu->addAction(ibef);
    menu->addAction(iaft);
    menu->addAction(cdel);
    menu->popup(mapToGlobal(pos));

    connect(ibef, SIGNAL(triggered(bool)), this, SLOT(ibef_triggered(bool)));
    connect(iaft, SIGNAL(triggered(bool)), this, SLOT(iaft_triggered(bool)));
    connect(cdel, SIGNAL(triggered(bool)), this, SLOT(cdel_triggered(bool)));
}

void AutoMacronUI::on_RWDEdit_toggled(bool checked)
{
    delays = checked;
}

void AutoMacronUI::ibef_triggered(bool checked)
{
    int temp = 0;
    if(edit_index % 2 != 0)
        temp = edit_index - 1;
    else
        temp = edit_index;


    myThread = new QFuture<void>(QtConcurrent::run(edit, &EditMacro::recordSingle, delays, temp));
    myThread->waitForFinished();
    delete myThread;
    myThread = NULL;
    vector<string> keys, moux, mouy;
    keys = edit->displayMacro();
    moux = edit->mouseInfo('x');
    mouy = edit->mouseInfo('y');
    set_lists(ui->KeyboardListEditW,
              ui->MouseListEditW,
              keys, moux, mouy);
}

void AutoMacronUI::iaft_triggered(bool checked)
{
    int temp = 0;
    if(edit_index % 2 == 0)
        temp = edit_index + 2;
    else
        temp = edit_index + 1;


    myThread = new QFuture<void>(QtConcurrent::run(edit, &EditMacro::recordSingle, delays, temp));
    myThread->waitForFinished();
    delete myThread;
    myThread = NULL;
    vector<string> keys, moux, mouy;
    keys = edit->displayMacro();
    moux = edit->mouseInfo('x');
    mouy = edit->mouseInfo('y');
    set_lists(ui->KeyboardListEditW,
              ui->MouseListEditW,
              keys, moux, mouy);
}

void AutoMacronUI::cdel_triggered(bool checked)
{
    int temp, delay;
     if(edit_index%2 != 0)
         temp = edit_index - 1;
     else
         temp = edit_index;
     delay = QInputDialog::getInt(this, tr("Enter Delay"),tr("delay"), QLineEdit::Normal);
     cout << temp << endl;
     if(delay != 0)
     {

         edit->changeDelay(temp, delay);

         vector<string> keys, moux, mouy;
         keys = edit->displayMacro();
         moux = edit->mouseInfo('x');
         mouy = edit->mouseInfo('y');
         set_lists(ui->KeyboardListEditW,
               ui->MouseListEditW,
               keys, moux, mouy);
     }

}

void AutoMacronUI::on_RMPEdit_toggled(bool checked)
{
    positions = checked;
}
