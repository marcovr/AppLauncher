# AppLauncher

Allows to launch Windows Store apps without flashing a console or hardcoding executable paths which change with each version.

Usage:
```
applauncher.exe <AppId> [Args...]
applauncher.exe dotPDNLLC.paint.net_h55e3w7q8jbva!dotPDNLLC.paint.net C:\Image.png
```

## Why is this useful?
This allows to set a store app as the default image editor in the registry. Just edit
`Computer\HKEY_CLASSES_ROOT\SystemFileAssociations\image\shell\edit\command` and set its value to e.g. `applauncher.exe dotPDNLLC.paint.net_h55e3w7q8jbva!dotPDNLLC.paint.net "%1"`

There is also a way to do this without the applauncher, but it will flash a command line window: `cmd /c start shell:AppsFolder\dotPDNLLC.paint.net_h55e3w7q8jbva!dotPDNLLC.paint.net "%1"`


## To get the AppId
```pwsh
$installedapps = get-AppxPackage
foreach ($app in $installedapps)
{
    foreach ($id in (Get-AppxPackageManifest $app).package.applications.application.id)
    {
        $app.packagefamilyname + "!" + $id
    }
}
```

## To build
First, install the Visual Studio 2022 build tools (full VS also works). Then just run `build.bat`

## Related links
- https://www.mrlacey.com/2017/01/launch-store-installed-app-from-command.html
- https://mouri.moe/en/2021/11/07/Launch-Windows-Store-App-via-Win32-API/
- https://learn.microsoft.com/de-de/windows-server/administration/windows-commands/start
