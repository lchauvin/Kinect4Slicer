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

// Qt includes
#include <QtPlugin>

// Kinect4Slicer Logic includes
#include <vtkSlicerKinect4SlicerLogic.h>

// Kinect4Slicer includes
#include "qSlicerKinect4SlicerModule.h"
#include "qSlicerKinect4SlicerModuleWidget.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerKinect4SlicerModule, qSlicerKinect4SlicerModule);

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerKinect4SlicerModulePrivate
{
public:
  qSlicerKinect4SlicerModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerKinect4SlicerModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerKinect4SlicerModulePrivate
::qSlicerKinect4SlicerModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerKinect4SlicerModule methods

//-----------------------------------------------------------------------------
qSlicerKinect4SlicerModule
::qSlicerKinect4SlicerModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerKinect4SlicerModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerKinect4SlicerModule::~qSlicerKinect4SlicerModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerKinect4SlicerModule::helpText()const
{
  return "This is a loadable module bundled in an extension";
}

//-----------------------------------------------------------------------------
QString qSlicerKinect4SlicerModule::acknowledgementText()const
{
  return "This work was was partially funded by NIH grant 3P41RR013218-12S1";
}

//-----------------------------------------------------------------------------
QStringList qSlicerKinect4SlicerModule::contributors()const
{
  QStringList moduleContributors;
  moduleContributors << QString("Jean-Christophe Fillion-Robin (Kitware)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerKinect4SlicerModule::icon()const
{
  return QIcon(":/Icons/Kinect4Slicer.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerKinect4SlicerModule::categories() const
{
  return QStringList() << "Examples";
}

//-----------------------------------------------------------------------------
QStringList qSlicerKinect4SlicerModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerKinect4SlicerModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation * qSlicerKinect4SlicerModule
::createWidgetRepresentation()
{
  return new qSlicerKinect4SlicerModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerKinect4SlicerModule::createLogic()
{
  return vtkSlicerKinect4SlicerLogic::New();
}
