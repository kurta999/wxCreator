#include "main_frame.h"
#include <wx/valnum.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>
#include <wx/richtooltip.h>
#include <wx/clipbrd.h>
#include <wx/richmsgdlg.h>
#include <wx/aui/aui.h>
#include <wx/filepicker.h>
#include <wx/socket.h>
#include <any>
#include <wx/aui/aui.h>
#include <wx/dataview.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/aui/aui.h>
#include "wx/treelist.h"
#include "wx/treectrl.h"

enum
{
	PGID = 1,
	ID_Hello = 1,
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_SIZE(MyFrame::OnSize)
EVT_MENU(ID_Hello, MyFrame::OnHelp)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(MyPanel, wxPanel)
	EVT_MOTION(MyPanel::OnMouseMotion)
	EVT_LEFT_DOWN(MyPanel::OnMouseLeftDown)
	EVT_ENTER_WINDOW(MyPanel::OnMouseEnter)
	EVT_LEAVE_WINDOW(MyPanel::OnMouseLeave)
	EVT_PG_CHANGED(PGID, MyPanel::OnPropertyGridChange)
wxEND_EVENT_TABLE()

std::unordered_map<void*, wxTypes> objects;
wxAuiNotebook* ctrl;
static const char* type_names[] = { "wxComboBox", "wxChoice", "wxListBox", "wxCheckBox", "wxRadioButton", "wxStaticLine", "wxSlider", "wxGauge", "wxButton", "wxStaticText", "wxSpinCtrl", "wxTextCtrl" };

void MyFrame::OnSize(wxSizeEvent& size)
{
	if (panel && panel->m_Log)
		panel->m_Log->Append(wxString::Format("New panel size: %d, %d", size.GetSize().x, size.GetSize().y));
}

void MyFrame::OnHelp(wxCommandEvent& event)
{
	wxMessageBox("Click on objects in the bottom of the screen to create them.\nAfterwards click on them and move with the mouse on the screen\n\
		Re-selecting an object can be done with Right mouse button\nMove Up & Down, Left & Right with keys\nResize them with 4, 8, 6, 2", "Help");
}

void MyFrame::Changeing(wxAuiNotebookEvent& event)
{
	wxString str;
	for (auto x : objects)
	{
		if (!x.first) continue;
		if (x.second == wxTypes::Text)
		{
			wxStaticText* t = reinterpret_cast<wxStaticText*>(x.first);
			str += wxString::Format("new wxStaticText(this, wxID_ANY, wxT(\"%s\"), wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				t->GetLabelText(), t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
		}		
		if (x.second == wxTypes::ComboBox)
		{
			wxComboBox* t = reinterpret_cast<wxComboBox*>(x.first);
			str += wxString::Format("new wxComboBox(this, wxID_ANY, wxT(\"%s\"), wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				t->GetLabelText(), t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
		}		
		if (x.second == wxTypes::Choise)
		{
			wxChoice* t = reinterpret_cast<wxChoice*>(x.first);
			str += wxString("wxArrayString m_choiceChoices;\n");
			str += wxString::Format("new wxChoice(this, wxID_ANY, wxPoint(%d, %d), wxSize(%d, %d), m_choiceChoices, 0);\n", 
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			str += wxString("m_wxChoice->SetSelection(0);\n");
		}
		if (x.second == wxTypes::ListBox)
		{
			wxListBox* t = reinterpret_cast<wxListBox*>(x.first);
			str += wxString::Format("new wxListBox(this, wxID_ANY, wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
		}		
		if (x.second == wxTypes::CheckBox)
		{
			wxCheckBox* t = reinterpret_cast<wxCheckBox*>(x.first);
			str += wxString::Format("new wxCheckBox(this, wxID_ANY, wxT(\"%s\"), wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				t->GetLabelText(), t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
		}		
		if (x.second == wxTypes::StaticLine)
		{
			wxStaticLine* t = reinterpret_cast<wxStaticLine*>(x.first);
			str += wxString::Format("new wxStaticLine(this, wxID_ANY, wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
		}
		if (x.second == wxTypes::Slider)
		{
			wxSlider* t = reinterpret_cast<wxSlider*>(x.first);
			str += wxString::Format("new wxSlider(this, wxID_ANY, %d, %d, %d, wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				0, t->GetMin(), t->GetMax(), t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
		}		
		if (x.second == wxTypes::Gauge)
		{
			wxGauge* t = reinterpret_cast<wxGauge*>(x.first);
			str += wxString::Format("new wxGauge(this, wxID_ANY, 100, wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
		}		
		if (x.second == wxTypes::SpinControl)
		{
			wxSpinCtrl* t = reinterpret_cast<wxSpinCtrl*>(x.first);
			str += wxString::Format("new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(%d, %d), wxSize(%d, %d), wxSP_ARROW_KEYS, 1, 255, 1);\n", 
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
		}		
		if (x.second == wxTypes::TextControl)
		{
			wxSpinCtrl* t = reinterpret_cast<wxSpinCtrl*>(x.first);
			str += wxString::Format("new wxTextCtrl(this, wxID_ANY, wxT(\"%s\"), wxPoint(%d, %d), wxDefaultSize, 0);\n", 
				t->GetLabelText(), t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
		}	
	}
	cpp_panel->m_StyledTextCtrl->ClearAll();
	cpp_panel->m_StyledTextCtrl->AppendText(str);
}

MyFrame::MyFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition,
		wxSize(1024, 1000))
{
	m_mgr.SetManagedWindow(this);
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Read help\tCtrl-H",
		"Read description about this program");
	menuFile->Append(wxID_EXIT);
	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&Help");
	SetMenuBar(menuBar);

	CreateStatusBar();
	SetStatusText("Welcome in wxCreator v0.1 alpha");

	const wxIcon icon(wxT("./icon.ico"), wxBITMAP_TYPE_ICO);
	SetIcon(icon);
	wxAuiToolBar* tb5 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW | wxAUI_TB_VERTICAL);
	tb5->SetToolBitmapSize(FromDIP(wxSize(48, 48)));
	tb5->AddTool(0, "Refresh measurements", wxArtProvider::GetBitmap(wxART_INFORMATION), "Refresh measurements");
	tb5->AddSeparator();
	tb5->AddTool(1, "Update", wxArtProvider::GetBitmap(wxART_CDROM), "Request configurations update");
	tb5->AddTool(2, "Test", wxArtProvider::GetBitmap(wxART_FILE_SAVE), "Send configurations to aircheck");
	tb5->AddTool(3, "Test", wxArtProvider::GetBitmap(wxART_MISSING_IMAGE), "Restart aircheck");
	tb5->Realize();
	panel = new MyPanel(this);
	cpp_panel = new CppPanel(this);

	wxSize client_size = GetClientSize();
	ctrl = new wxAuiNotebook(this, wxID_ANY, wxPoint(client_size.x, client_size.y), FromDIP(wxSize(430, 200)), wxAUI_NB_TOP | wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE | wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_MIDDLE_CLICK_CLOSE | wxAUI_NB_TAB_EXTERNAL_MOVE | wxNO_BORDER);
	ctrl->Freeze();
	ctrl->Connect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler(MyFrame::Changeing), NULL, this);
	ctrl->AddPage(panel, "Front page", false);
	ctrl->AddPage(cpp_panel, "C++ Code", false);
	ctrl->Thaw();

	m_mgr.AddPane(ctrl, wxAuiPaneInfo().Name("notebook_content").CenterPane().PaneBorder(false));
	m_mgr.AddPane(tb5, wxAuiPaneInfo().Name("tb5").Caption("Sample Vertical Toolbar").ToolbarPane().Top().GripperTop());
	m_mgr.Update();

}

wxPGProperty* m_pgId;
wxPGProperty* m_pgPos;
wxPGProperty* m_pgSize;
wxPGProperty* m_pgMinSize;
wxPGProperty* m_pgMaxSize;
wxPGProperty* m_pgForegroundColor;
wxPGProperty* m_pgBackgroundColor;
wxPGProperty* m_pgFont;
wxPGProperty* m_pgTooltip;
wxPGProperty* m_pgEnabled;
wxPGProperty* m_pgHidden;
wxPropertyGrid* m_propertyGrid1;

class PropertyGrid
{
public:
	PropertyGrid(MyPanel* parent, int id, wxString pos, wxString size, wxColour color)
	{
		m_propertyGrid = new wxPropertyGrid(parent, PGID, wxPoint(850, 0), wxSize(300, 500), wxPG_DEFAULT_STYLE);
		m_pgId = m_propertyGrid->Append(new wxIntProperty(wxT("ID"), wxPG_LABEL, id));
		m_pgPos = m_propertyGrid->Append(new wxStringProperty(wxT("Position"), wxPG_LABEL, pos));
		m_pgSize = m_propertyGrid->Append(new wxStringProperty(wxT("Size"), wxPG_LABEL, size));
		m_pgMinSize = m_propertyGrid->Append(new wxStringProperty(wxT("Min size"), wxPG_LABEL, size));
		m_pgMaxSize = m_propertyGrid->Append(new wxStringProperty(wxT("Max Size"), wxPG_LABEL, size));
		m_pgForegroundColor = m_propertyGrid->Append(new wxColourProperty(wxT("Fg. Colour"), wxPG_LABEL, color));
		m_pgBackgroundColor = m_propertyGrid->Append(new wxColourProperty(wxT("Bg. Colour"), wxPG_LABEL, color));
		m_pgFont = m_propertyGrid->Append(new wxFontProperty(wxT("Font"), wxPG_LABEL));
		m_pgTooltip = m_propertyGrid->Append(new wxStringProperty(wxT("Tooltip"), wxPG_LABEL));
		m_pgEnabled = m_propertyGrid->Append(new wxBoolProperty(wxT("Enabled"), wxPG_LABEL, true));
		m_pgHidden = m_propertyGrid->Append(new wxBoolProperty(wxT("Hidden"), wxPG_LABEL, true));
	}

	void Update(int id, wxPoint pos, wxSize size, wxSize min_size, wxSize max_size, const wxColour f_color, wxColour b_color, wxFont font, bool bEnable,
		bool bHidden)
	{
		m_pgId->SetValue(id);
		m_pgPos->SetValue(wxString::Format("%d,%d", pos.x, pos.y));
		m_pgSize->SetValue(wxString::Format("%d,%d", size.x, size.y));
		m_pgMinSize->SetValue(wxString::Format("%d,%d", min_size.x, min_size.y));
		m_pgMaxSize->SetValue(wxString::Format("%d,%d", max_size.x, max_size.y));
		
		wxVariant f_clr, b_clr, fnt;
		f_clr << f_color;
		b_clr << b_color;
		fnt << font;
		m_pgForegroundColor->SetValue(f_clr);
		m_pgBackgroundColor->SetValue(b_clr);
		m_pgFont->SetValue(fnt);
		m_pgEnabled->SetValue(bEnable);
		m_pgHidden->SetValue(bHidden);
	}
public:
	wxPropertyGrid* m_propertyGrid;
	wxPGProperty* m_pgID;
	wxPGProperty* m_pgPos;
	wxPGProperty* m_pgSize;
	wxPGProperty* m_pgColor;
};

class PropertyGridButton : public PropertyGrid
{
	/*
	PropertyGridButton(wxFrame* parent, int id, wxString& pos, wxString& size, wxColour& color)
	{
		m_propertyGrid->SetPropertyValueString(wx)
	}
	*/
};

CppPanel::CppPanel(wxFrame* parent)
	: wxPanel(parent, wxID_ANY)
{
	
	m_StyledTextCtrl = new wxStyledTextCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(1024, 900), 0, wxEmptyString);
	m_StyledTextCtrl->SetUseTabs(true);
	m_StyledTextCtrl->SetTabWidth(4);
	m_StyledTextCtrl->SetIndent(4);
	m_StyledTextCtrl->SetTabIndents(true);
	m_StyledTextCtrl->SetBackSpaceUnIndents(true);
	m_StyledTextCtrl->SetViewEOL(false);
	m_StyledTextCtrl->SetViewWhiteSpace(false);
	m_StyledTextCtrl->SetMarginWidth(2, 0);
	m_StyledTextCtrl->SetIndentationGuides(true);
	m_StyledTextCtrl->SetMarginType(1, wxSTC_MARGIN_SYMBOL);
	m_StyledTextCtrl->SetMarginMask(1, wxSTC_MASK_FOLDERS);
	m_StyledTextCtrl->SetMarginWidth(1, 16);
	m_StyledTextCtrl->SetMarginSensitive(1, true);
	m_StyledTextCtrl->SetProperty(wxT("fold"), wxT("1"));
	m_StyledTextCtrl->SetFoldFlags(wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);
	m_StyledTextCtrl->SetMarginType(0, wxSTC_MARGIN_NUMBER);
	m_StyledTextCtrl->SetMarginWidth(0, m_StyledTextCtrl->TextWidth(wxSTC_STYLE_LINENUMBER, wxT("_99999")));
	m_StyledTextCtrl->MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS);
	m_StyledTextCtrl->MarkerSetBackground(wxSTC_MARKNUM_FOLDER, wxColour(wxT("BLACK")));
	m_StyledTextCtrl->MarkerSetForeground(wxSTC_MARKNUM_FOLDER, wxColour(wxT("WHITE")));
	m_StyledTextCtrl->MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS);
	m_StyledTextCtrl->MarkerSetBackground(wxSTC_MARKNUM_FOLDEROPEN, wxColour(wxT("BLACK")));
	m_StyledTextCtrl->MarkerSetForeground(wxSTC_MARKNUM_FOLDEROPEN, wxColour(wxT("WHITE")));
	m_StyledTextCtrl->MarkerDefine(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY);
	m_StyledTextCtrl->MarkerDefine(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS);
	m_StyledTextCtrl->MarkerSetBackground(wxSTC_MARKNUM_FOLDEREND, wxColour(wxT("BLACK")));
	m_StyledTextCtrl->MarkerSetForeground(wxSTC_MARKNUM_FOLDEREND, wxColour(wxT("WHITE")));
	m_StyledTextCtrl->MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS);
	m_StyledTextCtrl->MarkerSetBackground(wxSTC_MARKNUM_FOLDEROPENMID, wxColour(wxT("BLACK")));
	m_StyledTextCtrl->MarkerSetForeground(wxSTC_MARKNUM_FOLDEROPENMID, wxColour(wxT("WHITE")));
	m_StyledTextCtrl->MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY);
	m_StyledTextCtrl->MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY);
	m_StyledTextCtrl->SetSelBackground(true, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
	m_StyledTextCtrl->SetSelForeground(true, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));


}

PropertyGrid* m_propgrid = nullptr;

MyPanel::MyPanel(wxFrame* parent)
    : wxPanel(parent, wxID_ANY)
{	
	m_propgrid = new PropertyGrid(this, 100, wxT("0,0"), wxT("0,0"), wxColor(*wxRED));

	m_wxButton = new wxButton(this, wxID_ANY, wxT("btn"), wxPoint(0, 815), wxSize(25, 25), 0);
	m_wxButton->SetToolTip("wxButton - DClick for text change, Middle click for pos change");
	m_wxButton->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxButton - pos: %d,%d", m_wxButton->GetPosition().x, m_wxButton->GetPosition().y));

			void* tmp = new wxButton(this, wxID_ANY, wxT("wxButton"), wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = wxTypes::Button;
			m_SelectedWidget = tmp;

			((wxButton*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
			((wxButton*)(tmp))->Bind(wxEVT_LEFT_DCLICK, &MyPanel::OnDoubleClick, this);
			((wxButton*)(tmp))->Bind(wxEVT_MIDDLE_DOWN, &MyPanel::OnMiddleClick, this);
		});

	m_wxComboBox = new wxComboBox(this, wxID_ANY, wxT("combo"), wxPoint(30, 815), wxSize(40, 25), 0);
	m_wxComboBox->SetToolTip("wxComboBox - DClick for text change, Middle click for pos change");
	m_wxComboBox->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxComboBox - pos: %d,%d", m_wxComboBox->GetPosition().x, m_wxComboBox->GetPosition().y));

			void* tmp = new wxComboBox(this, wxID_ANY, wxT("wxComboBox"), wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = wxTypes::Button;
			m_SelectedWidget = tmp;

			((wxButton*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
			((wxButton*)(tmp))->Bind(wxEVT_LEFT_DCLICK, &MyPanel::OnDoubleClick, this);
			((wxButton*)(tmp))->Bind(wxEVT_MIDDLE_DOWN, &MyPanel::OnMiddleClick, this);
		});

	wxArrayString m_choiceChoices;
	m_wxChoice = new wxChoice(this, wxID_ANY, wxPoint(80, 815), wxSize(40, 25), m_choiceChoices, 0);
	m_wxChoice->SetSelection(0);
	m_wxChoice->SetToolTip("wxChoice - DClick for text change, Middle click for pos change");
	m_wxChoice->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxChoice - pos: %d,%d", m_wxChoice->GetPosition().x, m_wxChoice->GetPosition().y));

			wxArrayString m_choiceChoices2;
			m_choiceChoices2.Add("First");
			m_choiceChoices2.Add("Second");
			void* tmp = new wxChoice(this, wxID_ANY, wxPoint(80, 815), wxSize(40, 25), m_choiceChoices2, 0);
			((wxChoice*)(tmp))->SetSelection(0);
			objects[tmp] = wxTypes::Button;
			m_SelectedWidget = tmp;

			((wxChoice*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
			((wxChoice*)(tmp))->Bind(wxEVT_LEFT_DCLICK, &MyPanel::OnDoubleClick, this);
			((wxChoice*)(tmp))->Bind(wxEVT_MIDDLE_DOWN, &MyPanel::OnMiddleClick, this);
		});

	m_wxListBox = new wxListBox(this, wxID_ANY, wxPoint(120, 815), wxSize(40, 25), 0);
	m_wxListBox->SetToolTip("wxComboBox - DClick for text change, Middle click for pos change");
	m_wxListBox->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxComboBox - pos: %d,%d", m_wxListBox->GetPosition().x, m_wxListBox->GetPosition().y));

			void* tmp = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = wxTypes::Button;
			m_SelectedWidget = tmp;

			((wxListBox*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
			((wxListBox*)(tmp))->Bind(wxEVT_LEFT_DCLICK, &MyPanel::OnDoubleClick, this);
			((wxListBox*)(tmp))->Bind(wxEVT_MIDDLE_DOWN, &MyPanel::OnMiddleClick, this);
		});

	m_wxCheckBox = new wxCheckBox(this, wxID_ANY, wxT("Check Me!"), wxPoint(140, 815), wxSize(40, 25), 0);
	m_wxCheckBox->SetToolTip("wxCheckBox - DClick for text change, Middle click for pos change");
	m_wxCheckBox->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxCheckBox - pos: %d,%d", m_wxCheckBox->GetPosition().x, m_wxCheckBox->GetPosition().y));

			void* tmp = new wxCheckBox(this, wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = wxTypes::Button;
			m_SelectedWidget = tmp;

			((wxCheckBox*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
			((wxCheckBox*)(tmp))->Bind(wxEVT_LEFT_DCLICK, &MyPanel::OnDoubleClick, this);
			((wxCheckBox*)(tmp))->Bind(wxEVT_MIDDLE_DOWN, &MyPanel::OnMiddleClick, this);
		});

	m_wxRadioButton = new wxRadioButton(this, wxID_ANY, wxT("RadioBtn"), wxPoint(190, 815), wxSize(40, 25), 0);
	m_wxRadioButton->SetToolTip("wxCheckBox - DClick for text change, Middle click for pos change");
	m_wxRadioButton->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxRadioButton - pos: %d,%d", m_wxRadioButton->GetPosition().x, m_wxRadioButton->GetPosition().y));

			void* tmp = new wxRadioButton(this, wxID_ANY, wxT("RadioBtn"), wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = wxTypes::Button;
			m_SelectedWidget = tmp;

			((wxRadioButton*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
			((wxRadioButton*)(tmp))->Bind(wxEVT_LEFT_DCLICK, &MyPanel::OnDoubleClick, this);
			((wxRadioButton*)(tmp))->Bind(wxEVT_MIDDLE_DOWN, &MyPanel::OnMiddleClick, this);
		});

	m_wxStaticLine = new wxStaticLine(this, wxID_ANY, wxPoint(230, 815), wxSize(40, 25), 0);
	m_wxStaticLine->SetToolTip("wxCheckBox - DClick for text change, Middle click for pos change");
	m_wxStaticLine->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxStaticLine - pos: %d,%d", m_wxStaticLine->GetPosition().x, m_wxStaticLine->GetPosition().y));

			void* tmp = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = wxTypes::StaticLine;
			m_SelectedWidget = tmp;

			((wxStaticLine*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
			((wxStaticLine*)(tmp))->Bind(wxEVT_LEFT_DCLICK, &MyPanel::OnDoubleClick, this);
			((wxStaticLine*)(tmp))->Bind(wxEVT_MIDDLE_DOWN, &MyPanel::OnMiddleClick, this);
		});

	m_wxSlider = new wxSlider(this, wxID_ANY, 50, 0, 100, wxPoint(260, 815), wxSize(40, 25), 0);
	m_wxSlider->SetToolTip("wxCheckBox - DClick for text change, Middle click for pos change");
	m_wxSlider->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxSlider - pos: %d,%d", m_wxSlider->GetPosition().x, m_wxSlider->GetPosition().y));

			void* tmp = new wxSlider(this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = wxTypes::Slider;
			m_SelectedWidget = tmp;

			((wxSlider*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
			((wxSlider*)(tmp))->Bind(wxEVT_LEFT_DCLICK, &MyPanel::OnDoubleClick, this);
			((wxSlider*)(tmp))->Bind(wxEVT_MIDDLE_DOWN, &MyPanel::OnMiddleClick, this);
		});

	m_wxGauge = new wxGauge(this, wxID_ANY, 100, wxPoint(290, 815), wxSize(40, 25), 0);
	m_wxGauge->SetToolTip("wxGauge - DClick for text change, Middle click for pos change");
	m_wxGauge->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxSlider - pos: %d,%d", m_wxGauge->GetPosition().x, m_wxGauge->GetPosition().y));

			void* tmp = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, 0);
			((wxGauge*)(tmp))->SetValue(20);
			objects[tmp] = wxTypes::Slider;
			m_SelectedWidget = tmp;

			((wxGauge*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
			((wxGauge*)(tmp))->Bind(wxEVT_LEFT_DCLICK, &MyPanel::OnDoubleClick, this);
			((wxGauge*)(tmp))->Bind(wxEVT_MIDDLE_DOWN, &MyPanel::OnMiddleClick, this);
		});


	m_wxStaticText = new wxStaticText(this, wxID_ANY, wxT("wxStaticText"), wxPoint(0, 785), wxDefaultSize, 0);
	m_wxStaticText->SetToolTip("DClick for text change, Middle click for pos change");
	m_wxStaticText->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxStaticText - pos: %d,%d", m_wxStaticText->GetPosition().x, m_wxStaticText->GetPosition().y));

			void* tmp = new wxStaticText(this, wxID_ANY, wxT("wxStaticText"), wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = wxTypes::Text;
			m_SelectedWidget = tmp;
			
			((wxStaticText*)(tmp))->Bind(wxEVT_RIGHT_DOWN, &MyPanel::OnClick, this);
			((wxStaticText*)(tmp))->Bind(wxEVT_LEFT_DCLICK, &MyPanel::OnDoubleClick, this);
			((wxStaticText*)(tmp))->Bind(wxEVT_MIDDLE_DOWN, &MyPanel::OnMiddleClick, this);
		});

	m_wxSpinCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(76, 785), wxDefaultSize, wxSP_ARROW_KEYS, 1, 255, 1);
	m_wxSpinCtrl->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxSpinCtrl - pos: %d,%d", m_wxSpinCtrl->GetPosition().x, m_wxSpinCtrl->GetPosition().y));

			void* tmp = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 255, 1);
			objects[tmp] = wxTypes::SpinControl;
			m_SelectedWidget = tmp;

			((wxSpinCtrl*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
			((wxSpinCtrl*)(tmp))->Bind(wxEVT_LEFT_DCLICK, &MyPanel::OnDoubleClick, this);
			((wxSpinCtrl*)(tmp))->Bind(wxEVT_MIDDLE_DOWN, &MyPanel::OnMiddleClick, this);
		});

	m_wxTextCtrl = new wxTextCtrl(this, wxID_ANY, wxT("wxTextCtrl"), wxPoint(140, 785), wxDefaultSize, 0);
	m_wxTextCtrl->SetToolTip("DClick for text change, Middle click for pos change");
	m_wxTextCtrl->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxTextCtrl - pos: %d,%d", m_wxStaticText->GetPosition().x, m_wxStaticText->GetPosition().y));

			void* tmp = new wxTextCtrl(this, wxID_ANY, wxT("wxTextCtrl"), wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = wxTypes::TextControl;
			m_SelectedWidget = tmp;
			
			((wxStaticText*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
			((wxStaticText*)(tmp))->Bind(wxEVT_LEFT_DCLICK, &MyPanel::OnDoubleClick, this);
			((wxStaticText*)(tmp))->Bind(wxEVT_MIDDLE_DOWN, &MyPanel::OnMiddleClick, this);
		});


	m_Log = new wxListBox(this, wxID_ANY, wxPoint(0, 700), wxSize(300, 80), 0, 0, wxLB_EXTENDED | wxLB_HSCROLL | wxLB_NEEDED_SB);
	m_Log->Bind(wxEVT_LEFT_DCLICK, [this](wxMouseEvent& event)
		{
			wxClipboard* clip = new wxClipboard();
			clip->Clear();
			clip->SetData(new wxTextDataObject(m_Log->GetString(m_Log->GetSelection())));
			clip->Flush();
			clip->Close();
		});
	this->Layout();
	this->Bind(wxEVT_CHAR_HOOK, &MyPanel::OnKeyDown, this);
}

wxTypes MyPanel::FindwxText(void* object_to_find)
{
	wxTypes a = wxTypes::Invalid;
	if (m_SelectedWidget || object_to_find)
	{
		try
		{
			a = objects[object_to_find == nullptr ? m_SelectedWidget : object_to_find];
		}
		catch (...) {}
	}
	return a;
}


void MyPanel::OnKeyDown(wxKeyEvent& event)
{
	m_Log->Append(wxString::Format("KeyDown: %d\n", (int)event.GetKeyCode()));
	
	int keycode = (int)event.GetKeyCode();
	wxTypes t = FindwxText();
	switch (keycode)
	{
	case 68: /* D */
	{

	}
	case 315: /* Up*/
	{
		if (t != wxTypes::Invalid)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxPoint pos = text->GetPosition();
			pos.y -= m_wxSpinCtrl->GetValue();
			text->SetPosition(std::move(pos));
		}
		break;
	}
	case 317: /* Down*/
	{
		if (t != wxTypes::Invalid)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxPoint pos = text->GetPosition();
			pos.y += m_wxSpinCtrl->GetValue();
			text->SetPosition(std::move(pos));
		}
		break;
	}
	case 314: /* Left*/
	{
		if (t != wxTypes::Invalid)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxPoint pos = text->GetPosition();
			pos.x -= m_wxSpinCtrl->GetValue();
			text->SetPosition(std::move(pos));
		}
		break;
	}
	case 316: /* Right*/
	{
		if (t != wxTypes::Invalid)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxPoint pos = text->GetPosition();
			pos.x += m_wxSpinCtrl->GetValue();
			text->SetPosition(std::move(pos));
		}
		break;
	}
	case 330: /* 6*/
	{
		if (t != wxTypes::Invalid)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxSize pos = text->GetSize();
			pos.x += 1;
			text->SetSize(std::move(pos));
		}
		break;
	}
	case 332: /* 8*/
	{
		if (t != wxTypes::Invalid)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxSize pos = text->GetSize();
			pos.y += 1;
			text->SetSize(std::move(pos));
		}
		break;
	}
	case 328: /* 4*/
	{
		if (t != wxTypes::Invalid)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxSize pos = text->GetSize();
			pos.x -= 1;
			text->SetSize(std::move(pos));
		}
		break;
	}	
	case 326: /* ¾*/
	{
		if (t != wxTypes::Invalid)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxSize pos = text->GetSize();
			pos.y -= 1;
			text->SetSize(std::move(pos));
		}
		break;
	}
	}
	event.Skip();
}

template <class T> void MyPanel::SetPos(void* ptr, wxPoint &pos)
{
	((T*)ptr)->SetPosition(pos);
}

void MyPanel::OnMouseLeftDown(wxMouseEvent& event)
{
	wxTypes t = FindwxText();
	if (t != wxTypes::Invalid)
	{
		m_Log->Append(wxString::Format(":: Current item is %s", type_names[static_cast<int>(t)]));
	}

}

void MyPanel::OnMouseMotion(wxMouseEvent& event)
{
	wxPoint pos = ScreenToClient(::wxGetMousePosition());
	wxMouseState mouse = wxGetMouseState();

	wxTypes t = FindwxText();
	if (t != wxTypes::Invalid && mouse.LeftIsDown())
	{
		switch (t)
		{
			case wxTypes::ComboBox:
				SetPos<wxComboBox>(m_SelectedWidget, pos);		
				break;	
			case wxTypes::Choise:
				SetPos<wxChoice>(m_SelectedWidget, pos);
				break;	
			case wxTypes::ListBox:
				SetPos<wxListBox>(m_SelectedWidget, pos);
				break;	
			case wxTypes::CheckBox:
				SetPos<wxCheckBox>(m_SelectedWidget, pos);
				break;	
			case wxTypes::RadioButton:
				SetPos<wxRadioButton>(m_SelectedWidget, pos);
				break;	
			case wxTypes::StaticLine:
				SetPos<wxStaticLine>(m_SelectedWidget, pos);
				break;	
			case wxTypes::Slider:
				SetPos<wxSlider>(m_SelectedWidget, pos);
				break;	
			case wxTypes::Gauge:
				SetPos<wxGauge>(m_SelectedWidget, pos);
				break;	
			case wxTypes::Button:
				SetPos<wxButton>(m_SelectedWidget, pos);
				break;			
			case wxTypes::Text:
			{
				SetPos<wxStaticText>(m_SelectedWidget, pos);
				wxStaticText* t = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
				m_propgrid->Update(0, t->GetPosition(), t->GetSize(), t->GetMinSize(), t->GetMaxSize(), t->GetForegroundColour(), t->GetBackgroundColour(), 
					t->GetFont(), t->IsEnabled(), !t->IsShown());
				break;
			}
			case wxTypes::SpinControl:
				SetPos<wxSpinCtrl>(m_SelectedWidget, pos);
				break;	
			case wxTypes::TextControl:
				SetPos<wxTextCtrl>(m_SelectedWidget, pos);
				break;
		}
	}
}

void MyPanel::OnMouseEnter(wxMouseEvent& event)
{

}

void MyPanel::OnMouseLeave(wxMouseEvent& event)
{

}

void MyPanel::OnPropertyGridChange(wxPropertyGridEvent& event)
{
	wxPGProperty* property = event.GetProperty();
	if (property == m_pgPos)
	{
		wxTypes t = FindwxText();
		if (t != wxTypes::Invalid)
		{
			int x, y;
			wxString str;
			property->GetValue().Convert(&str);
			if (sscanf(str.c_str(), "%d,%d", &x, &y) == 2)
			{
				((wxStaticText*)m_SelectedWidget)->SetPosition(wxPoint(x, y));
			}
		}
	}
	else if (property == m_pgSize)
	{
		wxTypes t = FindwxText();
		if (t != wxTypes::Invalid)
		{
			int x, y;
			wxString str;
			property->GetValue().Convert(&str);
			if (sscanf(str.c_str(), "%d,%d", &x, &y) == 2)
			{
				((wxStaticText*)m_SelectedWidget)->SetSize(wxSize(x, y));
			}
		}
	}
	else if (property == m_pgMinSize)
	{
		wxTypes t = FindwxText();
		if (t != wxTypes::Invalid)
		{
			int x, y;
			wxString str;
			property->GetValue().Convert(&str);
			if (sscanf(str.c_str(), "%d,%d", &x, &y) == 2)
			{
				((wxStaticText*)m_SelectedWidget)->SetMinSize(wxSize(x, y));
			}
		}
	}
	else if (property == m_pgMaxSize)
	{
		wxTypes t = FindwxText();
		if (t != wxTypes::Invalid)
		{
			int x, y;
			wxString str;
			property->GetValue().Convert(&str);
			if (sscanf(str.c_str(), "%d,%d", &x, &y) == 2)
			{
				((wxStaticText*)m_SelectedWidget)->SetMaxSize(wxSize(x, y));
			}
		}
	}
	else if (property == m_pgForegroundColor)
	{
		wxTypes t = FindwxText();
		if (t != wxTypes::Invalid)
		{
			wxVariant a = property->GetValue();
			wxColour color;
			color << a;
			((wxStaticText*)m_SelectedWidget)->SetForegroundColour(color);
			((wxStaticText*)m_SelectedWidget)->Refresh();  /* TODO: It doesn't work, find out how to refresh */
		}
	}		
	else if (property == m_pgBackgroundColor)
	{
		wxTypes t = FindwxText();
		if (t != wxTypes::Invalid)
		{
			wxVariant a = property->GetValue();
			wxColour color;
			color << a;
			((wxStaticText*)m_SelectedWidget)->SetBackgroundColour(color);
			((wxStaticText*)m_SelectedWidget)->Refresh();
		}
	}	
	else if (property == m_pgFont)
	{
		wxTypes t = FindwxText();
		if (t != wxTypes::Invalid)
		{
			wxVariant a = property->GetValue();
			wxFont fnt;
			fnt << a;
			((wxStaticText*)m_SelectedWidget)->SetFont(fnt);
		}
	}	
	else if (property == m_pgTooltip)
	{
		wxTypes t = FindwxText();
		if (t != wxTypes::Invalid)
		{
			wxString str;
			property->GetValue().Convert(&str);
			((wxStaticText*)m_SelectedWidget)->SetToolTip(str);
		}
	}	
	else if (property == m_pgEnabled)
	{
		wxTypes t = FindwxText();
		if (t != wxTypes::Invalid)
		{
			bool is_enabled;
			property->GetValue().Convert(&is_enabled);
			((wxStaticText*)m_SelectedWidget)->Enable(is_enabled);
		}
	}	
	else if (property == m_pgHidden)
	{
		wxTypes t = FindwxText();
		if (t != wxTypes::Invalid)
		{
			bool is_hide;
			property->GetValue().Convert(&is_hide);
			if(is_hide)
				((wxStaticText*)m_SelectedWidget)->Hide();
			else
				((wxStaticText*)m_SelectedWidget)->Show();
		}
	}
}

void MyPanel::OnClick(wxMouseEvent& event)
{
	void* obj = event.GetEventObject();
	wxTypes t = FindwxText(obj);
	if (t != wxTypes::Invalid)
	{
		switch (t)
		{
			case wxTypes::Text:
				m_SelectedWidget = obj;
				break;
			case wxTypes::Button:
			case wxTypes::SpinControl:
			case wxTypes::TextControl:
				m_SelectedWidget = obj;
				break;
		}
	}
}

void MyPanel::OnDoubleClick(wxMouseEvent& event)
{
	void* obj = event.GetEventObject();
	wxTypes t = FindwxText(obj);
	if (t != wxTypes::Invalid)
	{
		switch (t)
		{
			case wxTypes::Text:
			{
				wxTextEntryDialog myDialog(this, _("Enter new text"), _("Text change"));
				if (myDialog.ShowModal() == wxID_OK)
				{
					wxString str = myDialog.GetValue();
					((wxStaticText*)obj)->SetLabelText(str);
				}
				break;
			}
		}
	}
}

void MyPanel::OnMiddleClick(wxMouseEvent& event)
{
	void* obj = event.GetEventObject();
	wxPoint pos = ((wxStaticText*)obj)->GetPosition();
	wxTypes t = FindwxText(obj);
	if (t != wxTypes::Invalid)
	{
		switch (t)
		{
			case wxTypes::Text:
			{
				wxTextEntryDialog myDialog(this, _("Enter new position"), wxString::Format("Current Position - pos: %d,%d", pos.x, pos.y));
				if (myDialog.ShowModal() == wxID_OK)
				{
					wxString str = myDialog.GetValue();
					int x, y;
					if (sscanf(str.c_str(), "%d,%d", &x, &y) == 2)
					{
						((wxStaticText*)obj)->SetPosition(wxPoint(x, y));
					}
				}
				break;
			}
		}
	}
}