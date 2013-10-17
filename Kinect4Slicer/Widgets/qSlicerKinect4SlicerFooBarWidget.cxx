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

// FooBar Widgets includes
#include "qSlicerKinect4SlicerFooBarWidget.h"
#include "ui_qSlicerKinect4SlicerFooBarWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_Kinect4Slicer
class qSlicerKinect4SlicerFooBarWidgetPrivate
  : public Ui_qSlicerKinect4SlicerFooBarWidget
{
  Q_DECLARE_PUBLIC(qSlicerKinect4SlicerFooBarWidget);
protected:
  qSlicerKinect4SlicerFooBarWidget* const q_ptr;

public:
  qSlicerKinect4SlicerFooBarWidgetPrivate(
    qSlicerKinect4SlicerFooBarWidget& object);
  virtual void setupUi(qSlicerKinect4SlicerFooBarWidget*);
};

// --------------------------------------------------------------------------
qSlicerKinect4SlicerFooBarWidgetPrivate
::qSlicerKinect4SlicerFooBarWidgetPrivate(
  qSlicerKinect4SlicerFooBarWidget& object)
  : q_ptr(&object)
{
}

// --------------------------------------------------------------------------
void qSlicerKinect4SlicerFooBarWidgetPrivate
::setupUi(qSlicerKinect4SlicerFooBarWidget* widget)
{
  this->Ui_qSlicerKinect4SlicerFooBarWidget::setupUi(widget);
}

//-----------------------------------------------------------------------------
// qSlicerKinect4SlicerFooBarWidget methods

//-----------------------------------------------------------------------------
qSlicerKinect4SlicerFooBarWidget
::qSlicerKinect4SlicerFooBarWidget(QWidget* parentWidget)
  : Superclass( parentWidget )
  , d_ptr( new qSlicerKinect4SlicerFooBarWidgetPrivate(*this) )
{
  Q_D(qSlicerKinect4SlicerFooBarWidget);
  d->setupUi(this);
}

//-----------------------------------------------------------------------------
qSlicerKinect4SlicerFooBarWidget
::~qSlicerKinect4SlicerFooBarWidget()
{
}
