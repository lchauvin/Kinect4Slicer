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
#include <QDebug>
#include <QTimer>

// SlicerQt includes
#include "qSlicerKinect4SlicerModuleWidget.h"
#include "ui_qSlicerKinect4SlicerModuleWidget.h"

#include "vtkMRMLKinect4SlicerNode.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerKinect4SlicerModuleWidgetPrivate: public Ui_qSlicerKinect4SlicerModuleWidget
{
public:
  vtkMRMLKinect4SlicerNode* KinectSensor;
  QTimer* RefreshingTimer;

public:
  qSlicerKinect4SlicerModuleWidgetPrivate();
  ~qSlicerKinect4SlicerModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerKinect4SlicerModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerKinect4SlicerModuleWidgetPrivate::qSlicerKinect4SlicerModuleWidgetPrivate()
{
  this->KinectSensor = NULL;
  this->RefreshingTimer = new QTimer();
}

//-----------------------------------------------------------------------------
qSlicerKinect4SlicerModuleWidgetPrivate::~qSlicerKinect4SlicerModuleWidgetPrivate()
{
   if (this->KinectSensor)
   {
    this->KinectSensor->Delete();
   }
}

//-----------------------------------------------------------------------------
// qSlicerKinect4SlicerModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerKinect4SlicerModuleWidget::qSlicerKinect4SlicerModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerKinect4SlicerModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerKinect4SlicerModuleWidget::~qSlicerKinect4SlicerModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerKinect4SlicerModuleWidget::setup()
{
  Q_D(qSlicerKinect4SlicerModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();

  d->BodyPartSelector->setDisabled(true);
  d->TrackButton->setDisabled(true);

  connect(d->InitializeButton, SIGNAL(clicked()),
	  this, SLOT(onInitializeButtonClicked()));

  connect(d->BodyPartSelector, SIGNAL(currentIndexChanged(int)),
	  this, SLOT(onBodyPartChanged(int)));

  connect(d->TrackButton, SIGNAL(clicked()),
	  this, SLOT(onTrackButtonClicked()));

  connect(d->RefreshingTimer, SIGNAL(timeout()),
    this, SLOT(refreshKinectNodes()));
}

//-----------------------------------------------------------------------------
void qSlicerKinect4SlicerModuleWidget::onInitializeButtonClicked()
{
  Q_D(qSlicerKinect4SlicerModuleWidget);

  if (this->mrmlScene())
    {
    d->KinectSensor = vtkMRMLKinect4SlicerNode::New();
    if (d->KinectSensor)
	    {   
	    int init = d->KinectSensor->Initialize(this->mrmlScene());
	    if (init > 0)
        {
        d->BodyPartSelector->setEnabled(true);
        d->TrackButton->setEnabled(true);
        }
	     }
    }
}

//-----------------------------------------------------------------------------
void qSlicerKinect4SlicerModuleWidget::onBodyPartChanged(int newBodyPart)
{
  Q_D(qSlicerKinect4SlicerModuleWidget);
  
  if (d->KinectSensor)
    {
    d->KinectSensor->SetBodyPartIndex(newBodyPart);
    }
}

//-----------------------------------------------------------------------------
void qSlicerKinect4SlicerModuleWidget::onTrackButtonClicked()
{
  Q_D(qSlicerKinect4SlicerModuleWidget);

  if (d->KinectSensor)
    {
    if (d->RefreshingTimer->isActive())
      {
      d->RefreshingTimer->stop();
      }
    d->KinectSensor->UpdateTrackedNodes();
    d->RefreshingTimer->start(50);
    }
}

//-----------------------------------------------------------------------------
void qSlicerKinect4SlicerModuleWidget::refreshKinectNodes()
  {
  Q_D(qSlicerKinect4SlicerModuleWidget);

  if (d->KinectSensor)
    {
    d->KinectSensor->UpdateNodesPosition();
    }
  }

