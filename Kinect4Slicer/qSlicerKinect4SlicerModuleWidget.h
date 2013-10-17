/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

#ifndef __qSlicerKinect4SlicerModuleWidget_h
#define __qSlicerKinect4SlicerModuleWidget_h

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerKinect4SlicerModuleExport.h"

class qSlicerKinect4SlicerModuleWidgetPrivate;
class vtkMRMLNode;

/// \ingroup Slicer_QtModules_ExtensionTemplate
class Q_SLICER_QTMODULES_KINECT4SLICER_EXPORT qSlicerKinect4SlicerModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerKinect4SlicerModuleWidget(QWidget *parent=0);
  virtual ~qSlicerKinect4SlicerModuleWidget();

public slots:
  void onInitializeButtonClicked();
  void onBodyPartChanged(int newBodyPart);
  void onTrackButtonClicked();

protected:
  QScopedPointer<qSlicerKinect4SlicerModuleWidgetPrivate> d_ptr;
  
  virtual void setup();

private:
  Q_DECLARE_PRIVATE(qSlicerKinect4SlicerModuleWidget);
  Q_DISABLE_COPY(qSlicerKinect4SlicerModuleWidget);
};

#endif
