/** 
 * @file mainwindow.cpp
 * @author Arturo Casal
 * @date 2010
 * @version v0.1
 *
 * @brief Panico Live Radio Podcast music player for "Panico en el Núcleo" Podcast
 *
 * @note Copyright (C) Arturo Casal
 *
 * @par Licences
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this->ui->actionAbrir_ContentSet, SIGNAL(triggered()), this, SLOT(selectFile()));
    connect(this->ui->actionSalir, SIGNAL(triggered()), this, SLOT(closeApp()));
    connect(this, SIGNAL(destroyed()), this, SLOT(closeApp()));
    MainWindow::mainwindow = this;
    this->t_sess_status = new RadioPlayer::SessionStatus();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectFile()
{   // Get File
    int i;
    QString filename = QFileDialog::getOpenFileName(this, "Elige archivo descriptor de ContentSet...", ".", "*.xml");
    QFile file(filename);
    if (!file.exists()) {
        QErrorMessage qm(this); qm.showMessage("El fichero no existe.");
        qm.exec();
        return;
    }
    QFileInfo finfo(filename);
    //this->ui->labPlayList->setText(finfo.dir().absolutePath());

    // Parse Content Set XML
    Radio::ContentSet *cs = Radio::ContentSet::parseContentSet(filename);

    if (cs==NULL) {
        QErrorMessage qm(this); qm.showMessage("Documento mal formado.");
        qm.exec();
        return;
    }

    // Parse Session contained in "session" directory
    QDir tmpdir = finfo.dir();
    tmpdir.setPath(tmpdir.absolutePath()+"/sessions");
    if (tmpdir.exists() && tmpdir.entryInfoList(QStringList("*.xml"), QDir::Files,QDir::NoSort).size()>0) {
        QFileInfoList sesFileList = tmpdir.entryInfoList(QStringList("*.xml"), QDir::Files,QDir::NoSort);
        QStandardItemModel *sesList = new QStandardItemModel();
        for(i=0;i<sesFileList.size();i++) {
            sesList->appendRow(Session::parseSessionFromPath(sesFileList.at(i).absoluteFilePath(), cs));
        }
        this->ui->lstSessionList->setModel(sesList);
    } else {
        QErrorMessage qm(this); qm.showMessage("No hay sesiones disponibles para el ContentSet proporcionado.");
        qm.exec();
    }

    connect(this->ui->lstSessionList, SIGNAL(activated (QModelIndex)), this, SLOT(sessionListSelect(QModelIndex)));

    this->ui->labContentSetPath->setText("Abierto ContentSet \""+cs->getName()+"\". ");

    // Update UI
    /*this->ui->labContentSetPath->setText("Abierto \""+cs->getName()+"\": "+filename);

    QStandardItemModel *list = new QStandardItemModel();

    QVector<Radio::Section*> sects = cs->getSections();
    for(i=0;i<sects.size();i++) {
        list->appendRow(sects.at(i));
        QVector<Radio::Track*> tmp = sects.at(i)->getTrackList();
        for(j=0;j<tmp.size();j++) list->appendRow(tmp.at(j));
        tmp = sects.at(i)->getStepList();
        for(j=0;j<tmp.size();j++) list->appendRow(tmp.at(j));
    }



    this->ui->lstPlayList->setModel(list);
    connect(this->ui->lstPlayList, SIGNAL(activated (QModelIndex)), this, SLOT(listaSelect(QModelIndex)));*/
}

void MainWindow::sessionListSelect(QModelIndex index)
{
    int i,j;
    QStandardItemModel *mod = (QStandardItemModel *) index.model();

    QStandardItem *it = mod->item(index.row());
    Radio::Session *ss;
    ss = dynamic_cast<Radio::Session*>(it);
    if (ss==NULL) return;
    this->t_sess_status->setSession(ss);

    // Update right list
    QStandardItemModel *sesList = new QStandardItemModel();
    // Step 1 Clear
    for(i=0;i<ss->getSections().size();i++){
        ss->getSections().at(i)->clear();
        QVector<Radio::Track*> tmp = ss->getSections().at(i)->getTrackList();

        for(j=0;j<tmp.size();j++) {
            tmp.at(j)->clear();
        }
        tmp = ss->getSections().at(i)->getStepList();
        for(j=0;j<tmp.size();j++) {
            tmp.at(j)->clear();
        }
    }
    // Step 2 Add to UI-List
    for(i=0;i<ss->getSections().size();i++){
        UIListItem *uii = new UIListItem(ss->getSections().at(i));
        sesList->appendRow(uii);
        QVector<Radio::Track*> tmp = ss->getSections().at(i)->getTrackList();

        for(j=0;j<tmp.size();j++) {
            uii = new UIListItem(tmp.at(j));
            sesList->appendRow(uii);
        }
        tmp = ss->getSections().at(i)->getStepList();
        for(j=0;j<tmp.size();j++) {
            uii = new UIListItem(tmp.at(j));
            sesList->appendRow(uii);
        }
    }
    this->ui->lstPlayList->setModel(sesList);

    this->ui->labContentSetPath->setText("Abierta sesion \""+ss->getName()+"\" del ContentSet \""+ss->getContentSetName()+"\".");
    disconnect(this->ui->butPlay, SIGNAL(clicked()), this->t_sess_status, SLOT(start()));
    connect(this->ui->butPlay, SIGNAL(clicked()), this->t_sess_status, SLOT(start()));

    disconnect(this->ui->butNextSection, SIGNAL(clicked()), this->t_sess_status, SLOT(nextSectionByUser()));
    connect(this->ui->butNextSection, SIGNAL(clicked()), this->t_sess_status, SLOT(nextSectionByUser()));

    disconnect(this->ui->butNextStep, SIGNAL(clicked()), this->t_sess_status, SLOT(nextStep()));
    connect(this->ui->butNextStep, SIGNAL(clicked()), this->t_sess_status, SLOT(nextStep()));

}

void MainWindow::listaSelect(QModelIndex index) {
    int i = index.row();
    QStandardItemModel *mod = (QStandardItemModel *) index.model();
    //Radio::Track *tr = (Radio::Track *)mod->item(i);
    QStandardItem *it = mod->item(i);
    Radio::Track *tr;
    tr = dynamic_cast<Radio::Track*>(it);
    if (tr==NULL) return;
    tr->setPlayingState(true);
    this->ui->labPlayList->setText("Pulsado: "+QString::number(i)+"FIN"+tr->toString());
}

void MainWindow::closeApp()
{
    this->t_sess_status->stop();
    this->close();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    this->closeApp();
}

void MainWindow::setTrackSeekSliderMediaObject(Phonon::MediaObject *mo)
{
    this->ui->slMusicProgress->setMediaObject(mo);
}

void MainWindow::setStepSeekSliderMediaObject(Phonon::MediaObject *mo)
{
    this->ui->slStepProgress->setMediaObject(mo);
}

MainWindow* MainWindow::mainwindow = NULL;
Player* MainWindow::player = NULL;
