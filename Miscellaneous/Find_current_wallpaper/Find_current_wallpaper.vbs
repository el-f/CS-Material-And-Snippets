' Launches find_current_wallpaper.ps1 script

Set WshShell = CreateObject("WScript.Shell")
WshShell.Run "powershell.exe -nologo -ExecutionPolicy Bypass -command Find_current_wallpaper.ps1",0
Set WshShell = Nothing
