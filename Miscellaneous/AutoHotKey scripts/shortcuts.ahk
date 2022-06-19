#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

; keys:
; + shift
; ^ ctrl
; ! alt

; disable shift+delete perma deleting files
+Delete::
KeyWait Shift
Send {Delete}

; Open Downloads folder
^!d::Run "D:\Downloads" ; ctrl+alt+d
return

^!e::Run "E:\Elfein" ; ctrl+alt+e
return

^!f::Run "C:\Foobar2000\Foobar2000.exe" ; ctrl+alt+f
return

;^!c::Run www.google.com ; ctrl+alt+c
;return

^!v::Run "E:\Video" ; ctrl+alt+v
return

;^!g::Run "C:\Users\Elazar\Google Drive" ; ctrl+alt+g
;return

^!y::Run "I:\Elfein_Archive\Programs\RockboxUtility-v1.3.1" ; ctrl+alt+y
return

;windows terminal
^!t::Run wt
return

;Cmder
;^!t::Run "E:\Elfein\Programs\cmder_mini\Cmder.exe"
;return

;mingw32-make.exe macro
;^!m::Send mingw32-make.exe
;return
