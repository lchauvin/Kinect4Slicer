#ifndef __vtkMRMLKinectPositionNode_h
#define __vtkMRMLKinectPositionNode_h

#include "vtkMRML.h"
#include "vtkMRMLScene.h"
#include "vtkMRMLNode.h"
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

protected:
  vtkMRMLKinectPositionNode();
  ~vtkMRMLKinectPositionNode();
  vtkMRMLKinectPositionNode(const vtkMRMLKinectPositionNode&);
  void operator=(const vtkMRMLKinectPositionNode&); 
};

#endif
