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

  d->TrackButton->setDisabled(true);

  connect(d->InitializeButton, SIGNAL(clicked()),
	  this, SLOT(onInitializeButtonClicked()));

  connect(d->BodyPartSelector, SIGNAL(currentIndexChanged(int)),
	  this, SLOT(onBodyPartChanged(int)));

  connect(d->TrackButton, SIGNAL(clicked()),
	  this, SLOT(onTrackButtonClicked()));
}

//-----------------------------------------------------------------------------
void qSlicerKinect4SlicerModuleWidget::onInitializeButtonClicked()
{
  Q_D(qSlicerKinect4SlicerModuleWidget);

  if (this->mrmlScene())
    {
    std::cerr << "Mrml scene ok" << std::endl;
    d->KinectSensor = vtkMRMLKinect4SlicerNode::New();
    if (d->KinectSensor)
	    {   
      std::cerr << "Kinect sensor ok" << std::endl;
	    int init = d->KinectSensor->Initialize(this->mrmlScene());
	    if (init > 0)
        {
        std::cerr << "Init succeed" << std::endl;
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
}
