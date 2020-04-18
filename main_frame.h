#include <wx/wx.h>
#include <wx/slider.h>
#include <wx/artprov.h>
#include <wx/spinctrl.h>
#include <wx/filepicker.h>
#include <wx/aui/aui.h>
#include <wx/button.h>
#include <wx/combobox.h>
#include <wx/choice.h>
#include <wx/statline.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/aui/aui.h>
#include <wx/stc/stc.h>
#include <wx/tglbtn.h>
#include <wx/srchctrl.h>
#include <wx/clrpicker.h>
#include <wx/fontpicker.h>
#include <wx/filepicker.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/timectrl.h>
#include <wx/calctrl.h>
#include <wx/treectrl.h>

enum class wxTypes : int
{
	Button,
	ComboBox,
	Choise,
	ListBox,
	CheckBox,
	RadioButton,
	StaticLine,
	Slider,
	Gauge,
	Text,
	SpinControl,
	SpinCtrlDouble,
	TextControl,
	ToggleButton,
	SearchCtrl,
	ColorPicker,
	FontPicker,
	FilePicker,
	DirPicker,
	DatePicker,
	TimePicker,
	CalendarCtrl,
	GenericDirCtrl,
	SpinButton,
	Maximum,
	Invalid = 0xFF,
};
template <class T> wxString GetNameFromEnum(T to_get);

class ObjectStructure;
class MyPanel : public wxPanel
{
public:
	MyPanel(wxFrame* parent);
	wxListBox* m_Log = nullptr;
	wxSpinCtrlDouble* m_wxSpinCtrlDouble = nullptr;
	wxSearchCtrl* m_wxSearchCtrl = nullptr;
	wxColourPickerCtrl* m_wxColourPickerCtrl = nullptr;
	wxFontPickerCtrl* m_wxFontPickerCtrl = nullptr;
	wxFilePickerCtrl* m_wxFilePickerCtrl = nullptr;
	wxDirPickerCtrl* m_wxDirPickerCtrl = nullptr;
	wxDatePickerCtrl* m_wxDatePickerCtrl = nullptr;
	wxTimePickerCtrl* m_wxTimePickerCtrl = nullptr;
	wxCalendarCtrl* m_wxCalendarCtrl = nullptr;
	void OnClick(wxMouseEvent& event);
	void* m_SelectedWidget = nullptr;
	wxSpinCtrl* m_wxSpinCtrl = nullptr;
	int m_speed = 1;
	wxTreeCtrl* m_TreeCtrl;
	wxTreeItemId m_RootItem;

private:
	wxButton* m_wxButton = nullptr;
	wxComboBox* m_wxComboBox = nullptr;
	wxChoice* m_wxChoice = nullptr;
	wxListBox* m_wxListBox = nullptr;
	wxCheckBox* m_wxCheckBox = nullptr;
	wxRadioBox* m_wxRadioBox = nullptr;
	wxRadioButton* m_wxRadioButton = nullptr;
	wxStaticLine* m_wxStaticLine = nullptr;
	wxSlider* m_wxSlider = nullptr;
	wxGauge* m_wxGauge = nullptr;
	wxStaticText* m_wxStaticText = nullptr;
	wxTextCtrl* m_wxTextCtrl = nullptr;
	wxToggleButton* m_wxToggleButton = nullptr;

	void OnKeyDown(wxKeyEvent& event);
	void OnMouseMotion(wxMouseEvent& event);
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseEnter(wxMouseEvent& event);
	void OnMouseLeave(wxMouseEvent& event);
	void OnPropertyGridChange(wxPropertyGridEvent& event);
	void MarkSelectedItem(void);
	void OnPaint(wxPaintEvent& event);
	void OnListCtrlSelChanged(wxTreeEvent& event);
	void LoadFromXml(wxString xml_path);
	template <class T> void SetPos(void* ptr, wxPoint& pos);
	ObjectStructure* FindwxText(void* object_to_find = nullptr);

	wxDECLARE_EVENT_TABLE();
};


class ObjectStructure
{
public:
	wxTypes type;
	int id; /**Item ID */
	wxString name; /**< Item name */
	uint8_t fg_color_changed;
	uint8_t bg_color_changed;
	wxTreeItemId item_id;
	ObjectStructure(MyPanel* p, void* widget, wxTypes _type, wxString _name = wxT(" ")) :
		type(_type), name(std::move(name))
	{
		extern uint16_t wx_list[];
		extern const char* type_names[12];
		id = wx_list[static_cast<int>(_type)]++;
		name = wxString::Format("%s_%d", GetNameFromEnum<wxTypes>(type), id);
		fg_color_changed = bg_color_changed = 0;
		p->m_SelectedWidget = widget;
		item_id = p->m_TreeCtrl->AppendItem(p->m_RootItem, name);
		p->m_TreeCtrl->ExpandAll();
		((wxButton*)(widget))->Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, p);
	}
	ObjectStructure(wxTypes _type, wxString _name = wxT(" ")) :
		type(_type), name(std::move(name))
	{
		extern uint16_t wx_list[];
		extern const char* type_names[12];
		id = wx_list[static_cast<int>(_type)]++;
		name = wxString::Format("%s_%d", GetNameFromEnum<wxTypes>(type), id);
		fg_color_changed = bg_color_changed = 0;
	}
};


class CppPanel : public wxPanel
{
public:
	CppPanel(wxFrame* parent);
	wxStyledTextCtrl* m_StyledTextCtrl = nullptr;

private:
};


class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title);
	~MyFrame()
	{
		// deinitialize the frame manager
		m_mgr.UnInit();
	}

	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnHelp(wxCommandEvent& event);
	void Changeing(wxAuiNotebookEvent& event);
	void OnMenuItemSelected(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
	MyPanel* panel;
private:
	CppPanel* cpp_panel;
	wxAuiManager m_mgr;
};