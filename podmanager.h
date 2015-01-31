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

    /** @returns true it the provided repository is a git repository. */
    bool isGitRepository(QString repository);

    /** Install the given pod to the repository. */
    bool installPod(QString repository, Pod pod);

    /** Removes the given pod from the repository. */
    bool removePod(QString repository, QString podName);

    /** Updates the given pod. */
    bool updatePod(QString repository, QString podName);

    /** Updates all pod in a repository. */
    bool updatePods(QString repository);

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

private:
    QNetworkAccessManager _networkAccessManager;
};
