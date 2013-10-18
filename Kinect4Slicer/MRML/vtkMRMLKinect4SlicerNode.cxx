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
  this->ClearTrackingNodes();
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

  HRESULT status = this->KinectSensor ? this->KinectSensor->NuiStatus() : E_NUI_NOTCONNECTED;
  if (status == E_NUI_NOTCONNECTED)
    {
    this->KinectSensor->Release();
    return 0;
    }

  // Initialize sensor
  HRESULT init;
  init = this->KinectSensor->NuiInitialize(
    NUI_INITIALIZE_FLAG_USES_SKELETON |
    NUI_INITIALIZE_FLAG_USES_COLOR);
 
  if (FAILED(init))
    {
    this->KinectSensor->Release();
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
void vtkMRMLKinect4SlicerNode::UpdateTrackedNodes()
  {

  this->ClearTrackingNodes();

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


void vtkMRMLKinect4SlicerNode::ClearTrackingNodes()
  {
  for (int i = 0; i < this->BodyJointPositions.size(); ++i)
    {
    vtkMRMLKinectPositionNode* tmpNode = this->BodyJointPositions[i];
    if (tmpNode)
      {
      tmpNode->Delete();
      }
    }
  this->BodyJointPositions.clear();
  }

void vtkMRMLKinect4SlicerNode::TrackHead()
  {
  // Head: 1 Node
  vtkMRMLKinectPositionNode* head
    = vtkMRMLKinectPositionNode::New();
  head->SetSkeletonPositionIndex(NUI_SKELETON_POSITION_HEAD);
  head->Initialize(this->GetScene(),"Head");
  this->BodyJointPositions.push_back(head);
  }

void vtkMRMLKinect4SlicerNode::TrackRightHand()
  {
  // Right hand: 1 Node
  vtkMRMLKinectPositionNode* rightHand
    = vtkMRMLKinectPositionNode::New();
  rightHand->SetSkeletonPositionIndex(NUI_SKELETON_POSITION_HAND_RIGHT);
  rightHand->Initialize(this->GetScene(),"RightHand");
  this->BodyJointPositions.push_back(rightHand);
  }

void vtkMRMLKinect4SlicerNode::TrackLeftHand()
  {
  // Left hand: 1 Node
  vtkMRMLKinectPositionNode* leftHand
    = vtkMRMLKinectPositionNode::New();
  leftHand->SetSkeletonPositionIndex(NUI_SKELETON_POSITION_HAND_LEFT);
  leftHand->Initialize(this->GetScene(),"LeftHand");
  this->BodyJointPositions.push_back(leftHand);
  }

void vtkMRMLKinect4SlicerNode::TrackBothHands()
  {
  // Both hands: 2 Nodes
  this->TrackRightHand();
  this->TrackLeftHand();
  }

void vtkMRMLKinect4SlicerNode::TrackRightArm()
  {
  // Right arm: 3 Nodes
  vtkMRMLKinectPositionNode* rightShoulder
    = vtkMRMLKinectPositionNode::New();
  rightShoulder->SetSkeletonPositionIndex(NUI_SKELETON_POSITION_SHOULDER_RIGHT);
  rightShoulder->Initialize(this->GetScene(),"RightShoulder");
  this->BodyJointPositions.push_back(rightShoulder);
  
  vtkMRMLKinectPositionNode* rightElbow
    = vtkMRMLKinectPositionNode::New();
  rightElbow->SetSkeletonPositionIndex(NUI_SKELETON_POSITION_ELBOW_RIGHT);
  rightElbow->Initialize(this->GetScene(),"RightElbow");
  this->BodyJointPositions.push_back(rightElbow);

  this->TrackRightHand();
  }

void vtkMRMLKinect4SlicerNode::TrackLeftArm()
  {
  // Left arm: 3 Nodes
  vtkMRMLKinectPositionNode* leftShoulder
    = vtkMRMLKinectPositionNode::New();
  leftShoulder->SetSkeletonPositionIndex(NUI_SKELETON_POSITION_SHOULDER_LEFT);
  leftShoulder->Initialize(this->GetScene(),"LeftShoulder");
  this->BodyJointPositions.push_back(leftShoulder);

  vtkMRMLKinectPositionNode* leftElbow
    = vtkMRMLKinectPositionNode::New();
  leftElbow->SetSkeletonPositionIndex(NUI_SKELETON_POSITION_ELBOW_LEFT);
  leftElbow->Initialize(this->GetScene(),"LeftElbow");
  this->BodyJointPositions.push_back(leftElbow);
  
  this->TrackLeftHand();
  }

void vtkMRMLKinect4SlicerNode::TrackBothArms()
  {
  // Both arms: 6 Nodes
  this->TrackRightArm();
  this->TrackLeftArm();
  }

void vtkMRMLKinect4SlicerNode::TrackBody()
  {
  // Body: ? Nodes
  }

//---------------------------------------------------------------------------
void vtkMRMLKinect4SlicerNode::UpdateNodesPosition()
  {
  if (this->BodyJointPositions.size() <= 0)
    {
    return;
    }

  NUI_SKELETON_FRAME newFrame;
  NuiSkeletonGetNextFrame(0, &newFrame);

  const NUI_IMAGE_FRAME* imageFrame;
  WaitForSingleObject(this->NextVideoFrameEvent, INFINITE);
  NuiImageStreamGetNextFrame(this->VideoStreamHandle, 0, &imageFrame);
  
  for (int i = 0; i < this->BodyJointPositions.size(); ++i)
    {
    vtkMRMLKinectPositionNode* updateNode = 
      this->BodyJointPositions[i];
    if (updateNode)
      {
      for (int i = 0; i < 6; ++i)
        {
        if (newFrame.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED)
          {
          NuiTransformSmooth(&newFrame, NULL);
          updateNode->UpdatePosition(&newFrame, i);
          continue;
          }
        }
      }
    }

  NuiImageStreamReleaseFrame(this->VideoStreamHandle, imageFrame);
  }
