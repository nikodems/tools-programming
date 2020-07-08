#include "MFCMain.h"
#include "resource.h"


BEGIN_MESSAGE_MAP(MFCMain, CWinApp)
	ON_COMMAND(ID_FILE_QUIT,	&MFCMain::MenuFileQuit)
	ON_COMMAND(ID_FILE_SAVETERRAIN, &MFCMain::MenuFileSaveTerrain)
	ON_COMMAND(ID_EDIT_SELECT, &MFCMain::MenuEditSelect)
	ON_COMMAND(ID_BUTTON40001,	&MFCMain::ToolBarButton1)
	ON_COMMAND(ID_BUTTON40006, &MFCMain::AIButton)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TOOL, &CMyFrame::OnUpdatePage)
END_MESSAGE_MAP()

BOOL MFCMain::InitInstance()
{
	//instanciate the mfc frame
	m_frame = new CMyFrame();
	m_pMainWnd = m_frame;

	m_frame->Create(	NULL,
					_T("World Of Flim-Flam Craft Editor"),
					WS_OVERLAPPEDWINDOW,
					CRect(100, 100, 1024, 768),
					NULL,
					NULL,
					0,
					NULL
				);

	//show and set the window to run and update. 
	m_frame->ShowWindow(SW_SHOW);
	m_frame->UpdateWindow();


	//get the rect from the MFC window so we can get its dimensions
	m_toolHandle = m_frame->m_DirXView.GetSafeHwnd();				//handle of directX child window
	m_frame->m_DirXView.GetClientRect(&WindowRECT);
	m_width		= WindowRECT.Width();
	m_height	= WindowRECT.Height();

	m_ToolSystem.onActionInitialise(m_toolHandle, m_width, m_height);

	return TRUE;
}

int MFCMain::Run()
{
	MSG msg;
	BOOL bGotMsg;

	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		if (true)
		{
			bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);
		}
		else
		{
			bGotMsg = (GetMessage(&msg, NULL, 0U, 0U) != 0);
		}

		if (bGotMsg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			m_ToolSystem.UpdateInput(&msg);
		}
		else
		{	
			//int ID = m_ToolSystem.getCurrentSelectionID();
			//std::wstring statusString = L"Selected Object: " + std::to_wstring(ID);
			std::wstring statusString = L"Selected Object: ";

			//Iterate through set of selected objects and add the object IDs onto the status string
			for (auto &i : m_ToolSystem.GetSelectionSet())
			{
				statusString += std::to_wstring(i);

				statusString += L", ";
			}

			m_ToolSystem.Tick(&msg);

			//send current object ID to status bar in The main frame
			m_frame->m_wndStatusBar.SetPaneText(1, statusString.c_str(), 1);	

			ObjectInfoDialogue();
		}
	}

	return (int)msg.wParam;
}

void MFCMain::MenuFileQuit()
{
	//will post message to the message thread that will exit the application normally
	PostQuitMessage(0);
}

void MFCMain::MenuFileSaveTerrain()
{
	m_ToolSystem.onActionSaveTerrain();
}

void MFCMain::MenuEditSelect()
{
	//SelectDialogue m_ToolSelectDialogue(NULL, &m_ToolSystem.m_sceneGraph);		//create our dialoguebox //modal constructor
	//m_ToolSelectDialogue.DoModal();	// start it up modal

	//modeless dialogue must be declared in the class.   If we do local it will go out of scope instantly and destroy itself
	m_ToolSelectDialogue.Create(IDD_DIALOG1);	//Start up modeless
	m_ToolSelectDialogue.ShowWindow(SW_SHOW);	//show modeless
	m_ToolSelectDialogue.SetObjectData(&m_ToolSystem.m_sceneGraph, &m_ToolSystem.m_selectedObject);
}

void MFCMain::ToolBarButton1()
{
	
	m_ToolSystem.onActionSave();
}

void MFCMain::AIButton()
{
	Game* gameClass = &m_ToolSystem.GetGameClass();

	m_aiNode.SetToolMainClass(&m_ToolSystem);
	m_aiNode.SetGameClass(&m_ToolSystem.GetGameClass());
	m_aiNode.CreateNode(gameClass->GetSceneGraph());

}

void MFCMain::ObjectInfoDialogue()
{
	//m_ObjectInfoDialogue.SetGameClass(&m_ToolSystem.GetGameClass());
	Game* gameClass = &m_ToolSystem.GetGameClass();
	//If only one object is selected
	if (m_ToolSystem.GetSelectionSet().size() == 1 )
	{
		//If it hasn't already been rendered
		if (!m_ObjectInfoDialogue.GetStatus())
		{
			m_ObjectInfoDialogue.Create(IDD_DIALOG3);
			m_ObjectInfoDialogue.ShowWindow(SW_SHOW);

		}
		else
		{
			//If it has been rendered then update the values inside the edit boxes
			m_ObjectInfoDialogue.ShowInfo(m_ToolSystem.GetSelectionSet(), m_ToolSystem.GetGameClass().GetSceneGraph());
		}
	}
	//If the selection has increased to more than one, end the window
	else if (m_ToolSystem.GetSelectionSet().size() > 1)
	{
		m_ObjectInfoDialogue.End();
	}
	//If no object is selected, continue rendering
	//This is important as clicking on the window launches the mouse picking function which updates the selection. Could be improved by somehow limiting the mouse picking to the scene without the UI.
	else
	{
		if (m_ObjectInfoDialogue.GetStatus())
		{
			//Read the values from the edit boxes to update the scene graph
			m_ObjectInfoDialogue.ReadInfo(m_ToolSystem.GetSelectionSet(), gameClass->GetSceneGraph());

			//If any object has been updated
			if (m_ObjectInfoDialogue.GetUpdateStatus())
			{
				//Build the display list from the scene graph
				//Performance heavy, could be improved by updating the display list with the edited object only.
				gameClass->BuildDisplayList(&gameClass->GetSceneGraph());

				//Update scene graph inside ToolMain
				m_ToolSystem.UpdateSceneGraph(gameClass->GetSceneGraph());

				m_ObjectInfoDialogue.SetUpdateStatus(false);
			}
		}
	}
}


MFCMain::MFCMain()
{
}


MFCMain::~MFCMain()
{
}
