#ifndef __vtkMRMLKinectPositionNode_h
#define __vtkMRMLKinectPositionNode_h

#include <Windows.h>
#include "NuiApi.h"

#include "vtkMRML.h"
#include "vtkMRMLLinearTransformNode.h"
#include "vtkMRMLModelDisplayNode.h"
#include "vtkMRMLModelNode.h"
#include "vtkMRMLNode.h"
#include "vtkMRMLScene.h"

#include "vtkSlicerKinect4SlicerModuleMRMLExport.h"

class vtkMRMLNode;
class vtkMRMLScene;

class  VTK_SLICER_KINECT4SLICER_MODULE_MRML_EXPORT vtkMRMLKinectPositionNode : public vtkMRMLNode
{
public:

  static vtkMRMLKinectPositionNode *New();
  vtkTypeMacro(vtkMRMLKinectPositionNode, vtkMRMLNode);

  //--------------------------------------------------------------------------
  // MRMLNode methods
  //--------------------------------------------------------------------------

  virtual vtkMRMLNode* CreateNodeInstance();
  // Description:
  // Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() {return "Kinect";};

  virtual const char* GetIcon() {return ":/Icons/Kinect.png";};

  // Description:
  // Read node attributes from XML file
  virtual void ReadXMLAttributes( const char** atts);
  
  // Description:
  // Write this node's information to a MRML file in XML format.
  virtual void WriteXML(ostream& of, int indent);

  virtual void UpdateScene(vtkMRMLScene *scene);

  // Description:
  // Copy the node's attributes to this object
  virtual void Copy(vtkMRMLNode *node);

  // Description:
  // alternative method to propagate events generated in Display nodes
  virtual void ProcessMRMLEvents ( vtkObject * /*caller*/, 
                                   unsigned long /*event*/, 
                                   void * /*callData*/ );

  virtual int Initialize(vtkMRMLScene* scene, const char* nodeName);

  vtkGetMacro(SkeletonPositionIndex, int);
  vtkSetMacro(SkeletonPositionIndex, int);

  void UpdatePosition(NUI_SKELETON_FRAME* skeletonFrame, int SkeletonIndex);

protected:
  vtkMRMLKinectPositionNode();
  ~vtkMRMLKinectPositionNode();
  vtkMRMLKinectPositionNode(const vtkMRMLKinectPositionNode&);
  void operator=(const vtkMRMLKinectPositionNode&);

  vtkMRMLLinearTransformNode* NodeTransform;
  vtkMatrix4x4* NodeMatrix;
  vtkMRMLModelNode* NodeModel;
  int SkeletonPositionIndex;

  std::vector<double*> NodesColor;
  double HipCenter[3];
  double Spine[3];
  double ShoulderCenter[3];
  double Head[3];
  double ShoulderLeft[3];
  double ElbowLeft[3];
  double WristLeft[3];
  double HandLeft[3];
  double ShoulderRight[3];
  double ElbowRight[3];
  double WristRight[3];
  double HandRight[3];
  double HipLeft[3];
  double KneeLeft[3];
  double AnkleLeft[3];
  double FootLeft[3];
  double HipRight[3];
  double KneeRight[3];
  double AnkleRight[3];
  double FootRight[3];
};

#endif
