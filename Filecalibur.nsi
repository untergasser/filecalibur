!define VERSION "0.7.0"
!define NAME "Filecalibur"
!define UNINSTREG "Software\Microsoft\Windows\CurrentVersion\Uninstall\Filecalibur"
!define QTPATH "C:\Qt\5.5\mingw492_32\bin\"

!include "MUI2.nsh"
!include "logiclib.nsh"
!include "WinVer.nsh"

Name "${NAME} ${VERSION}"
OutFile "Filecalibur.exe"
InstallDir "$PROGRAMFILES32\Filecalibur"
InstallDirRegKey HKLM "Software\Filecalibur" "Install_Dir"
RequestExecutionLevel admin
!define MUI_ABORTWARNING
!define MUI_ICON "src\files\Logo_128.ico"

; Show the dialogs
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES  
!insertmacro MUI_LANGUAGE "English"

Function .onInit
	${IfNot} ${AtLeastWin7}
		MessageBox MB_OK "At least Windows 7 is required."
		Quit
	${EndIf}
FunctionEnd

; Copy the files
Section "Filecalibur" Filecalibur
    SetOutPath "$INSTDIR"
    File ${QTPATH}icudt54.dll
    File ${QTPATH}icuin54.dll
    File ${QTPATH}icuuc54.dll
    File ${QTPATH}libgcc_s_dw2-1.dll
    File ${QTPATH}libstdc++-6.dll
    File ${QTPATH}libwinpthread-1.dll
    File ${QTPATH}Qt5Core.dll
    File ${QTPATH}Qt5Gui.dll
    File ${QTPATH}Qt5Network.dll
    File ${QTPATH}Qt5Widgets.dll

    File build-Release\release\Filecalibur.exe
    File src\files\Logo_128.ico
    File src\files\license.txt

	SetOutPath "$INSTDIR\platforms"
    File ${QTPATH}..\plugins\platforms\qminimal.dll
    File ${QTPATH}..\plugins\platforms\qoffscreen.dll
    File ${QTPATH}..\plugins\platforms\qwindows.dll
	
	SetOutPath "$INSTDIR\hashdeep"
    File progs\hashdeep\CHANGES.txt
    File progs\hashdeep\COPYING.txt
    File progs\hashdeep\FILEFORMAT.txt
    File progs\hashdeep\hashdeep.exe
    File progs\hashdeep\HASHDEEP.txt
    File progs\hashdeep\hashdeep64.exe
    File progs\hashdeep\md5deep.exe
    File progs\hashdeep\MD5DEEP.txt
    File progs\hashdeep\md5deep64.exe
    File progs\hashdeep\sha1deep.exe
    File progs\hashdeep\sha1deep64.exe
    File progs\hashdeep\sha256deep.exe
    File progs\hashdeep\sha256deep64.exe
    File progs\hashdeep\tigerdeep.exe
    File progs\hashdeep\tigerdeep64.exe
    File progs\hashdeep\whirlpooldeep.exe
    File progs\hashdeep\whirlpooldeep64.exe

	SetOutPath "$INSTDIR\rsync"
    File progs\rsync\cygwin1.dll
    File progs\rsync\cyggcc_s-1.dll
    File progs\rsync\cygiconv-2.dll
    File progs\rsync\license.txt
    File progs\rsync\NEWS.txt
    File progs\rsync\rsync.exe
    File progs\rsync\rsync.html

	SetOutPath "$INSTDIR\winmerge"
    File progs\winmerge\WinMerge-2.14.0-Setup.exe

	; Start menu link
	createDirectory "$SMPROGRAMS\Filecalibur"
	createShortCut "$SMPROGRAMS\Filecalibur\Filecalibur.lnk" "$INSTDIR\Filecalibur.exe" "" "$INSTDIR\Logo_128.ico"
	createShortCut "$DESKTOP\Filecalibur.lnk" "$INSTDIR\Filecalibur.exe" "" "$INSTDIR\Logo_128.ico"
  
    ; Save installation path in registry
    WriteRegStr HKLM SOFTWARE\Filecalibur "Install_Dir" "$INSTDIR"
  
    ; This is required for correct information in the uninstal page
    WriteRegStr HKLM "${UNINSTREG}" "DisplayName" "${NAME}"
	WriteRegStr HKLM "${UNINSTREG}" "DisplayVersion" "${VERSION}"
    WriteRegStr HKLM "${UNINSTREG}" "Publisher" "A. Untergasser"
    WriteRegStr HKLM "${UNINSTREG}" "URLInfoAbout" "http://sourceforge.net/projects/filecalibur/"
    WriteRegStr HKLM "${UNINSTREG}" "DisplayIcon" '"$INSTDIR\Logo_128.ico"'
    WriteRegStr HKLM "${UNINSTREG}" "UninstallString" '"$INSTDIR\uninstall.exe"'
    WriteRegDWORD HKLM "${UNINSTREG}" "NoModify" 1
    WriteRegDWORD HKLM "${UNINSTREG}" "NoRepair" 1
    WriteUninstaller "uninstall.exe"
	
	MessageBox MB_YESNO "Install WinMerge?" /SD IDYES IDNO endInstWinMerge
    ExecWait "$INSTDIR\winmerge\WinMerge-2.14.0-Setup.exe"
    Goto endInstWinMerge
    endInstWinMerge:
SectionEnd

; Remove all files
Section "Uninstall"
	; Get install directory from registry
	ReadRegStr $INSTDIR HKLM SOFTWARE\Filecalibur "Install_Dir"
	
    ; Clean Registry
    DeleteRegKey HKLM "${UNINSTREG}"
    DeleteRegKey HKLM SOFTWARE\Filecalibur
  
    ; Delete all files
	Delete "$DESKTOP\Filecalibur.lnk"
	Delete "$SMPROGRAMS\Filecalibur\Filecalibur.lnk"

    Delete "$INSTDIR\hashdeep\CHANGES.txt"
    Delete "$INSTDIR\hashdeep\COPYING.txt"
    Delete "$INSTDIR\hashdeep\FILEFORMAT.txt"
    Delete "$INSTDIR\hashdeep\hashdeep.exe"
    Delete "$INSTDIR\hashdeep\HASHDEEP.txt"
    Delete "$INSTDIR\hashdeep\hashdeep64.exe"
    Delete "$INSTDIR\hashdeep\md5deep.exe"
    Delete "$INSTDIR\hashdeep\MD5DEEP.txt"
    Delete "$INSTDIR\hashdeep\md5deep64.exe"
    Delete "$INSTDIR\hashdeep\sha1deep.exe"
    Delete "$INSTDIR\hashdeep\sha1deep64.exe"
    Delete "$INSTDIR\hashdeep\sha256deep.exe"
    Delete "$INSTDIR\hashdeep\sha256deep64.exe"
    Delete "$INSTDIR\hashdeep\tigerdeep.exe"
    Delete "$INSTDIR\hashdeep\tigerdeep64.exe"
    Delete "$INSTDIR\hashdeep\whirlpooldeep.exe"
    Delete "$INSTDIR\hashdeep\whirlpooldeep64.exe"

    Delete "$INSTDIR\rsync\cygwin1.dll"
    Delete "$INSTDIR\rsync\cyggcc_s-1.dll"
    Delete "$INSTDIR\rsync\cygiconv-2.dll"
    Delete "$INSTDIR\rsync\license.txt"
    Delete "$INSTDIR\rsync\NEWS.txt"
    Delete "$INSTDIR\rsync\rsync.exe"
    Delete "$INSTDIR\rsync\rsync.html"

    Delete "$INSTDIR\winmerge\WinMerge-2.14.0-Setup.exe"
	
    Delete "$INSTDIR\platforms\qminimal.dll"
    Delete "$INSTDIR\platforms\qoffscreen.dll"
    Delete "$INSTDIR\platforms\qwindows.dll"

    Delete "$INSTDIR\icudt52.dll"
    Delete "$INSTDIR\icuin52.dll"
    Delete "$INSTDIR\icuuc52.dll"
    Delete "$INSTDIR\libgcc_s_dw2-1.dll"
    Delete "$INSTDIR\libstdc++-6.dll"
    Delete "$INSTDIR\libwinpthread-1.dll"
    Delete "$INSTDIR\Qt5Core.dll"
    Delete "$INSTDIR\Qt5Gui.dll"
    Delete "$INSTDIR\Qt5Network.dll"
    Delete "$INSTDIR\Qt5Widgets.dll"

    Delete "$INSTDIR\Filecalibur.exe"
    Delete "$INSTDIR\Logo_128.ico"
    Delete "$INSTDIR\license.txt"
    Delete "$INSTDIR\uninstall.exe"

    ; Remove Directories
	RMDir "$INSTDIR\hashdeep"
	RMDir "$INSTDIR\rsync"
	RMDir "$INSTDIR\winmerge"
    RMDir "$INSTDIR\platforms"
    RMDir "$INSTDIR"
	RMDir "$SMPROGRAMS\Filecalibur"
	
	MessageBox MB_YESNO "Uninstall WinMerge?" /SD IDYES IDNO endUnInstWinMerge
    ExecWait "$INSTDIR\..\WinMerge\unins000.exe"
    Goto endUnInstWinMerge
    endUnInstWinMerge:
SectionEnd
