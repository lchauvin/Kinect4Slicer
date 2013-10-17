/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

#ifndef __qSlicerKinect4SlicerFooBarWidget_h
#define __qSlicerKinect4SlicerFooBarWidget_h

// Qt includes
#include <QWidget>

// FooBar Widgets includes
#include "qSlicerKinect4SlicerModuleWidgetsExport.h"

class qSlicerKinect4SlicerFooBarWidgetPrivate;

/// \ingroup Slicer_QtModules_Kinect4Slicer
class Q_SLICER_MODULE_KINECT4SLICER_WIDGETS_EXPORT qSlicerKinect4SlicerFooBarWidget
  : public QWidget
{
  Q_OBJECT
public:
  typedef QWidget Superclass;
  qSlicerKinect4SlicerFooBarWidget(QWidget *parent=0);
  virtual ~qSlicerKinect4SlicerFooBarWidget();

protected slots:

protected:
  QScopedPointer<qSlicerKinect4SlicerFooBarWidgetPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerKinect4SlicerFooBarWidget);
  Q_DISABLE_COPY(qSlicerKinect4SlicerFooBarWidget);
};

#endif
