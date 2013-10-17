#ifndef __vtkMRMLKinect4SlicerNode_h
#define __vtkMRMLKinect4SlicerNode_h

#include <windows.h>
#include "NuiApi.h"

#include "vtkMRML.h"
#include "vtkMRMLScene.h"
#include "vtkMRMLNode.h"
#include "vtkMRMLKinectPositionNode.h"
#include "vtkSlicerKinect4SlicerModuleMRMLExport.h"

class  VTK_SLICER_KINECT4SLICER_MODULE_MRML_EXPORT vtkMRMLKinect4SlicerNode : public vtkMRMLNode
{
public:
  static vtkMRMLKinect4SlicerNode *New();
  vtkTypeMacro(vtkMRMLKinect4SlicerNode, vtkMRMLNode);

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

  virtual int Initialize(vtkMRMLScene* scene);

  vtkGetMacro(BodyPartIndex, int);
  vtkSetMacro(BodyPartIndex, int);

  void BeginTracking();

protected:
  vtkMRMLKinect4SlicerNode();
  ~vtkMRMLKinect4SlicerNode();
  vtkMRMLKinect4SlicerNode(const vtkMRMLKinect4SlicerNode&);
  void operator=(const vtkMRMLKinect4SlicerNode&); 

  void ClearTracking() {};
  void TrackHead();
  void TrackRightHand();
  void TrackRightArm();
  void TrackLeftHand();
  void TrackLeftArm();
  void TrackBothHands();
  void TrackBothArms();
  void TrackBody();

  HANDLE NextVideoFrameEvent;
  HANDLE VideoStreamHandle;
  HANDLE NextSkeletonEvent;

  INuiSensor* KinectSensor;
  bool AlreadyTracking;
  int BodyPartIndex;
  std::vector<vtkMRMLKinectPositionNode*> BodyJointPositions;
  
};

#endif
