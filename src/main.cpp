#include <Windows.h>
#include <shobjidl.h>

int main()
{
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
			hr = ::CoAllowSetForegroundWindow(
				pApplicationActivationManager, 
				nullptr);
			if (SUCCEEDED(hr))
			{
				DWORD dwProcessId = 0;
				// Launch the app
				hr = pApplicationActivationManager->ActivateApplication(
					L"dotPDNLLC.paint.net_h55e3w7q8jbva!dotPDNLLC.paint.net",
					nullptr,
					AO_NONE,
					&dwProcessId);
			}

			pApplicationActivationManager->Release();
		}

		::CoUninitialize();
	}

    return hr;
}
