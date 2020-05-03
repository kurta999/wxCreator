#include "main_frame.h"
#include <wx/valnum.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>
#include <wx/richtooltip.h>
#include <wx/clipbrd.h>
#include <wx/richmsgdlg.h>
#include <wx/aui/aui.h>
#include <wx/filepicker.h>
#include <wx/tglbtn.h>
#include <wx/socket.h>
#include <any>
#include <wx/aui/aui.h>
#include <wx/dataview.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/aui/aui.h>
#include "wx/treelist.h"
#include "wx/treectrl.h"
#include <wx/dirctrl.h>
#include "magic_enum.hpp"
#include <wx/xml/xml.h>

constexpr int WINDOW_SIZE_X = 1280;
constexpr int WINDOW_SIZE_Y = 1024;

enum
{
	PGID = 1,
	ID_Hello = 2,
	ID_wxSpinCltrDouble,
	ID_wxSearchCtrl,
	ID_wxFontPickerCtrl,
	ID_wxFilePickerCtrl,
	ID_wxDirPickerCtrl,
	ID_wxDatePickerCtrl,
	ID_wxTimePickerCtrl,
	ID_wxCalendarCtrl,
	ID_wxGenericDirCtrl,
	ID_wxSpinButton,
	TreeTest_Ctrl
};

static const wxString button_style_flags[] = {
	"wxBORDER_NONE",
	"wxBU_BOTTOM",
	"wxBU_EXACTFIT",
	"wxBU_LEFT",
	"wxBU_NOTEXT",
	"wxBU_RIGHT",
	"wxBU_TOP",
};
static const long button_style_values[] = {
	wxBORDER_NONE,
	wxBU_BOTTOM,
	wxBU_EXACTFIT,
	wxBU_LEFT,
	wxBU_NOTEXT,
	wxBU_RIGHT,
	wxBU_TOP,
};

static const wxString slider_style_flags[] = {
	"wxSL_AUTOTICKS",
	"wxSL_BOTH",
	"wxSL_BOTTOM",
	"wxSL_HORIZONTAL",
	"wxSL_INVERSE",
	"wxSL_LABELS",
	"wxSL_LEFT",
	"wxSL_MIN_MAX_LABELS",
	"wxSL_RIGHT",
	"wxSL_SELRANGE",
	"wxSL_TOP",
	"wxSL_VALUE_LABEL",
	"wxSL_VERTICAL",
};
static const long slider_style_values[] = {
	wxSL_AUTOTICKS,
	wxSL_BOTH,
	wxSL_BOTTOM,
	wxSL_HORIZONTAL,
	wxSL_INVERSE,
	wxSL_LABELS,
	wxSL_LEFT,
	wxSL_MIN_MAX_LABELS,
	wxSL_RIGHT,
	wxSL_SELRANGE,
	wxSL_TOP,
	wxSL_VALUE_LABEL,
	wxSL_VERTICAL,
};

static const wxString statictext_style_flags[] = {
	"wxALIGN_CENTER_HORIZONTAL",
	"wxALIGN_LEFT",
	"wxALIGN_RIGHT",
	"wxST_ELLIPSIZE_END",
	"wxST_ELLIPSIZE_MIDDLE",
	"wxST_ELLIPSIZE_START",
	"wxST_NO_AUTORESIZE",
};
static const long statictext_style_values[] = {
	wxALIGN_CENTER_HORIZONTAL,
	wxALIGN_LEFT,
	wxALIGN_RIGHT,
	wxST_ELLIPSIZE_END,
	wxST_ELLIPSIZE_MIDDLE,
	wxST_ELLIPSIZE_START,
	wxST_NO_AUTORESIZE,
};

static const wxString textctrl_style_flags[] = {
	"wxTE_AUTO_URL",
	"wxTE_BESTWRAP",
	"wxTE_CAPITALIZE",
	"wxTE_CENTER",
	"wxTE_CHARWRAP",
	"wxTE_DONTWRAP",
	"wxTE_LEFT",
	"wxTE_MULTILINE",
	"wxTE_NOHIDESEL",
	"wxTE_NO_VSCROLL",
	"wxTE_PASSWORD",
	"wxTE_PROCESS_ENTER",
	"wxTE_PROCESS_TAB",
	"wxTE_READONLY",
	"wxTE_RICH",
	"wxTE_RICH2",
	"wxTE_RIGHT",
	"wxTE_WORDWRAP",
};
static const long textctrl_style_values[] = {
	wxHSCROLL,
	wxTE_AUTO_URL,
	wxTE_BESTWRAP,
	wxTE_CAPITALIZE,
	wxTE_CENTER,
	wxTE_CHARWRAP,
	wxTE_DONTWRAP,
	wxTE_LEFT,
	wxTE_MULTILINE,
	wxTE_NOHIDESEL,
	wxTE_NO_VSCROLL,
	wxTE_PASSWORD,
	wxTE_PROCESS_ENTER,
	wxTE_PROCESS_TAB,
	wxTE_READONLY,
	wxTE_RICH,
	wxTE_RICH2,
	wxTE_RIGHT,
	wxTE_WORDWRAP,
};

static const wxString combobox_style_flags[] = {
	"wxCB_DROPDOWN",
	"wxCB_READONLY",
	"wxCB_SIMPLE",
	"wxCB_SORT",
	"wxTE_PROCESS_ENTER",
};
static const long combobox_style_values[] = {
	wxCB_DROPDOWN,
	wxCB_READONLY,
	wxCB_SIMPLE,
	wxCB_SORT,
	wxTE_PROCESS_ENTER,
};

static const wxString choice_style_flags[] = {
	"wxCB_SORT",
};
static const long choice_style_values[] = {
	wxCB_SORT
};

static const wxString checkbox_style_flags[] = {
	"wxALIGN_RIGHT",
	"wxCHK_2STATE",
	"wxCHK_3STATE",
	"wxCHK_ALLOW_3RD_STATE_FOR_USER",
};
static const long checkbox_style_values[] = {
	wxALIGN_RIGHT,
	wxCHK_2STATE,
	wxCHK_3STATE,
	wxCHK_ALLOW_3RD_STATE_FOR_USER,
};

static const wxString gauge_style_flags[] = {
	"wxGA_HORIZONTAL",
	"wxGA_SMOOTH",
	"wxGA_VERTICAL",
};
static const long gauge_style_values[] = {
	wxGA_HORIZONTAL,
	wxGA_SMOOTH,
	wxGA_VERTICAL,
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_SIZE(MyFrame::OnSize)
EVT_MENU(ID_Hello, MyFrame::OnHelp)
EVT_MENU(wxID_OPEN, MyFrame::OnOpen)
EVT_MENU(wxID_SAVE, MyFrame::OnSave)
EVT_MENU(wxID_SAVEAS, MyFrame::OnSaveAs)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(MyPanel, wxPanel)
EVT_MOTION(MyPanel::OnMouseMotion)
EVT_LEFT_DOWN(MyPanel::OnMouseLeftDown)
EVT_ENTER_WINDOW(MyPanel::OnMouseEnter)
EVT_LEAVE_WINDOW(MyPanel::OnMouseLeave)
EVT_PG_CHANGED(PGID, MyPanel::OnPropertyGridChange)
EVT_PAINT(MyPanel::OnPaint)
EVT_TREE_SEL_CHANGED(TreeTest_Ctrl, MyPanel::OnListCtrlSelChanged)
wxEND_EVENT_TABLE()

uint16_t wx_list[static_cast<int>(wxTypes::Maximum)];
std::unordered_map<void*, ObjectStructure*> objects;
wxAuiNotebook* ctrl;
wxString file_path;

template <class T> wxString GetNameFromEnum(T to_get)
{
	char ret[32];
	auto color_name = magic_enum::enum_name(to_get);
	memcpy(ret, color_name.data(), color_name.length());
	ret[color_name.length()] = 0;
	wxString str(ret);
	return str;
}

void* GetWidgetByName(wxString& strName)
{
	for (auto x : objects)
	{
		if (x.second->name == strName)
			return x.first;
	}
	return nullptr;
}

void* GetWidgetByItemID(wxTreeItemId id)
{
	for (auto x : objects)
	{
		if (x.second->item_id == id)
			return x.first;
	}
	return nullptr;
}

void MyFrame::OnSize(wxSizeEvent& size)
{
	if (panel && panel->m_Log)
		panel->m_Log->Append(wxString::Format("New panel size: %d, %d", size.GetSize().x, size.GetSize().y));
}

void MyFrame::OnHelp(wxCommandEvent& event)
{
	wxMessageBox("Click on objects in the bottom of the screen to create them.\nAfterwards click on them and move with the mouse on the screen\n\
		Re-selecting an object can be done with Left mouse button\nMove Up & Down, Left & Right with keys\nResize them with 4, 8, 6, 2", "Help");
}

void MyFrame::OnOpen(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open XML file"), "", "", "XML files (*.xml)|*.xml", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	for (auto x : objects)
	{
		if (!x.first || !x.second) continue;
		wxStaticText* t = reinterpret_cast<wxStaticText*>(x.first);
		t->Destroy();
	}
	objects.clear();
	wxString path = openFileDialog.GetPath();
	panel->LoadFromXml(path);
	file_path = path;
}

void MyFrame::OnSave(wxCommandEvent& event)
{
	if (file_path.IsEmpty())
	{
		wxFileDialog saveFileDialog(this, _("Save XML file"), "", "", "XML files (*.xml)|*.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (saveFileDialog.ShowModal() == wxID_CANCEL)
			return;
		file_path = saveFileDialog.GetPath();
	}
	SaveWidgets();
}

void MyFrame::OnSaveAs(wxCommandEvent& event)
{
	wxFileDialog saveFileDialog(this, _("Save XML file"), "", "", "XML files (*.xml)|*.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;
	file_path = saveFileDialog.GetPath();
	SaveWidgets();
}

void MyFrame::SaveWidgets(void)
{
	wxFile file;
	bool status = file.Open(file_path, wxFile::OpenMode::write);
	if (!status)
		return;
	wxString lines = "<wxCreatorXmlFile>\n";
	for (auto x : objects)
	{
		if (!x.first || !x.second) continue;

		if (x.second->type == wxTypes::Button)
		{
			wxButton* t = reinterpret_cast<wxButton*>(x.first);
			wxFont font = t->GetFont();
			lines += wxString::Format("\t<widget type=\"button\" id=\"-1\" name=\"%s\" label=\"%s\" tooltip=\"%s\" pos=\"%d,%d\" size=\"%d,%d\" min_size=\"%d,%d\" max_size=\"%d,%d\"\
 fg_color=\"%d,%d,%d\" bg_color=\"%d,%d,%d\" font=\"%d,%d,%d,%d,%d,%s\" flags=\"%d\" />\n", x.second->name, t->GetLabelText(), t->GetToolTipText(),
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, t->GetMinSize().x, t->GetMinSize().y, t->GetMaxSize().x, t->GetMaxSize().y,
				t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue(),
				t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue(), font.GetPointSize(), font.GetFamily(), font.GetStyle(), font.GetWeight(),
				font.GetUnderlined(), font.GetFaceName(), t->GetWindowStyleFlag());
		}
		else if (x.second->type == wxTypes::ComboBox)
		{
			wxComboBox* t = reinterpret_cast<wxComboBox*>(x.first);
			wxFont font = t->GetFont();
			lines += wxString::Format("\t<widget type=\"combobox\" id=\"-1\" name=\"%s\" label=\"%s\" tooltip=\"%s\" pos=\"%d,%d\" size=\"%d,%d\" min_size=\"%d,%d\" max_size=\"%d,%d\"\
 fg_color=\"%d,%d,%d\" bg_color=\"%d,%d,%d\" font=\"%d,%d,%d,%d,%d,%s\" flags=\"%d\" />\n", x.second->name, t->GetLabelText(), t->GetToolTipText(),
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, t->GetMinSize().x, t->GetMinSize().y, t->GetMaxSize().x, t->GetMaxSize().y,
				t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue(),
				t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue(), font.GetPointSize(), font.GetFamily(), font.GetStyle(), font.GetWeight(),
				font.GetUnderlined(), font.GetFaceName(), t->GetWindowStyleFlag());
		}
		else if (x.second->type == wxTypes::Choise)
		{
			wxChoice* t = reinterpret_cast<wxChoice*>(x.first);
			wxFont font = t->GetFont();
			lines += wxString::Format("\t<widget type=\"choice\" id=\"-1\" name=\"%s\" tooltip=\"%s\" pos=\"%d,%d\" size=\"%d,%d\" min_size=\"%d,%d\" max_size=\"%d,%d\"\
 fg_color=\"%d,%d,%d\" bg_color=\"%d,%d,%d\" font=\"%d,%d,%d,%d,%d,%s\" flags=\"%d\" />\n", x.second->name, t->GetToolTipText(),
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, t->GetMinSize().x, t->GetMinSize().y, t->GetMaxSize().x, t->GetMaxSize().y,
				t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue(),
				t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue(), font.GetPointSize(), font.GetFamily(), font.GetStyle(), font.GetWeight(),
				font.GetUnderlined(), font.GetFaceName(), t->GetWindowStyleFlag());
		}
		else if (x.second->type == wxTypes::ListBox)
		{
			wxListBox* t = reinterpret_cast<wxListBox*>(x.first);
			wxFont font = t->GetFont();
			lines += wxString::Format("\t<widget type=\"choice\" id=\"-1\" name=\"%s\" tooltip=\"%s\" pos=\"%d,%d\" size=\"%d,%d\" min_size=\"%d,%d\" max_size=\"%d,%d\"\
 fg_color=\"%d,%d,%d\" bg_color=\"%d,%d,%d\" font=\"%d,%d,%d,%d,%d,%s\" flags=\"%d\" />\n", x.second->name, t->GetToolTipText(),
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, t->GetMinSize().x, t->GetMinSize().y, t->GetMaxSize().x, t->GetMaxSize().y,
				t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue(),
				t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue(), font.GetPointSize(), font.GetFamily(), font.GetStyle(), font.GetWeight(),
				font.GetUnderlined(), font.GetFaceName(), t->GetWindowStyleFlag());
		}
		else if (x.second->type == wxTypes::CheckBox)
		{
			wxCheckBox* t = reinterpret_cast<wxCheckBox*>(x.first);
			wxFont font = t->GetFont();
			lines += wxString::Format("\t<widget type=\"combobox\" id=\"-1\" name=\"%s\" label=\"%s\" tooltip=\"%s\" pos=\"%d,%d\" size=\"%d,%d\" min_size=\"%d,%d\" max_size=\"%d,%d\"\
 fg_color=\"%d,%d,%d\" bg_color=\"%d,%d,%d\" font=\"%d,%d,%d,%d,%d,%s\" flags=\"%d\" />\n", x.second->name, t->GetLabelText(), t->GetToolTipText(),
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, t->GetMinSize().x, t->GetMinSize().y, t->GetMaxSize().x, t->GetMaxSize().y,
				t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue(),
				t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue(), font.GetPointSize(), font.GetFamily(), font.GetStyle(), font.GetWeight(),
				font.GetUnderlined(), font.GetFaceName(), t->GetWindowStyleFlag());
		}
		else if (x.second->type == wxTypes::RadioButton)
		{
			wxRadioButton* t = reinterpret_cast<wxRadioButton*>(x.first);
			wxFont font = t->GetFont();
			lines += wxString::Format("\t<widget type=\"combobox\" id=\"-1\" name=\"%s\" label=\"%s\" tooltip=\"%s\" pos=\"%d,%d\" size=\"%d,%d\" min_size=\"%d,%d\" max_size=\"%d,%d\"\
 fg_color=\"%d,%d,%d\" bg_color=\"%d,%d,%d\" font=\"%d,%d,%d,%d,%d,%s\" flags=\"%d\" />\n", x.second->name, t->GetLabelText(), t->GetToolTipText(),
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, t->GetMinSize().x, t->GetMinSize().y, t->GetMaxSize().x, t->GetMaxSize().y,
				t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue(),
				t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue(), font.GetPointSize(), font.GetFamily(), font.GetStyle(), font.GetWeight(),
				font.GetUnderlined(), font.GetFaceName(), t->GetWindowStyleFlag());
		}
		else if (x.second->type == wxTypes::StaticLine)
		{
			wxStaticLine* t = reinterpret_cast<wxStaticLine*>(x.first);
			wxFont font = t->GetFont();
			lines += wxString::Format("\t<widget type=\"staticline\" id=\"-1\" name=\"%s\" tooltip=\"%s\" pos=\"%d,%d\" size=\"%d,%d\" min_size=\"%d,%d\" max_size=\"%d,%d\"\
 fg_color=\"%d,%d,%d\" bg_color=\"%d,%d,%d\" font=\"%d,%d,%d,%d,%d,%s\" flags=\"%d\" />\n", x.second->name, t->GetToolTipText(),
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, t->GetMinSize().x, t->GetMinSize().y, t->GetMaxSize().x, t->GetMaxSize().y,
				t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue(),
				t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue(), font.GetPointSize(), font.GetFamily(), font.GetStyle(), font.GetWeight(),
				font.GetUnderlined(), font.GetFaceName(), t->GetWindowStyleFlag());
		}
		else if (x.second->type == wxTypes::Slider)
		{
			wxSlider* t = reinterpret_cast<wxSlider*>(x.first);
			wxFont font = t->GetFont();
			lines += wxString::Format("\t<widget type=\"slider\" id=\"-1\" name=\"%s\" tooltip=\"%s\" value=\"%d\" min=\"%d\" max=\"%d\" pos=\"%d,%d\" size=\"%d,%d\" min_size=\"%d,%d\" max_size=\"%d,%d\"\
 fg_color=\"%d,%d,%d\" bg_color=\"%d,%d,%d\" font=\"%d,%d,%d,%d,%d,%s\" flags=\"%d\" />\n", x.second->name, t->GetToolTipText(), t->GetValue(), t->GetMin(), t->GetMax(),
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, t->GetMinSize().x, t->GetMinSize().y, t->GetMaxSize().x, t->GetMaxSize().y,
				t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue(),
				t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue(), font.GetPointSize(), font.GetFamily(), font.GetStyle(), font.GetWeight(),
				font.GetUnderlined(), font.GetFaceName(), t->GetWindowStyleFlag());
		}		
		else if (x.second->type == wxTypes::Gauge)
		{
			wxGauge* t = reinterpret_cast<wxGauge*>(x.first);
			wxFont font = t->GetFont();
			lines += wxString::Format("\t<widget type=\"gauge\" id=\"-1\" name=\"%s\" tooltip=\"%s\" value=\"%d\" max=\"%d\" pos=\"%d,%d\" size=\"%d,%d\" min_size=\"%d,%d\" max_size=\"%d,%d\"\
 fg_color=\"%d,%d,%d\" bg_color=\"%d,%d,%d\" font=\"%d,%d,%d,%d,%d,%s\" flags=\"%d\" />\n", x.second->name, t->GetToolTipText(), t->GetValue(), 100,
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, t->GetMinSize().x, t->GetMinSize().y, t->GetMaxSize().x, t->GetMaxSize().y,
				t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue(),
				t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue(), font.GetPointSize(), font.GetFamily(), font.GetStyle(), font.GetWeight(),
				font.GetUnderlined(), font.GetFaceName(), t->GetWindowStyleFlag());
		}
		else if (x.second->type == wxTypes::SpinControl)
		{
			wxSpinCtrl* t = reinterpret_cast<wxSpinCtrl*>(x.first);
			wxFont font = t->GetFont();
			lines += wxString::Format("\t<widget type=\"spincontrol\" id=\"-1\" name=\"%s\" tooltip=\"%s\" value=\"%d\" min=\"%d\" max=\"%d\" pos=\"%d,%d\" size=\"%d,%d\" min_size=\"%d,%d\" max_size=\"%d,%d\"\
 fg_color=\"%d,%d,%d\" bg_color=\"%d,%d,%d\" font=\"%d,%d,%d,%d,%d,%s\" flags=\"%d\" />\n", x.second->name, t->GetToolTipText(), t->GetValue(), t->GetMin(), t->GetMax(),
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, t->GetMinSize().x, t->GetMinSize().y, t->GetMaxSize().x, t->GetMaxSize().y,
				t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue(),
				t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue(), font.GetPointSize(), font.GetFamily(), font.GetStyle(), font.GetWeight(),
				font.GetUnderlined(), font.GetFaceName(), t->GetWindowStyleFlag());
		}
		else if (x.second->type == wxTypes::SpinCtrlDouble)
		{
			wxSpinCtrlDouble* t = reinterpret_cast<wxSpinCtrlDouble*>(x.first);
			wxFont font = t->GetFont();
			lines += wxString::Format("\t<widget type=\"spincontroldouble\" id=\"-1\" name=\"%s\" tooltip=\"%s\" value=\"%d\" min=\"%d\" max=\"%d\" inc=\"%d\" pos=\"%d,%d\" size=\"%d,%d\" min_size=\"%d,%d\" max_size=\"%d,%d\"\
 fg_color=\"%d,%d,%d\" bg_color=\"%d,%d,%d\" font=\"%d,%d,%d,%d,%d,%s\" flags=\"%d\" />\n", x.second->name, t->GetToolTipText(), t->GetValue(), t->GetMin(), t->GetMax(), t->GetIncrement(),
				t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, t->GetMinSize().x, t->GetMinSize().y, t->GetMaxSize().x, t->GetMaxSize().y,
				t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue(),
				t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue(), font.GetPointSize(), font.GetFamily(), font.GetStyle(), font.GetWeight(),
				font.GetUnderlined(), font.GetFaceName(), t->GetWindowStyleFlag());
		}
		else if (x.second->type == wxTypes::TextControl)
		{
			wxTextCtrl* t = reinterpret_cast<wxTextCtrl*>(x.first);
			wxFont font = t->GetFont();
			lines += wxString::Format("\t<widget type=\"textcontrol\" id=\"-1\" name=\"%s\" label=\"%s\" tooltip=\"%s\" pos=\"%d,%d\" size=\"%d,%d\" min_size=\"%d,%d\" max_size=\"%d,%d\"\
 fg_color=\"%d,%d,%d\" bg_color=\"%d,%d,%d\" font=\"%d,%d,%d,%d,%d,%s\" flags=\"%d\" />\n", x.second->name, t->GetLabelText(), t->GetToolTipText(),
			t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, t->GetMinSize().x, t->GetMinSize().y, t->GetMaxSize().x, t->GetMaxSize().y,
			t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue(),
			t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue(), font.GetPointSize(), font.GetFamily(), font.GetStyle(), font.GetWeight(),
			font.GetUnderlined(), font.GetFaceName(), t->GetWindowStyleFlag());
		}
		else if (x.second->type == wxTypes::ToggleButton)
		{
			wxToggleButton* t = reinterpret_cast<wxToggleButton*>(x.first);
			wxFont font = t->GetFont();
			lines += wxString::Format("\t<widget type=\"togglebutton\" id=\"-1\" name=\"%s\" label=\"%s\" tooltip=\"%s\" pos=\"%d,%d\" size=\"%d,%d\" min_size=\"%d,%d\" max_size=\"%d,%d\"\
 fg_color=\"%d,%d,%d\" bg_color=\"%d,%d,%d\" font=\"%d,%d,%d,%d,%d,%s\" flags=\"%d\" />\n", x.second->name, t->GetLabelText(), t->GetToolTipText(),
			t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, t->GetMinSize().x, t->GetMinSize().y, t->GetMaxSize().x, t->GetMaxSize().y,
			t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue(),
			t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue(), font.GetPointSize(), font.GetFamily(), font.GetStyle(), font.GetWeight(),
			font.GetUnderlined(), font.GetFaceName(), t->GetWindowStyleFlag());
		}
		else if (x.second->type == wxTypes::Text)
		{
			wxToggleButton* t = reinterpret_cast<wxToggleButton*>(x.first);
			wxFont font = t->GetFont();
			lines += wxString::Format("\t<widget type=\"togglebutton\" id=\"-1\" name=\"%s\" label=\"%s\" tooltip=\"%s\" pos=\"%d,%d\" size=\"%d,%d\" min_size=\"%d,%d\" max_size=\"%d,%d\"\
 fg_color=\"%d,%d,%d\" bg_color=\"%d,%d,%d\" font=\"%d,%d,%d,%d,%d,%s\" flags=\"%d\" />\n", x.second->name, t->GetLabelText(), t->GetToolTipText(),
			t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, t->GetMinSize().x, t->GetMinSize().y, t->GetMaxSize().x, t->GetMaxSize().y,
			t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue(),
			t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue(), font.GetPointSize(), font.GetFamily(), font.GetStyle(), font.GetWeight(),
			font.GetUnderlined(), font.GetFaceName(), t->GetWindowStyleFlag());
		}
	}
	lines += "</wxCreatorXmlFile>\n";
	file.Write(lines);
	file.Close();
}

void MyFrame::AddFlags(wxString& wxstr, void* widget, ObjectStructure* obj, const long* to_pointer, const wxString* to_pointer_str, const long max_array_size)
{
	wxStaticText* t = reinterpret_cast<wxStaticText*>(widget);
	int counter = 0;
	for (uint8_t i = 0; i != max_array_size; i++)
	{
		if (t->GetWindowStyleFlag() & to_pointer[i])
		{
			if (counter)
				wxstr += " | ";
			wxstr += to_pointer_str[i];
			counter++;
		}
	}
	if (wxstr.IsEmpty())
		wxstr = "0";
}

void MyFrame::AddFontAndColor(wxString& wxstr, void* widget, ObjectStructure* obj)
{
	wxStaticText* t = reinterpret_cast<wxStaticText*>(widget);
	wxString tooltip = t->GetToolTipText();
	if(!tooltip.IsEmpty())
		wxstr += wxString::Format("%s->SetToolTip(\"%s\");\n", obj->name, tooltip);
	if(obj->fg_color_changed)
		wxstr += wxString::Format("%s->SetForegroundColour(wxColour(%d, %d, %d));\n",
			obj->name, t->GetForegroundColour().Red(), t->GetForegroundColour().Green(), t->GetForegroundColour().Blue());
	if(obj->bg_color_changed)
		wxstr += wxString::Format("%s->SetBackgroundColour(wxColour(%d, %d, %d));\n",
			obj->name, t->GetBackgroundColour().Red(), t->GetBackgroundColour().Green(), t->GetBackgroundColour().Blue());
	wxSize min_size = t->GetMinSize();
	if(min_size.x != -1 || min_size.y != -1)
		wxstr += wxString::Format("%s->SetMinSize(wxPoint(%d, %d));\n", obj->name, min_size.x, min_size.y);
	wxSize max_size = t->GetMaxSize();
	if(max_size.x != -1 || max_size.y != -1)
		wxstr += wxString::Format("%s->SetMaxSize(wxPoint(%d, %d));\n", obj->name, max_size.x, max_size.y);
	wxFont font = t->GetFont();
	wxString strFontPointSize;
	if (font.GetPointSize() != -1)
		strFontPointSize = wxString::Format("%d", font.GetPointSize());
	else
		strFontPointSize = wxString("wxNORMAL_FONT->GetPointSize()");
	if (font.GetFamily() != wxFONTFAMILY_DEFAULT || !font.GetFaceName().IsEmpty() || font.GetStyle() != wxFONTSTYLE_NORMAL || font.GetWeight() != wxFONTWEIGHT_NORMAL
		|| font.GetUnderlined())
	{
		wxFontWeight a = font.GetWeight();
		wxstr += wxString::Format("%s->SetFont( wxFont(%s, %s, %s, %s, %s, wxT(\"%s\")));\n",
			obj->name, strFontPointSize, GetNameFromEnum<wxFontFamily>(font.GetFamily()), GetNameFromEnum<wxFontStyle>(font.GetStyle()),
			GetNameFromEnum<wxFontWeight>(a),
			font.GetUnderlined() ? wxString("true") : wxString("false"), font.GetFaceName());
		Sleep(10);
	}
	wxstr += "\n";
}

void MyFrame::Changeing(wxAuiNotebookEvent& event)
{
	wxString str;
	for (auto x : objects)
	{
		if (!x.first || !x.second) continue;
		if (x.second->type == wxTypes::Button)
		{
			wxStaticText* t = reinterpret_cast<wxStaticText*>(x.first);
			wxString flagsStr;
			AddFlags(flagsStr, x.first, x.second, button_style_values, button_style_flags, WXSIZEOF(button_style_flags));
			str += wxString::Format("%s = new wxButton(this, wxID_ANY, wxT(\"%s\"), wxPoint(%d, %d), wxSize(%d, %d), %s);\n",
				x.second->name, t->GetLabelText(), t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y, flagsStr);
			AddFontAndColor(str, x.first, x.second);
		}		
		if (x.second->type == wxTypes::Text)
		{
			wxStaticText* t = reinterpret_cast<wxStaticText*>(x.first);
			wxString flagsStr;
			AddFlags(flagsStr, x.first, x.second, statictext_style_values, statictext_style_flags, WXSIZEOF(statictext_style_values));
			str += wxString::Format("%s = new wxStaticText(this, wxID_ANY, wxT(\"%s\"), wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				x.second->name, t->GetLabelText(), t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}		
		if (x.second->type == wxTypes::ComboBox)
		{
			wxComboBox* t = reinterpret_cast<wxComboBox*>(x.first);
			wxString flagsStr;
			AddFlags(flagsStr, x.first, x.second, combobox_style_values, combobox_style_flags, WXSIZEOF(combobox_style_values));
			str += wxString::Format("%s = new wxComboBox(this, wxID_ANY, wxT(\"%s\"), wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				x.second->name, t->GetLabelText(), t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}
		if (x.second->type == wxTypes::Choise)
		{
			wxChoice* t = reinterpret_cast<wxChoice*>(x.first);
			str += wxString("wxArrayString m_choiceChoices;\n");
			wxString flagsStr;
			AddFlags(flagsStr, x.first, x.second, choice_style_values, choice_style_flags, WXSIZEOF(choice_style_values));
			str += wxString::Format("%s = new wxChoice(this, wxID_ANY, wxPoint(%d, %d), wxSize(%d, %d), m_choiceChoices, 0);\n", 
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			str += wxString::Format("%s->SetSelection(0);\n", x.second->name);
			AddFontAndColor(str, x.first, x.second);
		}
		if (x.second->type == wxTypes::ListBox)
		{
			wxListBox* t = reinterpret_cast<wxListBox*>(x.first);
			str += wxString::Format("%s = new wxListBox(this, wxID_ANY, wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}		
		if (x.second->type == wxTypes::CheckBox)
		{
			wxCheckBox* t = reinterpret_cast<wxCheckBox*>(x.first);
			wxString flagsStr;
			AddFlags(flagsStr, x.first, x.second, checkbox_style_values, checkbox_style_flags, WXSIZEOF(checkbox_style_values));
			str += wxString::Format("%s = new wxCheckBox(this, wxID_ANY, wxT(\"%s\"), wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				x.second->name, t->GetLabelText(), t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}		
		if (x.second->type == wxTypes::StaticLine)
		{
			wxStaticLine* t = reinterpret_cast<wxStaticLine*>(x.first);
			//wxString flagsStr;
			//AddFlags(flagsStr, x.first, x.second, checkbox_style_values, checkbox_style_flags, WXSIZEOF(checkbox_style_values));
			str += wxString::Format("%s = new wxStaticLine(this, wxID_ANY, wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}
		if (x.second->type == wxTypes::Slider)
		{
			wxSlider* t = reinterpret_cast<wxSlider*>(x.first);
			wxString flagsStr;
			AddFlags(flagsStr, x.first, x.second, slider_style_values, slider_style_flags, WXSIZEOF(slider_style_values));
			str += wxString::Format("%s = new wxSlider(this, wxID_ANY, %d, %d, %d, wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				x.second->name, 0, t->GetMin(), t->GetMax(), t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}		
		if (x.second->type == wxTypes::Gauge)
		{
			wxGauge* t = reinterpret_cast<wxGauge*>(x.first);
			wxString flagsStr;
			AddFlags(flagsStr, x.first, x.second, gauge_style_values, gauge_style_flags, WXSIZEOF(gauge_style_values));
			str += wxString::Format("%s = new wxGauge(this, wxID_ANY, 100, wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}		
		if (x.second->type == wxTypes::SpinControl)
		{
			wxSpinCtrl* t = reinterpret_cast<wxSpinCtrl*>(x.first);
			str += wxString::Format("%s = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(%d, %d), wxSize(%d, %d), wxSP_ARROW_KEYS, 1, 255, 1);\n", 
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}		
		if (x.second->type == wxTypes::TextControl)
		{
			wxTextCtrl* t = reinterpret_cast<wxTextCtrl*>(x.first);
			wxString flagsStr;
			AddFlags(flagsStr, x.first, x.second, textctrl_style_values, textctrl_style_flags, WXSIZEOF(textctrl_style_values));
			str += wxString::Format("%s = new wxTextCtrl(this, wxID_ANY, wxT(\"%s\"), wxPoint(%d, %d), 0);\n", 
				x.second->name, t->GetLabelText(), t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}		
		if (x.second->type == wxTypes::ToggleButton)
		{
			wxToggleButton* t = reinterpret_cast<wxToggleButton*>(x.first);
			str += wxString::Format("%s = new wxToggleButton(this, wxID_ANY, wxT(\"%s\"), wxPoint(%d, %d), 0);\n", 
				x.second->name, t->GetLabelText(), t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}	
		if (x.second->type == wxTypes::SpinCtrlDouble)
		{
			wxSpinCtrlDouble* t = reinterpret_cast<wxSpinCtrlDouble*>(x.first);
			str += wxString::Format("%s = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(%d, %d), wxSize(%d, %d), wxSP_ARROW_KEYS, 0, 100, 0, 1);\n", 
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}	
		if (x.second->type == wxTypes::SearchCtrl)
		{
			wxSearchCtrl* t = reinterpret_cast<wxSearchCtrl*>(x.first);
			str += wxString::Format("%s = new wxSearchCtrl(this, wxID_ANY, wxEmptyString, wxPoint(%d, %d), wxSize(%d, %d), 0);\n", 
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}
		if (x.second->type == wxTypes::FontPicker)
		{
			wxFontPickerCtrl* t = reinterpret_cast<wxFontPickerCtrl*>(x.first);
			str += wxString::Format("%s = new wxFontPickerCtrl(this, wxID_ANY, wxNullFont, xPoint(%d, %d), wxSize(%d, %d), wxFNTP_DEFAULT_STYLE);\n", 
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}	
		if (x.second->type == wxTypes::FilePicker)
		{
			wxFilePickerCtrl* t = reinterpret_cast<wxFilePickerCtrl*>(x.first);
			str += wxString::Format("%s = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, wxT(\"Select a file\"), wxT(\"*.*\"), wxPoint(%d, %d), wxSize(%d, %d), wxFLP_DEFAULT_STYLE);\n",
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}	
		if (x.second->type == wxTypes::DirPicker)
		{
			wxDirPickerCtrl* t = reinterpret_cast<wxDirPickerCtrl*>(x.first);
			str += wxString::Format("%s = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, wxT(\"Select a folder\"), wxPoint(%d, %d), wxSize(%d, %d), wxDIRP_DEFAULT_STYLE);\n",
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}	
		if (x.second->type == wxTypes::DatePicker)
		{
			wxDatePickerCtrl* t = reinterpret_cast<wxDatePickerCtrl*>(x.first);
			str += wxString::Format("%s = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxPoint(%d, %d), wxSize(%d, %d), wxDP_DEFAULT);\n",
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}	
		if (x.second->type == wxTypes::TimePicker)
		{
			wxTimePickerCtrl* t = reinterpret_cast<wxTimePickerCtrl*>(x.first);
			str += wxString::Format("%s = new wxTimePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxPoint(%d, %d), wxSize(%d, %d), wxTP_DEFAULT);\n",
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}	
		if (x.second->type == wxTypes::CalendarCtrl)
		{
			wxCalendarCtrl* t = reinterpret_cast<wxCalendarCtrl*>(x.first);
			str += wxString::Format("%s = new wxCalendarCtrl(this, wxID_ANY, wxDefaultDateTime, wxPoint(%d, %d), wxSize(%d, %d), wxCAL_SHOW_HOLIDAYS);\n",
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}			
		if (x.second->type == wxTypes::GenericDirCtrl)
		{
			wxGenericDirCtrl* t = reinterpret_cast<wxGenericDirCtrl*>(x.first);
			str += wxString::Format("%s = new wxGenericDirCtrl(this, wxID_ANY, wxEmptyString, wxPoint(%d, %d), wxSize(%d, %d), wxDIRCTRL_3D_INTERNAL | wxSUNKEN_BORDER, wxEmptyString, 0);\n",
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}
		if (x.second->type == wxTypes::SpinButton)
		{
			wxSpinButton* t = reinterpret_cast<wxSpinButton*>(x.first);
			str += wxString::Format("%s = new wxSpinButton(this, wxID_ANY, wxPoint(%d, %d), wxSize(%d, %d), 0);\n",
				x.second->name, t->GetPosition().x, t->GetPosition().y, t->GetSize().x, t->GetSize().y);
			AddFontAndColor(str, x.first, x.second);
		}
	}
	cpp_panel->m_StyledTextCtrl->ClearAll();
	cpp_panel->m_StyledTextCtrl->AddText(str);
}

void MyFrame::OnMenuItemSelected(wxCommandEvent& event)
{
	int a = event.GetId();
	switch (event.GetId())
	{
		case ID_wxSpinCltrDouble:
		{
			panel->m_Log->Append(wxString::Format("Clicked on wxSpinCtrlDouble"));

			void* tmp = new wxSpinCtrlDouble(panel, wxID_ANY, wxEmptyString, wxPoint(0, 70), wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0, 1);
			objects[tmp] = new ObjectStructure(panel, tmp, wxTypes::SpinCtrlDouble);
			break;
		}
		case ID_wxSearchCtrl:
		{
			panel->m_Log->Append(wxString::Format("Clicked on wxSearchCtrl"));

			void* tmp = new wxSearchCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(0, 70), wxDefaultSize, 0);
			objects[tmp] = new ObjectStructure(panel, tmp, wxTypes::SearchCtrl);
#ifndef __WXMAC__
			((wxSearchCtrl*)(tmp))->ShowSearchButton(true);
#endif
			((wxSearchCtrl*)(tmp))->ShowCancelButton(false);
			break;
		}
		case ID_wxFontPickerCtrl:
		{
			panel->m_Log->Append(wxString::Format("Clicked on wxFontPickerCtrl"));

			void* tmp = new wxFontPickerCtrl(panel, wxID_ANY, wxNullFont, wxPoint(0, 70), wxDefaultSize, wxFNTP_DEFAULT_STYLE);
			objects[tmp] = new ObjectStructure(panel, tmp, wxTypes::FontPicker);
			((wxFontPickerCtrl*)(tmp))->SetMaxPointSize(100);
			break;
		}
		case ID_wxFilePickerCtrl:
		{
			panel->m_Log->Append(wxString::Format("Clicked on wxFilePickerCtrl"));

			void* tmp = new wxFilePickerCtrl(panel, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxPoint(0, 70), wxDefaultSize, wxFLP_DEFAULT_STYLE);
			objects[tmp] = new ObjectStructure(panel, tmp, wxTypes::FilePicker);
			break;
		}
		case ID_wxDirPickerCtrl:
		{
			panel->m_Log->Append(wxString::Format("Clicked on wxDirPickerCtrl"));

			void* tmp = new wxDirPickerCtrl(panel, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxPoint(0, 70), wxDefaultSize, wxDIRP_DEFAULT_STYLE);
			objects[tmp] = new ObjectStructure(panel, tmp, wxTypes::DirPicker);
			break;
		}
		case ID_wxDatePickerCtrl:
		{
			panel->m_Log->Append(wxString::Format("Clicked on wxDatePickerCtrl"));

			void* tmp = new wxDatePickerCtrl(panel, wxID_ANY, wxDefaultDateTime, wxPoint(0, 70), wxDefaultSize, wxDP_DEFAULT);
			objects[tmp] = new ObjectStructure(panel, tmp, wxTypes::DatePicker);			
			break;
		}
		case ID_wxTimePickerCtrl:
		{
			panel->m_Log->Append(wxString::Format("Clicked on wxTimePickerCtrl"));

			void* tmp = new wxTimePickerCtrl(panel, wxID_ANY, wxDefaultDateTime, wxPoint(0, 70), wxDefaultSize, wxTP_DEFAULT);
			objects[tmp] = new ObjectStructure(panel, tmp, wxTypes::TimePicker);
			break;
		}
		case ID_wxCalendarCtrl:
		{
			panel->m_Log->Append(wxString::Format("Clicked on wxCalendarCtrl"));

			void* tmp = new wxCalendarCtrl(panel, wxID_ANY, wxDefaultDateTime, wxPoint(0, 70), wxDefaultSize, wxCAL_SHOW_HOLIDAYS);
			objects[tmp] = new ObjectStructure(panel, tmp, wxTypes::CalendarCtrl);
			break;
		}
		case ID_wxGenericDirCtrl:
		{
			panel->m_Log->Append(wxString::Format("Clicked on wxGenericDirCtrl"));

			void* tmp = new wxGenericDirCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(0, 70), wxDefaultSize, wxDIRCTRL_3D_INTERNAL | wxSUNKEN_BORDER, wxEmptyString, 0);
			objects[tmp] = new ObjectStructure(panel, tmp, wxTypes::GenericDirCtrl);
			break;
		}
		case ID_wxSpinButton:
		{
			panel->m_Log->Append(wxString::Format("Clicked on wxGenericDirCtrl"));

			void* tmp = new wxSpinButton(panel, wxID_ANY, wxPoint(0, 70), wxDefaultSize, 0);
			objects[tmp] = new ObjectStructure(panel, tmp, wxTypes::SpinButton);
			break;
		}

	}
}

MyFrame::MyFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition,
		wxSize(WINDOW_SIZE_X, WINDOW_SIZE_Y))
{
	m_mgr.SetManagedWindow(this);
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_OPEN, "&Open file\tCtrl-O", "Open file");
	menuFile->Append(wxID_SAVE, "&Save file\tCtrl-S", "Save file");
	menuFile->Append(wxID_SAVEAS, "&Save file As\tCtrl-S", "Save file As other");
	menuFile->Append(ID_Hello, "&Read help\tCtrl-H", "Read description about this program");
	menuFile->Append(wxID_EXIT);
	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	SetMenuBar(menuBar);

	CreateStatusBar();
	SetStatusText("Welcome in wxCreator v0.2");

	const wxIcon icon(wxT("./icon.ico"), wxBITMAP_TYPE_ICO);
	SetIcon(icon);
	wxAuiToolBar* tb5 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxSize(25, 25), wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW | wxAUI_TB_VERTICAL);
	tb5->SetToolBitmapSize(FromDIP(wxSize(25, 25)));
	tb5->AddTool(ID_wxSpinCltrDouble, "wxSpinCltrDouble", wxArtProvider::GetBitmap(wxART_INFORMATION), "SpinCltrDouble");
	tb5->AddTool(ID_wxSearchCtrl, "wxSearchCtrl", wxArtProvider::GetBitmap(wxART_CDROM), "wxSearchCtrl");
	tb5->AddTool(ID_wxFontPickerCtrl, "wxFontPickerCtrl", wxArtProvider::GetBitmap(wxART_FILE_SAVE), "wxFontPickerCtrl");
	tb5->AddTool(ID_wxFilePickerCtrl, "wxFilePickerCtrl", wxArtProvider::GetBitmap(wxART_MISSING_IMAGE), "wxFilePickerCtrl");
	tb5->AddTool(ID_wxDirPickerCtrl, "wxDirPickerCtrl", wxArtProvider::GetBitmap(wxART_MISSING_IMAGE), "wxDirPickerCtrl");
	tb5->AddTool(ID_wxDatePickerCtrl, "wxDatePickerCtrl", wxArtProvider::GetBitmap(wxART_MISSING_IMAGE), "wxDatePickerCtrl");
	tb5->AddTool(ID_wxTimePickerCtrl, "wxTimePickerCtrl", wxArtProvider::GetBitmap(wxART_MISSING_IMAGE), "wxTimePickerCtrl");
	tb5->AddTool(ID_wxCalendarCtrl, "wxCalendarCtrl", wxArtProvider::GetBitmap(wxART_MISSING_IMAGE), "wxCalendarCtrl");
	tb5->AddTool(ID_wxGenericDirCtrl, "wxGenericDirCtrl", wxArtProvider::GetBitmap(wxART_MISSING_IMAGE), "wxGenericDirCtrl");
	tb5->AddTool(ID_wxSpinButton, "wxSpinButton", wxArtProvider::GetBitmap(wxART_MISSING_IMAGE), "wxSpinButton");
	tb5->Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&MyFrame::OnMenuItemSelected, NULL, this);

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

wxPGProperty* m_pgType;
wxPGProperty* m_pgId;
wxPGProperty* m_pgName;
wxPGProperty* m_pgLabel;
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
wxPGProperty* m_pgButtonStyle;
wxPGProperty* m_pgSliderStyle;
wxPGProperty* m_pgStaticTextStyle;
wxPGProperty* m_pgTextCtrlStyle;
wxPGProperty* m_pgComboBoxStyle;
wxPGProperty* m_pgChoiseStyle;
wxPGProperty* m_pgCheckboxStyle;
wxPGProperty* m_pgGaugeStyle;
wxPropertyGrid* m_propertyGrid;


class PropertyGrid
{
public:
	//PropertyGrid() { }
	PropertyGrid(MyPanel* parent, int id, wxString pos, wxString size, wxColour color)
	{
		m_propertyGrid = new wxPropertyGrid(parent, PGID, wxPoint(850, 300), wxSize(300, 1000), wxPG_DEFAULT_STYLE);
		wxPGProperty* pid = m_propertyGrid->Append(new wxPropertyCategory("wxCreator Item"));
		pid->SetValue("Value");


		m_pgType = m_propertyGrid->Append(new wxStringProperty(wxT("Type"), wxPG_LABEL));
		m_propertyGrid->DisableProperty("Type");

		m_pgId = m_propertyGrid->Append(new wxIntProperty(wxT("ID"), wxPG_LABEL, id));
		m_pgName = m_propertyGrid->Append(new wxStringProperty(wxT("Name"), wxPG_LABEL));
		m_pgLabel = m_propertyGrid->Append(new wxStringProperty(wxT("Label"), wxPG_LABEL));
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

		wxPGChoices m_combinedFlags;
		m_combinedFlags.Add(WXSIZEOF(button_style_flags), button_style_flags, button_style_values);
		m_pgButtonStyle = m_propertyGrid->Append(new wxFlagsProperty(wxT("Button flags"), wxPG_LABEL, m_combinedFlags));
		m_propertyGrid->SetPropertyAttribute("Button flags", wxPG_BOOL_USE_CHECKBOX, true, wxPG_RECURSE);

		wxPGChoices m_combinedFlags2;
		m_combinedFlags2.Add(WXSIZEOF(slider_style_flags), slider_style_flags, slider_style_values);
		m_pgSliderStyle = m_propertyGrid->Append(new wxFlagsProperty(wxT("Slider flags"), wxPG_LABEL, m_combinedFlags2));
		m_propertyGrid->SetPropertyAttribute("Slider flags", wxPG_BOOL_USE_CHECKBOX, true, wxPG_RECURSE);
		
		wxPGChoices m_combinedFlags3;
		m_combinedFlags3.Add(WXSIZEOF(statictext_style_flags), statictext_style_flags, statictext_style_values);
		m_pgStaticTextStyle = m_propertyGrid->Append(new wxFlagsProperty(wxT("StaticText flags"), wxPG_LABEL, m_combinedFlags3));
		m_propertyGrid->SetPropertyAttribute("StaticText flags", wxPG_BOOL_USE_CHECKBOX, true, wxPG_RECURSE);
		
		wxPGChoices m_combinedFlags4;
		m_combinedFlags4.Add(WXSIZEOF(textctrl_style_flags), textctrl_style_flags, textctrl_style_values);
		m_pgTextCtrlStyle = m_propertyGrid->Append(new wxFlagsProperty(wxT("TextControl flags"), wxPG_LABEL, m_combinedFlags4));
		m_propertyGrid->SetPropertyAttribute("TextControl flags", wxPG_BOOL_USE_CHECKBOX, true, wxPG_RECURSE);
		
		wxPGChoices m_combinedFlags5;
		m_combinedFlags5.Add(WXSIZEOF(combobox_style_flags), combobox_style_flags, combobox_style_values);
		m_pgComboBoxStyle = m_propertyGrid->Append(new wxFlagsProperty(wxT("ComboBox flags"), wxPG_LABEL, m_combinedFlags5));
		m_propertyGrid->SetPropertyAttribute("ComboBox flags", wxPG_BOOL_USE_CHECKBOX, true, wxPG_RECURSE);

		wxPGChoices m_combinedFlags6;
		m_combinedFlags6.Add(WXSIZEOF(choice_style_flags), choice_style_flags, choice_style_values);
		m_pgChoiseStyle = m_propertyGrid->Append(new wxFlagsProperty(wxT("Choice flags"), wxPG_LABEL, m_combinedFlags6));
		m_propertyGrid->SetPropertyAttribute("Choice flags", wxPG_BOOL_USE_CHECKBOX, true, wxPG_RECURSE);

		wxPGChoices m_combinedFlags7;
		m_combinedFlags7.Add(WXSIZEOF(checkbox_style_flags), checkbox_style_flags, checkbox_style_values);
		m_pgCheckboxStyle = m_propertyGrid->Append(new wxFlagsProperty(wxT("Checkbox flags"), wxPG_LABEL, m_combinedFlags7));
		m_propertyGrid->SetPropertyAttribute("Checkbox flags", wxPG_BOOL_USE_CHECKBOX, true, wxPG_RECURSE);
	
		wxPGChoices m_combinedFlags8;
		m_combinedFlags8.Add(WXSIZEOF(gauge_style_flags), gauge_style_flags, gauge_style_values);
		m_pgGaugeStyle = m_propertyGrid->Append(new wxFlagsProperty(wxT("Gauge flags"), wxPG_LABEL, m_combinedFlags8));
		m_propertyGrid->SetPropertyAttribute("Gauge flags", wxPG_BOOL_USE_CHECKBOX, true, wxPG_RECURSE);
	}

	void Update(std::pair<void*, ObjectStructure*> pair)
	{
		wxStaticText* t = reinterpret_cast<wxStaticText*>(pair.first);
		m_pgType->SetValue(GetNameFromEnum<wxTypes>(pair.second->type));
		m_pgId->SetValue(pair.second->id);
		m_pgName->SetValue(pair.second->name);
		m_pgLabel->SetValue(t->GetLabelText());
		m_pgPos->SetValue(wxString::Format("%d,%d", t->GetPosition().x, t->GetPosition().y));
		m_pgSize->SetValue(wxString::Format("%d,%d", t->GetSize().x, t->GetSize().y));
		m_pgMinSize->SetValue(wxString::Format("%d,%d", t->GetMinSize().x, t->GetMinSize().y));
		m_pgMaxSize->SetValue(wxString::Format("%d,%d", t->GetMaxSize().x, t->GetMaxSize().y));
		
		wxVariant f_clr, b_clr, fnt;
		f_clr << t->GetForegroundColour();
		b_clr << t->GetBackgroundColour();
		fnt << t->GetFont();
		m_pgForegroundColor->SetValue(f_clr);
		m_pgBackgroundColor->SetValue(b_clr);
		m_pgFont->SetValue(fnt);
		m_pgTooltip->SetValue(t->GetToolTipText());
		m_pgEnabled->SetValue(t->IsEnabled());
		m_pgHidden->SetValue(!t->IsShown());
		switch (pair.second->type)
		{
		case wxTypes::Slider:
		{
			m_pgSliderStyle->SetValue(reinterpret_cast<wxSlider*>(t)->GetWindowStyleFlag());
			break;
		}
		}
	}
public:
	
	wxPGProperty* m_pgID;
	wxPGProperty* m_pgPos;
	wxPGProperty* m_pgSize;
	wxPGProperty* m_pgColor;
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

	// Set the lexer to the C++ lexer
	m_StyledTextCtrl->SetLexer(wxSTC_LEX_CPP);

	// Set the color to use for various elements
	m_StyledTextCtrl->StyleSetForeground(wxSTC_C_COMMENTLINE, wxColor(60, 162, 2));
	m_StyledTextCtrl->StyleSetForeground(wxSTC_C_PREPROCESSOR, wxColor(0, 0, 255));
	m_StyledTextCtrl->StyleSetForeground(wxSTC_C_STRING, wxColor(255, 60, 10));
	m_StyledTextCtrl->StyleSetForeground(wxSTC_C_WORD, wxColor(0, 0, 255));

	// Give a list of keywords. They will be given the style specified for
	// wxSTC_C_WORD items.
	m_StyledTextCtrl->SetKeyWords(0, wxT("return int char this new"));

}

PropertyGrid* m_propgrid = nullptr;

MyPanel::MyPanel(wxFrame* parent)
    : wxPanel(parent, wxID_ANY)
{	
	m_TreeCtrl = new wxTreeCtrl(this, TreeTest_Ctrl, wxPoint(850, 0), wxSize(300, 300), wxTR_DEFAULT_STYLE);
	m_RootItem = m_TreeCtrl->AddRoot("Items");
	m_propgrid = new PropertyGrid(this, 100, wxT("0,0"), wxT("0,0"), wxColor(*wxRED));

	m_wxButton = new wxButton(this, wxID_ANY, wxT("btn"), wxPoint(0, 815), wxSize(25, 25), 0);
	m_wxButton->SetToolTip("wxButton");
	m_wxButton->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxButton - pos: %d,%d", m_wxButton->GetPosition().x, m_wxButton->GetPosition().y));
			void* tmp = new wxButton(this, wxID_ANY, wxT("wxButton"), wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = new ObjectStructure(this, tmp, wxTypes::Button);
		});

	m_wxComboBox = new wxComboBox(this, wxID_ANY, wxT("combo"), wxPoint(30, 815), wxSize(25, 25), 0);
	m_wxComboBox->SetToolTip("wxComboBox");
	m_wxComboBox->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxComboBox - pos: %d,%d", m_wxComboBox->GetPosition().x, m_wxComboBox->GetPosition().y));

			void* tmp = new wxComboBox(this, wxID_ANY, wxT("wxComboBox"), wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = new ObjectStructure(this, tmp, wxTypes::ComboBox);
		});

	wxArrayString m_choiceChoices;
	m_wxChoice = new wxChoice(this, wxID_ANY, wxPoint(60, 815), wxSize(25, 25), m_choiceChoices, 0);
	m_wxChoice->SetSelection(0);
	m_wxChoice->SetToolTip("wxChoice");
	m_wxChoice->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxChoice - pos: %d,%d", m_wxChoice->GetPosition().x, m_wxChoice->GetPosition().y));

			wxArrayString m_choiceChoices2;
			m_choiceChoices2.Add("First");
			m_choiceChoices2.Add("Second");
			void* tmp = new wxChoice(this, wxID_ANY, wxPoint(80, 815), wxSize(40, 25), m_choiceChoices2, 0);
			((wxChoice*)(tmp))->SetSelection(0);
			objects[tmp] = new ObjectStructure(this, tmp, wxTypes::Choise);
		});

	m_wxListBox = new wxListBox(this, wxID_ANY, wxPoint(90, 815), wxSize(25, 25), 0);
	m_wxListBox->SetToolTip("wxListBox");
	m_wxListBox->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxComboBox - pos: %d,%d", m_wxListBox->GetPosition().x, m_wxListBox->GetPosition().y));

			void* tmp = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = new ObjectStructure(this, tmp, wxTypes::ListBox);
		});

	m_wxCheckBox = new wxCheckBox(this, wxID_ANY, wxT("Check Me!"), wxPoint(120, 815), wxSize(25, 25), 0);
	m_wxCheckBox->SetToolTip("wxCheckBox");
	m_wxCheckBox->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxCheckBox - pos: %d,%d", m_wxCheckBox->GetPosition().x, m_wxCheckBox->GetPosition().y));

			void* tmp = new wxCheckBox(this, wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = new ObjectStructure(this, tmp, wxTypes::CheckBox);
		});

	m_wxRadioButton = new wxRadioButton(this, wxID_ANY, wxT("RadioBtn"), wxPoint(150, 815), wxSize(25, 25), 0);
	m_wxRadioButton->SetToolTip("wxRadioButton");
	m_wxRadioButton->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxRadioButton - pos: %d,%d", m_wxRadioButton->GetPosition().x, m_wxRadioButton->GetPosition().y));

			void* tmp = new wxRadioButton(this, wxID_ANY, wxT("RadioBtn"), wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = new ObjectStructure(this, tmp, wxTypes::RadioButton);
		});

	m_wxStaticLine = new wxStaticLine(this, wxID_ANY, wxPoint(180, 815), wxSize(25, 25), 0);
	m_wxStaticLine->SetToolTip("wxStaticLine");
	m_wxStaticLine->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxStaticLine - pos: %d,%d", m_wxStaticLine->GetPosition().x, m_wxStaticLine->GetPosition().y));

			void* tmp = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = new ObjectStructure(this, tmp, wxTypes::StaticLine);
		});

	m_wxSlider = new wxSlider(this, wxID_ANY, 50, 0, 100, wxPoint(210, 815), wxSize(25, 25), 0);
	m_wxSlider->SetToolTip("wxSlider");
	m_wxSlider->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxSlider - pos: %d,%d", m_wxSlider->GetPosition().x, m_wxSlider->GetPosition().y));

			void* tmp = new wxSlider(this, wxID_ANY, 80, 0, 100, wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = new ObjectStructure(this, tmp, wxTypes::Slider);
		});

	m_wxGauge = new wxGauge(this, wxID_ANY, 100, wxPoint(240, 815), wxSize(25, 25), 0);
	m_wxGauge->SetValue(60);
	m_wxGauge->SetToolTip("wxGauge");
	m_wxGauge->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxGauge - pos: %d,%d", m_wxGauge->GetPosition().x, m_wxGauge->GetPosition().y));

			void* tmp = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, 0);
			((wxGauge*)(tmp))->SetValue(20);
			objects[tmp] = new ObjectStructure(this, tmp, wxTypes::Gauge);
		});


	m_wxStaticText = new wxStaticText(this, wxID_ANY, wxT("wxStaticText"), wxPoint(0, 785), wxDefaultSize, 0);
	m_wxStaticText->SetToolTip("wxStaticText");
	m_wxStaticText->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxStaticText - pos: %d,%d", m_wxStaticText->GetPosition().x, m_wxStaticText->GetPosition().y));

			void* tmp = new wxStaticText(this, wxID_ANY, wxT("wxStaticText"), wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = new ObjectStructure(this, tmp, wxTypes::Text);
		});

	m_wxSpinCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(76, 785), wxSize(25, 25), wxSP_ARROW_KEYS, 1, 255, 1);
	m_wxSpinCtrl->SetToolTip("wxSpinCtrl");
	m_wxSpinCtrl->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxSpinCtrl - pos: %d,%d", m_wxSpinCtrl->GetPosition().x, m_wxSpinCtrl->GetPosition().y));

			void* tmp = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 255, 1);
			objects[tmp] = new ObjectStructure(this, tmp, wxTypes::SpinControl);
		});

	m_wxTextCtrl = new wxTextCtrl(this, wxID_ANY, wxT("wxTextCtrl"), wxPoint(140, 785), wxSize(25, 25), 0);
	m_wxTextCtrl->SetToolTip("wxTextCtrl");
	m_wxTextCtrl->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxTextCtrl - pos: %d,%d", m_wxStaticText->GetPosition().x, m_wxStaticText->GetPosition().y));

			void* tmp = new wxTextCtrl(this, wxID_ANY, wxT("wxTextCtrl"), wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = new ObjectStructure(this, tmp, wxTypes::TextControl);
		});

	m_wxToggleButton = new wxToggleButton(this, wxID_ANY, wxT("Toggle me!"), wxPoint(170, 785), wxSize(25, 25), 0);
	m_wxToggleButton->SetToolTip("wxToggleButton");
	m_wxToggleButton->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event)
		{
			m_Log->Append(wxString::Format("Clicked on wxToggleButton - pos: %d,%d", m_wxStaticText->GetPosition().x, m_wxStaticText->GetPosition().y));

			void* tmp = new wxToggleButton(this, wxID_ANY, wxT("Toggle me!"), wxDefaultPosition, wxDefaultSize, 0);
			objects[tmp] = new ObjectStructure(this, tmp, wxTypes::ToggleButton);
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

ObjectStructure* MyPanel::FindwxText(void* object_to_find)
{
	ObjectStructure* a = nullptr;
	if (m_SelectedWidget != nullptr || object_to_find)
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
	//m_Log->Append(wxString::Format("OnKeyDown: %d\n", (int)event.GetKeyCode()));
	
	int keycode = (int)event.GetKeyCode();
	ObjectStructure* t = FindwxText();
	if (t == nullptr) return;
	switch (keycode)
	{
	case 388: /* + */
	{
		m_Log->Append(wxString::Format("Move speed has increased to %d.\n", ++m_speed));
		break;
	}	
	case 390: /* - */
	{
		if (!--m_speed)
			m_speed = 1;
		m_Log->Append(wxString::Format("Move speed has decresed to %d.\n", m_speed));
		break;
	}
	case 68: /* D */
	{
		switch (t->type)
		{
			case wxTypes::Button:
			{
				wxButton* text = reinterpret_cast<wxButton*>(m_SelectedWidget);
				wxButton* new_btn = new wxButton(this, wxID_ANY, text->GetLabelText(), text->GetPosition(), text->GetSize(), text->GetWindowStyleFlag());
				new_btn->SetForegroundColour(text->GetForegroundColour());
				new_btn->SetBackgroundColour(text->GetBackgroundColour());
				new_btn->SetFont(text->GetFont());
				objects[new_btn] = new ObjectStructure(this, new_btn, wxTypes::Button);
				break;			
			}
			case wxTypes::ComboBox:
			{
				wxComboBox* text = reinterpret_cast<wxComboBox*>(m_SelectedWidget);
				wxComboBox* new_btn = new wxComboBox(this, wxID_ANY, text->GetLabelText(), text->GetPosition(), text->GetSize());
				new_btn->SetForegroundColour(text->GetForegroundColour());
				new_btn->SetBackgroundColour(text->GetBackgroundColour());
				new_btn->SetFont(text->GetFont());
				objects[new_btn] = new ObjectStructure(this, new_btn, wxTypes::ComboBox);
				break;			
			}		
			case wxTypes::Choise:
			{
				wxChoice* text = reinterpret_cast<wxChoice*>(m_SelectedWidget);
				wxChoice* new_btn = new wxChoice(this, wxID_ANY, text->GetPosition(), text->GetSize(), text->GetStrings(), text->GetWindowStyleFlag());
				new_btn->SetForegroundColour(text->GetForegroundColour());
				new_btn->SetBackgroundColour(text->GetBackgroundColour());
				new_btn->SetFont(text->GetFont());
				objects[new_btn] = new ObjectStructure(this, new_btn, wxTypes::Choise);
				break;			
			}
			case wxTypes::ListBox:
			{
				wxListBox* text = reinterpret_cast<wxListBox*>(m_SelectedWidget);
				wxArrayString m_choiceChoices2;
				m_choiceChoices2.Add("First");
				m_choiceChoices2.Add("Second");
				wxListBox* new_text = new wxListBox(this, wxID_ANY, text->GetPosition(), text->GetSize(), m_choiceChoices2, text->GetWindowStyleFlag());
				new_text->SetForegroundColour(text->GetForegroundColour());
				new_text->SetBackgroundColour(text->GetBackgroundColour());
				new_text->SetFont(text->GetFont());
				objects[new_text] = new ObjectStructure(this, new_text, wxTypes::ListBox);
				break;
			}
			case wxTypes::CheckBox:
			{
				wxCheckBox* text = reinterpret_cast<wxCheckBox*>(m_SelectedWidget);
				wxCheckBox* new_text = new wxCheckBox(this, wxID_ANY, text->GetLabelText(), text->GetPosition(), text->GetSize(), text->GetWindowStyleFlag());
				new_text->SetForegroundColour(text->GetForegroundColour());
				new_text->SetBackgroundColour(text->GetBackgroundColour());
				new_text->SetFont(text->GetFont());
				objects[new_text] = new ObjectStructure(this, new_text, wxTypes::CheckBox);
				break;
			}
			case wxTypes::RadioButton:
			{
				wxRadioButton* text = reinterpret_cast<wxRadioButton*>(m_SelectedWidget);
				wxRadioButton* new_text = new wxRadioButton(this, wxID_ANY, text->GetLabelText(), text->GetPosition(), text->GetSize(), text->GetWindowStyleFlag());
				new_text->SetForegroundColour(text->GetForegroundColour());
				new_text->SetBackgroundColour(text->GetBackgroundColour());
				new_text->SetFont(text->GetFont());
				objects[new_text] = new ObjectStructure(this, new_text, wxTypes::RadioButton);
				break;
			}
			case wxTypes::StaticLine:
			{
				wxStaticLine* text = reinterpret_cast<wxStaticLine*>(m_SelectedWidget);
				wxStaticLine* new_text = new wxStaticLine(this, wxID_ANY, text->GetPosition(), text->GetSize(), text->GetWindowStyleFlag());
				new_text->SetForegroundColour(text->GetForegroundColour());
				new_text->SetBackgroundColour(text->GetBackgroundColour());
				new_text->SetFont(text->GetFont());
				objects[new_text] = new ObjectStructure(this, new_text, wxTypes::StaticLine);
				break;
			}	
			case wxTypes::Slider:
			{
				wxSlider* text = reinterpret_cast<wxSlider*>(m_SelectedWidget);
				wxSlider* new_text = new wxSlider(this, wxID_ANY, text->GetValue(), text->GetMin(), text->GetMax(), text->GetPosition(), text->GetSize(), text->GetWindowStyleFlag());
				new_text->SetForegroundColour(text->GetForegroundColour());
				new_text->SetBackgroundColour(text->GetBackgroundColour());
				new_text->SetFont(text->GetFont());
				objects[new_text] = new ObjectStructure(this, new_text, wxTypes::Slider);
				break;
			}			
			case wxTypes::Gauge:
			{
				wxGauge* text = reinterpret_cast<wxGauge*>(m_SelectedWidget);
				wxGauge* new_text = new wxGauge(this, wxID_ANY, text->GetRange(), text->GetPosition(), text->GetSize(), text->GetWindowStyleFlag());
				new_text->SetForegroundColour(text->GetForegroundColour());
				new_text->SetBackgroundColour(text->GetBackgroundColour());
				new_text->SetFont(text->GetFont());
				objects[new_text] = new ObjectStructure(this, new_text, wxTypes::Gauge);
				break;
			}	
			case wxTypes::Text:
			{
				wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
				wxStaticText* new_text = new wxStaticText(this, wxID_ANY, text->GetLabelText(), text->GetPosition(), text->GetSize(), text->GetWindowStyleFlag());
				new_text->SetForegroundColour(text->GetForegroundColour());
				new_text->SetBackgroundColour(text->GetBackgroundColour());
				new_text->SetFont(text->GetFont());
				objects[new_text] = new ObjectStructure(this, new_text, wxTypes::Text);
				break;
			}
			case wxTypes::SpinControl:
			{
				wxSpinCtrl* text = reinterpret_cast<wxSpinCtrl*>(m_SelectedWidget);
				wxSpinCtrl* new_text = new wxSpinCtrl(this, wxID_ANY, text->GetLabelText(), text->GetPosition(), text->GetSize(), text->GetWindowStyleFlag());
				new_text->SetForegroundColour(text->GetForegroundColour());
				new_text->SetBackgroundColour(text->GetBackgroundColour());
				new_text->SetFont(text->GetFont());
				objects[new_text] = new ObjectStructure(this, new_text, wxTypes::SpinControl);
				break;
			}			
			case wxTypes::SpinCtrlDouble:
			{
				wxSpinCtrlDouble* text = reinterpret_cast<wxSpinCtrlDouble*>(m_SelectedWidget);
				wxSpinCtrlDouble* new_text = new wxSpinCtrlDouble(this, wxID_ANY, text->GetLabelText(), text->GetPosition(), text->GetSize(), text->GetWindowStyleFlag());
				new_text->SetForegroundColour(text->GetForegroundColour());
				new_text->SetBackgroundColour(text->GetBackgroundColour());
				new_text->SetFont(text->GetFont());
				objects[new_text] = new ObjectStructure(this, new_text, wxTypes::SpinCtrlDouble);
				break;
			}
			case wxTypes::TextControl:
			{
				wxTextCtrl* text = reinterpret_cast<wxTextCtrl*>(m_SelectedWidget);
				wxTextCtrl* new_text = new wxTextCtrl(this, wxID_ANY, text->GetLabelText(), text->GetPosition(), text->GetSize(), text->GetWindowStyleFlag());
				new_text->SetForegroundColour(text->GetForegroundColour());
				new_text->SetBackgroundColour(text->GetBackgroundColour());
				new_text->SetFont(text->GetFont());
				objects[new_text] = new ObjectStructure(this, new_text, wxTypes::TextControl);
				break;
			}			
			case wxTypes::ToggleButton:
			{
				wxToggleButton* text = reinterpret_cast<wxToggleButton*>(m_SelectedWidget);
				wxToggleButton* new_text = new wxToggleButton(this, wxID_ANY, text->GetLabelText(), text->GetPosition(), text->GetSize(), text->GetWindowStyleFlag());
				new_text->SetForegroundColour(text->GetForegroundColour());
				new_text->SetBackgroundColour(text->GetBackgroundColour());
				new_text->SetFont(text->GetFont());
				objects[new_text] = new ObjectStructure(this, new_text, wxTypes::ToggleButton);
				break;
			}			
			case wxTypes::SearchCtrl:
			{
				wxSearchCtrl* text = reinterpret_cast<wxSearchCtrl*>(m_SelectedWidget);
				wxSearchCtrl* new_text = new wxSearchCtrl(this, wxID_ANY, text->GetLabelText(), text->GetPosition(), text->GetSize(), text->GetWindowStyleFlag());
				new_text->SetForegroundColour(text->GetForegroundColour());
				new_text->SetBackgroundColour(text->GetBackgroundColour());
				new_text->SetFont(text->GetFont());
				objects[new_text] = new ObjectStructure(this, new_text, wxTypes::SearchCtrl);
				break;
			}
		}
		break;
	}
	case 127: /* Delete */
	{
		if (t != nullptr)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			objects.erase(m_SelectedWidget);
			text->Destroy();
		}
		break;
	}
	case 315: /* Up*/
	{
		if (t != nullptr)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxPoint pos = text->GetPosition();
			pos.y -= m_speed;
			text->SetPosition(std::move(pos));
			m_propgrid->Update(std::make_pair((void*)text, t));
		}
		break;
	}
	case 317: /* Down*/
	{
		if (t != nullptr)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxPoint pos = text->GetPosition();
			pos.y += m_speed;
			text->SetPosition(std::move(pos));
			m_propgrid->Update(std::make_pair((void*)text, t));
		}
		break;
	}
	case 314: /* Left*/
	{
		if (t != nullptr)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxPoint pos = text->GetPosition();
			pos.x -= m_speed;
			text->SetPosition(std::move(pos));
			m_propgrid->Update(std::make_pair((void*)text, t));
		}
		break;
	}
	case 316: /* Right*/
	{
		if (t != nullptr)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxPoint pos = text->GetPosition();
			pos.x += m_speed;
			text->SetPosition(std::move(pos));
			m_propgrid->Update(std::make_pair((void*)text, t));
		}
		break;
	}
	case 330: /* 6*/
	{
		if (t != nullptr)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxSize pos = text->GetSize();
			pos.x += m_speed;
			text->SetSize(std::move(pos));
			m_propgrid->Update(std::make_pair((void*)text, t));
		}
		break;
	}
	case 332: /* 8*/
	{
		if (t != nullptr)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxSize pos = text->GetSize();
			pos.y += m_speed;
			text->SetSize(std::move(pos));
			m_propgrid->Update(std::make_pair((void*)text, t));
		}
		break;
	}
	case 328: /* 4*/
	{
		if (t != nullptr)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxSize pos = text->GetSize();
			pos.x -= m_speed;
			text->SetSize(std::move(pos));
			m_propgrid->Update(std::make_pair((void*)text, t));
		}
		break;
	}	
	case 326: /* 2 */
	{
		if (t != nullptr)
		{
			wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
			wxSize pos = text->GetSize();
			pos.y -= m_speed;
			text->SetSize(std::move(pos));
			m_propgrid->Update(std::make_pair((void*)text, t));
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
	ObjectStructure* t = FindwxText();
	if (t != nullptr)
	{
		m_Log->Append(wxString::Format(":: Current item is %s", GetNameFromEnum<wxTypes>(t->type)));
	}
}

void MyPanel::OnMouseMotion(wxMouseEvent& event)
{
	wxPoint pos = ScreenToClient(::wxGetMousePosition());
	wxMouseState mouse = wxGetMouseState();

	ObjectStructure* t = FindwxText();
	if (t != nullptr && mouse.LeftIsDown())
	{
		wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
		m_propgrid->Update(std::make_pair((void*)text, t));
		switch (t->type)
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
				break;
			}
			case wxTypes::SpinControl:
				SetPos<wxSpinCtrl>(m_SelectedWidget, pos);
				break;	
			case wxTypes::TextControl:
				SetPos<wxTextCtrl>(m_SelectedWidget, pos);
				break;
			case wxTypes::ToggleButton:
				SetPos<wxTextCtrl>(m_SelectedWidget, pos);
				break;
			case wxTypes::SearchCtrl:
				SetPos<wxTextCtrl>(m_SelectedWidget, pos);
				break;
			case wxTypes::ColorPicker:
				SetPos<wxTextCtrl>(m_SelectedWidget, pos);
				break;
			case wxTypes::FontPicker:
				SetPos<wxTextCtrl>(m_SelectedWidget, pos);
				break;
			case wxTypes::FilePicker:
				SetPos<wxTextCtrl>(m_SelectedWidget, pos);
				break;
			case wxTypes::DirPicker:
				SetPos<wxTextCtrl>(m_SelectedWidget, pos);
				break;
			case wxTypes::DatePicker:
				SetPos<wxTextCtrl>(m_SelectedWidget, pos);
				break;
			case wxTypes::TimePicker:
				SetPos<wxTextCtrl>(m_SelectedWidget, pos);
				break;
			case wxTypes::CalendarCtrl:
				SetPos<wxTextCtrl>(m_SelectedWidget, pos);
				break;
			case wxTypes::GenericDirCtrl:
				SetPos<wxTextCtrl>(m_SelectedWidget, pos);
				break;
			case wxTypes::SpinButton:
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
	ObjectStructure* t = FindwxText();
	if (property == m_pgName)
	{
		if (t != nullptr)
		{
			wxString str;
			property->GetValue().Convert(&str);	
			t->name = std::move(str);
		}
	}	
	if (property == m_pgLabel)
	{
		if (t != nullptr)
		{
			wxString str;
			property->GetValue().Convert(&str);
			((wxStaticText*)m_SelectedWidget)->SetLabelText(str);
		}
	}	
	if (property == m_pgPos)
	{
		if (t != nullptr)
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
		if (t != nullptr)
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
		if (t != nullptr)
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
		if (t != nullptr)
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
		if (t != nullptr)
		{
			wxVariant a = property->GetValue();
			wxColour color;
			color << a;
			((wxStaticText*)m_SelectedWidget)->SetForegroundColour(color);
			((wxStaticText*)m_SelectedWidget)->Refresh();
			t->fg_color_changed = 1;
		}
	}		
	else if (property == m_pgBackgroundColor)
	{
		if (t != nullptr)
		{
			wxVariant a = property->GetValue();
			wxColour color;
			color << a;
			((wxStaticText*)m_SelectedWidget)->SetBackgroundColour(color);
			((wxStaticText*)m_SelectedWidget)->Refresh();
			t->bg_color_changed = 1;
		}
	}	
	else if (property == m_pgFont)
	{
		if (t != nullptr)
		{
			wxVariant a = property->GetValue();
			wxFont fnt;
			fnt << a;
			((wxStaticText*)m_SelectedWidget)->SetFont(fnt);
		}
	}	
	else if (property == m_pgTooltip)
	{
		if (t != nullptr)
		{
			wxString str;
			property->GetValue().Convert(&str);
			((wxStaticText*)m_SelectedWidget)->SetToolTip(str);
		}
	}	
	else if (property == m_pgEnabled)
	{
		if (t != nullptr)
		{
			bool is_enabled;
			property->GetValue().Convert(&is_enabled);
			((wxStaticText*)m_SelectedWidget)->Enable(is_enabled);
		}
	}	
	else if (property == m_pgHidden)
	{
		if (t != nullptr)
		{
			bool is_hide;
			property->GetValue().Convert(&is_hide);
			if(is_hide)
				((wxStaticText*)m_SelectedWidget)->Hide();
			else
				((wxStaticText*)m_SelectedWidget)->Show();
		}
	}	
	else if (property == m_pgButtonStyle)
	{
		if (t != nullptr && t->type == wxTypes::Button)
		{
			long flags;
			property->GetValue().Convert(&flags);
			wxButton* old = ((wxButton*)(m_SelectedWidget));
			void* tmp = new wxButton(this, wxID_ANY, old->GetLabelText(), old->GetPosition(), old->GetSize(), flags);
			old->Destroy();
			auto nodeHandler = objects.extract(old);
			nodeHandler.key() = tmp;
			objects.insert(std::move(nodeHandler));
			old = nullptr;
			m_SelectedWidget = tmp;
			((wxButton*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);

		}
	}	
	else if (property == m_pgSliderStyle)
	{
		if (t != nullptr && t->type == wxTypes::Slider)
		{
			long flags;
			property->GetValue().Convert(&flags);
			wxSlider* old = ((wxSlider*)(m_SelectedWidget));
			void* tmp = new wxSlider(this, wxID_ANY, 80, 0, 100, old->GetPosition(), old->GetSize(), flags);
			old->Destroy();
			auto nodeHandler = objects.extract(old);
			nodeHandler.key() = tmp;
			objects.insert(std::move(nodeHandler));
			old = nullptr;
			m_SelectedWidget = tmp;
			((wxSlider*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
		}
	}	
	else if (property == m_pgStaticTextStyle)
	{
		if (t != nullptr && t->type == wxTypes::Text)
		{
			long flags;
			property->GetValue().Convert(&flags);
			wxStaticText* old = ((wxStaticText*)(m_SelectedWidget));
			void* tmp = new wxStaticText(this, wxID_ANY, old->GetLabelText(), old->GetPosition(), old->GetSize(), flags);
			old->Destroy();
			auto nodeHandler = objects.extract(old);
			nodeHandler.key() = tmp;
			objects.insert(std::move(nodeHandler));
			old = nullptr;
			m_SelectedWidget = tmp;
			((wxStaticText*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
		}
	}
	else if (property == m_pgTextCtrlStyle)
	{
		if (t != nullptr && t->type == wxTypes::TextControl)
		{
			long flags;
			property->GetValue().Convert(&flags);
			wxTextCtrl* old = ((wxTextCtrl*)(m_SelectedWidget));
			void* tmp = new wxTextCtrl(this, wxID_ANY, old->GetLabelText(), old->GetPosition(), old->GetSize(), flags);
			old->Destroy();
			auto nodeHandler = objects.extract(old);
			nodeHandler.key() = tmp;
			objects.insert(std::move(nodeHandler));
			old = nullptr;
			m_SelectedWidget = tmp;
			((wxStaticText*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
		}
	}
	else if (property == m_pgComboBoxStyle)
	{
		if (t != nullptr && t->type == wxTypes::ComboBox)
		{
			long flags;
			property->GetValue().Convert(&flags);
			wxComboBox* old = ((wxComboBox*)(m_SelectedWidget));
			wxArrayString a;
			void* tmp = new wxComboBox(this, wxID_ANY, old->GetLabelText(), old->GetPosition(), old->GetSize(), a, flags);
			old->Destroy();
			auto nodeHandler = objects.extract(old);
			nodeHandler.key() = tmp;
			objects.insert(std::move(nodeHandler));
			old = nullptr;
			m_SelectedWidget = tmp;
			((wxComboBox*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
		}
	}
	else if (property == m_pgChoiseStyle)
	{
		if (t != nullptr && t->type == wxTypes::Choise)
		{
			long flags;
			property->GetValue().Convert(&flags);
			wxChoice* old = ((wxChoice*)(m_SelectedWidget));
			wxArrayString a;
			void* tmp = new wxChoice(this, wxID_ANY, old->GetPosition(), old->GetSize(), a, flags);
			old->Destroy();
			auto nodeHandler = objects.extract(old);
			nodeHandler.key() = tmp;
			objects.insert(std::move(nodeHandler));
			old = nullptr;
			m_SelectedWidget = tmp;
			((wxChoice*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
		}
	}
	else if (property == m_pgGaugeStyle)
	{
		if (t != nullptr && t->type == wxTypes::Gauge)
		{
			long flags;
			property->GetValue().Convert(&flags);
			wxGauge* old = ((wxGauge*)(m_SelectedWidget));
			void* tmp = new wxGauge(this, wxID_ANY, 100, old->GetPosition(), old->GetSize(), flags);
			old->Destroy();
			auto nodeHandler = objects.extract(old);
			nodeHandler.key() = tmp;
			objects.insert(std::move(nodeHandler));
			old = nullptr;
			m_SelectedWidget = tmp;
			((wxGauge*)(tmp))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
		}
	}
}

void MyPanel::OnClick(wxMouseEvent& event)
{
	void* obj = event.GetEventObject();
	ObjectStructure* t = FindwxText(obj);
	if (t != nullptr)
	{
		m_SelectedWidget = obj;
		m_Log->Append(wxString::Format("Clicked on %s", GetNameFromEnum<wxTypes>(t->type)));
		MarkSelectedItem();
		wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
		m_propgrid->Update(std::make_pair((void*)text, t));
		switch (t->type)
		{
		case wxTypes::Slider:
		{
			break;
		}
		case wxTypes::Button:
		{
			break;
		}		
		case wxTypes::Text:
		{
			break;
		}
		}
	}
}

void MyPanel::MarkSelectedItem(void)
{
	wxClientDC dc(this);
	ObjectStructure* t = FindwxText();
	if (t != nullptr)
	{
		wxPoint pos = ((wxStaticText*)m_SelectedWidget)->GetPosition();
		wxSize size = ((wxStaticText*)m_SelectedWidget)->GetSize();
		dc.Clear();
		dc.SetPen(wxPen(*wxRED, 1));
		dc.DrawRectangle(pos.x - 1, pos.y - 1, size.x + 2, size.y + 2);
	}
	/*
	dc.SetPen(wxPen(*wxBLACK, 1));
	for (int x = 0; x != 1024; x++)
	{
		for (int y = 0; y != 768; y++)
		{
			if(x % 10 == 0 && y % 10 == 0)
				dc.DrawPoint(x, y);
		}
	}
	*/
}

void MyPanel::OnPaint(wxPaintEvent& event)
{
	MarkSelectedItem();
}

void MyPanel::OnListCtrlSelChanged(wxTreeEvent& event)
{
	wxTreeItemId label = event.GetItem();
	void* obj = GetWidgetByItemID(label);
	ObjectStructure* t = FindwxText(obj);
	if (t != nullptr && obj != nullptr)
	{
		m_SelectedWidget = obj;
		m_Log->Append(wxString::Format("Clicked on %s", GetNameFromEnum<wxTypes>(t->type)));
		MarkSelectedItem();
		wxStaticText* text = reinterpret_cast<wxStaticText*>(m_SelectedWidget);
		m_propgrid->Update(std::make_pair((void*)text, t));
	}
}

void MyPanel::LoadFromXml(wxString xml_path)
{
	wxXmlDocument doc;
	if (!doc.Load(xml_path))
		return;

	wxString a = doc.GetRoot()->GetName();
	if (a != "wxCreatorXmlFile")
		return;
	wxXmlNode* child = doc.GetRoot()->GetChildren();
	while (child)
	{
		wxPoint pos;
		wxSize size, min_size, max_size;
		int fontsize, fontfamily, fontstyle, fontweight, is_underlined;
		char fontname[128];

		wxString str = child->GetName();
		if (str == "widget")
		{
			wxString str_type = child->GetAttribute("type");
			if (str_type == "button")
			{
				uint8_t fg_colors[3], bg_colors[3];
				sscanf(child->GetAttribute("pos").c_str(), "%d,%d", &pos.x, &pos.y);
				sscanf(child->GetAttribute("size").c_str(), "%d,%d", &size.x, &size.y);
				sscanf(child->GetAttribute("min_size").c_str(), "%d,%d", &min_size.x, &min_size.y);
				sscanf(child->GetAttribute("max_size").c_str(), "%d,%d", &max_size.x, &max_size.y);
				sscanf(child->GetAttribute("fg_color").c_str(), "%hhd,%hhd,%hhd", &fg_colors[0], &fg_colors[1], &fg_colors[2]);
				sscanf(child->GetAttribute("bg_color").c_str(), "%hhd,%hhd,%hhd", &bg_colors[0], &bg_colors[1], &bg_colors[2]);
				sscanf(child->GetAttribute("font").c_str(), "%d,%d,%d,%d,%d,%[^\n]s", &fontsize, &fontfamily, &fontstyle, &fontweight, &is_underlined, fontname);
				wxButton* tmp = new wxButton(this, wxID_ANY, child->GetAttribute("label"), pos, size, wxAtoi(child->GetAttribute("flags")));
				tmp->SetToolTip(child->GetAttribute("tooltip"));
				tmp->SetMinSize(min_size);
				tmp->SetMaxSize(max_size);
				tmp->SetForegroundColour(wxColour(fg_colors[0], fg_colors[1], fg_colors[2]));
				tmp->SetBackgroundColour(wxColour(bg_colors[0], bg_colors[1], bg_colors[2]));
				tmp->SetFont(wxFont(fontsize, static_cast<wxFontFamily>(fontfamily), static_cast<wxFontStyle>(fontstyle), static_cast<wxFontWeight>(fontweight), is_underlined != 0, wxString(fontname)));
				objects[tmp] = new ObjectStructure(this, tmp, wxTypes::Button);
			}
			if (str_type == "combobox")
			{
				uint8_t fg_colors[3], bg_colors[3];
				sscanf(child->GetAttribute("pos").c_str(), "%d,%d", &pos.x, &pos.y);
				sscanf(child->GetAttribute("size").c_str(), "%d,%d", &size.x, &size.y);
				sscanf(child->GetAttribute("min_size").c_str(), "%d,%d", &min_size.x, &min_size.y);
				sscanf(child->GetAttribute("max_size").c_str(), "%d,%d", &max_size.x, &max_size.y);
				sscanf(child->GetAttribute("fg_color").c_str(), "%hhd,%hhd,%hhd", &fg_colors[0], &fg_colors[1], &fg_colors[2]);
				sscanf(child->GetAttribute("bg_color").c_str(), "%hhd,%hhd,%hhd", &bg_colors[0], &bg_colors[1], &bg_colors[2]);
				sscanf(child->GetAttribute("font").c_str(), "%d,%d,%d,%d,%d,%[^\n]s", &fontsize, &fontfamily, &fontstyle, &fontweight, &is_underlined, fontname);
				wxArrayString a;
				wxComboBox* tmp = new wxComboBox(this, wxID_ANY, child->GetAttribute("label"), pos, size, a, wxAtoi(child->GetAttribute("flags")));
				tmp->SetToolTip(child->GetAttribute("tooltip"));
				tmp->SetMinSize(min_size);
				tmp->SetMaxSize(max_size);
				tmp->SetForegroundColour(wxColour(fg_colors[0], fg_colors[1], fg_colors[2]));
				tmp->SetBackgroundColour(wxColour(bg_colors[0], bg_colors[1], bg_colors[2]));
				tmp->SetFont(wxFont(fontsize, static_cast<wxFontFamily>(fontfamily), static_cast<wxFontStyle>(fontstyle), static_cast<wxFontWeight>(fontweight), is_underlined != 0, wxString(fontname)));
				objects[tmp] = new ObjectStructure(this, tmp, wxTypes::ComboBox);
			}
			if (str_type == "choise")
			{
				uint8_t fg_colors[3], bg_colors[3];
				sscanf(child->GetAttribute("pos").c_str(), "%d,%d", &pos.x, &pos.y);
				sscanf(child->GetAttribute("size").c_str(), "%d,%d", &size.x, &size.y);
				sscanf(child->GetAttribute("min_size").c_str(), "%d,%d", &min_size.x, &min_size.y);
				sscanf(child->GetAttribute("max_size").c_str(), "%d,%d", &max_size.x, &max_size.y);
				sscanf(child->GetAttribute("fg_color").c_str(), "%hhd,%hhd,%hhd", &fg_colors[0], &fg_colors[1], &fg_colors[2]);
				sscanf(child->GetAttribute("bg_color").c_str(), "%hhd,%hhd,%hhd", &bg_colors[0], &bg_colors[1], &bg_colors[2]);
				sscanf(child->GetAttribute("font").c_str(), "%d,%d,%d,%d,%d,%[^\n]s", &fontsize, &fontfamily, &fontstyle, &fontweight, &is_underlined, fontname);
				wxArrayString a;
				wxChoice* tmp = new wxChoice(this, wxID_ANY, pos, size, a, wxAtoi(child->GetAttribute("flags")));
				tmp->SetToolTip(child->GetAttribute("tooltip"));
				tmp->SetMinSize(min_size);
				tmp->SetMaxSize(max_size);
				tmp->SetForegroundColour(wxColour(fg_colors[0], fg_colors[1], fg_colors[2]));
				tmp->SetBackgroundColour(wxColour(bg_colors[0], bg_colors[1], bg_colors[2]));
				tmp->SetFont(wxFont(fontsize, static_cast<wxFontFamily>(fontfamily), static_cast<wxFontStyle>(fontstyle), static_cast<wxFontWeight>(fontweight), is_underlined != 0, wxString(fontname)));
				objects[tmp] = new ObjectStructure(this, tmp, wxTypes::Choise);
			}
			if (str_type == "listbox")
			{
				uint8_t fg_colors[3], bg_colors[3];
				sscanf(child->GetAttribute("pos").c_str(), "%d,%d", &pos.x, &pos.y);
				sscanf(child->GetAttribute("size").c_str(), "%d,%d", &size.x, &size.y);
				sscanf(child->GetAttribute("min_size").c_str(), "%d,%d", &min_size.x, &min_size.y);
				sscanf(child->GetAttribute("max_size").c_str(), "%d,%d", &max_size.x, &max_size.y);
				sscanf(child->GetAttribute("fg_color").c_str(), "%hhd,%hhd,%hhd", &fg_colors[0], &fg_colors[1], &fg_colors[2]);
				sscanf(child->GetAttribute("bg_color").c_str(), "%hhd,%hhd,%hhd", &bg_colors[0], &bg_colors[1], &bg_colors[2]);
				sscanf(child->GetAttribute("font").c_str(), "%d,%d,%d,%d,%d,%[^\n]s", &fontsize, &fontfamily, &fontstyle, &fontweight, &is_underlined, fontname);
				wxArrayString a;
				wxListBox* tmp = new wxListBox(this, wxID_ANY, pos, size, a, wxAtoi(child->GetAttribute("flags")));
				tmp->SetToolTip(child->GetAttribute("tooltip"));
				tmp->SetMinSize(min_size);
				tmp->SetMaxSize(max_size);
				tmp->SetForegroundColour(wxColour(fg_colors[0], fg_colors[1], fg_colors[2]));
				tmp->SetBackgroundColour(wxColour(bg_colors[0], bg_colors[1], bg_colors[2]));
				tmp->SetFont(wxFont(fontsize, static_cast<wxFontFamily>(fontfamily), static_cast<wxFontStyle>(fontstyle), static_cast<wxFontWeight>(fontweight), is_underlined != 0, wxString(fontname)));
				objects[tmp] = new ObjectStructure(this, tmp, wxTypes::Choise);
			}
			if (str_type == "checkbox")
			{
				uint8_t fg_colors[3], bg_colors[3];
				sscanf(child->GetAttribute("pos").c_str(), "%d,%d", &pos.x, &pos.y);
				sscanf(child->GetAttribute("size").c_str(), "%d,%d", &size.x, &size.y);
				sscanf(child->GetAttribute("min_size").c_str(), "%d,%d", &min_size.x, &min_size.y);
				sscanf(child->GetAttribute("max_size").c_str(), "%d,%d", &max_size.x, &max_size.y);
				sscanf(child->GetAttribute("fg_color").c_str(), "%hhd,%hhd,%hhd", &fg_colors[0], &fg_colors[1], &fg_colors[2]);
				sscanf(child->GetAttribute("bg_color").c_str(), "%hhd,%hhd,%hhd", &bg_colors[0], &bg_colors[1], &bg_colors[2]);
				sscanf(child->GetAttribute("font").c_str(), "%d,%d,%d,%d,%d,%[^\n]s", &fontsize, &fontfamily, &fontstyle, &fontweight, &is_underlined, fontname);
				wxCheckBox* tmp = new wxCheckBox(this, wxID_ANY, child->GetAttribute("label"), pos, size, wxAtoi(child->GetAttribute("flags")));
				tmp->SetToolTip(child->GetAttribute("tooltip"));
				tmp->SetMinSize(min_size);
				tmp->SetMaxSize(max_size);
				tmp->SetForegroundColour(wxColour(fg_colors[0], fg_colors[1], fg_colors[2]));
				tmp->SetBackgroundColour(wxColour(bg_colors[0], bg_colors[1], bg_colors[2]));
				tmp->SetFont(wxFont(fontsize, static_cast<wxFontFamily>(fontfamily), static_cast<wxFontStyle>(fontstyle), static_cast<wxFontWeight>(fontweight), is_underlined != 0, wxString(fontname)));
				objects[tmp] = new ObjectStructure(this, tmp, wxTypes::CheckBox);
			}
			if (str_type == "radiobutton")
			{
				uint8_t fg_colors[3], bg_colors[3];
				sscanf(child->GetAttribute("pos").c_str(), "%d,%d", &pos.x, &pos.y);
				sscanf(child->GetAttribute("size").c_str(), "%d,%d", &size.x, &size.y);
				sscanf(child->GetAttribute("min_size").c_str(), "%d,%d", &min_size.x, &min_size.y);
				sscanf(child->GetAttribute("max_size").c_str(), "%d,%d", &max_size.x, &max_size.y);
				sscanf(child->GetAttribute("fg_color").c_str(), "%hhd,%hhd,%hhd", &fg_colors[0], &fg_colors[1], &fg_colors[2]);
				sscanf(child->GetAttribute("bg_color").c_str(), "%hhd,%hhd,%hhd", &bg_colors[0], &bg_colors[1], &bg_colors[2]);
				sscanf(child->GetAttribute("font").c_str(), "%d,%d,%d,%d,%d,%[^\n]s", &fontsize, &fontfamily, &fontstyle, &fontweight, &is_underlined, fontname);
				wxRadioButton* tmp = new wxRadioButton(this, wxID_ANY, child->GetAttribute("label"), pos, size, wxAtoi(child->GetAttribute("flags")));
				tmp->SetToolTip(child->GetAttribute("tooltip"));
				tmp->SetMinSize(min_size);
				tmp->SetMaxSize(max_size);
				tmp->SetForegroundColour(wxColour(fg_colors[0], fg_colors[1], fg_colors[2]));
				tmp->SetBackgroundColour(wxColour(bg_colors[0], bg_colors[1], bg_colors[2]));
				tmp->SetFont(wxFont(fontsize, static_cast<wxFontFamily>(fontfamily), static_cast<wxFontStyle>(fontstyle), static_cast<wxFontWeight>(fontweight), is_underlined != 0, wxString(fontname)));
				objects[tmp] = new ObjectStructure(this, tmp, wxTypes::RadioButton);
			}
			if (str_type == "staticline")
			{
				uint8_t fg_colors[3], bg_colors[3];
				sscanf(child->GetAttribute("pos").c_str(), "%d,%d", &pos.x, &pos.y);
				sscanf(child->GetAttribute("size").c_str(), "%d,%d", &size.x, &size.y);
				sscanf(child->GetAttribute("min_size").c_str(), "%d,%d", &min_size.x, &min_size.y);
				sscanf(child->GetAttribute("max_size").c_str(), "%d,%d", &max_size.x, &max_size.y);
				sscanf(child->GetAttribute("fg_color").c_str(), "%hhd,%hhd,%hhd", &fg_colors[0], &fg_colors[1], &fg_colors[2]);
				sscanf(child->GetAttribute("bg_color").c_str(), "%hhd,%hhd,%hhd", &bg_colors[0], &bg_colors[1], &bg_colors[2]);
				sscanf(child->GetAttribute("font").c_str(), "%d,%d,%d,%d,%d,%[^\n]s", &fontsize, &fontfamily, &fontstyle, &fontweight, &is_underlined, fontname);
				wxStaticLine* tmp = new wxStaticLine(this, wxID_ANY, pos, size, wxAtoi(child->GetAttribute("flags")));
				tmp->SetToolTip(child->GetAttribute("tooltip"));
				tmp->SetMinSize(min_size);
				tmp->SetMaxSize(max_size);
				tmp->SetForegroundColour(wxColour(fg_colors[0], fg_colors[1], fg_colors[2]));
				tmp->SetBackgroundColour(wxColour(bg_colors[0], bg_colors[1], bg_colors[2]));
				tmp->SetFont(wxFont(fontsize, static_cast<wxFontFamily>(fontfamily), static_cast<wxFontStyle>(fontstyle), static_cast<wxFontWeight>(fontweight), is_underlined != 0, wxString(fontname)));
				objects[tmp] = new ObjectStructure(this, tmp, wxTypes::StaticLine);
			}
			if (str_type == "slider")
			{
				uint8_t fg_colors[3], bg_colors[3];
				sscanf(child->GetAttribute("pos").c_str(), "%d,%d", &pos.x, &pos.y);
				sscanf(child->GetAttribute("size").c_str(), "%d,%d", &size.x, &size.y);
				sscanf(child->GetAttribute("min_size").c_str(), "%d,%d", &min_size.x, &min_size.y);
				sscanf(child->GetAttribute("max_size").c_str(), "%d,%d", &max_size.x, &max_size.y);
				sscanf(child->GetAttribute("fg_color").c_str(), "%hhd,%hhd,%hhd", &fg_colors[0], &fg_colors[1], &fg_colors[2]);
				sscanf(child->GetAttribute("bg_color").c_str(), "%hhd,%hhd,%hhd", &bg_colors[0], &bg_colors[1], &bg_colors[2]);
				sscanf(child->GetAttribute("font").c_str(), "%d,%d,%d,%d,%d,%[^\n]s", &fontsize, &fontfamily, &fontstyle, &fontweight, &is_underlined, fontname);
				wxSlider* tmp = new wxSlider(this, wxID_ANY, wxAtoi(child->GetAttribute("value")), wxAtoi(child->GetAttribute("min")),
					wxAtoi(child->GetAttribute("max")), pos, size, wxAtoi(child->GetAttribute("flags")));
				tmp->SetToolTip(child->GetAttribute("tooltip"));
				tmp->SetMinSize(min_size);
				tmp->SetMaxSize(max_size);
				tmp->SetForegroundColour(wxColour(fg_colors[0], fg_colors[1], fg_colors[2]));
				tmp->SetBackgroundColour(wxColour(bg_colors[0], bg_colors[1], bg_colors[2]));
				tmp->SetFont(wxFont(fontsize, static_cast<wxFontFamily>(fontfamily), static_cast<wxFontStyle>(fontstyle), static_cast<wxFontWeight>(fontweight), is_underlined != 0, wxString(fontname)));
				objects[tmp] = new ObjectStructure(this, tmp, wxTypes::Slider);
			}
			if (str_type == "gauge")
			{
				uint8_t fg_colors[3], bg_colors[3];
				sscanf(child->GetAttribute("pos").c_str(), "%d,%d", &pos.x, &pos.y);
				sscanf(child->GetAttribute("size").c_str(), "%d,%d", &size.x, &size.y);
				sscanf(child->GetAttribute("min_size").c_str(), "%d,%d", &min_size.x, &min_size.y);
				sscanf(child->GetAttribute("max_size").c_str(), "%d,%d", &max_size.x, &max_size.y);
				sscanf(child->GetAttribute("fg_color").c_str(), "%hhd,%hhd,%hhd", &fg_colors[0], &fg_colors[1], &fg_colors[2]);
				sscanf(child->GetAttribute("bg_color").c_str(), "%hhd,%hhd,%hhd", &bg_colors[0], &bg_colors[1], &bg_colors[2]);
				sscanf(child->GetAttribute("font").c_str(), "%d,%d,%d,%d,%d,%[^\n]s", &fontsize, &fontfamily, &fontstyle, &fontweight, &is_underlined, fontname);
				wxGauge* tmp = new wxGauge(this, wxID_ANY, wxAtoi(child->GetAttribute("max")), pos, size, wxAtoi(child->GetAttribute("flags")));
				tmp->SetValue(wxAtoi(child->GetAttribute("value")));
				tmp->SetToolTip(child->GetAttribute("tooltip"));
				tmp->SetMinSize(min_size);
				tmp->SetMaxSize(max_size);
				tmp->SetForegroundColour(wxColour(fg_colors[0], fg_colors[1], fg_colors[2]));
				tmp->SetBackgroundColour(wxColour(bg_colors[0], bg_colors[1], bg_colors[2]));
				tmp->SetFont(wxFont(fontsize, static_cast<wxFontFamily>(fontfamily), static_cast<wxFontStyle>(fontstyle), static_cast<wxFontWeight>(fontweight), is_underlined != 0, wxString(fontname)));
				objects[tmp] = new ObjectStructure(this, tmp, wxTypes::Gauge);
			}
			if (str_type == "spincontrol")
			{
				uint8_t fg_colors[3], bg_colors[3];
				sscanf(child->GetAttribute("pos").c_str(), "%d,%d", &pos.x, &pos.y);
				sscanf(child->GetAttribute("size").c_str(), "%d,%d", &size.x, &size.y);
				sscanf(child->GetAttribute("min_size").c_str(), "%d,%d", &min_size.x, &min_size.y);
				sscanf(child->GetAttribute("max_size").c_str(), "%d,%d", &max_size.x, &max_size.y);
				sscanf(child->GetAttribute("fg_color").c_str(), "%hhd,%hhd,%hhd", &fg_colors[0], &fg_colors[1], &fg_colors[2]);
				sscanf(child->GetAttribute("bg_color").c_str(), "%hhd,%hhd,%hhd", &bg_colors[0], &bg_colors[1], &bg_colors[2]);
				sscanf(child->GetAttribute("font").c_str(), "%d,%d,%d,%d,%d,%[^\n]s", &fontsize, &fontfamily, &fontstyle, &fontweight, &is_underlined, fontname);
				wxSpinCtrl* tmp = new wxSpinCtrl(this, wxID_ANY, child->GetAttribute("label"), pos, size, wxAtoi(child->GetAttribute("flags")),
					wxAtoi(child->GetAttribute("min")), wxAtoi(child->GetAttribute("max")), wxAtoi(child->GetAttribute("value")));
				tmp->SetToolTip(child->GetAttribute("tooltip"));
				tmp->SetMinSize(min_size);
				tmp->SetMaxSize(max_size);
				tmp->SetForegroundColour(wxColour(fg_colors[0], fg_colors[1], fg_colors[2]));
				tmp->SetBackgroundColour(wxColour(bg_colors[0], bg_colors[1], bg_colors[2]));
				tmp->SetFont(wxFont(fontsize, static_cast<wxFontFamily>(fontfamily), static_cast<wxFontStyle>(fontstyle), static_cast<wxFontWeight>(fontweight), is_underlined != 0, wxString(fontname)));
				objects[tmp] = new ObjectStructure(this, tmp, wxTypes::SpinControl);
			}
			if (str_type == "spincontroldouble")
			{
				uint8_t fg_colors[3], bg_colors[3];
				sscanf(child->GetAttribute("pos").c_str(), "%d,%d", &pos.x, &pos.y);
				sscanf(child->GetAttribute("size").c_str(), "%d,%d", &size.x, &size.y);
				sscanf(child->GetAttribute("min_size").c_str(), "%d,%d", &min_size.x, &min_size.y);
				sscanf(child->GetAttribute("max_size").c_str(), "%d,%d", &max_size.x, &max_size.y);
				sscanf(child->GetAttribute("fg_color").c_str(), "%hhd,%hhd,%hhd", &fg_colors[0], &fg_colors[1], &fg_colors[2]);
				sscanf(child->GetAttribute("bg_color").c_str(), "%hhd,%hhd,%hhd", &bg_colors[0], &bg_colors[1], &bg_colors[2]);
				sscanf(child->GetAttribute("font").c_str(), "%d,%d,%d,%d,%d,%[^\n]s", &fontsize, &fontfamily, &fontstyle, &fontweight, &is_underlined, fontname);
				wxSpinCtrlDouble* tmp = new wxSpinCtrlDouble(this, wxID_ANY, child->GetAttribute("label"), pos, size, wxAtoi(child->GetAttribute("flags")),
					wxAtoi(child->GetAttribute("min")), wxAtoi(child->GetAttribute("max")), wxAtoi(child->GetAttribute("value")), wxAtoi(child->GetAttribute("inc")));
				tmp->SetToolTip(child->GetAttribute("tooltip"));
				tmp->SetMinSize(min_size);
				tmp->SetMaxSize(max_size);
				tmp->SetForegroundColour(wxColour(fg_colors[0], fg_colors[1], fg_colors[2]));
				tmp->SetBackgroundColour(wxColour(bg_colors[0], bg_colors[1], bg_colors[2]));
				tmp->SetFont(wxFont(fontsize, static_cast<wxFontFamily>(fontfamily), static_cast<wxFontStyle>(fontstyle), static_cast<wxFontWeight>(fontweight), is_underlined != 0, wxString(fontname)));
				objects[tmp] = new ObjectStructure(this, tmp, wxTypes::SpinCtrlDouble);
			}
			else if (str_type == "textcontrol")
			{
				uint8_t fg_colors[3], bg_colors[3];
				sscanf(child->GetAttribute("pos").c_str(), "%d,%d", &pos.x, &pos.y);
				sscanf(child->GetAttribute("size").c_str(), "%d,%d", &size.x, &size.y);
				sscanf(child->GetAttribute("min_size").c_str(), "%d,%d", &min_size.x, &min_size.y);
				sscanf(child->GetAttribute("max_size").c_str(), "%d,%d", &max_size.x, &max_size.y);
				sscanf(child->GetAttribute("fg_color").c_str(), "%hhd,%hhd,%hhd", &fg_colors[0], &fg_colors[1], &fg_colors[2]);
				sscanf(child->GetAttribute("bg_color").c_str(), "%hhd,%hhd,%hhd", &bg_colors[0], &bg_colors[1], &bg_colors[2]);
				sscanf(child->GetAttribute("font").c_str(), "%d,%d,%d,%d,%d,%[^\n]s", &fontsize, &fontfamily, &fontstyle, &fontweight, &is_underlined, fontname);
				wxTextCtrl* tmp = new wxTextCtrl(this, wxID_ANY, child->GetAttribute("label"), pos, size, wxAtoi(child->GetAttribute("flags")));
				tmp->SetToolTip(child->GetAttribute("tooltip"));
				tmp->SetMinSize(min_size);
				tmp->SetMaxSize(max_size);
				tmp->SetForegroundColour(wxColour(fg_colors[0], fg_colors[1], fg_colors[2]));
				tmp->SetBackgroundColour(wxColour(bg_colors[0], bg_colors[1], bg_colors[2]));
				tmp->SetFont(wxFont(fontsize, static_cast<wxFontFamily>(fontfamily), static_cast<wxFontStyle>(fontstyle), static_cast<wxFontWeight>(fontweight), is_underlined != 0, wxString(fontname)));
				objects[tmp] = new ObjectStructure(this, tmp, wxTypes::TextControl);
			}
			else if (str_type == "togglebutton")
			{
				uint8_t fg_colors[3], bg_colors[3];
				sscanf(child->GetAttribute("pos").c_str(), "%d,%d", &pos.x, &pos.y);
				sscanf(child->GetAttribute("size").c_str(), "%d,%d", &size.x, &size.y);
				sscanf(child->GetAttribute("min_size").c_str(), "%d,%d", &min_size.x, &min_size.y);
				sscanf(child->GetAttribute("max_size").c_str(), "%d,%d", &max_size.x, &max_size.y);
				sscanf(child->GetAttribute("fg_color").c_str(), "%hhd,%hhd,%hhd", &fg_colors[0], &fg_colors[1], &fg_colors[2]);
				sscanf(child->GetAttribute("bg_color").c_str(), "%hhd,%hhd,%hhd", &bg_colors[0], &bg_colors[1], &bg_colors[2]);
				sscanf(child->GetAttribute("font").c_str(), "%d,%d,%d,%d,%d,%[^\n]s", &fontsize, &fontfamily, &fontstyle, &fontweight, &is_underlined, fontname);
				wxToggleButton* tmp = new wxToggleButton(this, wxID_ANY, child->GetAttribute("label"), pos, size, wxAtoi(child->GetAttribute("flags")));
				tmp->SetToolTip(child->GetAttribute("tooltip"));
				tmp->SetMinSize(min_size);
				tmp->SetMaxSize(max_size);
				tmp->SetForegroundColour(wxColour(fg_colors[0], fg_colors[1], fg_colors[2]));
				tmp->SetBackgroundColour(wxColour(bg_colors[0], bg_colors[1], bg_colors[2]));
				tmp->SetFont(wxFont(fontsize, static_cast<wxFontFamily>(fontfamily), static_cast<wxFontStyle>(fontstyle), static_cast<wxFontWeight>(fontweight), is_underlined != 0, wxString(fontname)));
				objects[tmp] = new ObjectStructure(this, tmp, wxTypes::ToggleButton);
			}
			else if (str_type == "statictext")
			{
				uint8_t fg_colors[3], bg_colors[3];
				sscanf(child->GetAttribute("pos").c_str(), "%d,%d", &pos.x, &pos.y);
				sscanf(child->GetAttribute("size").c_str(), "%d,%d", &size.x, &size.y);
				sscanf(child->GetAttribute("min_size").c_str(), "%d,%d", &min_size.x, &min_size.y);
				sscanf(child->GetAttribute("max_size").c_str(), "%d,%d", &max_size.x, &max_size.y);
				sscanf(child->GetAttribute("fg_color").c_str(), "%hhd,%hhd,%hhd", &fg_colors[0], &fg_colors[1], &fg_colors[2]);
				sscanf(child->GetAttribute("bg_color").c_str(), "%hhd,%hhd,%hhd", &bg_colors[0], &bg_colors[1], &bg_colors[2]);
				sscanf(child->GetAttribute("font").c_str(), "%d,%d,%d,%d,%d,%[^\n]s", &fontsize, &fontfamily, &fontstyle, &fontweight, &is_underlined, fontname);
				wxStaticText* tmp = new wxStaticText(this, wxID_ANY, child->GetAttribute("label"), pos, size, wxAtoi(child->GetAttribute("flags")));
				tmp->SetToolTip(child->GetAttribute("tooltip"));
				tmp->SetMinSize(min_size);
				tmp->SetMaxSize(max_size);
				tmp->SetForegroundColour(wxColour(fg_colors[0], fg_colors[1], fg_colors[2]));
				tmp->SetBackgroundColour(wxColour(bg_colors[0], bg_colors[1], bg_colors[2]));
				tmp->SetFont(wxFont(fontsize, static_cast<wxFontFamily>(fontfamily), static_cast<wxFontStyle>(fontstyle), static_cast<wxFontWeight>(fontweight), is_underlined != 0, wxString(fontname)));
				objects[tmp] = new ObjectStructure(this, tmp, wxTypes::Text);
			}
		}
		child = child->GetNext();
	}

}
