#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

#SingleInstance, Force

F19::
SendRaw, <> ; Sends <>
return

F14::
Browser = "C:\Program Files (x86)\Google\Chrome\Application\chrome.exe"

IfWinExist ahk_exe chrome.exe
{
    WinActivate, ahk_exe chrome.exe
    SendInput, ^t
}
else
    ;WinGet, chromePID, PID, ahk_exe chrome.exe
    Run %Browser%

return

F15::
Atom = "C:\Users\HaoHao\AppData\Local\atom\atom.exe"

Run %Atom%

return
