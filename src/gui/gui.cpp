#include "gui.h"
#include <wx/sizer.h>   
#include <wx/valtext.h> 
#include <stdexcept>
#include <iostream> 

BEGIN_EVENT_TABLE(Gui, wxFrame)
    EVT_BUTTON(ID_SearchButton, Gui::OnSearchButtonClicked) 
    EVT_MENU(wxID_EXIT, Gui::OnQuit)                     
END_EVENT_TABLE()

Gui::Gui(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) 
{
    wxPanel *panel = new wxPanel(this, wxID_ANY); 
    searchPatternInputCtrl = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    searchPathInputCtrl = new wxTextCtrl(panel, wxID_ANY, wxT("."), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER); 
    searchButton = new wxButton(panel, ID_SearchButton, wxT("Search"));
    searchResultsOutputCtrl = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL); 
    wxBoxSizer *inputSizer = new wxBoxSizer(wxHORIZONTAL); 
    inputSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Pattern:")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    inputSizer->Add(searchPatternInputCtrl, 1, wxEXPAND | wxALL, 5); 
    inputSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Path:")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    inputSizer->Add(searchPathInputCtrl, 1, wxEXPAND | wxALL, 5);    
    inputSizer->Add(searchButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5); 
    topSizer->Add(inputSizer, 0, wxEXPAND | wxALL, 5); 
    topSizer->Add(searchResultsOutputCtrl, 1, wxEXPAND | wxALL, 5); 
    panel->SetSizer(topSizer);
    topSizer->SetSizeHints(this); 
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT); 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, wxT("&File"));
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText(wxT("Ready"));
    searchPatternInputCtrl->Bind(wxEVT_TEXT_ENTER, &Gui::OnSearchButtonClicked, this);
    searchPathInputCtrl->Bind(wxEVT_TEXT_ENTER, &Gui::OnSearchButtonClicked, this);
}

void Gui::OnQuit(wxCommandEvent& event) {
    Close(true); 
}

void Gui::OnSearchButtonClicked(wxCommandEvent& event) {
    PerformSearchAndUpdateResults();
}

void Gui::PerformSearchAndUpdateResults() {
    wxString pattern = searchPatternInputCtrl->GetValue();
    wxString path = searchPathInputCtrl->GetValue();

    if (pattern.IsEmpty()) {
        wxMessageBox(wxT("Search pattern cannot be empty."), wxT("Input Error"), wxOK | wxICON_WARNING, this);
        searchPatternInputCtrl->SetFocus();
        return;
    }
    if (path.IsEmpty()) {
        wxMessageBox(wxT("Search path cannot be empty."), wxT("Input Error"), wxOK | wxICON_WARNING, this);
        searchPathInputCtrl->SetFocus();
        return;
    }

    SetStatusText(wxT("Searching..."));
    searchResultsOutputCtrl->Clear(); 

    try {
        
        std::vector<std::string> results = ripgrep_backend.search(pattern.ToStdString(), path.ToStdString());

        if (results.empty()) {
            searchResultsOutputCtrl->SetValue(wxT("No results found."));
        } else {
            wxString resultsText;
            for (const auto& line : results) {
                resultsText += wxString::FromUTF8(line.c_str()); 
                resultsText += wxT("\n"); 
            }
            searchResultsOutputCtrl->SetValue(resultsText);
        }
        SetStatusText(wxT("Search complete."));

    } catch (const std::exception& e) {
        wxString errorMsg = wxString::Format(wxT("Error executing ripgrep: %s"), wxString::FromUTF8(e.what()));
        searchResultsOutputCtrl->SetValue(errorMsg);
        SetStatusText(wxT("Error occurred."));
        wxLogError(errorMsg); 
    } catch (...) {
        wxString errorMsg = wxT("An unknown error occurred while running ripgrep.");
        searchResultsOutputCtrl->SetValue(errorMsg);
        SetStatusText(wxT("Unknown error occurred."));
        wxLogError(errorMsg);
    }
}
