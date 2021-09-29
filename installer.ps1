try {
    remove-item alias:ls -ErrorAction Stop
    remove-item alias:pwd -ErrorAction Stop
    remove-item alias:cat -ErrorAction Stop
} catch [System.Management.Automation.ItemNotFoundException] {
    "Some aliases are already removed"
} catch { "Some unknown error occured" }

Copy-Item .\ls\ls.exe -Destination 'C:\Windows\System32\'
Copy-Item .\pwd\pwd.exe -Destination 'C:\Windows\System32\'
Copy-Item .\cat\cat.exe -Destination 'C:\Windows\System32\'