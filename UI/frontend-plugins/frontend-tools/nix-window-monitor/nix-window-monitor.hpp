#pragma once

#include <vector>
#include <string>

using namespace std;

class NixWindowMonitor {
public:
	virtual void currentWindowTitle(const string &title);
	virtual void windowTitles(const vector<string> &titles);
};


// CreateNixWindowMonitor
//
// Factory method to create window monitor in linux
//
// Should select based on environment or trials which implementation
// of NixWindowMonitor that can be called
//
static NixWindowMonitor* CreateNixWindowMonitor();
