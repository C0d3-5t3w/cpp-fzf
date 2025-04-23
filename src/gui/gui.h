#ifndef GUI_H
#define GUI_H

#include "../ripgrep/ripgrep.h"
#include <wx/wx.h> 
#include <string>
#include <vector>

class wxTextCtrl;
class wxButton;
class wxListBox; 

class Gui : public wxFrame { 

public:
    Gui(const wxString& title); 

    void OnSearchButtonClicked(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event); 

private:
    wxTextCtrl* searchPatternInputCtrl;
    wxTextCtrl* searchPathInputCtrl;
    wxButton* searchButton;
    wxTextCtrl* searchResultsOutputCtrl; 

    Ripgrep ripgrep_backend;

    DECLARE_EVENT_TABLE()

    void PerformSearchAndUpdateResults(); 
};

enum {
    ID_SearchButton = wxID_HIGHEST + 1 
};


#endif 