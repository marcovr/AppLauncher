#include <Windows.h>
#include <shobjidl.h>
#include <shlwapi.h>
#include <comdef.h>
#include <string>
#include <sstream>

int main()
{
	int argc = 0;
	LPWSTR cmdLine = GetCommandLineW();
    LPWSTR* argv = CommandLineToArgvW(cmdLine, &argc);

	if (argc == 1)
	{
		MessageBoxW(
			nullptr,
			L"Please pass an App Id as first argument.\nFor example: \"dotPDNLLC.paint.net_h55e3w7q8jbva!dotPDNLLC.paint.net\"",
			argv[0],
			MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);

		LocalFree(argv);
		return 1;
	}

	HRESULT hr = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	if (SUCCEEDED(hr))
	{
		IApplicationActivationManager* pApplicationActivationManager = nullptr;
		hr = ::CoCreateInstance(
			CLSID_ApplicationActivationManager,
			nullptr,
			CLSCTX_LOCAL_SERVER,
			IID_IApplicationActivationManager,
			(LPVOID*)&pApplicationActivationManager);

		if (SUCCEEDED(hr))
		{
			// This call ensures that the app is launched as the foreground window
			hr = ::CoAllowSetForegroundWindow(pApplicationActivationManager, nullptr);
			if (SUCCEEDED(hr))
			{
				LPWSTR appId = argv[1];
				LPWSTR args = nullptr;
				DWORD dwProcessId = 0;

				if (argc > 2)
				{
					args = StrStrW(cmdLine, argv[2]);

					// Include quote if present
					if (args != nullptr && args[-1] == '"')
					{
						args--;
					}
				}

				// Launch the app
				hr = pApplicationActivationManager->ActivateApplication(
					appId,
					args,
					AO_NONE,
					&dwProcessId);
			}

			pApplicationActivationManager->Release();
		}

		::CoUninitialize();
	}

	if (!SUCCEEDED(hr))
	{
		std::wstringstream ss;
		ss << L"0x" << std::hex << std::uppercase << hr;

		_com_error err(hr);
		std::wstring msg = std::wstring(err.ErrorMessage());
		std::wstring a = std::wstring(argv[1]);
		std::wstring errorMsg = L"Failed to launch: " + a + L"\n\nError: " + msg + L"\nHRESULT: " + ss.str();

		MessageBoxW(
			nullptr,
			errorMsg.c_str(),
			argv[0],
			MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}

	LocalFree(argv);

    return hr;
}
