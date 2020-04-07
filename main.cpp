#include "main.h"
#include "main_frame.h"
#include <wx/wxprec.h>
#include <wx/gbsizer.h>
#include <wx/grid.h>
#include <Windows.h>
#include <string>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame(wxT("wxCreator"));
    frame->Show(true);   
    return true;
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{

}