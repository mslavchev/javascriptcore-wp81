//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "JavaScriptCore\\JavaScriptCore.h"
#include <string>

using namespace App1;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
	InitializeComponent();

	JavaScriptCoreDemo();
}

void MainPage::JavaScriptCoreDemo()
{
	JSGlobalContextRef ctx = JSGlobalContextCreate(nullptr);

	std::string scriptText("(function(){ return 'Hello ' + 'from ' + 'JavaScriptCore!'; })()");

	JSStringRef script = JSStringCreateWithUTF8CString(scriptText.c_str());
	JSValueRef result = JSEvaluateScript(ctx, script, nullptr, nullptr, 0, nullptr);
	JSStringRelease(script);

	char* buf = nullptr;

	if (result != nullptr)
	{
		JSStringRef str = JSValueToStringCopy(ctx, result, nullptr);
		int len = JSStringGetLength(str) + 1;
		buf = new char[len * sizeof(char)];
		JSStringGetUTF8CString(str, buf, len);
		JSStringRelease(str);
	}

	std::string s(buf);

	if (buf != nullptr)
	{
		std::string resultStr(buf);
		delete[] buf;
	}

	Button^ btn = ref new Button();
	btn->Content = ref new String(std::wstring(s.begin(), s.end()).c_str());
	Window^ wnd = Window::Current;
	wnd->Content = btn;

	JSGlobalContextRelease(ctx);

	ctx = nullptr;
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter

	// TODO: Prepare page for display here.

	// TODO: If your application contains multiple pages, ensure that you are
	// handling the hardware Back button by registering for the
	// Windows::Phone::UI::Input::HardwareButtons.BackPressed event.
	// If you are using the NavigationHelper provided by some templates,
	// this event is handled for you.
}
