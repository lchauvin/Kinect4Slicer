#include "vtkMRMLKinect4SlicerNode.h"

#include <vtkObjectFactory.h>

//----------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLKinect4SlicerNode);


//----------------------------------------------------------------------------
vtkMRMLKinect4SlicerNode::vtkMRMLKinect4SlicerNode()
  {
  this->HideFromEditors = false;

  this->KinectSensor = NULL;
  this->AlreadyTracking = false;
  this->BodyPartIndex = 0;

  this->NextVideoFrameEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
  this->NextSkeletonEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
  }

//----------------------------------------------------------------------------
vtkMRMLKinect4SlicerNode::~vtkMRMLKinect4SlicerNode()
  {
  }

//----------------------------------------------------------------------------
void vtkMRMLKinect4SlicerNode::WriteXML(ostream& of, int nIndent)
  {
  Superclass::WriteXML(of, nIndent);
  }


//----------------------------------------------------------------------------
void vtkMRMLKinect4SlicerNode::ReadXMLAttributes(const char** atts)
  {
  Superclass::ReadXMLAttributes(atts);
  }

//----------------------------------------------------------------------------
void vtkMRMLKinect4SlicerNode::Copy(vtkMRMLNode *anode)
  {
  Superclass::Copy(anode);
  }

//-----------------------------------------------------------
void vtkMRMLKinect4SlicerNode::UpdateScene(vtkMRMLScene *scene)
  {
  Superclass::UpdateScene(scene);
  }

//---------------------------------------------------------------------------
void vtkMRMLKinect4SlicerNode::ProcessMRMLEvents ( vtkObject *caller,
  unsigned long event, 
  void *callData )
  {
  Superclass::ProcessMRMLEvents(caller, event, callData);
  }

//---------------------------------------------------------------------------
int vtkMRMLKinect4SlicerNode::Initialize(vtkMRMLScene* scene)
  {
  if (!scene)
    {
    return -1;
    }

  this->SetScene(scene);

  // Detect number of sensors
  int numSensors = 0;
  if (NuiGetSensorCount(&numSensors) < 0 || numSensors < 1)
    {
    return 0;
    }

  if (NuiCreateSensorByIndex(0, &this->KinectSensor) < 0)
    {
    return 0;
    }

  // Initialize sensor
  HRESULT init;
  init = this->KinectSensor->NuiInitialize(
    NUI_INITIALIZE_FLAG_USES_SKELETON |
    NUI_INITIALIZE_FLAG_USES_COLOR);
 
  if (FAILED(init))
    {
    return 0;
    }

  // Open new image stream
  HRESULT openStream;
  openStream = this->KinectSensor->NuiImageStreamOpen(
    NUI_IMAGE_TYPE_COLOR,
    NUI_IMAGE_RESOLUTION_1280x960,
    0,
    2,
    this->NextVideoFrameEvent,
    &this->VideoStreamHandle);
  
  if (FAILED(openStream))
    {
    return 0;
    }

  // Enable Skeleton tracking
  HRESULT enableTracking;
  enableTracking = this->KinectSensor->NuiSkeletonTrackingEnable(this->NextSkeletonEvent, 0);

  if (FAILED(enableTracking))
    {
    return 0;
    }

  return 1;
  }

//---------------------------------------------------------------------------
void vtkMRMLKinect4SlicerNode::BeginTracking()
  {

  if (this->AlreadyTracking)
    {
    this->ClearTracking();
    }

  switch (this->BodyPartIndex)
    {
  case 0:
    this->TrackHead();
    break;
  case 1:
    this->TrackRightHand();
    break;
  case 2:
    this->TrackLeftHand();
    break;
  case 3:
    this->TrackBothHands();
    break;
  case 4:
    this->TrackRightArm();
    break;
  case 5:
    this->TrackLeftArm();
    break;
  case 6:
    this->TrackBothArms();
    break;
  case 7:
    this->TrackBody();
    break;
  default:
    this->TrackBothArms();
    break;
    }
  }


void vtkMRMLKinect4SlicerNode::TrackHead()
  {
  // Head: 1 Node
  }

void vtkMRMLKinect4SlicerNode::TrackRightHand()
  {
  // Right hand: 1 Node
  }

void vtkMRMLKinect4SlicerNode::TrackLeftHand()
  {
  // Left hand: 1 Node
  }

void vtkMRMLKinect4SlicerNode::TrackBothHands()
  {
  // Both hands: 2 Nodes
  }

void vtkMRMLKinect4SlicerNode::TrackRightArm()
  {
  // Right arm: 3 Nodes
  }

void vtkMRMLKinect4SlicerNode::TrackLeftArm()
  {
  // Left arm: 3 Nodes
  }

void vtkMRMLKinect4SlicerNode::TrackBothArms()
  {
  // Both arms: 6 Nodes
  }

void vtkMRMLKinect4SlicerNode::TrackBody()
  {
  // Body: ? Nodes
  }