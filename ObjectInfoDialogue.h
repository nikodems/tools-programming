#ifndef _OBJECT_INFO_DIALOGUE_H
#define _OBJECT_INFO_DIALOGUE_H

#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"

#include "DisplayObject.h"
#include "SceneObject.h"

#include <set>
#include <vector>


// ObjectInfoDialogue dialog

class ObjectInfoDialogue : public CDialogEx
{
	DECLARE_DYNAMIC(ObjectInfoDialogue)

public:
	ObjectInfoDialogue(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ObjectInfoDialogue();

	bool GetStatus();

	void End();

	//void ShowInfo(std::set<int> selectedObjects, std::vector<DisplayObject> displayList);
	void ShowInfo(std::set<int> &selectedObjects, std::vector<SceneObject> sceneGraph);
	//void ReadInfo(std::set<int> selectedObjects, std::vector<DisplayObject> &displayList);
	void ReadInfo(std::set<int> selectedObjects, std::vector<SceneObject> &sceneGraph);

	//void SetGameClass(Game* gameClass);

	void SetUpdateStatus(bool status);
	bool GetUpdateStatus();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog() override;

	bool isRendered;

	DECLARE_MESSAGE_MAP()
private:
	CEdit m_editPosX;
	CEdit m_editPosY;
	CEdit m_editPosZ;

	//Game* m_gameClass;
	CEdit m_editID;

	bool m_isSceneGraphUpdated = false;

private:
	afx_msg void OnChangeEdit();
};
#endif