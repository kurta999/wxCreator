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

constexpr int DEFAULT_WAIT_TIME = 400;

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
	TextControl,
	Invalid = 0xFF,
};

class MyPanel : public wxPanel
{
public:
	MyPanel(wxFrame* parent);
	wxListBox* m_Log = nullptr;

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
	wxSpinCtrl* m_wxSpinCtrl = nullptr;
	wxStaticText* m_wxStaticText = nullptr;
	wxTextCtrl* m_wxTextCtrl = nullptr;
	void* m_SelectedWidget = nullptr;

	void OnKeyDown(wxKeyEvent& event);
	void OnMouseMotion(wxMouseEvent& event);
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseEnter(wxMouseEvent& event);
	void OnMouseLeave(wxMouseEvent& event);
	void OnPropertyGridChange(wxPropertyGridEvent& event);
	void OnClick(wxMouseEvent& event);
	void OnDoubleClick(wxMouseEvent& event);
	void OnMiddleClick(wxMouseEvent& event);
	template <class T> void SetPos(void* ptr, wxPoint& pos);
	wxTypes FindwxText(void* object_to_find = nullptr);
	wxDECLARE_EVENT_TABLE();
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
	wxDECLARE_EVENT_TABLE();
	MyPanel* panel;
private:
	CppPanel* cpp_panel;
	wxAuiManager m_mgr;
};