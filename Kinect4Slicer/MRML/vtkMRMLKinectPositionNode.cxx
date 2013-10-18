#include <iostream>
#include <sstream>
#include <string>

#include "vtkMRMLKinectPositionNode.h"

#include "vtkMatrix4x4.h"
#include "vtkSphereSource.h"

#include <vtkObjectFactory.h>

//----------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLKinectPositionNode);


//----------------------------------------------------------------------------
vtkMRMLKinectPositionNode::vtkMRMLKinectPositionNode()
  {
  this->HideFromEditors = true;
  
  this->NodeTransform = NULL;
  this->NodeMatrix = NULL;
  this->NodeModel = NULL;
  this->SkeletonPositionIndex = 0;

  this->HipCenter[0] = 169;
  this->HipCenter[1] = 176;
  this->HipCenter[2] = 155;

  this->Spine[0] = 169;
  this->Spine[1] = 176;
  this->Spine[2] = 155;

  this->ShoulderCenter[0] = 168;
  this->ShoulderCenter[1] = 230;
  this->ShoulderCenter[2] = 29;

  this->Head[0] = 200;
  this->Head[1] = 0;
  this->Head[2] = 0;

  this->ShoulderLeft[0] = 79;
  this->ShoulderLeft[1] = 84;
  this->ShoulderLeft[2] = 33;

  this->ElbowLeft[0] = 84;
  this->ElbowLeft[1] = 33;
  this->ElbowLeft[2] = 42;

  this->WristLeft[0] = 255;
  this->WristLeft[1] = 126;
  this->WristLeft[2] = 0;

  this->HandLeft[0] = 215;
  this->HandLeft[1] = 86;
  this->HandLeft[2] = 0;

  this->ShoulderRight[0] = 33;
  this->ShoulderRight[1] = 79;
  this->ShoulderRight[2] = 84;

  this->ElbowRight[0] = 33;
  this->ElbowRight[1] = 33;
  this->ElbowRight[2] = 84;

  this->WristRight[0] = 77;
  this->WristRight[1] = 109;
  this->WristRight[2] = 243;

  this->HandRight[0] = 37;
  this->HandRight[1] = 69;
  this->HandRight[2] = 243;

  this->HipLeft[0] = 77;
  this->HipLeft[1] = 109;
  this->HipLeft[2] = 243;

  this->KneeLeft[0] = 69;
  this->KneeLeft[1] = 33;
  this->KneeLeft[2] = 84;

  this->AnkleLeft[0] = 229;
  this->AnkleLeft[1] = 170;
  this->AnkleLeft[2] = 122;

  this->FootLeft[0] = 255;
  this->FootLeft[1] = 126;
  this->FootLeft[2] = 0;

  this->HipRight[0] = 181;
  this->HipRight[1] = 165;
  this->HandRight[2] = 213;

  this->KneeRight[0] = 71;
  this->KneeRight[1] = 222;
  this->KneeRight[2] = 76;

  this->AnkleRight[0] = 245;
  this->AnkleRight[1] = 228;
  this->AnkleRight[2] = 156;

  this->FootRight[0] = 77;
  this->FootRight[1] = 109;
  this->FootRight[2] = 243;

  this->NodesColor.push_back(this->HipCenter);
  this->NodesColor.push_back(this->Spine);
  this->NodesColor.push_back(this->ShoulderCenter);
  this->NodesColor.push_back(this->Head);
  this->NodesColor.push_back(this->ShoulderLeft);
  this->NodesColor.push_back(this->ElbowLeft);
  this->NodesColor.push_back(this->WristLeft);
  this->NodesColor.push_back(this->HandLeft);
  this->NodesColor.push_back(this->ShoulderRight);
  this->NodesColor.push_back(this->ElbowRight);
  this->NodesColor.push_back(this->WristRight);
  this->NodesColor.push_back(this->HandRight);
  this->NodesColor.push_back(this->HipLeft);
  this->NodesColor.push_back(this->KneeLeft);
  this->NodesColor.push_back(this->AnkleLeft);
  this->NodesColor.push_back(this->FootLeft);
  this->NodesColor.push_back(this->HipRight);
  this->NodesColor.push_back(this->KneeRight);
  this->NodesColor.push_back(this->AnkleRight);
  this->NodesColor.push_back(this->FootRight);
  }

//----------------------------------------------------------------------------
vtkMRMLKinectPositionNode::~vtkMRMLKinectPositionNode()
  {
  if (this->NodeModel)
    {
    this->GetScene()->RemoveNode(this->NodeModel);
    this->NodeModel->Delete();
    }

  if (this->NodeMatrix)
    {
    this->NodeMatrix->Delete();
    }

  if (this->NodeTransform)
    {
    this->GetScene()->RemoveNode(this->NodeTransform);
    this->NodeTransform->Delete();
    }
  }

//----------------------------------------------------------------------------
void vtkMRMLKinectPositionNode::WriteXML(ostream& of, int nIndent)
  {
  Superclass::WriteXML(of, nIndent);
  }


//----------------------------------------------------------------------------
void vtkMRMLKinectPositionNode::ReadXMLAttributes(const char** atts)
  {
  Superclass::ReadXMLAttributes(atts);
  }

//----------------------------------------------------------------------------
void vtkMRMLKinectPositionNode::Copy(vtkMRMLNode *anode)
  {
  Superclass::Copy(anode);
  }

//-----------------------------------------------------------
void vtkMRMLKinectPositionNode::UpdateScene(vtkMRMLScene *scene)
  {
  Superclass::UpdateScene(scene);
  }

//---------------------------------------------------------------------------
void vtkMRMLKinectPositionNode::ProcessMRMLEvents ( vtkObject *caller,
  unsigned long event, 
  void *callData )
  {
  Superclass::ProcessMRMLEvents(caller, event, callData);
  }

//-----------------------------------------------------------
int vtkMRMLKinectPositionNode::Initialize(vtkMRMLScene *scene, const char* nodeName)
  {
  if (!scene || !nodeName)
    {
    return 0;
    }

  if (!this->NodeTransform && !this->NodeMatrix && !this->NodeModel)
    {
    std::stringstream modelName;
    modelName << nodeName << "Model";

    std::stringstream transformName;
    transformName << nodeName << "Transform";

    std::cerr << "SkeletonPositionIndex: " << this->SkeletonPositionIndex << std::endl;
    double* modelColor = this->NodesColor[this->SkeletonPositionIndex];
    std::cerr << "Color: " << modelColor[0] << "," << modelColor[1] << "," << modelColor[2] << std::endl;
    double mColor[3] = {modelColor[0]/255, modelColor[1]/255, modelColor[2]/255};

    this->NodeTransform = vtkMRMLLinearTransformNode::New();
    this->NodeMatrix = vtkMatrix4x4::New();
    this->NodeTransform->SetAndObserveMatrixTransformToParent(this->NodeMatrix);
    this->NodeTransform->SetName(transformName.str().c_str());
    scene->AddNode(this->NodeTransform);

    // Create new model
    this->NodeModel = vtkMRMLModelNode::New();
    vtkSmartPointer<vtkMRMLModelDisplayNode> displayNode =
      vtkSmartPointer<vtkMRMLModelDisplayNode>::New();

    vtkSmartPointer<vtkSphereSource> sphereModel = 
      vtkSmartPointer<vtkSphereSource>::New();
    sphereModel->SetRadius(5.0);
    sphereModel->SetCenter(0,0,0);
    sphereModel->Update();

    this->NodeModel->SetAndObservePolyData(sphereModel->GetOutput());
    displayNode->SetInputPolyData(this->NodeModel->GetPolyData());
    displayNode->SetColor(mColor[0], mColor[1], mColor[2]);

    scene->AddNode(displayNode.GetPointer());
    scene->AddNode(this->NodeModel);

    this->NodeModel->SetName(modelName.str().c_str());
    this->NodeModel->SetAndObserveDisplayNodeID(displayNode->GetID());
    this->NodeModel->SetAndObserveTransformNodeID(this->NodeTransform->GetID());
    this->NodeModel->HideFromEditorsOff();
    }

  this->SetName(nodeName);
  this->SetScene(scene);

  return 1;
  }

//-----------------------------------------------------------
void vtkMRMLKinectPositionNode::UpdatePosition(NUI_SKELETON_FRAME* skeletonFrame, int skeletonIndex)
  {
  if (!this->NodeMatrix)
    {
    return;
    }

  // Kinect units are in meters, Slicer units are in millimeters
  // (Conversion should be a 1000, but models too far)
  Vector4 nodePosition = skeletonFrame->SkeletonData[skeletonIndex].SkeletonPositions[this->SkeletonPositionIndex];
  this->NodeMatrix->SetElement(0,3,nodePosition.x*100);
  this->NodeMatrix->SetElement(1,3,nodePosition.z*100);
  this->NodeMatrix->SetElement(2,3,nodePosition.y*100);
  }
