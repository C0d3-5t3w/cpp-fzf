#include <wx/wx.h>
#include "gui/gui.h" 

class MyApp : public wxApp {
public:
    virtual bool OnInit(); 
};

wxIMPLEMENT_APP(MyApp); 

bool MyApp::OnInit() {
    if (!wxApp::OnInit())
        return false;

    Gui *frame = new Gui(wxT("fzf"));
    frame->Show(true);

    return true; 
}
