#include "vtkMRMLKinectPositionNode.h"

#include <vtkObjectFactory.h>

//----------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLKinectPositionNode);


//----------------------------------------------------------------------------
vtkMRMLKinectPositionNode::vtkMRMLKinectPositionNode()
{
  this->HideFromEditors = true;
}

//----------------------------------------------------------------------------
vtkMRMLKinectPositionNode::~vtkMRMLKinectPositionNode()
{
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
