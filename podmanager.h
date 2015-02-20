///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of qt-pods.                                          //
//    Copyright (C) 2015 Jacob Dawid, jacob@omg-it.works                     //
//                                                                           //
//    qt-pods is free software: you can redistribute it and/or modify        //
//    it under the terms of the GNU General Public License as published by   //
//    the Free Software Foundation, either version 3 of the License, or      //
//    (at your option) any later version.                                    //
//                                                                           //
//    qt-pods is distributed in the hope that it will be useful,             //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                           //
//                                                                           //
//    You should have received a copy of the GNU General Public License      //
//    along with qt-pods. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#pragma once

// Own includes
#include "pod.h"

// Qt includes
#include <QString>
#include <QObject>
#include <QNetworkAccessManager>

/**
 * Central class for performing pod operations.
 * Please be aware that no matter what these methods do, they are
 * all blocking.
 */
class PodManager : public QObject {
    Q_OBJECT
public:
    PodManager(QObject *parent = 0);

public slots:
    /** @returns true it the provided repository is a git repository. */
    bool isGitRepository(QString repository);

    /** Install the given pod to the repository. */
    bool installPod(QString repository, Pod pod);
    bool installPods(QString repository, QList<Pod> pods);

    /** Removes the given pod from the repository. */
    bool removePod(QString repository, QString podName);
    bool removePods(QString repository, QStringList podNames);

    /** Updates the given pod. */
    bool updatePod(QString repository, QString podName);
    bool updatePods(QString repository, QStringList podNames);

    /** Updates all pods in a repository. */
    bool updateAllPods(QString repository);

    /** @returns a list of all installed pods in a repository. */
    QList<Pod> installedPods(QString repository);

    /** @returns a list of all available pods from the given sources. */
    QList<Pod> availablePods(QStringList sources);

    /**
     * Regenerates the pods.pri for the given repository.
     * @param repository
     */
    void generatePodsPri(QString repository);

    /**
     * Regenerates the pods-subdirs.pri for the given repository.
     * @param repository
     */
    void generatePodsSubdirsPri(QString repository);

    /**
     * Regenerates the subdirs *.pro file for the given repository,
     * if it doesn't exit yet. The file is named exactly as the repositories
     * name in order to stick to the naming convention, that each directory
     * should contain a single project file with the same name.
     * @param repository
     */
    void generateSubdirsPro(QString repository);

    /**
     * Checks whether an installed pods is a valid pod, ie.
     * - pod name is all lowercase
     * - pod exists
     * - pod contains pro and pri
     * - pod contains LICENSE and README.md
     * @param repository
     * @param podName
     * @return
     */
    bool checkPod(QString repository, QString podName);

signals:
    void isGitRepositoryFinished(QString repository, bool isGitRepository);
    void installPodFinished(QString repository, Pod pod, bool success);
    void installPodsFinished(QString repository, QList<Pod> pods, bool success);
    void removePodFinished(QString repository, QString podName, bool success);
    void removePodsFinished(QString repository, QStringList podNames, bool success);
    void updatePodFinished(QString repository, QString podName, bool success);
    void updatePodsFinished(QString repository, QStringList podNames, bool success);
    void updateAllPodsFinished(QString repository, bool success);
    void installedPodsFinished(QString repository, QList<Pod> installedPods);
    void availablePodsFinished(QStringList sources, QList<Pod> availablePods);
    void generatePodsPriFinished(QString repository);
    void generatePodsSubdirsPriFinished(QString repository);
    void generateSubdirsProFinished(QString repository);
    void checkPodFinished(QString repository, QString podName, bool isValidPod);

private:
    void purgePodInfo(QString repository, QString podName);
    void writePodInfo(QString repository, Pod pod);
    void readPodInfo(QString repository, Pod& pod);

    void stageFile(QString repository, QString fileName);

    QNetworkAccessManager *_networkAccessManager;
};
