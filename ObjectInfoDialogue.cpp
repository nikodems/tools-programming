// ObjectInfoDialogue.cpp : implementation file
//

#include "ObjectInfoDialogue.h"
#include "afxdialogex.h"


// ObjectInfoDialogue dialog

IMPLEMENT_DYNAMIC(ObjectInfoDialogue, CDialogEx)

BEGIN_MESSAGE_MAP(ObjectInfoDialogue, CDialogEx)
	ON_COMMAND(IDOK, &ObjectInfoDialogue::End)
	ON_EN_CHANGE(IDC_EDIT1, &ObjectInfoDialogue::OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT2, &ObjectInfoDialogue::OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT3, &ObjectInfoDialogue::OnChangeEdit)
END_MESSAGE_MAP()

ObjectInfoDialogue::ObjectInfoDialogue(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

ObjectInfoDialogue::~ObjectInfoDialogue()
{
}

bool ObjectInfoDialogue::GetStatus()
{
	return isRendered;
}

void ObjectInfoDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//Assign the variables to the edit boxes
	DDX_Control(pDX, IDC_EDIT1, m_editPosX);
	DDX_Control(pDX, IDC_EDIT2, m_editPosY);
	DDX_Control(pDX, IDC_EDIT3, m_editPosZ);
	DDX_Control(pDX, IDC_EDIT4, m_editID);
}

BOOL ObjectInfoDialogue::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	isRendered = true;

	return TRUE;
}

void ObjectInfoDialogue::End()
{
	isRendered = false;

	DestroyWindow();
}

void ObjectInfoDialogue::SetUpdateStatus(bool status)
{
	m_isSceneGraphUpdated = status;
}

bool ObjectInfoDialogue::GetUpdateStatus()
{
	return m_isSceneGraphUpdated;
}

void ObjectInfoDialogue::ShowInfo(std::set<int> &selectedObjects, std::vector<SceneObject> sceneGraph)
{
	CString tempString;
	float tempFloat;
	if (selectedObjects.size() == 1)
	{
		int tempID = *selectedObjects.begin();
		for (auto &i : sceneGraph)
		{
			if (tempID == i.ID)
			{
				int precision = 2;

				tempString.Format(_T("%i"), i.ID);

				m_editID.SetWindowTextW((LPCTSTR)tempString);

				//X Coord
				tempFloat = i.posX;

				tempString.Format(_T("%.*f"), precision, tempFloat);

				m_editPosX.SetWindowTextW((LPCTSTR)tempString);

				//Y Coord
				tempFloat = i.posY;

				tempString.Format(_T("%.*f"), precision, tempFloat);

				m_editPosY.SetWindowTextW((LPCTSTR)tempString);

				//Z Coord
				tempFloat = i.posZ;

				tempString.Format(_T("%.*f"), precision, tempFloat);

				m_editPosZ.SetWindowTextW((LPCTSTR)tempString);
			}

		}
	}
	else
	{
		End();
	}
}

void ObjectInfoDialogue::ReadInfo(std::set<int> selectedObjects, std::vector<SceneObject> &sceneGraph)
{
	CString tempString;
	float xFloat, yFloat, zFloat;
	int id;

	//Retrieve all the values in the boxes
	m_editPosX.GetWindowTextW(tempString);
	_stscanf(tempString, _T("%f"), &xFloat);

	m_editPosY.GetWindowTextW(tempString);
	_stscanf(tempString, _T("%f"), &yFloat);

	m_editPosZ.GetWindowTextW(tempString);
	_stscanf(tempString, _T("%f"), &zFloat);

	m_editID.GetWindowTextW(tempString);
	_stscanf(tempString, _T("%i"), &id);

	for (auto &i : sceneGraph)
	{
		//Update the values in the scene graph
		if (id == i.ID)
		{
			i.posX = xFloat;
			i.posY = yFloat;
			i.posZ = zFloat;
		}
	}
}


void ObjectInfoDialogue::OnChangeEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	SetUpdateStatus(true);
}
